/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.h
 * Author: hwalog
 *
 * Created on April 12, 2020, 10:49 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "attracting_element.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <vector>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <numeric>

// Extern to avoid multiple definitions
// Source: http://www.cplusplus.com/forum/unices/5784/#msg25741 (jsmith answer)
extern unsigned char key [ ALLEGRO_KEY_MAX ] ;

class Player
{
    
public : 
    
    float x, y ;
    bool is_in_jump ;
    int jump_timer ;
    std::vector < Attracting_element > list_of_elements_attracting_the_player ;
    bool gravity_changed ;
    bool can_jump ;
    bool done ;
    
    const int number_of_frames_in_a_jump = 5 ;
    
    
    Player ( std::vector < Attracting_element > list_of_elements_attracting_the_player ) ;
    
    void move () ;
    
    std::pair <float, float> get_direction_x_y () ;
    
    void jump ( ALLEGRO_TIMER * timer ) ;
    
    void gravity ( std::vector<Attracting_element> elements ) ;

    void verify_if_player_can_jump () ;
    
    void get_closest_elements ( std::vector < Attracting_element > list_of_attracting_elements ) ;
    
    std::pair <float, float> get_speed () ;
    
    std::pair < float, float > calculate_distance_between_the_player_and_the_first_attracting_element () ;
    
    std::pair <float, float> smoothen_landing ( std::pair <float, float> speed_x_y ) ;
    
    void draw_player () ;
    
    void print_above_player ( std::string text ) ;
} ;

float calculate_ratio ( float x_static, float y_static, float x_moving, float y_moving ) ;

#endif /* PLAYER_H */

