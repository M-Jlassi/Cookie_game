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
    number_of_y_for_one_x = calculate_number_of_y_for_one_x (
            left_boundary_x, left_boundary_y,
            right_boundary_x, right_boundary_y
    ) ;
    
    
    
    
    
    angle = calculate_angle (
        left_boundary_x, left_boundary_y,
        right_boundary_x, right_boundary_y
    ) ;
    
    cout << "Angle" << endl ;
    cout << angle << endl << endl ;
    
    
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
    horizontal ( element_to_copy .horizontal ),
    angle ( element_to_copy .angle) {}

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
        horizontal = element_to_copy .horizontal,
        angle = element_to_copy .angle ;
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
    
    description_of_element += "Angle = " + std::to_string ( element.angle) + "\n";

    return strm << description_of_element << std::endl ;
}






float calculate_number_of_y_for_one_x ( float x1, float y1, float x2, float y2 )
{
    float distance_between_x = abs ( x1 - x2 ) ;
    
    float distance_between_y = abs ( y1 - y2 ) ;
    
    float number_of_y_for_one_x = distance_between_y / distance_between_x ;
    
    return number_of_y_for_one_x ;
}






float calculate_angle ( float x1, float y1, float x2, float y2 )
{
    float number_of_y_for_one_x = calculate_number_of_y_for_one_x ( x1, y1, x2, y2 ) ;
    
    
    int direction_x ;
    
    if ( x1 < x2 )
    {
        direction_x =  1 ;
    }
    
    if ( x1 > x2 )
    {
        direction_x =  -1 ;
    }
    
    if ( x1 == x2 )
    {
        direction_x =  0 ;
    }
    
    
    int direction_y ;
    
    if ( y1 < y2 )
    {
        direction_y =  1 ;
    }
    
    if ( y1 > y2 )
    {
        direction_y =  -1 ;
    }
    
    if ( y1 == y2 )
    {
        direction_y =  0 ;
    }
    
    
    float angle ;
    
    
    // Horizontal line
    if ( number_of_y_for_one_x == 0 )
    {
        if ( direction_x == 1 )
        {
            angle = 0 ;
        }
        
        else if ( direction_x == -1 )
        {
            angle = 1 ;
        }
    }
    
    
    // Vertical line
    else if ( std::isinf ( number_of_y_for_one_x ) )
    {
        if ( direction_y == 1 )
        {
            angle = 1.5 ;
        }
        
        else if ( direction_y == -1 )
        {
            angle = 0.5 ;
        }
    }
    
    
    // From 0 to 0.5 (between 0° to 90°)
    else if ( direction_x == 1 && direction_y == -1 )
    {
        // Case where angle is 0.25
        if ( number_of_y_for_one_x == 1 )
        {
            angle = 0.25 ;
        }
        
        // Case where angle is between 0 and 0.25 (between 0° and 45°)
        else if ( number_of_y_for_one_x < 1 )
        {
            angle = number_of_y_for_one_x / 4 ;
        }

        // Case where angle is between 0.25 and 0.5 (between 45° and 90°)
        else if ( number_of_y_for_one_x > 1 )
        {
            // Angle goes from 1 to 0
            angle = 1 / number_of_y_for_one_x ;

            // Then inverse growth of angle
            angle *= -1 ;

            // Tighten the interval from -1 to 0 to -0.25 to 0
            angle /= 4 ;

            // And make it be between 0.25 and 0.5
            angle += 0.5 ;
        }
    }
    
    
    // From 0.5 to 1 (between 90° to 180°)
    else if ( direction_x == -1 && direction_y == -1 )
    {
        // Case where angle is 0.75
        if ( number_of_y_for_one_x == 1 )
        {
            angle = 0.75 ;
        }
        
        // Case where angle is between 0.5 and 0.75 (between 90° and 135°)
        else if ( number_of_y_for_one_x > 1 )
        {
            // Angle divided so that it goes from 0 to 1
            angle = 1 / number_of_y_for_one_x ;

            // Tightening (goes from 0 to 0.25)
            angle /= 4 ;

            // Add (goes from 0.5 to 0.75)
            angle += 0.5 ;
        }

        // Case where angle is between 0.75 and 1 (between 135° and 180°)
        else if ( number_of_y_for_one_x < 1 )
        {
            // Inverse growth (goes from -1 to 0)
            angle = number_of_y_for_one_x * ( -1 ) ;

            // Angle divided from -1 to 0 to -0.25 to 0
            angle /= 4 ;

            // Add constant (from 0.75 to 1)
            angle += 1 ;
        }
    }
    
    
    
    // From 1 to 1.5 (between 180° to 270°)
    else if ( direction_x == -1 && direction_y == 1 )
    {
        // Case where angle is 1.25
        if ( number_of_y_for_one_x == 1 )
        {
            angle = 1.25 ;
        }
        
        // Case where angle is between 1 and 1.25 (between 180° and 225°)
        else if ( number_of_y_for_one_x < 1 )
        {
            // From 0 to 0.25
            angle = number_of_y_for_one_x / 4 ;

            // From 1 to 1.25
            angle += 1 ;
        }

        // Case where angle is between 1.25 and 1.5 (between 225° and 270°)
        else if ( number_of_y_for_one_x > 1 )
        {
            // From 1 to 0
            angle = 1 / number_of_y_for_one_x ;

            // From -1 to 0
            angle *= -1 ;

            // From -0.25 to 0
            angle /= 4 ;

            // From 1.5 and 1.75
            angle += 1.5 ;
        }
    }
    
    
    // From 1.5 to 2 (between 270° to 360°)
    else if ( direction_x == 1 && direction_y == 1 )
    {
        // Case where angle is 1.75
        if ( number_of_y_for_one_x == 1 )
        {
            angle = 1.75 ;
        }
        
        // Case where angle is between 1.5 and 1.75 (between 270° and 315°)
        else if ( direction_x == 1 && direction_y == 1 && number_of_y_for_one_x > 1 )
        {
            // From 0 to 1
            angle = number_of_y_for_one_x / 4 ;

            // From 0 to 0.25
            angle /= 4 ;

            // From 1.5 to 1.75
            angle += 1.5 ;
        }

        // Case where angle is between 1.75 and 2 (between 315° and 360°)
        else if ( direction_x == 1 && direction_y == 1 && number_of_y_for_one_x < 1 )
        {
            // From -1 to 0
            angle = number_of_y_for_one_x * ( -1 ) ;

            // From -0.25 to 0
            angle /= 4 ;

            // From 1.75 to 2
            angle += 2 ;
        }
    }
    
    return angle ;
}

/*
 * Logs to test angles
 * 
cout << "First quarter" << endl << endl ;

cout << "Ratio HORIZONTAL LEFT TO RIGHT" << endl << endl ;
calculate_angle ( 0, 0, 10, 0 ) ;
cout << endl << endl ;

cout << "Ratio LEFT TO RIGHT - BOTTOM TO TOP - SLOW SLOPE" << endl << endl ;
calculate_angle ( 54, 54, 542, 10 ) ;
cout << endl << endl ;

cout << "Ratio LEFT TO RIGHT - BOTTOM TO TOP - 1 SLOPE" << endl << endl ;
calculate_angle ( 10, 100, 100, 10 ) ;
cout << endl << endl ;

cout << "Ratio LEFT TO RIGHT - BOTTOM TO TOP - FAST SLOPE" << endl << endl ;
calculate_angle ( 54, 5400, 542, 10 ) ;
cout << endl << endl ;



cout << "Second quarter" << endl << endl ;

cout << "Ratio VERTICAL BOTTOM TO TOP" << endl << endl ;
calculate_angle ( 0, 100, 0, 10 ) ;
cout << endl << endl ;

cout << "Ratio RIGHT TO LEFT - BOTTOM TO TOP - FAST SLOPE" << endl << endl ;
calculate_angle ( 264, 100000, 42, 10 ) ;
cout << endl << endl ;

cout << "Ratio RIGHT TO LEFT - BOTTOM TO TOP - 1 SLOPE" << endl << endl ;
calculate_angle ( 100, 100, 10, 10 ) ;
cout << endl << endl ;

cout << "Ratio RIGHT TO LEFT - BOTTOM TO TOP - SLOW SLOPE" << endl << endl ;
calculate_angle ( 54, 5, 5, 4 ) ;
cout << endl << endl ;


cout << "Third quarter" << endl << endl ;

cout << "Ratio HORIZONTAL RIGHT TO LEFT" << endl << endl ;
calculate_angle ( 25, 0, 5, 0 ) ;
cout << endl << endl ;

cout << "Ratio RIGHT TO LEFT - TOP TO BOTTOM - SLOW SLOPE" << endl << endl ;
calculate_angle ( 264, 1, 42, 20 ) ;
cout << endl << endl ;

cout << "Ratio RIGHT TO LEFT - TOP TO BOTTOM - 1 SLOPE" << endl << endl ;
calculate_angle ( 100, 10, 10, 100 ) ;
cout << endl << endl ;

cout << "Ratio RIGHT TO LEFT - TOP TO BOTTOM - FAST SLOPE" << endl << endl ;
calculate_angle ( 54, 5, 5, 214 ) ;
cout << endl << endl ;


cout << "Fourth quarter" << endl << endl ;

cout << "Ratio VERTICAL TOP TO BOTTOM" << endl << endl ;
calculate_angle ( 10, 40, 10, 60 ) ;
cout << endl << endl ;

cout << "Ratio LEFT TO RIGHT - TOP TO BOTTOM - FAST SLOPE" << endl << endl ;
calculate_angle ( 10, 10, 100, 101 ) ;
cout << endl << endl ;

cout << "Ratio LEFT TO RIGHT - TOP TO BOTTOM - 1 SLOPE" << endl << endl ;
calculate_angle ( 10, 10, 100, 100 ) ;
cout << endl << endl ;

cout << "Ratio LEFT TO RIGHT - TOP TO BOTTOM - SLOW SLOPE" << endl << endl ;
calculate_angle ( 10, 10, 100, 99 ) ;
cout << endl << endl ;
*/


Linear_equation::Linear_equation () : number_of_y_for_one_x ( 0 ),
    value_of_y_when_x_is_zero ( 0 ), direction_x ( 1 ), direction_y ( 0 )
{
    equation_string = Linear_equation ( number_of_y_for_one_x,
        value_of_y_when_x_is_zero, direction_x, direction_y ) .equation_string ;
}


Linear_equation::Linear_equation (
    float number_of_y_for_one_x, float value_of_y_when_x_is_zero,
    int direction_x, int direction_y
) : number_of_y_for_one_x ( number_of_y_for_one_x ),
    value_of_y_when_x_is_zero ( value_of_y_when_x_is_zero ),
    direction_x ( direction_x ), direction_y ( direction_y )
{
    string x_string_representation, y_string_representation ;
    string message_for_horizontal_and_vertical_lines = "" ;
    
    if ( direction_x == 1 || direction_x == 0 )
    {
        x_string_representation = "+X" ;
        
        if ( direction_x == 0 )
        {
            if ( direction_y == 1 )
            {
                message_for_horizontal_and_vertical_lines = "where there is ( +Y )" ;
            }

            else if ( direction_y == -1 )
            {
                message_for_horizontal_and_vertical_lines = "where there is ( -Y )" ;
            }
        }
    }

    else if ( direction_x == -1 )
    {
        x_string_representation = "-X" ;
    }
    
    
    
    
    if ( direction_y == 1 || direction_y == 0 )
    {
        y_string_representation = "+Y" ;
        
        if ( direction_y == 0 )
        {
            if ( direction_x == 1 )
            {
                message_for_horizontal_and_vertical_lines = "where there is ( +X )" ;
            }

            else if ( direction_x == -1 )
            {
                message_for_horizontal_and_vertical_lines = "where there is ( -X )" ;
            }
        }
    }

    else if ( direction_y == -1 )
    {
        y_string_representation = "-Y" ;
    }
    
    
    
    
    if ( number_of_y_for_one_x == 0 )
    {        
        equation_string = y_string_representation + " =" ;
    }
    
    else if ( std::isinf ( number_of_y_for_one_x ) )
    {
        equation_string = x_string_representation + " =" ;
    }

    else
    {
        equation_string = y_string_representation + " = " ;
        equation_string += std::to_string ( number_of_y_for_one_x ) + " * " ;
        equation_string += "( " + x_string_representation + " )" ;
    }

    string string_value_of_y_when_x_is_zero = std::to_string ( value_of_y_when_x_is_zero ) ;

    equation_string += value_of_y_when_x_is_zero >= 0
        ? " + " + string_value_of_y_when_x_is_zero
        : " - " + string_value_of_y_when_x_is_zero .substr ( 1, string_value_of_y_when_x_is_zero .length () - 1 ) ;
    
    if ( direction_x == 0 || direction_y == 0 )
    {
        equation_string += " " + message_for_horizontal_and_vertical_lines ;
    }
}

/*
Linear_equation Linear_equation ( float x, float y, float number_of_y_for_one_x,
    int direction_x, int direction_y ) :
    number_of_y_for_one_x ( number_of_y_for_one_x ), direction_x ( direction_x ),
    direction_y ( direction_y )
{}*/


Linear_equation calculate_linear_equation_with_one_coordinate ( float x1, float y1,
    int direction_x, int direction_y, float number_of_y_for_one_x )
{
    float x2 = x1 + ( direction_x * 1 ) ;
    float y2 = y1 + ( direction_y * number_of_y_for_one_x ) ;
    
    return calculate_linear_equation_of_element ( x1, y1, x2, y2 ) ;
}



std::ostream& operator<<( std::ostream &strm, const Linear_equation &linear_equation )
{
    string description_of_element = "Linear_equation: " ;
    description_of_element += linear_equation .equation_string ;
            
    return strm << description_of_element << std::endl ;
}



Linear_equation calculate_linear_equation_of_element ( float x1, float y1, float x2, float y2 )
{
    /*
    cout << "Points" << encalculate_x_and_y_to_add_for_a_one_unit_movementdl << endl ;
    cout << "X1: " << x1 << endl ;
    cout << "Y1: " << y1 << endl ;
    cout << "X2: " << x2 << endl ;
    cout << "Y2: " << y2 << endl ;
    */
    
    int direction_x, direction_y ;
    
    if ( x1 < x2 )
    {
        direction_x = 1 ;
    }
    
    else if ( x1 > x2 )
    {
        direction_x = -1 ;
    }
    
    else if ( x1 == x2 )
    {
        direction_x = 0 ;
    }
    
    
    if ( y1 < y2 )
    {
        direction_y = 1 ;
    }
    
    else if ( y1 > y2 )
    {
        direction_y = -1 ;
    }
    
    else if ( y1 == y2 )
    {
        direction_y = 0 ;
    }
    
    // In the form y = ax + b where a is "number_of_y_for_one_x" and b is "value_of_y_when_x_is_zero"
    float number_of_y_for_one_x = calculate_number_of_y_for_one_x ( x1, y1, x2, y2 ) ;
    
    float value_of_y_when_x_is_zero = calculate_value_of_y_when_x_is_zero ( 
        x1, y1, x2, y2, number_of_y_for_one_x
    ) ;
    
    Linear_equation linear_equation = Linear_equation (
        number_of_y_for_one_x, value_of_y_when_x_is_zero, direction_x, direction_y
    ) ;
    
    return linear_equation ;
}


float calculate_value_of_y_when_x_is_zero ( float x1, float y1, float x2, float y2,
    float number_of_y_for_one_x )
{
    
    float value_of_y_when_x_is_zero ;
    
    // Vertical element
    if ( abs ( x1 - x2 ) == 0 )
    {
        value_of_y_when_x_is_zero = x1 ;
    }
    
    else
    {
        // Directions of X and Y go in the same way (1 and 1, or -1 and -1)
        // Or if direction of Y is 0
        if ( ( x1 - x2 ) > 0 && ( y1 - y2 ) > 0
            || ( x1 - x2 ) < 0 && ( y1 - y2 ) < 0
            || abs ( y1 - y2 ) == 0 )
        {
            value_of_y_when_x_is_zero = y1 - ( number_of_y_for_one_x * x1 ) ;
        }
        
        // Directions of X and Y go in opposite ways (-1 and 1, or 1 and -1)
        else if ( ( x1 - x2 ) < 0 && ( y1 - y2 ) > 0
            || ( x1 - x2 ) > 0 && ( y1 - y2 ) < 0 )
        {
            value_of_y_when_x_is_zero = y1 + ( number_of_y_for_one_x * x1 ) ;
        }
    }
    
    return value_of_y_when_x_is_zero ;
}


Linear_equation calculate_perpendicular_linear_equation (
    float x1, float y1, float x2, float y2
)
{
    Linear_equation linear_equation_of_element
        = calculate_linear_equation_of_element ( x1, y1, x2, y2 ) ;
    
    
    int perpendicular_direction_x, perpendicular_direction_y ;
    
    if ( linear_equation_of_element .direction_x == 1 )
    {
        if ( linear_equation_of_element .direction_y == 1 )
        {
            perpendicular_direction_x = 1 ;
            perpendicular_direction_y = -1 ;
        }
        
        else if ( linear_equation_of_element .direction_y == -1 )
        {
            perpendicular_direction_x = -1 ;
            perpendicular_direction_y = -1 ;
        }
        
        else if ( linear_equation_of_element .direction_y == 0 )
        {
            perpendicular_direction_x = 0 ;
            perpendicular_direction_y = -1 ;
        }
    }
    
    else if ( linear_equation_of_element .direction_x == -1 )
    {
        if ( linear_equation_of_element .direction_y == 1 )
        {
            perpendicular_direction_x = 1 ;
            perpendicular_direction_y = 1 ;
        }
        
        else if ( linear_equation_of_element .direction_y == -1 )
        {
            perpendicular_direction_x = -1 ;
            perpendicular_direction_y = 1 ;
        }
        
        else if ( linear_equation_of_element .direction_y == 0 )
        {
            perpendicular_direction_x = 0 ;
            perpendicular_direction_y = 1 ;
        }
    }
    
    else if ( linear_equation_of_element .direction_x == 0 )
    {
        if ( linear_equation_of_element .direction_y == 1 )
        {
            perpendicular_direction_x = 1 ;
            perpendicular_direction_y = 0 ;
        }
        
        else if ( linear_equation_of_element .direction_y == -1 )
        {
            perpendicular_direction_x = -1 ;
            perpendicular_direction_y = 0 ;
        }
    }
    
    float perpendicular_number_of_y_for_one_x
        = ( 1 / linear_equation_of_element .number_of_y_for_one_x ) ;
    
    
    float perpendicular_value_of_y_when_x_is_zero =
        calculate_value_of_y_when_x_is_zero (
            x1, y1,
            x1 + ( perpendicular_direction_x * ( 1 / perpendicular_number_of_y_for_one_x ) ),
            y1 + ( perpendicular_direction_y * perpendicular_number_of_y_for_one_x ),
            perpendicular_number_of_y_for_one_x
        ) ;
    
    Linear_equation perpendicular_linear_equation
        = Linear_equation (
            perpendicular_number_of_y_for_one_x,
            perpendicular_value_of_y_when_x_is_zero,
            perpendicular_direction_x,
            perpendicular_direction_y
        ) ;
    
    return perpendicular_linear_equation ;
}



bool Linear_equation::point_is_to_the_left_of_the_line ( float x, float y )
{    
    if ( direction_x != 0 && direction_y != 0 )
    {
        float value_of_y_if_x_is_on_the_line = calculate_value_of_y_if_x_is_on_the_line ( x ) ;

        
        // Verify if the real point is to the left of the line
        
        // If the line goes from left to right, the hypothetic point should be beneath the real point
        
        if ( direction_x == 1 )
        {
            if ( value_of_y_if_x_is_on_the_line > y )
            {
                return true ;
            }
        }
        
        // If the line goes from right to left, the hypothetic point should be above the real point
        
        else if ( direction_x == -1 )
        {
            if ( value_of_y_if_x_is_on_the_line < y )
            {
                return true ;
            }
        }
    }
    
    
    
    else if ( direction_x == 0 )
    {
        // Vertical from top to bottom
        
        if ( direction_y == 1 )
        {
            if ( x > value_of_y_when_x_is_zero )
            {
                return true ;
            }
        }
        
        // Vertical from bottom to top
        
        if ( direction_y == -1 )
        {
            if ( x < value_of_y_when_x_is_zero )
            {
                return true ;
            }
        }
    }
    
    
    
    else if ( direction_y == 0 )
    {
        // Horizontal from left to right
        
        if ( direction_x == 1 )
        {
            if ( y < value_of_y_when_x_is_zero )
            {
                return true ;
            }
        }
        
        // Horizontal from right to left
        
        if ( direction_x == -1 )
        {
            if ( y > value_of_y_when_x_is_zero )
            {
                return true ;
            }
        }
    }
    
    
    return false ;
}



float Linear_equation::calculate_value_of_y_if_x_is_on_the_line ( float x )
{
    // Calculate the hypothetic value of Y with the linear equation
    
    float value_of_y_if_x_is_on_the_line ;

    // If X and Y have the same direction, the slope of the line goes downwards
    // The Y we want to calculate will increase when X increases

    if ( direction_x == direction_y )
    {
        value_of_y_if_x_is_on_the_line =
            ( number_of_y_for_one_x * x )
            + value_of_y_when_x_is_zero ;
    }

    // If X and Y have opposite directions, the slope of the line goes upwards
    // The Y we want to calculate will decrease when X increases

    else if ( direction_x == ( -1 ) * direction_y )
    {
        value_of_y_if_x_is_on_the_line =
            ( number_of_y_for_one_x * ( -1 ) * x )
            + value_of_y_when_x_is_zero ;
    }
    
    
    return value_of_y_if_x_is_on_the_line ;
}



bool Linear_equation::point_is_on_the_line ( float x, float y )
{
    if ( direction_x != 0 && direction_y != 0 )
    {
        float value_of_y_if_x_is_on_the_line = calculate_value_of_y_if_x_is_on_the_line ( x ) ;

        if ( value_of_y_if_x_is_on_the_line == y )
        {
            return true ;
        }
    }
    
    // Vertical line: X is constant
    
    else if ( direction_x == 0 )
    {
        if ( value_of_y_when_x_is_zero == x )
        {
            return true ;
        }
    }
    
    // Horizontal line: Y is constant
    
    else if ( direction_y == 0 )
    {
        if ( value_of_y_when_x_is_zero == y )
        {
            return true ;
        }
    }
    
    
    return false ;
}



Linear_equation Linear_equation::calculate_line_going_in_the_opposite_direction ()
{
    int opposite_line_direction_x = ( -1 ) * direction_x ;
    int opposite_line_direction_y = ( -1 ) * direction_y ;
    
    return Linear_equation ( number_of_y_for_one_x, value_of_y_when_x_is_zero,
        opposite_line_direction_x, opposite_line_direction_y ) ;
}



std::pair<float, float> Linear_equation::calculate_x_and_y_to_add_for_a_one_unit_movement ()
{
    std::pair<float, float> x_and_y ;
    
    // Vertical line
    
    if ( std::isinf ( number_of_y_for_one_x ) )
    {
        x_and_y .first = 0 ;
        x_and_y .second = direction_y * 1 ;
    }
    
    // Horizontal line
    
    else if ( number_of_y_for_one_x == 0 )
    {
        x_and_y .first = direction_x * 1 ;
        x_and_y .second = 0 ;
    }
    
    else
    {
        /*
        * We try to solve x² + y² = 1
        * With y² = ( number_of_y_for_one_x * x )²
        * 
        * Total of sum:
        * Then we have x² + ( number_of_y_for_one_x * x )² = 1
        * So this is ( 1 + number_of_y_for_one_x ) * x² = 1
        * 
        * X for a one unit movement:
        * x² = 1 / ( 1 + number_of_y_for_one_x )
        * 
        * Y for a one unit movement:
        * y = number_of_y_for_one_x * x ;
        */
        
        
        float x_squared = 1 ;
        float y_squared = ( number_of_y_for_one_x * x_squared ) *
            ( number_of_y_for_one_x * x_squared ) ;

        float total_of_sum = x_squared + y_squared ;

        float x_squared_for_a_one_unit_movement = 1 / total_of_sum ;
        float x_for_a_one_unit_movement = sqrt ( x_squared_for_a_one_unit_movement ) ;

        float y_for_a_one_unit_movement =
            number_of_y_for_one_x * x_for_a_one_unit_movement ;
        
    
        x_and_y .first = direction_x * x_for_a_one_unit_movement ;
        x_and_y .second = direction_y * y_for_a_one_unit_movement ;
    }

    
    return x_and_y ;
}