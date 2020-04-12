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


class Attracting_element
{
    
public:
    
    int x_inf, y_inf ;
    int x_sup, y_sup ;
    bool horizontal ;
    
    Attracting_element () ;
    
    Attracting_element ( int x_inf, int y_inf, int x_sup, int y_sup ) ;
    
    Attracting_element ( Attracting_element const& element_to_copy ) ;
    
    Attracting_element& operator = ( Attracting_element const& element_to_copy ) ;
    
    bool operator == (const Attracting_element& element) ;
    
} ;


#endif /* ATTRACTING_ELEMENT_H */

