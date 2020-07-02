/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <allegro5/allegro_primitives.h>

#include "player.h"

using namespace std;

Player::Player ( vector < Attracting_element > list_of_elements_attracting_the_player ) : x ( 600 ), y ( 800 ),
is_in_jump ( false ), list_of_elements_attracting_the_player ( list_of_elements_attracting_the_player ),
gravity_changed ( false ), can_jump ( false ), done ( false ) {}


void Player::move ()
{
    
    std::pair <float, float> direction_x_y = 
        list_of_elements_attracting_the_player [ 0 ] .linear_equation
        .calculate_x_and_y_to_add_for_a_one_unit_movement () ;
    
    if ( key [ ALLEGRO_KEY_LEFT ] )
    {
        x += direction_x_y .first * ( - 5 ) ;
        y += direction_x_y .second * ( - 5 ) ;
    }
        
        

    if ( key [ ALLEGRO_KEY_RIGHT ] )
    {
        x += direction_x_y .first * 5 ;
        y += direction_x_y .second * 5 ;
    }
    //cout << "X: " << x << endl ;
    //cout << "Y: " << y << endl ;
        
}




void Player::jump ( ALLEGRO_TIMER * timer )
{

    int time_since_jump_instruction = al_get_timer_count ( timer ) -
        jump_timer ;
    
    std::pair <float, float> direction_x_y =
        list_of_elements_attracting_the_player [ 0 ] .linear_equation
        .calculate_perpendicular_linear_equation ( x, y )
        .calculate_x_and_y_to_add_for_a_one_unit_movement () ;
    
    if ( is_in_jump )
    {
        if ( gravity_changed )
        {
            is_in_jump = false ;
            return ;
        }

        if ( time_since_jump_instruction > number_of_frames_in_a_jump )
        {
            is_in_jump = false ;
            return ;
        }

        // The player is in the first part of the jump

        if ( time_since_jump_instruction <= number_of_frames_in_a_jump )
        {
            x += direction_x_y .first * 20 ;
            y += direction_x_y .second * 20 ;
        }

        return ;

    }

    if ( key [ ALLEGRO_KEY_SPACE ] )
    {
        if ( is_in_jump || ! can_jump ) return ;
        
        is_in_jump = true ;
        can_jump = false ;
        jump_timer = al_get_timer_count ( timer ) ;

        x += direction_x_y .first * 20 ;
        y += direction_x_y .second * 20 ;
    }

}


void Player::gravity ( std::vector<Attracting_element> elements )
{
    gravity_changed = false ;

    verify_if_player_can_jump () ;

    get_closest_elements ( elements ) ;
    
    std::pair <float, float> speed_x_y = get_speed () ;

    x += speed_x_y .first ;
    y += speed_x_y .second ;
    
}



void Player::verify_if_player_can_jump ()
{
    if ( list_of_elements_attracting_the_player [ 0 ]
        .linear_equation .point_is_on_the_line ( x, y ) )
    {
        
        can_jump = true ;
    }
    
    
}





void Player::get_closest_elements (
    std::vector < Attracting_element > list_of_attracting_elements )
{
    pair <float, float> test_coordinates_from_player_position ;
    test_coordinates_from_player_position .first = x ;
    test_coordinates_from_player_position .second = y ;
    
    
    /*
     * Initialize the position of the point where we will start iterating towards the elements.
     * (list_of_test_coordinates_from_player_position) 
     * 
     * Initialize the directions towards which we will iterate.
     * (list_of_x_and_y_to_add_for_a_one_unit_movement)
     */
    
    vector < pair < float, float > > list_of_test_coordinates_from_player_position ;
    
    Linear_equation linear_equation_of_the_attracting_element ;
    vector < Linear_equation > list_of_linear_equations_of_the_attracting_elements ;
    
    Linear_equation line_going_in_the_direction_of_the_element ;
    
    pair <float, float> x_and_y_to_add_for_a_one_unit_movement ;
    vector < pair < float, float > > list_of_x_and_y_to_add_for_a_one_unit_movement ;
    
    
    for ( int i = 0 ; i < list_of_attracting_elements .size () ; i ++ )
    {
        list_of_test_coordinates_from_player_position .push_back (
            test_coordinates_from_player_position ) ;
        
        
        
        linear_equation_of_the_attracting_element =
        calculate_linear_equation_of_element (
            list_of_attracting_elements [ i ] .left_boundary_x,
            list_of_attracting_elements [ i ] .left_boundary_y,
            list_of_attracting_elements [ i ] .right_boundary_x,
            list_of_attracting_elements [ i ] .right_boundary_y
        ) ;
    
        list_of_linear_equations_of_the_attracting_elements .push_back (
            linear_equation_of_the_attracting_element ) ;
    
    
        line_going_in_the_direction_of_the_element =
            list_of_attracting_elements [ i ]
            .calculate_line_going_in_the_direction_of_the_element ( x, y ) ;
        
        
        x_and_y_to_add_for_a_one_unit_movement =
            line_going_in_the_direction_of_the_element
            .calculate_x_and_y_to_add_for_a_one_unit_movement () ;
        

        list_of_x_and_y_to_add_for_a_one_unit_movement .push_back (
            x_and_y_to_add_for_a_one_unit_movement ) ;
    }
    
    
    vector < int > index_of_elements_reached ;
    bool has_reached_an_element = false ;
    int number_of_iterations = 0 ;
    
    while ( ! has_reached_an_element )
    {
        for ( int i = 0 ; i < list_of_attracting_elements .size () ; i ++ )
        {
            // Increase player coordinates in direction to the element
        
            list_of_test_coordinates_from_player_position [ i ] .first +=
                list_of_x_and_y_to_add_for_a_one_unit_movement [ i ] .first ;

            list_of_test_coordinates_from_player_position [ i ] .second +=
                list_of_x_and_y_to_add_for_a_one_unit_movement [ i ] .second ;

            
            if ( ! ( list_of_linear_equations_of_the_attracting_elements [ i ]
                .point_is_to_the_left_of_the_line (
                    list_of_test_coordinates_from_player_position [ i ] .first,
                    list_of_test_coordinates_from_player_position [ i ] .second
                ) )
                && 
                list_of_attracting_elements [ i ]
                .point_is_within_the_boundaries_of_the_element (
                    list_of_test_coordinates_from_player_position [ i ] .first,
                    list_of_test_coordinates_from_player_position [ i ] .second
                ) )
            {
                index_of_elements_reached .push_back ( i ) ;
                has_reached_an_element = true ;
            }
        }
        
        
        number_of_iterations ++ ;
    }
    
    
    for ( int i = 0 ; i < list_of_attracting_elements .size () ; i ++ )
    {
        al_draw_line (
                x,
                y,
                list_of_test_coordinates_from_player_position [ i ] .first,
                list_of_test_coordinates_from_player_position [ i ] .second,
                al_map_rgb_f ( 0.2, 1, 1 ), 1
        ) ;    
    }
    
    list_of_elements_attracting_the_player .clear () ;
    
    for ( int i = 0 ; i < index_of_elements_reached .size () ; i ++ )
    {
        list_of_elements_attracting_the_player .push_back (
            list_of_attracting_elements [ index_of_elements_reached [ i ] ] ) ;
    }
    
    
    /*
    // PRINT ABOVE THE PLAYER
    std::ostringstream ss ;
    //ss << number_of_iterations ;
    //string iterations ( ss .str () ) ;
    
    for ( int i = 0 ; i < index_of_elements_reached .size () ; i ++ )
    {
        ss << index_of_elements_reached [ i ] << " ; " ;
    }
    
    string indices ( ss .str () ) ;
    
    print_above_player ( indices ) ;
    */
}


std::pair <float, float> Player::get_speed ()
{
    Linear_equation line_going_in_the_direction_of_the_element ;
    
    pair < float, float > speed_x_y_for_the_element ;
    
    vector < float > list_of_speeds_x ;
    vector < float > list_of_speeds_y ;
        
    for ( int i = 0 ; i < list_of_elements_attracting_the_player .size () ; i ++ )
    {
        line_going_in_the_direction_of_the_element = 
            list_of_elements_attracting_the_player [ i ]
            .calculate_line_going_in_the_direction_of_the_element ( x, y ) ;

        speed_x_y_for_the_element = line_going_in_the_direction_of_the_element
            .calculate_x_and_y_to_add_for_a_one_unit_movement () ;
        
    
        list_of_speeds_x .push_back ( speed_x_y_for_the_element .first ) ;
        list_of_speeds_y .push_back ( speed_x_y_for_the_element .second ) ;
    }
    

    
    
    pair < float, float > speed_x_y ;
    
    speed_x_y .first = std::accumulate (
        list_of_speeds_x .begin (), list_of_speeds_x .end (), 0.0 ) ;
    
    speed_x_y .first /= list_of_speeds_x .size () ;
    
    
    speed_x_y .second = std::accumulate (
        list_of_speeds_y .begin (), list_of_speeds_y .end (), 0.0 ) ;
    
    speed_x_y .second /= list_of_speeds_y .size () ;
    
    
    speed_x_y .first *= 5 ;
    speed_x_y .second *= 5 ;
    
    
    speed_x_y = smoothen_landing ( speed_x_y ) ;
    
    
    
    return speed_x_y ;
}



std::pair < float, float >
    Player::calculate_distance_between_the_player_and_the_first_attracting_element ()
{
    Linear_equation line_going_in_the_direction_of_the_first_attracting_element = 
        list_of_elements_attracting_the_player [ 0 ]
        .calculate_line_going_in_the_direction_of_the_element ( x, y ) ;

    pair < float, float > point_on_the_element = 
        calculate_the_point_of_intersection (
            list_of_elements_attracting_the_player [ 0 ] .linear_equation,
            line_going_in_the_direction_of_the_first_attracting_element
        ) ;
    
    pair < float, float > distance_between_the_player_and_the_element ;
    
    distance_between_the_player_and_the_element .first =
        point_on_the_element .first - x ;
    
    std::ostringstream ss ;
    ss << point_on_the_element .second << " | " ;
    ss << y << " || " ;
    ss << can_jump << " [[[";
    ss << distance_between_the_player_and_the_element .second ;
    string text ( ss .str () ) ;
    print_above_player ( text ) ;
    
    distance_between_the_player_and_the_element .second =
        point_on_the_element .second - y ;
    
    al_draw_filled_circle ( point_on_the_element .first, point_on_the_element .second, 3,
                al_map_rgb_f ( 1, 0.8, 0.5 ) ) ;
    
    return distance_between_the_player_and_the_element ;
}






std::pair <float, float> Player::smoothen_landing ( std::pair <float, float> speed_x_y )
{
    pair < float, float > distance_x_y_between_the_player_and_the_element =
        calculate_distance_between_the_player_and_the_first_attracting_element () ;

    
    if ( abs ( speed_x_y .first ) >
        abs ( distance_x_y_between_the_player_and_the_element .first ) )
    {
        speed_x_y .first =
            distance_x_y_between_the_player_and_the_element .first ;
 
    }
    
    if ( abs ( speed_x_y .second ) >
         abs ( distance_x_y_between_the_player_and_the_element .second ) )
    {
        speed_x_y .second =
            distance_x_y_between_the_player_and_the_element .second ;
    }
    
    
    return speed_x_y ;
}



void Player::print_above_player ( string text )
{
    int length_of_string = text .length () ;
    
    char char_array [ length_of_string + 1 ] ;
    
    strcpy ( char_array, text .c_str () ) ;
    
    ALLEGRO_FONT* font = al_create_builtin_font();
    
    al_draw_text ( font, al_map_rgb ( 255, 255, 255 ),
        x, y - 50, ALLEGRO_ALIGN_CENTER, char_array ) ;
}