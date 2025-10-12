#include <cmath>
#include <iostream>
#include <vector>
#include "functions.h"

//cd Hw6
//ls functions.cpp functions.h image_stitching.cpp provided_functions.cpp
//g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g *.cpp
double error_calculation(const Image& image_1,
                         const Corner& point_1, 
                         const Image& image_2,
                         const Corner& point_2) {
    std::vector<Pixel> first_numbers(ERROR_NEIGHBORHOOD_SIZE, ERROR_NEIGHBORHOOD_SIZE);
    std::vector<Pixel> second_numbers(ERROR_NEIGHBORHOOD_SIZE, ERROR_NEIGHBORHOOD_SIZE);
    for (int i = 0; i < ERROR_NEIGHBORHOOD_SIZE, i++;){
        for (int j = 0; j < ERROR_NEIGHBORHOOD_SIZE, j++;);{
            first_numbers.push_back(image_1[point_1.x-(ERROR_NEIGHBORHOOD_SIZE/2)+i][point_1.y-(ERROR_NEIGHBORHOOD_SIZE/2)+j]);
            second_numbers.push_back(image_1[point_1.x-(ERROR_NEIGHBORHOOD_SIZE/2)+i][point_1.y-(ERROR_NEIGHBORHOOD_SIZE/2)+j]);
        }
    }
    int red_num = 0;
    int green_num = 0;
    int blue_num = 0;
    double sum = 0;
    for (long unsigneed int i = 0; i < first_numbers.size(); i++){
        red_num = (first_numbers[i].red-second_numbers[i].red)**2;
        green_num = (first_numbers[i].green-second_numbers[i].green)**2;
        blue_num = (first_numbers[i].blue-second_numbers[i].blue)**2;
        sum += (red_num+green_num+blue_num)**(1/2)
    }
    // TODO(student): Complete error calculation function.
    return sum;
}

std::vector<CornerPair> match_corners(const Image&,
                                      const std::vector<Corner>&,
                                      const Image&,
                                      const std::vector<Corner>&) {
    // TODO(student): Complete key points matching algorithm
    return {};
}

void map_coordinates(const Matrix&,
                     size_t,
                     size_t,
                     double&,
                     double&) {
    // TODO(student): Complete map function with homography
}

Image merge_images(const Image&,
                   const Image&,
                   const std::vector<std::vector<double>>&) {
    // TODO(student): Complete merge function.
    return {};
}
