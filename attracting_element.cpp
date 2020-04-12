/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "attracting_element.h"
    
Attracting_element::Attracting_element () : x_inf(0), y_inf(0), x_sup(0), y_sup(0) {}

Attracting_element::Attracting_element ( int x_inf, int y_inf, int x_sup, int y_sup ) :
x_inf ( x_inf ), y_inf ( y_inf ), x_sup ( x_sup ), y_sup ( y_sup )
{
    if ( y_inf == y_sup )
    {
        horizontal = true ;
    }

    if ( x_inf == x_sup )
    {
        horizontal = false ;
    }
}

Attracting_element::Attracting_element ( Attracting_element const& element_to_copy ) :
    x_inf ( element_to_copy .x_inf ), y_inf ( element_to_copy .y_inf ),
    x_sup ( element_to_copy .x_sup ), y_sup ( element_to_copy .y_sup ),
    horizontal ( element_to_copy .horizontal ) {}

Attracting_element& Attracting_element::operator = ( Attracting_element const& element_to_copy )
{
    if ( ! ( this == & element_to_copy ) )
    {
        x_inf = element_to_copy .x_inf ;
        y_inf = element_to_copy .y_inf ;
        x_sup = element_to_copy .x_sup ;
        y_sup = element_to_copy .y_sup ;
        horizontal = element_to_copy .horizontal ;
    }

    return *this ;
}

bool Attracting_element::operator == (const Attracting_element& element)
{    
    if ( x_inf == element. x_inf
        && x_sup == element. x_sup
        && y_inf == element. y_inf
        && y_sup == element. y_sup
        && horizontal == element .horizontal )
    {
        return true ;
    }

    return false;
}