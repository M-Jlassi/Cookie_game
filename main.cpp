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

std::pair <float, float> calculate_ratios ( float x1, float x2, float y1, float y2 )
{
    // First is x_ratio_for_one_y
    // Second is y_ratio_for_one_x
    
    std::pair <float, float> ratios ;
    
    float difference_between_x = abs ( x2 - x1 ) ;
    float difference_between_y = abs ( y2 - y1 ) ;
    
    if ( difference_between_x == 0 )
    {
        ratios .first = 0 ;
        ratios .second = 1 ;
    }
    
    else if ( difference_between_y == 0 )
    {
        ratios .first = 1 ;
        ratios .second = 0 ;
    }
    
    else
    {
        ratios .first = difference_between_x / difference_between_y ;
        ratios .second = difference_between_y / difference_between_x ;
    }
    
    return ratios ;
}

std::pair <float, float> calculate_distance_between_player_and_attracting_element (
    Player player )
{
    std::pair <float, float> coordinates_of_closest_point ;
    
    std::pair <float, float> test_coordinates_from_player_position ;
    test_coordinates_from_player_position .first = player .x ;
    test_coordinates_from_player_position .second = player .y ;
    
    std::pair <float, float> test_ratios = calculate_ratios (
            player .element_attracting_the_player -> left_boundary_x, player .x,
            player .element_attracting_the_player -> left_boundary_y, player .y
    );
    
    float direction_to_follow_x ;
    float direction_to_follow_y ;
    
    // Horizontal element
    if ( player .element_attracting_the_player -> x_ratio_for_one_y == 1 
            && player .element_attracting_the_player -> y_ratio_for_one_x == 0 )
    {
        direction_to_follow_x = 0 ;
        direction_to_follow_y = 1 ;
    }
    
    // Vertical element
    else if ( player .element_attracting_the_player -> x_ratio_for_one_y == 0
            && player .element_attracting_the_player -> y_ratio_for_one_x == 1 )
    {
        direction_to_follow_x = 1 ;
        direction_to_follow_y = 0 ;
    }
    
    else
    {
        direction_to_follow_x = player .element_attracting_the_player -> y_ratio_for_one_x ;
        direction_to_follow_y = player .element_attracting_the_player -> x_ratio_for_one_y ;
    }
    
    // Bottom-left corner
    if ( player .element_attracting_the_player -> x_direction == 1
            && player .element_attracting_the_player -> y_direction == 1 )
    {
        direction_to_follow_x *= -1 ;
        direction_to_follow_y *= 1 ;
    }
    
    // Bottom-right corner
    else if ( player .element_attracting_the_player -> x_direction == 1
            && player .element_attracting_the_player -> y_direction == -1 )
    {
        direction_to_follow_x *= 1 ;
        direction_to_follow_y *= 1 ;
    }
    
    // Top-left corner
    else if ( player .element_attracting_the_player -> x_direction == -1
            && player .element_attracting_the_player -> y_direction == 1 )
    {
        direction_to_follow_x *= -1 ;
        direction_to_follow_y *= -1 ;
    }
    
    // Top-right corner
    else if ( player .element_attracting_the_player -> x_direction == -1
            && player .element_attracting_the_player -> y_direction == -1 )
    {
        direction_to_follow_x *= 1 ;
        direction_to_follow_y *= -1 ;
    }
    
    else if ( player .element_attracting_the_player -> x_direction == -1
            && player .element_attracting_the_player -> y_direction == 0 )
    {
        direction_to_follow_y *= -1 ;
    }
    
    else if ( player .element_attracting_the_player -> x_direction == 0
            && player .element_attracting_the_player -> y_direction == 1 )
    {
        direction_to_follow_x *= -1 ;
    }

    
    //bool element_found = false ;
    //int counter = 0 ;
    
    for ( int i = 0 ; i < 100 ; i++ )
    {
        if ( test_ratios .first == player .element_attracting_the_player -> x_ratio_for_one_y
            || test_ratios .second == player .element_attracting_the_player -> y_ratio_for_one_x )
        {
            break ;
        }
        
        test_coordinates_from_player_position .first += direction_to_follow_x ;
        test_coordinates_from_player_position .second += direction_to_follow_y ;
        
        test_ratios = calculate_ratios (
            player .element_attracting_the_player -> left_boundary_x,
            test_coordinates_from_player_position .first,
            player .element_attracting_the_player -> left_boundary_y,
            test_coordinates_from_player_position .second
        ) ;
    }
    


    /*
    cout << "Test" << endl ;
    cout << "Ratio X for one Y: " << test_ratios .first << endl ;
    cout << "Ratio Y for one X: " << test_ratios .second << endl << endl ;

    cout << "Element" << endl ;
    cout << "Ratio X for one Y: " << player .element_attracting_the_player -> x_ratio_for_one_y << endl ;
    cout << "Ratio Y for one X: " << player .element_attracting_the_player -> y_ratio_for_one_x << endl << endl ;
    */
    coordinates_of_closest_point .first = test_coordinates_from_player_position .first ;
    coordinates_of_closest_point .second = test_coordinates_from_player_position .second ;
    
    return coordinates_of_closest_point ;
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
    Attracting_element right_wall ( 1100, 725, 1100, 200 ) ;
    Attracting_element right_edge ( 1025, 800, 1100, 725 ) ;
    Attracting_element left_edge ( 100, 600, 175, 800 ) ;
    Attracting_element top_right_corner_one ( 1100, 200, 1050, 50 ) ;
    Attracting_element top_right_corner_two ( 1050, 50, 900, 0 ) ;
    Attracting_element ceiling ( 900, 0, 400, 50 ) ;
    Attracting_element little_ceiling ( 400, 50, 200, 50 ) ;
    Attracting_element top_left_corner ( 200, 50, 100, 600 ) ;
    
    Player player ( & floor ) ;
    
    vector<Attracting_element> elements ;
    elements .push_back ( floor ) ;
    elements .push_back ( right_wall ) ;
    elements .push_back ( right_edge ) ;
    elements .push_back ( left_edge ) ;
    elements .push_back ( top_right_corner_one ) ;
    elements .push_back ( top_right_corner_two ) ;
    elements .push_back ( ceiling ) ;
    elements .push_back ( little_ceiling ) ;
    elements .push_back ( top_left_corner ) ;
    
    /*
    
    cout << "floor: " << floor << endl ;
    cout << "right_wall: " << right_wall << endl ;
    cout << "right_edge: " << right_edge << endl ;
    cout << "left_edge: " << left_edge << endl ;
    cout << "top_right_corner_one: " << top_right_corner_one << endl ;
    cout << "top_right_corner_two: " << top_right_corner_two << endl ;
    cout << "ceiling: " << ceiling << endl ;    
    cout << "little_ceiling: " << little_ceiling << endl ;
    cout << "top_left_corner: " << top_left_corner << endl ;
    */
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
                player.x - 10, 
                player.y - 20, 
                player.x + 10, 
                player.y - 20,
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
        al_draw_filled_circle ( 1050, 50, 5,
                al_map_rgb_f ( 1, 1, 1 ) ) ;
        
        // Draw element attracting the player
        al_draw_line ( player .element_attracting_the_player -> left_boundary_x,
                player .element_attracting_the_player -> left_boundary_y,
                player .element_attracting_the_player -> right_boundary_x,
                player .element_attracting_the_player -> right_boundary_y,
                al_map_rgb_f ( 1, 1, 1 ), 1 ) ;
        
        std::pair <float, float> coordinates_of_closest_point = 
                calculate_distance_between_player_and_attracting_element ( player ) ;
        
        al_draw_line (
                player .x,
                player .y,
                coordinates_of_closest_point .first,
                coordinates_of_closest_point .second,
                al_map_rgb_f ( 0.2, 1, 1 ), 1
        ) ;
                
        al_flip_display () ;
        
    }
    
    al_destroy_display ( display ) ;
    al_destroy_timer ( timer ) ;
    al_destroy_event_queue ( event_queue ) ;
    
    return 0;
}

