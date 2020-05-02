/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "attracting_element.h"

using namespace std ;
    
Attracting_element::Attracting_element () : left_boundary_x ( 0 ),
    left_boundary_y ( 0 ), right_boundary_x ( 0 ), right_boundary_y ( 0 ) {}

Attracting_element::Attracting_element ( int left_boundary_x, int left_boundary_y,
    int right_boundary_x, int right_boundary_y ) : left_boundary_x ( left_boundary_x ),
    left_boundary_y ( left_boundary_y ), right_boundary_x ( right_boundary_x ),
    right_boundary_y ( right_boundary_y )
{
    if ( right_boundary_y == left_boundary_y )
    {
        horizontal = true ;
    }

    if ( left_boundary_x == right_boundary_x )
    {
        horizontal = false ;
    }
    
    
    
    
    float difference_between_x = abs ( right_boundary_x - left_boundary_x ) ;
    float difference_between_y = abs ( right_boundary_y - left_boundary_y ) ;
    
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
    
    
    
    
    if ( left_boundary_x < right_boundary_x )
    {
        x_direction = 1 ;
    }
    
    else if ( left_boundary_x > right_boundary_x )
    {
        x_direction = -1 ;
    }
    
    else
    {
        x_direction = 0 ;
    }
    
    
    
    if ( left_boundary_y < right_boundary_y )
    {
        y_direction = 1 ;
    }
    
    else if ( left_boundary_y > right_boundary_y )
    {
        y_direction = -1 ;
    }
    
    else
    {
        y_direction = 0 ;
    }
    
}

Attracting_element::Attracting_element ( Attracting_element const& element_to_copy ) :
    left_boundary_x ( element_to_copy .left_boundary_x ),
    left_boundary_y ( element_to_copy .left_boundary_y ),
    right_boundary_x ( element_to_copy .right_boundary_x ),
    right_boundary_y ( element_to_copy .right_boundary_y ),
    x_ratio_for_one_y ( element_to_copy .x_ratio_for_one_y ),
    y_ratio_for_one_x ( element_to_copy .y_ratio_for_one_x ),
    x_direction ( element_to_copy .x_direction ),
    y_direction ( element_to_copy .y_direction ),
    horizontal ( element_to_copy .horizontal ) {}

Attracting_element& Attracting_element::operator = ( Attracting_element const& element_to_copy )
{
    if ( ! ( this == & element_to_copy ) )
    {
        left_boundary_x = element_to_copy .left_boundary_x ;
        right_boundary_x = element_to_copy .right_boundary_x ;
        left_boundary_y = element_to_copy .left_boundary_y ;
        right_boundary_y = element_to_copy .right_boundary_y ;
        x_ratio_for_one_y = element_to_copy .x_ratio_for_one_y ;
        y_ratio_for_one_x = element_to_copy .y_ratio_for_one_x ;
        x_direction = element_to_copy .x_direction,
        y_direction = element_to_copy .y_direction,
        horizontal = element_to_copy .horizontal ;
    }

    return *this ;
}

bool Attracting_element::operator == (const Attracting_element& element)
{    
    if ( left_boundary_x == element. left_boundary_x
        && right_boundary_x == element. right_boundary_x
        && left_boundary_y == element. left_boundary_y
        && right_boundary_y == element. right_boundary_y
        && horizontal == element .horizontal )
    {
        return true ;
    }

    return false;
}

std::ostream& operator<<(std::ostream &strm, const Attracting_element &element)
{
    string description_of_element = "Attracting element:\n" ;
    description_of_element += "X left = " + std::to_string ( element.left_boundary_x ) + "\n";
    description_of_element += "Y bottom = " + std::to_string ( element.right_boundary_y ) + "\n";
    description_of_element += "X right = " + std::to_string ( element.right_boundary_x ) + "\n";
    description_of_element += "Y top = " + std::to_string ( element.left_boundary_y ) + "\n";
    
    description_of_element += "X ratio for one Y = " + std::to_string ( element.x_ratio_for_one_y ) + "\n";
    description_of_element += "Y ratio for one X = " + std::to_string ( element.y_ratio_for_one_x ) + "\n";
    
    description_of_element += "X direction = " + std::to_string ( element.x_direction ) + "\n";
    description_of_element += "Y direction = " + std::to_string ( element.y_direction ) + "\n";
    
    description_of_element += "Horizontal? " + std::to_string ( element.horizontal ) + "\n";

    return strm << description_of_element << std::endl ;
}