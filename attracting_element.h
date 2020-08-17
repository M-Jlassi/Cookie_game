/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   attracting_element.h
 * Author: hwalog
 *
 * Created on April 12, 2020, 11:01 PM
 */

#ifndef ATTRACTING_ELEMENT_H
#define ATTRACTING_ELEMENT_H

#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <string>
#include <math.h>
#include <vector>


class Linear_equation
{
public:
    
    std::string equation_string ;
    float number_of_y_for_one_x ;
    float value_of_y_when_x_is_zero ;
    int direction_x, direction_y ;
    
    Linear_equation () ;
    
    Linear_equation ( float number_of_y_for_one_x,
        float value_of_y_when_x_is_zero, int direction_x, int direction_y ) ;
    
    bool point_is_to_the_left_of_the_line ( float x, float y ) ;
    
    bool point_is_on_the_line ( float x, float y ) ;
    
    float calculate_value_of_y_if_x_is_on_the_line ( float x ) ;
    
    float calculate_value_of_x_if_y_is_on_the_line ( float y ) ;
    
    Linear_equation calculate_perpendicular_linear_equation (
        float x, float y ) ;
    
    Linear_equation calculate_line_going_in_the_opposite_direction () ;

    std::pair <float, float> calculate_x_and_y_to_add_for_a_one_unit_movement () ;
} ;

Linear_equation calculate_linear_equation_with_one_coordinate ( float x1, float y1,
    int direction_x, int direction_y, float number_of_y_for_one_x ) ;


std :: pair < float, float > calculate_the_point_of_intersection (
    Linear_equation linear_equation_1, Linear_equation linear_equation_2 ) ;

std::ostream& operator<<(std::ostream &strm, const Linear_equation &linear_equation ) ;

float calculate_number_of_y_for_one_x ( float x1, float y1, float x2, float y2 ) ;

float calculate_angle ( float x1, float y1, float x2, float y2 ) ;

Linear_equation
    calculate_linear_equation_of_element ( float x1, float y1, float x2, float y2 ) ;

float calculate_value_of_y_when_x_is_zero ( float x1, float y1, float x2, float y2,
    float number_of_y_for_one_x ) ;


class Attracting_element
{
    
public:
    
    float left_boundary_x, left_boundary_y ;
    float right_boundary_x, right_boundary_y ;
    float number_of_y_for_one_x ;
    float angle ;
    bool horizontal ;
    float x_ratio_for_one_y, y_ratio_for_one_x ;
    int x_direction, y_direction ;
    Linear_equation linear_equation ;
    
    Attracting_element () ;
    
    Attracting_element ( int left_boundary_x, int left_boundary_y,
        int right_boundary_x, int right_boundary_y ) ;
    
    Attracting_element ( Attracting_element const& element_to_copy ) ;
    
    Attracting_element& operator = ( Attracting_element const& element_to_copy ) ;
    
    bool operator == (const Attracting_element& element) ;
    
    Linear_equation calculate_linear_equation () ;
    
    Linear_equation calculate_line_going_in_the_direction_of_the_element (
        float x, float y ) ;
    
    bool point_is_within_the_boundaries_of_the_element ( float x, float y ) ;
    
} ;

std::ostream& operator<<(std::ostream &strm, const Attracting_element &element) ;

void draw_map ( std :: vector < Attracting_element > elements_of_the_map ) ;

bool floats_are_equal_with_1_decimal_precision ( float number1, float number2 ) ;


#endif /* ATTRACTING_ELEMENT_H */

