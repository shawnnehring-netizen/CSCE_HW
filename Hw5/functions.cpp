#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include "functions.h"
#include <vector>
Image load_image(const std::string& file) {
    // TODO(student): implement image loading
    if (file == ""){
        throw std::runtime_error("Invalid filename");
    }
    std::ifstream word_file(file);
    if (!(word_file.is_open())){
        throw std::runtime_error("Failed to open "+ file);
    }
    if (word_file.peek()==EOF){
        throw std::runtime_error("Failed to read type");
    }
    std::string p3 = "";
    long unsigned int width = 0;
    long unsigned int height = 0;
    int max_color = 0;
    int red = 0;
    int blue = 0;
    int green = 0;
    std::vector<Pixel> new_image = {};
    Image newer_image = {};
    Pixel new_pixel = {};
    word_file >> p3;
    if (!(p3 == "p3" || p3 == "P3")){
        throw std::runtime_error("Invalid type " + p3);
    }
    word_file >> width >> height;
    if (width > MAX_WIDTH || height > MAX_HEIGHT || word_file.fail() || width == 0 || height == 0){
        throw std::runtime_error("Invalid dimensions");
    }
    word_file >> max_color;
    if (max_color < 1 || max_color > 255){
        throw std::runtime_error("Invalid max color");
    }
    //std::cout << max_color << " " << width << " " << height << " " << p3 << "\n";
    long unsigned int step = 0;
    long unsigned int count = 0;
    while (word_file >> red >> green >> blue){
        if (red < 0 || green < 0 || blue < 0 || red > max_color || green > max_color || blue > max_color){
            throw std::runtime_error("Invalid color value");
        }
        //std::cout << red << " " << green << " " << blue << "\n";
        //std::cout << (uint8_t)red << " " << (uint8_t)green << " " << (uint8_t)blue << "\n";
        new_pixel.red = red;
        new_pixel.green = green;
        new_pixel.blue = blue;
        //std::cout << new_pixel.red << " " << new_pixel.green << " " << new_pixel.blue << "\n";
        new_image.push_back(new_pixel);
        count += 1;
        step+=1;
        if (step == width){
            newer_image.push_back(new_image);
            step = 0;
            new_image.clear();
        }
    }
    if (count < height*width){
        throw std::runtime_error("Not enough values");
    }
    int more = 0;
    if (count > height*width || word_file >> more){
        throw std::runtime_error("Too many values");
    }
    Image final_image(width, std::vector<Pixel>(height));
    for (long unsigned int i = 0; i < width; i++){
        for (long unsigned int j = 0; j < height; j++){
            final_image[i][j] = newer_image[j][i];
        }
    }
    return {final_image};
}

void output_image(const std::string& file,
                  const Image& pict) {
    std::string line = ""; 
    if (file == ""){
        throw std::invalid_argument("Invalid filename");
    }
    std::ofstream word_file(file);
    if (pict.size() == 0 || pict[0].size() == 0){
        throw std::invalid_argument("Invalid image");
    }
    if (!(word_file.is_open())){
        throw std::invalid_argument("Failed to open "+ file);
    }
    int width = pict.size();
    int height = pict[0].size();
    word_file << "P3\n" << width << " " << height << "\n" << "255\n";
    for (int i = 0; i < width; i++){ // Possible problem in not switching rows and columns 
        for (int j = 0; j < height; j++){ //SHOULD BE TRANSPOSED NOW
            word_file << pict[j][i].red << " " << pict[j][i].green << " " << pict[j][i].blue << "\n";
        }
    }
    // TODO(student): implement writing image to file
}

double map_coordinates(size_t s_dim,
                       size_t t_dim,
                       size_t p_cord) {
    if (s_dim <= 0 || t_dim <= 1){
        throw std::invalid_argument("Invalid dimension");
    }
    if (p_cord >= t_dim){
        throw std::invalid_argument("Invalid coordinate");
    }
    double coords = ((double)s_dim-1)/((double)t_dim-1) * p_cord;
    //std::cout << (double)s_dim-1 << " " <<((double)t_dim-1) << " " << p_cord << " " << coords <<"\n";
    // TODO(student): implement mapping function.
    return coords;
}

Pixel bicubic_interpolation(const Image& pict,
                            double x_old,
                            double y_old) {
    int x = std::trunc(x_old);
    int y = std::trunc(y_old);
    int width = pict.size();
    int height = pict[0].size();
    if (pict.size() == 0 || pict[0].size() == 0){
        throw std::invalid_argument("Invalid image");
    }
    if (x > width || y > height){
        throw std::invalid_argument("Invalid coordinate - ");
    }
    // TODO(student): Implement bicubic interpolation
    int x_0 = 0;
    int x_1 = x;
    int x_2 = 0;
    int x_3 = 0;
    if (x < 1){
        x_0 = x;
    }
    else {
        x_0 = x - 1;
    }
    if (x+1 > height){
        x_2 = x;
        x_3 = x;}
    else if (x + 2 > height){
        x_3 = x + 1;
        x_2 = x + 1;
    }
    else {
        x_2 = x + 1;
        x_3 = x + 2;
    }

    int y_0 = 0;
    int y_1 = y;
    int y_2 = 0;
    int y_3 = 0;
    if (y < 1){
        y_0 = y;
    }
    else {
        y_0 = y - 1;
    }
    if (y+1 > height){
        y_2 = y;
        y_3 = y;}
    else if (y + 2 > height){
        y_3 = y + 1;
        y_2 = y + 1;
    }
    else {
        y_2 = y + 1;
        y_3 = y + 2;
    }
    std::vector<Pixel> x_pixels = {};
    std::vector<int> y_values = {y_0, y_1, y_2, y_3};
    std::vector<int> x_values = {x_0, x_1, x_2, x_3};
    double rem_x = x_old - x;
    double rem_y = y_old - y;
    for (int j = 0; j < 4; j++){
        //std::cout << "a" << x_0 << y_values[j] <<  "\n";
        Pixel count1x = pict[x_0][y_values[j]];
        //std::cout << "b" << x_1 << y_values[j] << "\n";
        Pixel count2x = pict[x_1][y_values[j]];
        //std::cout << "c" << x_2 << y_values[j] << "\n";
        Pixel count3x = pict[x_2][y_values[j]];
        //std::cout << "d" << x_3 << y_values[j] << "\n";
        Pixel count4x = pict[x_3][y_values[j]];
        //std::cout << "e" << x_0 << y_values[j] << "\n";
        Pixel x1 = bicubic_pixel(rem_x, count1x, count2x, count3x, count4x);
        //std::cout << "f" << x_old << y_old << "\n";
        x_pixels.push_back(x1);
    }
    Pixel color = bicubic_pixel(rem_y, x_pixels[3], x_pixels[2], x_pixels[1], x_pixels[0]);
    return {color};
}

Image scale_image(const Image& pict,
                  size_t width,
                  size_t height) {
    int x_cord = 0;
    int y_cord = 0;
    Pixel pix = {};
    if (pict.empty()){
        throw std::invalid_argument("Invalid image");
    }
    if ((width > MAX_WIDTH) || (height > MAX_HEIGHT)){
        throw std::invalid_argument("Invalid dimension");
    } 
    Image new_image(width, std::vector<Pixel>(height)); // does it count 0-40 not including 40 so do i need to add 1
    int old_width = pict.size();
    int old_height = pict[0].size();
    for (long unsigned int i = 0; i < width; i++){
        for (long unsigned int j = 0; j < height; j++){
            //std::cout << "here" << "\n";
            x_cord = map_coordinates(old_width, width, i);
            //std::cout << "1" << "\n";
            y_cord = map_coordinates(old_height, height, j);
            //std::cout << "2" << x_cord << y_cord << "\n";
            pix = bicubic_interpolation(pict, x_cord, y_cord);
            //std::cout << "3" << "\n";
            new_image[i][j] = pix;
            //std::cout << "4" << "\n";
        }
    }
    // TODO(student): add loops to calculate scaled images
    return {new_image};
}
