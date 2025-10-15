#include <cmath>
#include <iostream>
#include <vector>
#include "functions.h"

//cd Hw6
//ls functions.cpp functions.h image_stitching.cpp provided_functions.cpp functions_part1.cpp
//g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g *.cpp
double error_calculation(const Image& image_1,
                         const Corner& point_1, 
                         const Image& image_2,
                         const Corner& point_2) {
    std::cout << "sill" << "\n";
    std::vector<Pixel> first_numbers(ERROR_NEIGHBORHOOD_SIZE);
    std::vector<Pixel> second_numbers(ERROR_NEIGHBORHOOD_SIZE);
    long unsigned int block = ERROR_NEIGHBORHOOD_SIZE/2;
    if (point_1.x < block || (image_1.size()-point_1.x) < block || point_2.x < block || (image_2.size()-point_2.x) < block || point_1.y < block || (image_1[0].size()-point_1.y) < block || point_2.x < block || (image_2.size()-point_2.x) < block){
        return INFINITY;}
    int x_value_1= 0;
    int y_value_1=0;
    int x_value_2=0;
    int y_value_2=0;
    std::cout << "silly" << "\n";
    for (unsigned int i = 0; i < ERROR_NEIGHBORHOOD_SIZE; i++){
        for (unsigned int j = 0; j < ERROR_NEIGHBORHOOD_SIZE; j++){
            x_value_1 = point_1.x-(ERROR_NEIGHBORHOOD_SIZE/2) + i;
            y_value_1 = point_1.y-(ERROR_NEIGHBORHOOD_SIZE/2) + j;
            x_value_2 = point_2.x-(ERROR_NEIGHBORHOOD_SIZE/2) + i;
            y_value_2 =point_2.y-(ERROR_NEIGHBORHOOD_SIZE/2) + j;
            //std::cout << x_value_1 << " " << y_value_1 << " " << x_value_2 << " " << y_value_2 << "\n";
            //std::cout << (int)image_1[x_value_1][y_value_1].red << " " << (int)image_2[x_value_2][y_value_2].red << " " << (int)image_1[x_value_1][y_value_1].red - (int)image_2[x_value_2][y_value_2].red <<"\n";
            first_numbers.push_back(image_1[x_value_1][y_value_1]);
            second_numbers.push_back(image_2[x_value_2][y_value_2]);
        }
    }
    int red_num = 0;
    int green_num = 0;
    int blue_num = 0;
    double sum = 0;
    for (long unsigned int i = 0; i < first_numbers.size(); i++){
        red_num = std::pow(((int)first_numbers[i].red - (int)second_numbers[i].red),2);
        green_num = std::pow(((int)first_numbers[i].green - (int)second_numbers[i].green),2);
        blue_num = std::pow(((int)first_numbers[i].blue - (int)second_numbers[i].blue),2);
        //std::cout << red_num << " " << green_num << " " << blue_num << "\n";
        sum += std::sqrt((red_num + green_num + blue_num));
    }
    // TODO(student): Complete error calculation function.
    return sum;
}

std::vector<CornerPair> match_corners(const Image& image_1,
                                      const std::vector<Corner>& corner_1,
                                      const Image& image_2,
                                      const std::vector<Corner>& corner_2) {
        std::cout << "blah" << "\n";
        std::vector<CornerPair> final_corn = {};
        std::vector<std::vector<double>> errors(corner_1.size(), std::vector<double>(corner_2.size()));
        double error = 0;
        for (long unsigned int i = 0; i < corner_1.size(); i++){
            for (long unsigned int j = 0; j < corner_2.size(); j++){
                //std::cout << "igu" << "\n";
                if (corner_1[i].x < image_1.size()/2){
                    errors[i][j] = INFINITY;
                    continue;
                }
                if (corner_2[j].x > image_2.size()/2){
                    errors[i][j] = INFINITY;
                    continue;
                } 
                if (corner_1[i].y - corner_2[j].y >= 100 || (int)corner_1[i].y - (int)corner_2[j].y <= -100){
                    errors[i][j] = INFINITY;
                    continue;
                }
                //std::cout << "silly" << "\n";
                error = error_calculation(image_1,corner_1[i],image_2,corner_2[j]);
                errors[i][j] = error;
            }
        }
        double lowest = INFINITY;
        double minimum = 0;
        std::vector<double> lowest_nums = {};
        while (lowest != INFINITY){
            for (long unsigned int i = 0; i < errors.size(); i++){
                for (long unsigned int j = 0; j < errors[i].size(); j++){
                if (errors[i][j] < lowest && errors[i][j] > minimum){
                    lowest = errors[i][j];
                }
                }
            }
            if (lowest != INFINITY){
                lowest_nums.push_back(lowest);
                minimum = lowest;
                lowest = INFINITY;
            }
        }
        std::vector<CornerPair> final_pairs = {};
        CornerPair fin_corn = {};
        for (long unsigned int k = 0; k < lowest_nums.size(); k++){
            for (long unsigned int i = 0; i < errors.size(); i++){
                for (long unsigned int j = 0; j < errors[i].size(); j++){
                if (lowest_nums[k] == errors[i][j]){
                    fin_corn.image1_corner = corner_1[i];
                    fin_corn.image2_corner = corner_2[j];
                    final_pairs.push_back(fin_corn);
                }
                }
            }    
        }
    // TODO(student): Complete key points matching algorithm
    return final_pairs;
}

void map_coordinates(const Matrix& matr,
                     size_t x,
                     size_t y,
                     double& map_x,
                     double& map_y) {
    std::vector<double> primes = {};
    double prime = 0;
    for (long unsigned int i = 0; i < matr.size(); i++){
        prime = matr[i][0]*x + matr[i][1]*y + matr[i][2];
        primes.push_back(prime);
    }
    map_x = primes[0]/primes[2];
    map_y = primes[1]/primes[2];

    // TODO(student): Complete map function with homography
}

Image merge_images(const Image& image_1,
                   const Image& image_2,
                   const std::vector<std::vector<double>>& tran_matr) {
    int width = image_1.size() * 1.75;
    int height = image_1[0].size() * 1.5;
    Image tran_image(width, std::vector<Pixel>(height), {});
    for (long unsigned int i = 0; i < tran_image.size(); i++){
        for (long unsigned int j = 0; j < tran_image[i].size(); j++){
            Pixel I1_pixel = {};
            Pixel I2_pixel = {};
            double map_x = 0;
            double map_y = 0;
            Pixel New_pixel = {0,0,0};
            bool I1 = false;
            bool I2 = false;

            map_coordinates(tran_matr, i, j, map_x, map_y);
            if (map_x < image_1.size() || map_y < image_1[0].size()){
                I1_pixel = bicubic_interpolation(image_1,map_x, map_y);
                I1 = true;
            }
            if (map_x < image_2.size() || map_y < image_2[0].size()){
                I2_pixel = bicubic_interpolation(image_2,map_x, map_y);
                I2 = true;
            }
            if (I1 && I2){
                New_pixel.red = (I1_pixel.red + I2_pixel.red) / 2;
                New_pixel.green = (I1_pixel.green + I2_pixel.green) / 2;
                New_pixel.blue = (I1_pixel.blue + I2_pixel.blue) / 2;
            }
            else if (I1 && !(I2)){
                New_pixel = I1_pixel;
            }
            else if (!(I1) && I2){
                New_pixel = I2_pixel;
            }
            else if (!(I1) && !(I2)){
                New_pixel = {0,0,0};
            }
            tran_image[i][j] = New_pixel;
        }
    }
    // TODO(student): Complete merge function.
    return tran_image;
}
