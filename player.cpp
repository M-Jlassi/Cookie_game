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
        list_of_elements_attracting_the_player [ 0 ]
        .calculate_linear_equation ()
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
    
    std::pair <int, int> direction_x_y = 
        list_of_elements_attracting_the_player [ 0 ]
        .calculate_linear_equation ()
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
            x += direction_x_y .second * 20 ;
            y += direction_x_y .first * ( - 20 ) ;
        }

        return ;

    }

    if ( key [ ALLEGRO_KEY_SPACE ] )
    {
        if ( is_in_jump || ! can_jump ) return ;

        is_in_jump = true ;
        can_jump = false ;
        jump_timer = al_get_timer_count ( timer ) ;

        x += direction_x_y .second * 20 ;
        y += direction_x_y .first * ( - 20 ) ;
    }

}


void Player::gravity ( std::vector<Attracting_element> elements )
{
    gravity_changed = false ;

    verify_if_player_can_jump () ;

    get_closest_element_from_the_list_of_elements ( elements ) ;

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





void Player::get_closest_element_from_the_list_of_elements (
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
                ) ) )
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
    /*
    list_of_elements_attracting_the_player [ 0 ] = *(new Attracting_element (
        list_of_attracting_elements [ index_of_new_attracting_element ] ) ) ;
*/}


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
        x - point_on_the_element .first ;
    
    distance_between_the_player_and_the_element .second =
        y - point_on_the_element .second ;
    
    // PRINT ABOVE THE PLAYER
    std::ostringstream ss ;
    ss << distance_between_the_player_and_the_element .first << " | " ;
    ss << distance_between_the_player_and_the_element .second ;
    string text ( ss .str () ) ;
    print_above_player ( text ) ;
    
    al_draw_filled_circle ( point_on_the_element .first, point_on_the_element .second, 5,
                al_map_rgb_f ( 1, 0.3, 0.7 ) ) ;
    
    return distance_between_the_player_and_the_element ;
}






std::pair <float, float> Player::smoothen_landing ( std::pair <float, float> speed_x_y )
{
    pair < float, float > distance_x_y_between_the_player_and_the_element =
        calculate_distance_between_the_player_and_the_first_attracting_element () ;

    if ( abs ( speed_x_y .first ) >
        ( distance_x_y_between_the_player_and_the_element .first ) )
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





std::pair<float, float> Player::get_player_ratio_depending_on_the_current_attracting_element ()
{
    float difference_between_x = abs ( x - list_of_elements_attracting_the_player [ 0 ] .left_boundary_x ) ;
    float difference_between_y = abs ( y - list_of_elements_attracting_the_player [ 0 ] .left_boundary_y ) ;
    
    float x_ratio_for_one_y ;
    float y_ratio_for_one_x ;
    
    if ( difference_between_x == 0 )
    {
        x_ratio_for_one_y = 0 ;
        y_ratio_for_one_x = 1 ;
    }
    
    else if ( difference_between_y == 0 )
    {
        x_ratio_for_one_y = 1 ;
        y_ratio_for_one_x = 0 ;
    }
    
    else
    {
        x_ratio_for_one_y = difference_between_x / difference_between_y ;
        y_ratio_for_one_x = difference_between_y / difference_between_x ;
    }
    /*
    cout << "Ratio element X: " << element_attracting_the_player -> x_ratio_for_one_y << endl ;
    cout << "Ratio element Y: " << element_attracting_the_player -> y_ratio_for_one_x << endl ;
    cout << "Ratio player X: " << x_ratio_for_one_y << endl ;
    cout << "Ratio player Y: " << y_ratio_for_one_x << endl << endl << endl ;
    */
    
    std::pair <float, float> player_ratios_x_y = std::pair<float, float> ( x_ratio_for_one_y, y_ratio_for_one_x ) ;
    
    return player_ratios_x_y ;
}



    
float calculate_ratio ( float x_static, float y_static,
    float x_moving, float y_moving )
{
    
    float moving_part = x_moving + y_moving ;
    
    float static_part = x_static + y_static ;
    
    cout << "Calculating ratio: " << moving_part << " / " << static_part << endl ;
    
    float ratio = moving_part / static_part ;
    
    return ratio ;
}






int Player::calculate_number_of_one_unit_iterations_between_player_and_attracting_element ( Attracting_element attracting_element )
{    
    std::pair <float, float> test_coordinates_from_player_position ;
    test_coordinates_from_player_position .first = x ;
    test_coordinates_from_player_position .second = y ;
    
    Linear_equation linear_equation_of_the_attracting_element =
        calculate_linear_equation_of_element (
            attracting_element .left_boundary_x,
            attracting_element .left_boundary_y,
            attracting_element .right_boundary_x,
            attracting_element .right_boundary_y
        ) ;
    
    
    // Verify if the player touches the element
    
    if ( linear_equation_of_the_attracting_element .point_is_on_the_line ( x, y ) )
    {
        return 0 ;
    }
    
    /*
     * Verify if the player is above the element
     * 
     * If so, locate whether the player is:
     *  Directly above: the closest way to the element will be the perpendicular to this element
     *  To the left: the closest way to the element will be in the direction of the left boundary
     *  To the right: the closest way to the element will be in the direction of the right boundary
     * 
     */
    
    Linear_equation line_going_to_the_element ;
            
    // Player is above the element?
    
    if ( linear_equation_of_the_attracting_element
        .point_is_to_the_left_of_the_line ( x, y ) )
    {        
        Linear_equation left_boundary_perpendicular_to_the_attracting_element =
            calculate_perpendicular_linear_equation (
                attracting_element .left_boundary_x,
                attracting_element .left_boundary_y,
                attracting_element .right_boundary_x,
                attracting_element .right_boundary_y
            ) ;
        
        if ( left_boundary_perpendicular_to_the_attracting_element
            .point_is_on_the_line ( x, y ) )
        {
            // Reverse perpendicular until get to the element
            
            line_going_to_the_element =
                left_boundary_perpendicular_to_the_attracting_element 
                .calculate_line_going_in_the_opposite_direction () ;
        }
        
        else if ( left_boundary_perpendicular_to_the_attracting_element
            .point_is_to_the_left_of_the_line (x, y ) )
        {
            // Linear_equation from the player to the left boundary position of the element
            
            line_going_to_the_element = calculate_linear_equation_of_element (
                x, y,
                attracting_element .left_boundary_x,
                attracting_element .left_boundary_y
            ) ;
        }
        
        // Player is to the right of the left perpendicular
        
        else
        {
            float x_right_boundary_if_line_continues =
                attracting_element .right_boundary_x
                + ( linear_equation_of_the_attracting_element .direction_x * 1 ) ;
            
            float y_right_boundary_if_line_continues =
                attracting_element .right_boundary_y
                + ( linear_equation_of_the_attracting_element .direction_y
                * linear_equation_of_the_attracting_element .number_of_y_for_one_x ) ;
            
            Linear_equation right_boundary_perpendicular_to_the_attracting_element =
                calculate_perpendicular_linear_equation (
                    attracting_element .right_boundary_x,
                    attracting_element .right_boundary_y,
                    x_right_boundary_if_line_continues,
                    y_right_boundary_if_line_continues
                ) ;
            
            Linear_equation line_going_in_the_opposite_direction =
                right_boundary_perpendicular_to_the_attracting_element
                .calculate_line_going_in_the_opposite_direction () ;
            
            // The player is just above the element
            
            if ( right_boundary_perpendicular_to_the_attracting_element
                .point_is_to_the_left_of_the_line ( x, y ) )
            {
                line_going_to_the_element =
                    calculate_linear_equation_with_one_coordinate (
                        x, y,
                        line_going_in_the_opposite_direction .direction_x,
                        line_going_in_the_opposite_direction .direction_y,
                        line_going_in_the_opposite_direction .number_of_y_for_one_x
                    ) ;
            }
            
            // The player is on the right boundary perpendicular
            
            else if ( right_boundary_perpendicular_to_the_attracting_element
                .point_is_on_the_line ( x, y ) )
            {                
                line_going_to_the_element = line_going_in_the_opposite_direction ;
            }
            
            // The player is to the right of the element
            
            else
            {
                line_going_to_the_element = calculate_linear_equation_of_element (
                    x, y,
                    attracting_element .right_boundary_x,
                    attracting_element .right_boundary_y
                ) ;
            }
        }
    }
    
    else
    {
        return -1 ;
    }
    
    pair <float, float> x_and_y_to_add_for_a_one_unit_movement =
        line_going_to_the_element .calculate_x_and_y_to_add_for_a_one_unit_movement () ;
    
    /*
     * PRINT ABOVE THE PLAYER
    std::ostringstream ss ;
    ss << x_and_y_to_add_for_a_one_unit_movement .first << " ; " ;
    ss << x_and_y_to_add_for_a_one_unit_movement .second ;
    string display_x_and_y ( ss .str () ) ;
    
    print_above_player (player, display_x_and_y ) ;
    */
    
    bool has_reached_the_element = false ;
    int number_of_iterations = 0 ;
    
    while ( ! has_reached_the_element )
    {
        // Increase player coordinates in direction to the element
        
        test_coordinates_from_player_position .first +=
            x_and_y_to_add_for_a_one_unit_movement .first ;
        
        test_coordinates_from_player_position .second +=
            x_and_y_to_add_for_a_one_unit_movement .second ;
        
        if ( ! ( linear_equation_of_the_attracting_element
            .point_is_to_the_left_of_the_line (
                test_coordinates_from_player_position .first,
                test_coordinates_from_player_position .second
            ) ) )
        {
            has_reached_the_element = true ;
        }
        
        number_of_iterations ++ ;
    }
    
    
    return number_of_iterations ;
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