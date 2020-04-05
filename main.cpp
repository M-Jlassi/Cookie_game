/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: hwalog
 *
 * Created on April 5, 2020, 5:38 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

void must_init ( bool test, const char * description )
{
    if ( test ) return ;
    
    printf ( "Could not initialize %s.\n", description ) ;
    exit ( 1 ) ;
}

typedef struct PLAYER
{
    float x, y ;
    bool is_in_jump ;
    int jump_timer ;
} PLAYER ;

PLAYER player ;

void player_init ()
{
    player.x = 100 ;
    player.y = 150 ;
    player.is_in_jump = false ;
}

unsigned char key [ ALLEGRO_KEY_MAX ] ;

void keyboard_init ()
{
    memset ( key, 0, sizeof ( key ) ) ;
}

#define NB_FRAMES_IN_A_JUMP 30

void jump ( ALLEGRO_TIMER * timer )
{
    
    int time_since_jump_instruction = al_get_timer_count ( timer ) - player .jump_timer ;
    
    if ( player.is_in_jump )
    {
        
        if ( time_since_jump_instruction > NB_FRAMES_IN_A_JUMP )
        {
            player .is_in_jump = false ;
            return ;
        }
        
        // The player is in the first part of the jump

        if ( time_since_jump_instruction <= NB_FRAMES_IN_A_JUMP / 2 )
        {
            player.y -= 5 ;
        }

        // The player is in the second part of the jump

        else
        {
            player.y += 5 ;
        }

        return ;

    }

    if ( key [ ALLEGRO_KEY_SPACE ] )
    {
        if ( player.is_in_jump ) return ;
        
        player.is_in_jump = true ;
        player.jump_timer = al_get_timer_count ( timer ) ;
        
    }
    
}

void gravity ()
{
    int pos_x = 750 ;
    int pos_y = 250 ;
    float dx, dy ;
    
    dx = ( pos_x - player.x ) / 50 ;
    dy = ( pos_y - player.y ) / 50 ;
    
    player.x += dx ;
    player.y += dy ;
}

int main(int argc, char** argv) {
    
    must_init ( al_init (), "allegro" ) ;
    must_init ( al_install_keyboard (), "keyboard" ) ;
    
    ALLEGRO_TIMER * timer = al_create_timer ( 1.0 / 30.0 ) ;
    must_init ( timer, "timer" ) ;
    
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue () ;
    must_init ( event_queue, "event queue" ) ;
    
    ALLEGRO_DISPLAY * display = al_create_display ( 1500, 500 ) ;
    must_init ( display, "display" ) ;
    
    must_init ( al_init_primitives_addon (), "primitives" ) ;

    al_register_event_source ( event_queue, al_get_keyboard_event_source () ) ;
    al_register_event_source ( event_queue, al_get_display_event_source ( display ) ) ;
    al_register_event_source ( event_queue, al_get_timer_event_source ( timer ) ) ;
    
    ALLEGRO_EVENT event ;
    
    al_start_timer ( timer ) ;
    
    int x_triangle = 0 ;
    
    #define KEY_SEEN 1
    #define KEY_RELEASED 2
    
    keyboard_init () ;
    player_init () ;
    
    bool done = false ;
    
    while ( 1 ) 
    {
        
        al_wait_for_event ( event_queue, &event ) ;
        
        switch ( event .type )
        {
            case ALLEGRO_EVENT_TIMER:
                
                if ( key [ ALLEGRO_KEY_LEFT ] )
                    player.x -= 5 ;
                
                if ( key [ ALLEGRO_KEY_RIGHT ] )
                    player.x += 5 ;
                    
                jump ( timer ) ;
                gravity () ;
                
                if ( key [ ALLEGRO_KEY_ESCAPE ] )
                    done = true ;
                
                // Ensures no key is missed between two iterations of ALLEGRO_EVENT_TIMER
                // More info here: https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace%3A-Input#how-it-works
                
                for ( int i = 0 ; i < ALLEGRO_KEY_MAX ; i++ )
                    key [ i ] &= KEY_SEEN ;
                
                break ;
                
            case ALLEGRO_EVENT_KEY_DOWN:
                
                key [ event .keyboard .keycode ] = KEY_SEEN | KEY_RELEASED ;
                break ;
                
            case ALLEGRO_EVENT_KEY_UP:
                
                key [ event .keyboard .keycode ] &= KEY_RELEASED ;
                break ;
                
        }
        
        if ( event .type == ALLEGRO_EVENT_DISPLAY_CLOSE ) break ;
        if ( done ) break ;
        
        al_clear_to_color ( al_map_rgb_f ( 0, 0, 0 ) ) ;
        
        al_draw_filled_triangle (
                player.x,
                player.y,
                player.x - 50, 
                player.y - 100, 
                player.x + 50, 
                player.y - 100,
                al_map_rgb_f ( 1, 1, 1 ) 
        ) ;
        
        al_draw_filled_circle ( 750, 250, 10, al_map_rgb_f ( 1, 1, 1 ) ) ;
        
        al_flip_display () ;
        
    }
    
    al_destroy_display ( display ) ;
    al_destroy_timer ( timer ) ;
    al_destroy_event_queue ( event_queue ) ;
    
    return 0;
}

