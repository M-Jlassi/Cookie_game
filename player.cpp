/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <allegro5/allegro_primitives.h>

#include "player.h"

using namespace std;

Player::Player ( Attracting_element * element ) : x ( 600 ), y ( 800 ),
is_in_jump ( false ), element_attracting_the_player ( element ),
gravity_changed ( false ), can_jump ( false ), done ( false ) {}


void Player::move ()
{
    
    std::pair <float, float> direction_x_y = Player::get_direction_x_y () ;
    
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

std::pair <float, float> Player::get_direction_x_y ()
{
    
    std::pair <float, float> direction_x_y ;
    std::pair <float, float> ratios_reduced_for_directions ;
    
    ratios_reduced_for_directions .first = element_attracting_the_player -> x_ratio_for_one_y ;
    ratios_reduced_for_directions .second = element_attracting_the_player -> y_ratio_for_one_x ;
    
    //cout << "Element ratio X for one Y: " << ratios_reduced_for_directions .first << endl ;
    //cout << "Element ratio Y for one X: " << ratios_reduced_for_directions .second << endl ;
    
    if ( element_attracting_the_player -> x_ratio_for_one_y
        > element_attracting_the_player -> y_ratio_for_one_x)
    {
        ratios_reduced_for_directions .first = 1 ;
    }
    
    else if ( element_attracting_the_player -> x_ratio_for_one_y
        < element_attracting_the_player -> y_ratio_for_one_x)
    {
        ratios_reduced_for_directions .second = 1 ;
    }
    
    direction_x_y .first = 
            ratios_reduced_for_directions .first *
            element_attracting_the_player -> x_direction ;
    
    direction_x_y .second = 
            ratios_reduced_for_directions .second *
            element_attracting_the_player -> y_direction ;
    
    //cout << "Direction X: " << direction_x_y .first << endl ;
    //cout << "Direction Y: " << direction_x_y .second << endl << endl ;
    
    return direction_x_y ;
}

void Player::jump ( ALLEGRO_TIMER * timer )
{

    int time_since_jump_instruction = al_get_timer_count ( timer ) -
        jump_timer ;
    
    std::pair <int, int> direction_x_y = Player::get_direction_x_y () ;

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

    //speed_x_y = smoothen_landing ( speed_x_y ) ;

    //cout << "Speed X: " <<  speed_x_y .first << endl ;
    //cout << "Speed Y: " <<  speed_x_y .second << endl ;
    
    x += speed_x_y .first ;
    y += speed_x_y .second ;
}



void Player::verify_if_player_can_jump ()
{
    if ( element_attracting_the_player ->
        linear_equation .point_is_on_the_line ( x, y ) )
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
    
    
    int index_of_new_attracting_element ;
    
    if ( index_of_elements_reached .size () == 2 )
    {
        for ( int i = 0 ; i < index_of_elements_reached .size () ; i ++ )
        {
            if ( list_of_attracting_elements [ index_of_elements_reached [ i ] ]
                == *element_attracting_the_player )
            {
                if ( i == 1 )
                {
                    index_of_new_attracting_element = 0 ;
                }
                
                if ( i == 0 )
                {
                    index_of_new_attracting_element = 1 ;
                }
            }
        }
    }
    
    else index_of_new_attracting_element = index_of_elements_reached [ 0 ] ;
    
    
    
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
    
    
    
    
    element_attracting_the_player = new Attracting_element (
        list_of_attracting_elements [ index_of_new_attracting_element ] ) ;
}


std::pair <float, float> Player::get_speed ()
{ 
    Linear_equation line_going_in_the_direction_of_the_element = 
        element_attracting_the_player ->
        calculate_line_going_in_the_direction_of_the_element ( x, y ) ;
    
    std::pair < float, float > speed_x_y =
        line_going_in_the_direction_of_the_element
        .calculate_x_and_y_to_add_for_a_one_unit_movement () ;
    
    return speed_x_y ;
}

std::pair <float, float> Player::smoothen_landing ( std::pair <float, float> speed_x_y )
{
    /*
    std::pair <float, float> player_ratios_current = get_player_ratio_depending_on_the_current_attracting_element () ;
    std::pair <float, float> player_ratios_after = calculate_ratios (
        element_attracting_the_player->left_boundary_x,
        element_attracting_the_player->left_boundary_y,
        x + speed_x_y .first,
        y + speed_x_y .second
    ) ;

     * /    
    /*
    if ( ( speed_x_y .first > 0  &&
            x + speed_x_y .first > element_attracting_the_player -> left_boundary_x )
        || ( speed_x_y .first < 0  &&
            x + speed_x_y .first < element_attracting_the_player -> right_boundary_x ) )
    {
        speed_x_y .first /= 2 ;
    }

    if ( ( speed_x_y .second > 0  &&
            y + speed_x_y .second > element_attracting_the_player -> right_boundary_y )
        || ( speed_x_y .second < 0  &&
            y + speed_x_y .second < element_attracting_the_player -> left_boundary_y ) )
    {
        speed_x_y .second /= 2 ;
    }*/
   /* 
    float difference_between_lowest_ratios_current ;
    float difference_between_lowest_ratios_after ;
    
    if ( player_ratios_current .first <= player_ratios_current .second )
    {
        //cout << "Player X ratio for one Y: " << player_ratios .first << endl ;
        //cout << "Element X ratio for one Y: " << element_attracting_the_player -> x_ratio_for_one_y << endl ;
        difference_between_lowest_ratios_current = abs (
                player_ratios_current .first - element_attracting_the_player -> x_ratio_for_one_y
        ) ;
        difference_between_lowest_ratios_after = abs (
                player_ratios_after .first - element_attracting_the_player -> x_ratio_for_one_y
        ) ;
    }
    
    else if ( player_ratios_current .first > player_ratios_current .second )
    {
        //cout << "Player Y ratio for one X: " << player_ratios .second << endl ;
        //cout << "Element Y ratio for one X: " << element_attracting_the_player -> y_ratio_for_one_x << endl ;
        difference_between_lowest_ratios_current = abs (
                player_ratios_current .second - element_attracting_the_player -> y_ratio_for_one_x
        ) ;
        difference_between_lowest_ratios_after = abs (
                player_ratios_after .second - element_attracting_the_player -> y_ratio_for_one_x
        ) ;
    }*/
    /*
    if ( difference_between_lowest_ratios_after > difference_between_lowest_ratios_current )
    {
        cout << difference_between_lowest_ratios_current << endl ;
        cout << difference_between_lowest_ratios_after << endl << endl ;
    }
    */
    //cout << "Difference between lowest ratios: " << difference_between_lowest_ratios << endl << endl ;
    
    

    return speed_x_y ;
}





std::pair<float, float> Player::get_player_ratio_depending_on_the_current_attracting_element ()
{
    float difference_between_x = abs ( x - element_attracting_the_player->left_boundary_x ) ;
    float difference_between_y = abs ( y - element_attracting_the_player->left_boundary_y ) ;
    
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