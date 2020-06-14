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

// Extern to avoid multiple definitions
// Source: http://www.cplusplus.com/forum/unices/5784/#msg25741 (jsmith answer)
extern unsigned char key [ ALLEGRO_KEY_MAX ] ;

class Player
{
    
public : 
    
    float x, y ;
    bool is_in_jump ;
    int jump_timer ;
    Attracting_element * element_attracting_the_player ;
    bool gravity_changed ;
    bool can_jump ;
    bool done ;
    
    const int number_of_frames_in_a_jump = 20 ;
    
    
    Player ( Attracting_element * element ) ;
    
    void move () ;
    
    std::pair <float, float> get_direction_x_y () ;
    
    void jump ( ALLEGRO_TIMER * timer ) ;
    
    void gravity ( std::vector<Attracting_element> elements ) ;

    void verify_if_player_can_jump () ;
    
    void get_closest_element ( std::vector<Attracting_element> elements ) ;
    
    void get_closest_element_from_the_list ( std::vector < Attracting_element > attracting_elements ) ;
    
    void get_closest_element_from_the_list_of_elements ( std::vector < Attracting_element > list_of_attracting_elements ) ;
    
    std::pair <float, float> get_speed () ;
    
    std::pair <float, float> smoothen_landing ( std::pair <float, float> speed_x_y ) ;
    
    std::pair<float, float> get_player_ratio_depending_on_the_current_attracting_element () ;
    
    int calculate_number_of_one_unit_iterations_between_player_and_attracting_element ( Attracting_element attracting_element ) ;
    
    void print_above_player ( std::string text ) ;
} ;

float calculate_ratio ( float x_static, float y_static, float x_moving, float y_moving ) ;

#endif /* PLAYER_H */

