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

#define NB_FRAMES_IN_A_JUMP 20

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

        if ( time_since_jump_instruction <= NB_FRAMES_IN_A_JUMP )
        {
            player.y -= 10 ;
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

typedef struct ATTRACTING_ELEMENT {
    int x_sup, y_sup ;
    int x_inf, y_inf ;
} ATTRACTING_ELEMENT ;

#define NUMBER_OF_ELEMENTS 5
ATTRACTING_ELEMENT elements [ NUMBER_OF_ELEMENTS ] ;

/*
void elements_init ()
{
    for ( int i = 0 ; i < NUMBER_OF_ELEMENTS ; i++ )
    {
        elements [ i ] .
    }
}
*/

void gravity ( ATTRACTING_ELEMENT element )
{
    float dx, dy ;
    
    if ( player.x > element.x_sup )
    {
        dx = ( element.x_sup - player.x ) / 50 ;
    }
    
    if ( player.x < element.x_inf )
    {
        dx = ( element.x_inf - player.x ) / 50 ;
    }
    
    if ( player.y > element.y_sup )
    {
        dy = ( element.y_sup - player.y ) / 50 ;
    }
    
    if ( player.y < element.y_inf )
    {
        dy = ( element.y_inf - player.y ) / 50 ;
    }
    
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
    
    ALLEGRO_DISPLAY * display = al_create_display ( 1200, 900 ) ;
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
    
    ATTRACTING_ELEMENT element ;
    element .x_inf = 175 ;
    element .y_inf = 800 ;
    element .x_sup = 1025;
    element .y_inf = 800 ;
    
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
                gravity ( element ) ;
                
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
        
        al_draw_filled_rectangle ( 0, 0, 100, 900, al_map_rgb_f ( 0.35, 0.35, 0.35 ) ) ;
        
        al_draw_filled_rectangle ( 1100, 0, 1200, 900, al_map_rgb_f ( 0.35, 0.35, 0.35 ) ) ;
        
        al_draw_filled_rectangle ( 0, 800, 1200, 900, al_map_rgb_f ( 0.35, 0.35, 0.35 ) ) ;
        
        al_draw_arc ( 175, 725, 100, 1.6, 1.6, al_map_rgb_f ( 0.35, 0.35, 0.35 ), 50 ) ;
        
        al_draw_arc ( 1025, 725, 100, 1.6, -1.6, al_map_rgb_f ( 0.35, 0.35, 0.35 ), 50 ) ;
        
        al_draw_filled_circle ( 1025, 800, 5, al_map_rgb_f ( 1, 1, 1 ) ) ;
        
        al_flip_display () ;
        
    }
    
    al_destroy_display ( display ) ;
    al_destroy_timer ( timer ) ;
    al_destroy_event_queue ( event_queue ) ;
    
    return 0;
}

