/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "player.h"
#include <iostream>

using namespace std;

Player::Player ( Attracting_element * element ) : x ( 600 ), y ( 800 ),
is_in_jump ( false ), element_attracting_the_player ( element ),
gravity_changed ( false ), can_jump ( false ), done ( false ) {}


void Player::move ()
{
    
    std::pair <float, float> direction_x_y = Player::get_direction_x_y () ;
    
    if ( key [ ALLEGRO_KEY_LEFT ] )
    {
        x += direction_x_y .first * ( - 15 ) ;
        y += direction_x_y .second * ( - 15 ) ;
    }
        
        

    if ( key [ ALLEGRO_KEY_RIGHT ] )
    {
        x += direction_x_y .first * 15 ;
        y += direction_x_y .second * 15 ;
    }
        
}

std::pair <float, float> Player::get_direction_x_y ()
{
    
    std::pair <float, float> direction_x_y ;
    std::pair <float, float> ratios_reduced_for_directions ;
    
    ratios_reduced_for_directions .first = element_attracting_the_player -> x_ratio_for_one_y ;
    ratios_reduced_for_directions .second = element_attracting_the_player -> y_ratio_for_one_x ;
    
    if ( element_attracting_the_player -> x_ratio_for_one_y
        > element_attracting_the_player -> y_ratio_for_one_x)
    {
        ratios_reduced_for_directions .second =
            ratios_reduced_for_directions .second / ratios_reduced_for_directions .first ;
        ratios_reduced_for_directions .first =
            ratios_reduced_for_directions .first / ratios_reduced_for_directions .first ;
    }
    
    else if ( element_attracting_the_player -> x_ratio_for_one_y
        < element_attracting_the_player -> y_ratio_for_one_x)
    {
        ratios_reduced_for_directions .first =
            ratios_reduced_for_directions .first / ratios_reduced_for_directions .second ;
        ratios_reduced_for_directions .second =
            ratios_reduced_for_directions .second / ratios_reduced_for_directions .second ;
    }
    
    direction_x_y .first = 
            ratios_reduced_for_directions .first *
            element_attracting_the_player -> x_direction ;
    
    direction_x_y .second = 
            ratios_reduced_for_directions .second *
            element_attracting_the_player -> y_direction ;
    
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

    get_closest_element ( elements ) ;

    std::pair <float, float> speed_x_y = get_speed () ;

    //speed_x_y = smoothen_landing ( speed_x_y ) ;

    cout << "Speed X: " <<  speed_x_y .first << endl ;
    cout << "Speed Y: " <<  speed_x_y .second << endl ;
    
    x += speed_x_y .first ;
    y += speed_x_y .second ;
}

void Player::verify_if_player_can_jump ()
{
    std::pair <float, float> player_ratios_x_y =
        Player::get_player_ratio_depending_on_the_current_attracting_element () ;
    
    if ( player_ratios_x_y .first == element_attracting_the_player -> x_ratio_for_one_y
        && player_ratios_x_y .second == element_attracting_the_player -> y_ratio_for_one_x )
    {
        can_jump = true ;
    }
}

void Player::get_closest_element ( std::vector<Attracting_element> elements )
{
    float distance_x_y_to_left_boundary ;
    float distance_x_y_to_right_boundary ;
    
    std::vector<float> distances_to_elements ;
    
    for ( int i = 0 ; i < elements .size() ; i++ )
    {
        distance_x_y_to_left_boundary = 
                abs ( x - elements [ i ] .left_boundary_x )
                + abs ( y - elements [ i ] .left_boundary_y );
        distance_x_y_to_right_boundary = 
                abs ( x - elements [ i ] .right_boundary_x )
                + abs ( y - elements [ i ] .right_boundary_y );
        
        distances_to_elements .push_back (
            distance_x_y_to_left_boundary + distance_x_y_to_right_boundary
        ) ;
    }
    /*
    for ( int i = 0 ; i < elements .size () ; i++ )
    {
        cout << "Distance to " << ( i == 0 ? "floor" : i == 1 ? "fight wall" : "right edge" ) << endl ;
        cout << distances_to_elements [ i ] << endl ;
    }
    cout << endl ;*/

    std::vector<float>::iterator iterator_of_minimum = std::min_element (
        distances_to_elements .begin(), distances_to_elements .end()
    ) ;

    int address_of_minimum = std::distance ( distances_to_elements .begin(),
            iterator_of_minimum ) ;

    if ( ! ( * element_attracting_the_player == elements [ address_of_minimum ] ) )
    {
        gravity_changed = true ;
    }

    element_attracting_the_player = new Attracting_element ( elements [ address_of_minimum ] ) ;
}


std::pair <float, float> Player::get_speed ()
{
    std::pair <float, float> speed_x_y ;
    
    std::pair <float, float> player_ratios = get_player_ratio_depending_on_the_current_attracting_element () ;
    
    /*
    float difference_between_lowest_ratios ;
    
    if ( player_ratios .first <= player_ratios .second )
    {
        cout << player_ratios .first << endl ;
        cout << element_attracting_the_player -> x_ratio_for_one_y << endl ;
        difference_between_lowest_ratios = abs (
                player_ratios .first - element_attracting_the_player -> x_ratio_for_one_y
        ) ;
    }
    
    else if ( player_ratios .first > player_ratios .second )
    {
        cout << player_ratios .second << endl ;
        cout << element_attracting_the_player -> y_ratio_for_one_x << endl ;
        difference_between_lowest_ratios = abs (
                player_ratios .second - element_attracting_the_player -> y_ratio_for_one_x
        ) ;
    }
    */
    
    if ( player_ratios .first == element_attracting_the_player -> x_ratio_for_one_y
        || player_ratios .second == element_attracting_the_player -> y_ratio_for_one_x )
    {
        cout << "YES" << endl ;
        speed_x_y .first = 0 ;
        speed_x_y .second = 0 ;
    }
    
    // Horizontal element
    else if ( element_attracting_the_player -> x_ratio_for_one_y == 1 
        && element_attracting_the_player -> y_ratio_for_one_x == 0 )
    {
        speed_x_y .first = 0 ;
        speed_x_y .second = 1 ;
    }
    
    // Vertical element
    else if ( element_attracting_the_player -> x_ratio_for_one_y == 0
        && element_attracting_the_player -> y_ratio_for_one_x == 1 )
    {
        speed_x_y .first = 1 ;
        speed_x_y .second = 0 ;
    }
    
    else
    {
        speed_x_y .first = element_attracting_the_player -> y_ratio_for_one_x ;
        speed_x_y .second = element_attracting_the_player -> x_ratio_for_one_y ;
    }
    
    // Bottom-left corner
    if ( element_attracting_the_player -> x_direction == 1
        && element_attracting_the_player -> y_direction == 1 )
    {
        speed_x_y .first *= -1 ;
        speed_x_y .second *= 1 ;
    }
    
    // Bottom-right corner
    else if ( element_attracting_the_player -> x_direction == 1
        && element_attracting_the_player -> y_direction == -1 )
    {
        speed_x_y .first *= 1 ;
        speed_x_y .second *= 1 ;
    }
    
    // Top-left corner
    else if ( element_attracting_the_player -> x_direction == -1
        && element_attracting_the_player -> y_direction == 1 )
    {
        speed_x_y .first *= -1 ;
        speed_x_y .second *= -1 ;
    }
    
    // Top-right corner
    else if ( element_attracting_the_player -> x_direction == -1
        && element_attracting_the_player -> y_direction == -1 )
    {
        speed_x_y .first *= 1 ;
        speed_x_y .second *= -1 ;
    }
    
    // Ceiling
    else if ( element_attracting_the_player -> x_direction == -1
        && element_attracting_the_player -> y_direction == 0 )
    {
        speed_x_y .second *= -1 ;
    }
    
    // Left wall
    else if ( element_attracting_the_player -> x_direction == 0
        && element_attracting_the_player -> y_direction == 1 )
    {
        speed_x_y .first *= -1 ;
    }
    
    return speed_x_y ;
}

std::pair <float, float> Player::smoothen_landing ( std::pair <float, float> speed_x_y )
{
    //std::pair <float, float> ratios = get_player_ratio_depending_on_the_current_attracting_element () ;
    
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
    }

    return speed_x_y ;
}

std::pair<float, float> Player::get_player_ratio_depending_on_the_current_attracting_element ()
{
    float difference_between_x = abs ( element_attracting_the_player->left_boundary_x - x ) ;
    float difference_between_y = abs ( element_attracting_the_player->left_boundary_y - y ) ;
    
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
    
    cout << "Ratio element X: " << element_attracting_the_player -> x_ratio_for_one_y << endl ;
    cout << "Ratio element Y: " << element_attracting_the_player -> y_ratio_for_one_x << endl ;
    cout << "Ratio player X: " << x_ratio_for_one_y << endl ;
    cout << "Ratio player Y: " << y_ratio_for_one_x << endl << endl << endl ;
    
    
    std::pair <float, float> player_ratios_x_y = std::pair<float, float> ( x_ratio_for_one_y, y_ratio_for_one_x ) ;
    
    return player_ratios_x_y ;
}
    
