// DO NOT EDIT REST OF THE FILE
// ONLY WRITE CODE BELOW THE "WRITE BELOW" COMMENTS

#include<cmath>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<iostream>

int main() {
    // You are required to create the matrices for 
    // the mentioned questions and print them to 
    // std::cout

    // Question 1
    // *****************************TODO***********************************


    std::cout << "Question 1\n" << std::endl;
    std::cout << "The point first rotates 90 degree clockwise, and then move down 2 units then right 2 units.\n";

    //---------------------------------------------------------------------
    // Question 2
    std::cout << "Question 2\n------------------------" << std::endl;
    // matrix definition for Question 2
    Eigen::Matrix3f rot_45;

    // Write the 3×3 transformation matrix for a 45 degrees
    // clockwise rotation in 2D (assuming homogeneous coordinates) 
    // Use the << operator to create the rot_45 matrix (WRITE BELOW)
    // DONT PRINT TO stdout
    // *****************************TODO***********************************
    rot_45 <<
        1 / sqrt(2),  1 / sqrt(2), 0.0,
        -1 / sqrt(2), 1 / sqrt(2), 0.0,
        0.0, 0.0, 1.0;

    std::cout << rot_45 << std::endl;
    std::cout << "------------------------\n";
    
    //---------------------------------------------------------------------
    // Question 3
    std::cout << "Question 3\n------------------------" << std::endl;

    // matrix definition for Question 3
    Eigen::Matrix4f translation;

    // Write the 4×4 transform matrix to move a point by (-2,8,3)
    // Use the << operator to create the translation matrix (WRITE BELOW)
    // *****************************TODO***********************************
    translation << 
        1.0, 0.0, 0.0, -2.0, 
        0.0, 1.0, 0.0, 8.0,
        0.0, 0.0, 1.0, 3.0,
        0.0, 0.0, 0.0, 1.0;
    std::cout << translation << std::endl;
    std::cout << "------------------------\n";

    //---------------------------------------------------------------------
    // Question 4
    std::cout << "Question 4\n------------------------" << std::endl;
    
    // Define and create (using << operator) the matrices here. 
    // Make sure that they have the correct dimensions and ordering.
    Eigen::Matrix3f Q4_Step_a, Q4_Step_b, Q4_Step_c, Q4_Step_d;
    Q4_Step_a <<
        1.0, 0.0, -1.0,
        0.0, 1.0, -5.0,
        0.0, 0.0, 1.0;

    Q4_Step_b <<
        2.0, 0.0, 0.0,
        0.0, 1.0/3.0, 0.0,
        0.0, 0.0, 1.0;

    Q4_Step_c <<
        1.0, 0.0, 2.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0;

    Q4_Step_d = Q4_Step_c * Q4_Step_b * Q4_Step_a; 
    // Print the initail transformation matrices and the final transformation 
    //  matrix to std out below
    // *****************************TODO***********************************
    std::cout << "4a: 'Translate to the Origin' Transformation Matrix:" << std::endl;
    std::cout << "'translate_to_origin' matrix TODO" << std::endl;
    std::cout << Q4_Step_a << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "4b: 'Scale to Target Rectangle Size' Transformation Matrix:" << std::endl;
    std::cout << "'scale' matrix TODO" << std::endl;
    std::cout << Q4_Step_b << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "4c: 'Translate to New Target Position' Transformation Matrix:" << std::endl;
    std::cout << "'translate_to_target_pos' matrix TODO" << std::endl;
    std::cout << Q4_Step_c << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "4d: Multiplication Result of 3 Transformation Matrices:" << std::endl;
    std::cout << "'final_transform' matrix TODO" << std::endl;
    std::cout << Q4_Step_d << std::endl;
    std::cout << "\n" << std::endl;

    return 0;
}
