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

#include <iostream>
#include <string>
#include <math.h>

class Attracting_element
{
    
public:
    
    int left_boundary_x, left_boundary_y ;
    int right_boundary_x, right_boundary_y ;
    float number_of_y_for_one_x ;
    float angle ;
    bool horizontal ;
    float x_ratio_for_one_y, y_ratio_for_one_x ;
    int x_direction, y_direction ;
    
    Attracting_element () ;
    
    Attracting_element ( int left_boundary_x, int left_boundary_y,
        int right_boundary_x, int right_boundary_y ) ;
    
    Attracting_element ( Attracting_element const& element_to_copy ) ;
    
    Attracting_element& operator = ( Attracting_element const& element_to_copy ) ;
    
    bool operator == (const Attracting_element& element) ;
    
} ;

std::ostream& operator<<(std::ostream &strm, const Attracting_element &element) ;

class Linear_equation_of_attracting_element
{
public:
    
    std::string equation_string ;
    float number_of_y_for_one_x ;
    float value_of_y_when_x_is_zero ;
    
    Linear_equation_of_attracting_element ( float number_of_y_for_one_x,
        float value_of_y_when_x_is_zero ) ;
} ;

std::ostream& operator<<(std::ostream &strm, const Linear_equation_of_attracting_element &linear_equation ) ;

float calculate_number_of_y_for_one_x ( float x1, float y1, float x2, float y2 ) ;

float calculate_angle ( float x1, float y1, float x2, float y2 ) ;

Linear_equation_of_attracting_element
    calculate_linear_equation_of_element ( float x1, float y1, float x2, float y2 ) ;

float calculate_value_of_y_when_x_is_zero ( float x1, float y1, float x2, float y2,
    float number_of_y_for_one_x ) ;



#endif /* ATTRACTING_ELEMENT_H */

