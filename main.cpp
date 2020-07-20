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


#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "player.h"
#include "attracting_element.h"
#include <iostream>
#include <sstream>

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






int main(int argc, char** argv)
{
    must_init ( al_init (), "allegro" ) ;
    must_init ( al_install_keyboard (), "keyboard" ) ;
    
    ALLEGRO_TIMER * timer = al_create_timer ( 1.0 / 30.0 ) ;
    must_init ( timer, "timer" ) ;
    
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue () ;
    must_init ( event_queue, "event queue" ) ;
    
    ALLEGRO_DISPLAY * display = al_create_display ( 1200, 900 ) ;
    must_init ( display, "display" ) ;
    
    must_init(al_init_image_addon(), "image");
    ALLEGRO_BITMAP* cookie_player = al_load_bitmap("images/cookie_char/cookie_player_35x60.png");
    must_init(cookie_player, "cookie_player");
    
    must_init ( al_init_primitives_addon (), "primitives" ) ;

    al_register_event_source ( event_queue, al_get_keyboard_event_source () ) ;
    al_register_event_source ( event_queue, al_get_display_event_source ( display ) ) ;
    al_register_event_source ( event_queue, al_get_timer_event_source ( timer ) ) ;
    
    ALLEGRO_EVENT event ;
    
    #define KEY_SEEN 1
    #define KEY_RELEASED 2

    al_start_timer ( timer ) ;

    keyboard_init () ;
    
    cout << "FLOOR" << endl << endl ;
    float number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 175, 800, 1025, 800 ) ;
    Linear_equation linear_equation_of_element = calculate_linear_equation_of_element ( 175, 800, 1025, 800 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    
    float x = 2000 ;
    float y = 2900 ;
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;
    
    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 175, 800, 1025, 800 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    
    
    
    
    cout << "RIGHT WALL" << endl << endl ;
    number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 1100, 725, 1100, 200 ) ;
    linear_equation_of_element = calculate_linear_equation_of_element ( 1100, 725, 1100, 200 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;
    
    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 1100, 725, 1100, 200 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    
    cout << "RIGHT EDGE" << endl << endl ;
    number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 1025, 800, 1100, 725 ) ;    
    linear_equation_of_element = calculate_linear_equation_of_element ( 1025, 800, 1100, 725 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;

    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 1025, 800, 1100, 725 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    
    
    
    cout << "LEFT EDGE" << endl << endl ;
    number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 100, 600, 175, 800 ) ;    
    linear_equation_of_element = calculate_linear_equation_of_element ( 100, 600, 175, 800 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;

    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 100, 600, 175, 800 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    
    cout << "TOP RIGHT CORNER ONE" << endl << endl ;
    number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 1100, 200, 1050, 50 ) ;
    linear_equation_of_element = calculate_linear_equation_of_element ( 1100, 200, 1050, 50 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;
    
    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 1100, 200, 1050, 50 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    
    cout << "TOP RIGHT CORNER TWO" << endl << endl ;
    number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 1050, 50, 900, 0 ) ;    
    linear_equation_of_element = calculate_linear_equation_of_element ( 1050, 50, 900, 0 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;
    
    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 1050, 50, 900, 0 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    
    cout << "CEILING" << endl << endl ;
    number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 900, 0, 400, 50 ) ;
    linear_equation_of_element = calculate_linear_equation_of_element ( 900, 0, 400, 50 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;
    
    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 900, 0, 400, 50 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    
    cout << "LITTLE CEILING" << endl << endl ;
    number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 400, 50, 200, 50 ) ;
    linear_equation_of_element = calculate_linear_equation_of_element ( 400, 50, 200, 50 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;
    
    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 400, 50, 200, 50 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    std::pair < float, float > x_and_y = 
        linear_equation_of_element .calculate_x_and_y_to_add_for_a_one_unit_movement () ;
    
    cout << "X and Y for a one unit movement" << endl ;
    cout << x_and_y .first << endl ;
    cout << x_and_y .second << endl << endl ;
    
    cout << "TOP LEFT CORNER" << endl << endl ;
    number_of_y_for_one_x = calculate_number_of_y_for_one_x ( 200, 50, 100, 600 ) ;
    linear_equation_of_element = calculate_linear_equation_of_element ( 200, 50, 100, 600 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    cout << "Point: " << "X = " << x << " ; Y = " << y << endl ;
    cout << linear_equation_of_element .point_is_to_the_left_of_the_line ( x, y ) << endl << endl ;
    
    cout << linear_equation_of_element .point_is_on_the_line ( x, y ) << endl << endl ;
    
    //linear_equation_of_element = calculate_perpendicular_linear_equation ( 200, 50, 100, 600 ) ;
    cout << linear_equation_of_element << endl << endl ;
    
    Attracting_element floor ( 175, 800, 1025, 800 ) ;
    Attracting_element right_wall ( 1100, 725, 1100, 200 ) ;
    Attracting_element right_edge ( 1025, 800, 1100, 725 ) ;
    Attracting_element left_edge ( 100, 600, 175, 800 ) ;
    Attracting_element top_right_corner_one ( 1100, 200, 1050, 50 ) ;
    Attracting_element top_right_corner_two ( 1050, 50, 900, 0 ) ;
    Attracting_element ceiling ( 900, 0, 400, 50 ) ;
    Attracting_element little_ceiling ( 400, 50, 200, 50 ) ;
    Attracting_element top_left_corner ( 200, 50, 100, 600 ) ;

    
    /*Attracting_element floor ( 10, 890, 1190, 890 ) ;
    Attracting_element left_wall ( 10, 10, 10, 890 ) ;
    Attracting_element left_wall_left_slope_of_hill ( 10, 300, 200, 450 ) ;
    Attracting_element left_wall_right_slope_of_hill ( 200, 450, 10, 600) ;
    Attracting_element right_wall ( 1190, 890, 1190, 10 ) ;
    Attracting_element ceiling ( 1190, 10, 10, 10 ) ;*/
    
    vector < Attracting_element > list_of_elements_attracting_the_player ;
    list_of_elements_attracting_the_player .push_back ( floor ) ;
    
    Player player ( list_of_elements_attracting_the_player ) ;
    
    /*vector<Attracting_element> elements ;
    elements .push_back ( floor ) ;
    elements .push_back ( left_wall ) ;
    elements .push_back ( left_wall_left_slope_of_hill ) ;
    elements .push_back ( left_wall_right_slope_of_hill ) ;
    elements .push_back ( right_wall ) ;
    elements .push_back ( ceiling ) ;*/
    
         vector<Attracting_element> elements ;
    elements .push_back ( floor ) ;
    elements .push_back ( left_edge ) ;
    elements .push_back ( right_wall ) ;
    elements .push_back ( right_edge ) ;
    elements .push_back ( left_edge ) ;
    elements .push_back ( top_right_corner_one ) ;
    elements .push_back ( top_right_corner_two ) ;
    elements .push_back ( ceiling ) ;
    elements .push_back ( little_ceiling ) ;
    elements .push_back ( top_left_corner ) ;

    
    std::pair <float, float> coordinates_of_closest_point ;

    coordinates_of_closest_point .first = 0 ;
    coordinates_of_closest_point .second = 0 ;
    
    
    
    while ( 1 ) 
    {        
        al_clear_to_color ( al_map_rgb_f ( 0, 0, 0 ) ) ;
        
        draw_map ( elements ) ;
        
        //al_draw_bitmap ( cookie_player, player .x - 17.5, player .y - 60, 0 ) ;
        
    // PRINT ABOVE THE PLAYER
    /*std::ostringstream ss ;
    ss << point_on_the_element .first << " | " ;
    ss << point_on_the_element .second ;
    string text ( ss .str () ) ;
    player .print_above_player ( text ) ;
    
        al_draw_filled_circle ( point_on_the_element .first, point_on_the_element .second, 3, al_map_rgb_f ( 1, 0, 1 ) ) ;
     * */
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
        
        player .draw_player () ;
        
        
        
        // Left wall
        //al_draw_filled_rectangle ( 0, 0, 100, 900,
          //      al_map_rgb_f ( 0.35, 0.35, 0.35 ) ) ;
        /*
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
        al_draw_filled_circle ( 1050, 50, 5,
                al_map_rgb_f ( 1, 1, 1 ) ) ;
        */
        // Draw elements attracting the player
        
        for ( int i = 0 ; i < player .list_of_elements_attracting_the_player .size () ; i ++ )
        {
            al_draw_line ( player .list_of_elements_attracting_the_player [ i ] .left_boundary_x,
                player .list_of_elements_attracting_the_player [ i ] .left_boundary_y,
                player .list_of_elements_attracting_the_player [ i ] .right_boundary_x,
                player .list_of_elements_attracting_the_player [ i ] .right_boundary_y,
                al_map_rgb_f ( 1, 1, 1 ), 1 ) ;
        }
        
        
        
          
        al_flip_display () ;
        
    }
    
    al_destroy_display ( display ) ;
    al_destroy_bitmap ( cookie_player ) ;
    al_destroy_timer ( timer ) ;
    al_destroy_event_queue ( event_queue ) ;
    
    return 0;
}

