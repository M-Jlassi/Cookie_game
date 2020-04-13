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

#include <allegro5/allegro_primitives.h>

#include "player.h"
#include "attracting_element.h"
#include <iostream>

using namespace std;

unsigned char key [ ALLEGRO_KEY_MAX ] ;

void must_init ( bool test, const char * description )
{
    if ( test ) return ;
    
    printf ( "Could not initialize %s.\n", description ) ;
    exit ( 1 ) ;
}



void keyboard_init ()
{
    memset ( key, 0, sizeof ( key ) ) ;
}



std::ostream& operator<<(std::ostream &strm, const Player &player)
{
    string description_of_element = "Player:\n" ;
    description_of_element += "X = " + std::to_string ( player.x ) + "\n";
    description_of_element += "Y = " + std::to_string ( player.y ) + "\n";
    description_of_element += "Is in jump? " + std::to_string ( player.is_in_jump ) + "\n";
    description_of_element += "Jump timer = " + std::to_string ( player.jump_timer ) + "\n";

    return strm << description_of_element << endl ;
}







/*
void elements_init ()
{
    for ( int i = 0 ; i < NUMBER_OF_ELEMENTS ; i++ )
    {
        elements [ i ] .
    }
}
*/

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
    
    #define KEY_SEEN 1
    #define KEY_RELEASED 2

    al_start_timer ( timer ) ;

    keyboard_init () ;
    
    Attracting_element floor ( 175, 800, 1025, 800 ) ;
    Attracting_element right_wall ( 1100, 725, 1100, 0 ) ;
    Attracting_element right_edge ( 1025, 800, 1100, 725 ) ;
    
    Player player ( & floor ) ;
    
    vector<Attracting_element> elements ;
    elements .push_back ( floor ) ;
    elements .push_back ( right_wall ) ;
    //elements .push_back ( right_edge ) ;
    
    
    
    while ( 1 ) 
    {        
        al_wait_for_event ( event_queue, &event ) ;
        
        switch ( event .type )
        {
            case ALLEGRO_EVENT_TIMER:
                
                player .move () ;
                    
                player .gravity ( elements ) ;
                
                player .jump ( timer ) ;
                
                if ( key [ ALLEGRO_KEY_ESCAPE ] )
                    player .done = true ;

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
        if ( player .done ) break ;
        
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
        
        // Left wall
        al_draw_filled_rectangle ( 0, 0, 100, 900,
                al_map_rgb_f ( 0.35, 0.35, 0.35 ) ) ;
        
        // Right wall
        al_draw_filled_rectangle ( 1100, 0, 1200, 900,
                al_map_rgb_f ( 0.35, 0.35, 0.35 ) ) ;
        
        // Floor
        al_draw_filled_rectangle ( 0, 800, 1200, 900,
                al_map_rgb_f ( 0.35, 0.35, 0.35 ) ) ;
        
        // Left arc
        al_draw_arc ( 175, 725, 100, 1.6, 1.6,
                al_map_rgb_f ( 0.35, 0.35, 0.35 ), 50 ) ;
        
        // Right arc
        al_draw_arc ( 1025, 725, 100, 1.6, -1.6,
                al_map_rgb_f ( 0.35, 0.35, 0.35 ), 50 ) ;
        
        // Point
        al_draw_filled_circle ( 1025, 800, 5,
                al_map_rgb_f ( 1, 1, 1 ) ) ;
        
        al_flip_display () ;
        
    }
    
    al_destroy_display ( display ) ;
    al_destroy_timer ( timer ) ;
    al_destroy_event_queue ( event_queue ) ;
    
    return 0;
}

