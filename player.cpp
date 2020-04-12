/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "player.h"


#include <vector>
#include <tuple>
#include <algorithm>



Player::Player () : x ( 100 ), y ( 150 ), is_in_jump ( false ), gravity_changed ( false ),
can_jump ( false ), done ( false ) {}


void Player::move ()
{
    if ( key [ ALLEGRO_KEY_LEFT ] )
        if ( element_attracting_the_player -> horizontal ) x -= 15 ;
        else y += 15 ;

    if ( key [ ALLEGRO_KEY_RIGHT ] )
        if ( element_attracting_the_player -> horizontal ) x += 15 ;
        else y -= 15 ;
}


void Player::jump ( ALLEGRO_TIMER * timer )
{

    int time_since_jump_instruction = al_get_timer_count ( timer ) -
        jump_timer ;

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
            if ( element_attracting_the_player -> horizontal ) y -= 20 ;
            else x -= 20 ;
        }

        return ;

    }

    if ( key [ ALLEGRO_KEY_SPACE ] )
    {
        if ( is_in_jump || ! can_jump ) return ;

        is_in_jump = true ;
        can_jump = false ;
        jump_timer = al_get_timer_count ( timer ) ;

        if ( element_attracting_the_player -> horizontal ) y -= 20 ;
        else x -= 20 ;

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
    if ( ( element_attracting_the_player -> horizontal
            && y == element_attracting_the_player -> y_inf ) 

        || ( element_attracting_the_player -> horizontal == false
            && x == element_attracting_the_player -> x_inf ) )

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
            distance_to_element .push_back ( elements [ i ] .y_inf - y ) ;
        }

        if ( elements [ i ] .horizontal == false )
        {
            distance_to_element .push_back ( elements [ i ] .x_inf - x ) ;
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

    if ( x > element -> x_sup )
    {
        speed_x_y .first = -10 ;
    }
    else if ( x < element -> x_inf )
    {
        speed_x_y .first = 10 ;
    }
    else speed_x_y .first = 0 ;

    if ( y > element -> y_sup )
    {
        speed_x_y .second = -10 ;
    }
    else if ( y < element -> y_inf )
    {
        speed_x_y .second = 10 ;
    }
    else speed_x_y .second = 0 ;

    return speed_x_y ;
}

std::pair <float, float> Player::smoothen_landing ( std::pair <float, float> speed_x_y )
{
    if ( ( speed_x_y .first > 0  &&
            x + speed_x_y .first > element_attracting_the_player -> x_inf )
        || ( speed_x_y .first < 0  &&
            x + speed_x_y .first < element_attracting_the_player -> x_sup ) )
    {
        speed_x_y .first /= 2 ;
    }

    if ( ( speed_x_y .second > 0  &&
            y + speed_x_y .second > element_attracting_the_player -> y_inf )
        || ( speed_x_y .second < 0  &&
            y + speed_x_y .second < element_attracting_the_player -> y_sup ) )
    {
        speed_x_y .second /= 2 ;
    }

    return speed_x_y ;
}
    
