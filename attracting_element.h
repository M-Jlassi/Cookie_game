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

class Attracting_element
{
    
public:
    
    int left_boundary_x, left_boundary_y ;
    int right_boundary_x, right_boundary_y ;
    bool horizontal ;
    float x_ratio_for_one_y, y_ratio_for_one_x ;
    
    Attracting_element () ;
    
    Attracting_element ( int left_boundary_x, int left_boundary_y,
        int right_boundary_x, int right_boundary_y ) ;
    
    Attracting_element ( Attracting_element const& element_to_copy ) ;
    
    Attracting_element& operator = ( Attracting_element const& element_to_copy ) ;
    
    bool operator == (const Attracting_element& element) ;
    
} ;

std::ostream& operator<<(std::ostream &strm, const Attracting_element &element) ;


#endif /* ATTRACTING_ELEMENT_H */

