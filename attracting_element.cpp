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
    
    
    linear_equation = calculate_linear_equation_of_element (
        left_boundary_x,
        left_boundary_y,
        right_boundary_x,
        right_boundary_y
    ) ;
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
    linear_equation ( element_to_copy .linear_equation ),
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
        linear_equation = element_to_copy .linear_equation,
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


Linear_equation Attracting_element :: calculate_linear_equation ()
{
    return calculate_linear_equation_of_element (
        left_boundary_x, left_boundary_y,
        right_boundary_x, right_boundary_y
    ) ;
}


// Defines the direction of the gravity

Linear_equation Attracting_element::calculate_line_going_in_the_direction_of_the_element (
        float x, float y )
{
    Linear_equation line_going_in_the_direction_of_the_element = Linear_equation () ;
    
    /* If the player crosses the linear equation of the element
     * Verify if it touches the element: return a perpendicular going below the element
     * Else: return the line going to the closest boundary
     */
    
    if ( linear_equation .point_is_on_the_line ( x, y ) )
    {
        
        
        /* This is the last case: the X and Y coordinates are between the 
         * boundaries of the element, return a perpendicular
         */
        
        if ( point_is_within_the_boundaries_of_the_element ( x, y ) )
        {
            line_going_in_the_direction_of_the_element = 
                linear_equation .calculate_perpendicular_linear_equation ( x, y )
                .calculate_line_going_in_the_opposite_direction () ;
        }
        
        else
        {
            if ( linear_equation .direction_x != 0 )
            {
                // From left to right

                if ( linear_equation .direction_x == 1 )
                {
                    // The point is to the left of the element

                    if ( x < left_boundary_x )
                    {
                        line_going_in_the_direction_of_the_element = linear_equation ;

                        return line_going_in_the_direction_of_the_element ;
                    }

                    else if ( x > right_boundary_x )
                    {
                        line_going_in_the_direction_of_the_element = linear_equation
                            .calculate_line_going_in_the_opposite_direction () ;

                        return line_going_in_the_direction_of_the_element ;
                    }
                }

                // From right to left

                else if ( linear_equation .direction_x == -1 )
                {
                    if ( x > left_boundary_x )
                    {
                        line_going_in_the_direction_of_the_element = linear_equation ;

                        return line_going_in_the_direction_of_the_element ;
                    }

                    else if ( x < right_boundary_x )
                    {
                        line_going_in_the_direction_of_the_element = linear_equation
                            .calculate_line_going_in_the_opposite_direction () ;

                        return line_going_in_the_direction_of_the_element ;
                    }
                }
            }

            // With a vertical line, verify if the Y coordinate is outside the boundaries

            else if ( linear_equation .direction_x == 1 )
            {
                if ( linear_equation .direction_y == 1 )
                {
                    if ( y < left_boundary_y )
                    {
                        line_going_in_the_direction_of_the_element = linear_equation ;

                        return line_going_in_the_direction_of_the_element ;
                    }

                    else if ( y > right_boundary_y )
                    {
                        line_going_in_the_direction_of_the_element = linear_equation
                            .calculate_line_going_in_the_opposite_direction () ;

                        return line_going_in_the_direction_of_the_element ;
                    }
                }

                else if ( linear_equation .direction_y == -1 )
                {
                    if ( y > left_boundary_y )
                    {
                        line_going_in_the_direction_of_the_element = linear_equation ;

                        return line_going_in_the_direction_of_the_element ;
                    }

                    else if ( y < right_boundary_y )
                    {
                        line_going_in_the_direction_of_the_element = linear_equation
                            .calculate_line_going_in_the_opposite_direction () ;

                        return line_going_in_the_direction_of_the_element ;
                    }
                }
            }
        }
        
        
        return line_going_in_the_direction_of_the_element ;
    }

    /*
     * Verify if the player is above the element
     * 
     * If so, locate whether the player is:
     *  Directly above: the closest way to the element will be the perpendicular to this element
     *  To the left: the closest way to the element will be in the direction of the left boundary
     *  To the right: the closest way to the element will be in the direction of the right boundary
     * 
     */


    // Player is above the element

    else if ( linear_equation .point_is_to_the_left_of_the_line ( x, y ) )
    {        
        Linear_equation left_boundary_perpendicular_to_the_attracting_element =
            linear_equation .calculate_perpendicular_linear_equation (
                left_boundary_x, left_boundary_y ) ;

        if ( left_boundary_perpendicular_to_the_attracting_element
            .point_is_on_the_line ( x, y ) )
        {
            // Reverse perpendicular until get to the element

            line_going_in_the_direction_of_the_element =
                left_boundary_perpendicular_to_the_attracting_element 
                .calculate_line_going_in_the_opposite_direction () ;
        }

        else if ( left_boundary_perpendicular_to_the_attracting_element
            .point_is_to_the_left_of_the_line (x, y ) )
        {
            // Linear_equation from the player to the left boundary position of the element

            line_going_in_the_direction_of_the_element = calculate_linear_equation_of_element (
                x, y,
                left_boundary_x,
                left_boundary_y
            ) ;
        }

        // Player is to the right of the left perpendicular

        else
        {
            /*float x_right_boundary_if_line_continues =
                right_boundary_x
                + ( linear_equation .direction_x * 1 ) ;

            float y_right_boundary_if_line_continues =
                right_boundary_y
                + ( linear_equation .direction_y
                * linear_equation .number_of_y_for_one_x ) ;
*/
            Linear_equation right_boundary_perpendicular_to_the_attracting_element =
                linear_equation .calculate_perpendicular_linear_equation (
                    right_boundary_x, right_boundary_y ) ;

            Linear_equation line_going_in_the_opposite_direction =
                right_boundary_perpendicular_to_the_attracting_element
                .calculate_line_going_in_the_opposite_direction () ;

            // The player is just above the element

            if ( right_boundary_perpendicular_to_the_attracting_element
                .point_is_to_the_left_of_the_line ( x, y ) )
            {
                line_going_in_the_direction_of_the_element =
                    calculate_linear_equation_with_one_coordinate (
                        x, y,
                        line_going_in_the_opposite_direction .direction_x,
                        line_going_in_the_opposite_direction .direction_y,
                        line_going_in_the_opposite_direction .number_of_y_for_one_x
                    ) ;
            }

            // The player is on the right boundary perpendicular

            else if ( right_boundary_perpendicular_to_the_attracting_element
                .point_is_on_the_line ( x, y ) )
            {                
                line_going_in_the_direction_of_the_element =
                    line_going_in_the_opposite_direction ;
            }

            // The player is to the right of the element

            else
            {
                line_going_in_the_direction_of_the_element =
                    calculate_linear_equation_of_element (
                        x, y,
                        right_boundary_x,
                        right_boundary_y
                    ) ;
            }
        }
    }
    
    // Player is below the element: same as above, with inverted boundaries

    else
    {
        Linear_equation left_boundary_perpendicular_to_the_reversed_attracting_element =
            linear_equation .calculate_perpendicular_linear_equation (
                right_boundary_x, right_boundary_y )
                .calculate_line_going_in_the_opposite_direction () ;

        if ( left_boundary_perpendicular_to_the_reversed_attracting_element
            .point_is_on_the_line ( x, y ) )
        {
            // Reverse perpendicular until get to the element

            line_going_in_the_direction_of_the_element =
                left_boundary_perpendicular_to_the_reversed_attracting_element 
                .calculate_line_going_in_the_opposite_direction () ;
        }

        else if ( left_boundary_perpendicular_to_the_reversed_attracting_element
            .point_is_to_the_left_of_the_line (x, y ) )
        {
            // Linear_equation from the player to the right boundary position of the element

            line_going_in_the_direction_of_the_element = calculate_linear_equation_of_element (
                x, y,
                right_boundary_x,
                right_boundary_y
            ) ;
        }

        // Player is to the right of the left perpendicular

        else
        {
            Linear_equation right_boundary_perpendicular_to_the_reversed_attracting_element =
                linear_equation .calculate_perpendicular_linear_equation (
                    left_boundary_x, left_boundary_y )
                    .calculate_line_going_in_the_opposite_direction () ;

            Linear_equation line_going_in_the_opposite_direction =
                right_boundary_perpendicular_to_the_reversed_attracting_element
                .calculate_line_going_in_the_opposite_direction () ;

            // The player is below the element, between the boundaries

            if ( right_boundary_perpendicular_to_the_reversed_attracting_element
                .point_is_to_the_left_of_the_line ( x, y ) )
            {
                line_going_in_the_direction_of_the_element =
                    calculate_linear_equation_with_one_coordinate (
                        x, y,
                        line_going_in_the_opposite_direction .direction_x,
                        line_going_in_the_opposite_direction .direction_y,
                        line_going_in_the_opposite_direction .number_of_y_for_one_x
                    ) ;
            }

            // The player is on the right boundary perpendicular

            else if ( right_boundary_perpendicular_to_the_reversed_attracting_element
                .point_is_on_the_line ( x, y ) )
            {                
                line_going_in_the_direction_of_the_element =
                    line_going_in_the_opposite_direction ;
            }

            // The player is to the left of the element

            else
            {
                line_going_in_the_direction_of_the_element =
                    calculate_linear_equation_of_element (
                        x, y,
                        left_boundary_x,
                        left_boundary_y
                    ) ;
            }
        }
    }


    return line_going_in_the_direction_of_the_element ;
}


// Function used to know if the player is above the element

bool Attracting_element :: point_is_within_the_boundaries_of_the_element ( float x, float y )
{
    // Check if the coordinates are farther than the boundaries

    // If the element has different X coordinates for left and right boundaries

    if ( linear_equation .direction_x != 0 )
    {
        // From left to right

        if ( linear_equation .direction_x == 1 )
        {
            // The point is to the left of the element

            if ( x < left_boundary_x )
            {
                return false ;
            }

            else if ( x > right_boundary_x )
            {
                return false ;
            }
        }

        // From right to left

        else if ( linear_equation .direction_x == -1 )
        {
            if ( x > left_boundary_x )
            {
                return false ;
            }

            else if ( x < right_boundary_x )
            {
                return false ;
            }
        }
    }

    // With a vertical line, verify if the Y coordinate is outside the boundaries

    else if ( linear_equation .direction_x == 1 )
    {
        if ( linear_equation .direction_y == 1 )
        {
            if ( y < left_boundary_y )
            {
                return false ;
            }

            else if ( y > right_boundary_y )
            {
                return false ;
            }
        }

        else if ( linear_equation .direction_y == -1 )
        {
            if ( y > left_boundary_y )
            {
                return false ;
            }

            else if ( y < right_boundary_y )
            {
                return false ;
            }
        }
    }
    
    return true ;
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
    value_of_y_when_x_is_zero ( 0 ), direction_x ( 0 ), direction_y ( 0 )
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


pair < float, float > calculate_the_point_of_intersection (
    Linear_equation linear_equation_1, Linear_equation linear_equation_2 )
{
    float point_of_intersection_x ;
    float point_of_intersection_y ;
    
    
    if ( linear_equation_1 .direction_y == 0 ) // Horizontal
    {
        // Lines are perpendicular
        
        if ( linear_equation_2 .direction_x == 0 ) // Vertical
        {
            point_of_intersection_y = linear_equation_1 .value_of_y_when_x_is_zero ;
            point_of_intersection_x = linear_equation_2 .value_of_y_when_x_is_zero ;
        }
        
        // Lines are not perpendicular
        
        else
        {
            point_of_intersection_y = linear_equation_1 .value_of_y_when_x_is_zero ;
            point_of_intersection_x = linear_equation_2 
                .calculate_value_of_x_if_y_is_on_the_line ( point_of_intersection_y ) ;
        }
    }
    
    else if ( linear_equation_2 .direction_y == 0 ) // Horizontal
    {
        // Lines are perpendicular 
        
        if ( linear_equation_1 .direction_x == 0 ) // Vertical
        {
            point_of_intersection_y = linear_equation_2 .value_of_y_when_x_is_zero ;
            point_of_intersection_x = linear_equation_1 .value_of_y_when_x_is_zero ;
        }
        
        // Lines are not perpendicular
        
        else
        {
            point_of_intersection_y = linear_equation_2 .value_of_y_when_x_is_zero ;
            point_of_intersection_x = linear_equation_1 
                .calculate_value_of_x_if_y_is_on_the_line ( point_of_intersection_y ) ;
        }
    }
    
    /*
     * The calculation of the point of intersection uses the following method:
     * 
     * 
     * Definition:
     * 
     * linear_equation_1: Y = a_1 * X + b_1
     * linear_equation_2: Y = a_2 * X + b_2
     * 
     * Where:
     *  a_1 is named "linear_equation_1 .number_of_y_for_one_x"
     *  a_2 is named "linear_equation_2 .number_of_y_for_one_x"
     *  b_1 is named "linear_equation_1 .value_of_y_when_x_is_zero"
     *  b_2 is named "linear_equation_2 .value_of_y_when_x_is_zero"
     * 
     * 
     * Solving:
     * 
     * linear_equation_1 = linear_equation_2 ?
     * 
     * So we isolate X:
     * 
     * a_1 * X + b_1 = a_2 * X + b_2
     * <=> a_1 * X = a_2 * X + b_2 - b_1
     * <=> a_1 * X - a_2 * X = b_2 - b_1
     * <=> ( a_1 - a_2 ) * X = b_2 - b_1
     * <=> X = ( b_2 - b_1 ) / ( a_1 - a_2 )
     */
    
    else
    {
        float number_of_y_for_one_x_oriented_1 ;

        // Slope going upward

        if ( linear_equation_1 .direction_x == (-1) * linear_equation_1 .direction_y )
        {
            number_of_y_for_one_x_oriented_1 =
                ( - 1 ) * linear_equation_1 .number_of_y_for_one_x ;
        }

        // Slope going downward
        
        else if ( linear_equation_1 .direction_x == linear_equation_1 .direction_y )
        {
            number_of_y_for_one_x_oriented_1 =
                linear_equation_1 .number_of_y_for_one_x ;
        }

        // Vertical
        
        else if ( linear_equation_1 .direction_x == 0 )
        {
            number_of_y_for_one_x_oriented_1 = 0 ;
        }


        float number_of_y_for_one_x_oriented_2 ;

        // Slope going upward

        if ( linear_equation_2 .direction_x == (-1) * linear_equation_2 .direction_y )
        {
            number_of_y_for_one_x_oriented_2 =
                ( - 1 ) * linear_equation_2 .number_of_y_for_one_x ;
        }

        // Slope going downward
        
        else if ( linear_equation_2 .direction_x == linear_equation_2 .direction_y )
        {
            number_of_y_for_one_x_oriented_2 =
                linear_equation_2 .number_of_y_for_one_x ;
        }

        // Vertical
        
        else if ( linear_equation_2 .direction_x == 0 )
        {
            number_of_y_for_one_x_oriented_2 = 0 ;
        }


        point_of_intersection_x =
            ( linear_equation_2 .value_of_y_when_x_is_zero
            - linear_equation_1 .value_of_y_when_x_is_zero )
            / ( number_of_y_for_one_x_oriented_1
            - number_of_y_for_one_x_oriented_2 ) ;
        
        point_of_intersection_y = linear_equation_1
            .calculate_value_of_y_if_x_is_on_the_line ( point_of_intersection_x ) ;
    }
    
    
    
    pair < float, float > point_of_intersection ;
    
    point_of_intersection .first = point_of_intersection_x ;
    point_of_intersection .second = point_of_intersection_y ;
    
    
    return point_of_intersection ;
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


Linear_equation Linear_equation::calculate_perpendicular_linear_equation (
    float x, float y )
{
    int perpendicular_direction_x, perpendicular_direction_y ;
    
    // From left to right
    
    if ( direction_x == 1 )
    {
        // From top to bottom
        
        if ( direction_y == 1 )
        {
            perpendicular_direction_x = 1 ; // From left to right
            perpendicular_direction_y = -1 ; // From bottom to top
        }
        
        // From bottom to top
        
        else if ( direction_y == -1 )
        {
            perpendicular_direction_x = -1 ; // From right to left
            perpendicular_direction_y = -1 ; // From bottom to top
        }
        
        // Horizontal
        
        else if ( direction_y == 0 )
        {
            perpendicular_direction_x = 0 ; // Vertical
            perpendicular_direction_y = -1 ; // From bottom to top
        }
    }
    
    // From right to left
    
    else if ( direction_x == -1 )
    {
        // From top to bottom
        
        if ( direction_y == 1 )
        {
            perpendicular_direction_x = 1 ; // From left to right
            perpendicular_direction_y = 1 ; // From top to bottom
        }
        
        // From bottom to top
        
        else if ( direction_y == -1 )
        {
            perpendicular_direction_x = -1 ; // From right to left
            perpendicular_direction_y = 1 ; // From top to bottom 
        }
        
        // Horizontal
                
        else if ( direction_y == 0 )
        {
            perpendicular_direction_x = 0 ; // Vertical
            perpendicular_direction_y = 1 ; // From top to bottom
        }
    }
    
    // Vertical
    
    else if ( direction_x == 0 )
    {
        // From top to bottom
        
        if ( direction_y == 1 )
        {
            perpendicular_direction_x = 1 ; // From left to right
            perpendicular_direction_y = 0 ; // Horizontal
        }
        
        // From bottom to top
        
        else if ( direction_y == -1 )
        {
            perpendicular_direction_x = -1 ; // From right to left
            perpendicular_direction_y = 0 ; // Horizontal
        }
    }
    
    float perpendicular_number_of_y_for_one_x
        = ( 1 / number_of_y_for_one_x ) ;
    
    
    float perpendicular_value_of_y_when_x_is_zero =
        calculate_value_of_y_when_x_is_zero (
            x, y,
            x + ( perpendicular_direction_x * ( 1 / perpendicular_number_of_y_for_one_x ) ),
            y + ( perpendicular_direction_y * perpendicular_number_of_y_for_one_x ),
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
    
    // Horizontal
    
    else if ( direction_y == 0 )
    {
        value_of_y_if_x_is_on_the_line = value_of_y_when_x_is_zero ;
    }
    
    // Vertical: any value of Y can be chosen
    
    else if ( direction_x == 0 )
    {
        value_of_y_if_x_is_on_the_line = 0 ;
    }
    
    
    return value_of_y_if_x_is_on_the_line ;
}


float Linear_equation :: calculate_value_of_x_if_y_is_on_the_line ( float y )
{    
    /*
     * The linear equation is in the form Y = a * X + b
     *  Where a is "number_of_y_for_one_x" and b is "value_of_y_when_x_is_zero"
     * 
     * We find X by doing the following:
     *  Y - b = a * X
     *  <=> X = ( Y - b ) / a 
     */
    
    float number_of_y_for_one_x_oriented ;
    
    if ( direction_x == direction_y )
    {
        number_of_y_for_one_x_oriented = number_of_y_for_one_x ;
    }
    
    if ( direction_x == ( -1 ) * direction_y )
    {
        number_of_y_for_one_x_oriented = ( -1 ) * number_of_y_for_one_x ;
    }
    
    float value_of_x_if_y_is_on_the_line = 
        ( y - value_of_y_when_x_is_zero )
        / number_of_y_for_one_x_oriented ;
    
    return value_of_x_if_y_is_on_the_line ;
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






void draw_map ( std :: vector < Attracting_element > elements_of_the_map )
{
    for ( int i = 0 ; i < elements_of_the_map .size () ; i ++ )
    {
        al_draw_line ( elements_of_the_map [ i ] .left_boundary_x,
            elements_of_the_map [ i ] .left_boundary_y,
            elements_of_the_map [ i ] .right_boundary_x,
            elements_of_the_map [ i ] .right_boundary_y,
            al_map_rgb_f ( 0.35, 0.35, 0.35 ), 3 ) ;
    }
    
    return ;
}