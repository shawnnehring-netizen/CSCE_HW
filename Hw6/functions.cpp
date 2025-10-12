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
    std::vector<Pixel> first_numbers(ERROR_NEIGHBORHOOD_SIZE);
    std::vector<Pixel> second_numbers(ERROR_NEIGHBORHOOD_SIZE);
    int x_value_1;
    int y_value_1;
    int x_value_2;
    int y_value_2;
    for (int i = 0; i < ERROR_NEIGHBORHOOD_SIZE, i++;){
        for (int j = 0; j < ERROR_NEIGHBORHOOD_SIZE, j++;){
            x_value_1 = point_1.x-(ERROR_NEIGHBORHOOD_SIZE/2)+i;
            y_value_1 = point_1.y-(ERROR_NEIGHBORHOOD_SIZE/2) + j;
            x_value_2 = point_2.y-(ERROR_NEIGHBORHOOD_SIZE/2) + i;
            y_value_2 =point_2.y-(ERROR_NEIGHBORHOOD_SIZE/2) + j;
            first_numbers.push_back(image_1[x_value_1][y_value_1]);
            second_numbers.push_back(image_2[x_value_2][y_value_2]);
        }
    }
    int red_num = 0;
    int green_num = 0;
    int blue_num = 0;
    double sum = 0;
    for (long unsigned int i = 0; i < first_numbers.size(); i++){
        red_num = std::pow((first_numbers[i].red-second_numbers[i].red),2);
        green_num = std::pow((first_numbers[i].green-second_numbers[i].green),2);
        blue_num = std::pow((first_numbers[i].blue-second_numbers[i].blue),2);
        sum += std::sqrt((red_num+green_num+blue_num));
    }
    // TODO(student): Complete error calculation function.
    return sum;
}

std::vector<CornerPair> match_corners(const Image& image_1,
                                      const std::vector<Corner>& corner_1,
                                      const Image& image_2,
                                      const std::vector<Corner>& corner_2) {
        std::vector<CornerPair> final_corn = {};
        std::vector<std::vector<double>> errors(corner_1.size(), std::vector<double>(corner_2.size()));
        double error = 0;
        for (long unsigned int i = 0; i < corner_1.size(); i++){
            for (long unsigned int j = 0; j < corner_2.size(); j++){
                error = error_calculation(image_1,corner_1[i],image_2,corner_2[j]);
                errors[i][j] = error;
            }
        }
        for (long usigned int i = 0; i < )

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
