/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "player.h"
#include <iostream>

using namespace std;

Player::Player ( Attracting_element * element ) : x ( 100 ), y ( 150 ),
is_in_jump ( false ), element_attracting_the_player ( element ),
gravity_changed ( false ), can_jump ( false ), done ( false ) {}


void Player::move ()
{
    
    std::pair <int, int> direction_x_y = Player::get_direction_x_y () ;
    
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

std::pair <int, int> Player::get_direction_x_y ()
{
    
    std::pair <int, int> direction_x_y ;
    
    if ( element_attracting_the_player -> left_boundary_x
        < element_attracting_the_player -> right_boundary_x )
    {
        direction_x_y .first = 1 ;
    }
    else if ( element_attracting_the_player -> left_boundary_x
        > element_attracting_the_player -> right_boundary_x )
    {
        direction_x_y .first = -1 ;
    }
    else if ( element_attracting_the_player -> left_boundary_x
        == element_attracting_the_player -> right_boundary_x )
    {
        direction_x_y .first = 0 ;
    }
    
    
    if ( element_attracting_the_player -> right_boundary_y
        < element_attracting_the_player -> left_boundary_y )
    {
        direction_x_y .second = -1 ;
    }
    else if ( element_attracting_the_player -> right_boundary_y 
        > element_attracting_the_player -> left_boundary_y )
    {
        direction_x_y .second = 1 ;
    }
    else if ( element_attracting_the_player -> right_boundary_y 
        == element_attracting_the_player -> left_boundary_y )
    {
        direction_x_y .second = 0 ;
    }
    
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

    std::pair <float, float> speed_x_y = get_speed ( element_attracting_the_player ) ;

    speed_x_y = smoothen_landing ( speed_x_y ) ;

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
    std::vector<int> distance_to_element ;

    for (int i = 0 ; i < elements .size() ; i++ )
    {
        if ( elements [ i ] .horizontal == true )
        {
            distance_to_element .push_back ( elements [ i ] .right_boundary_y - y ) ;
        }

        if ( elements [ i ] .horizontal == false )
        {
            distance_to_element .push_back ( elements [ i ] .left_boundary_x - x ) ;
        }
    }

    std::vector<int>::iterator iterator_of_minimum = std::min_element (
        distance_to_element .begin(), distance_to_element .end() ) ;

    int address_of_minimum = std::distance ( distance_to_element .begin(),
            iterator_of_minimum ) ;

    if ( ! ( * element_attracting_the_player == elements [ address_of_minimum ] ) )
    {
        gravity_changed = true ;
    }

    element_attracting_the_player = new Attracting_element ( elements [ address_of_minimum ] ) ;
}


std::pair <float, float> Player::get_speed ( Attracting_element * element )
{
    std::pair <float, float> speed_x_y ;
 
    if ( x > element -> right_boundary_x )
    {
        speed_x_y .first = -10 ;
    }
    else if ( x < element -> left_boundary_x )
    {
        speed_x_y .first = 10 ;
    }
    else speed_x_y .first = 0 ;

    if ( y > element -> left_boundary_y )
    {
        speed_x_y .second = -10 ;
    }
    else if ( y < element -> right_boundary_y )
    {
        speed_x_y .second = 10 ;
    }
    else speed_x_y .second = 0 ;

    return speed_x_y ;
}

std::pair <float, float> Player::smoothen_landing ( std::pair <float, float> speed_x_y )
{
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
    float difference_between_x = element_attracting_the_player->right_boundary_x - x ;
    float difference_between_y = element_attracting_the_player->right_boundary_y - y ;
    
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
    cout << *element_attracting_the_player ;
    cout << "X player: " << x << endl << "Y player: " << y << endl ;
    cout << "Ratio player X: " << x_ratio_for_one_y << endl ;
    cout << "Ratio player Y: " << y_ratio_for_one_x << endl << endl << endl ;
    */
    
    std::pair <float, float> player_ratios_x_y = std::pair<float, float> ( x_ratio_for_one_y, y_ratio_for_one_x ) ;
    
    return player_ratios_x_y ;
}
    
