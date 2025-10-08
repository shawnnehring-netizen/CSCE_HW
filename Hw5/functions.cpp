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
    if (word_file.eof()){
        throw std::runtime_error("Invalid filename");
    }
    if (!(word_file.is_open())){
        throw std::runtime_error("Failed to open <filename>");
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
    word_file >> width >> height;
    word_file >> max_color;
    if (!(p3 == "p3" || p3 == "P3")){
        throw std::runtime_error("Invalid type <type>");
    }
    if (width > MAX_WIDTH || height > MAX_HEIGHT){
        throw std::runtime_error("Invalid dimensions");
    }
    if (max_color < 1 || max_color > 255){
        throw std::runtime_error("Invalid max color");
    }
    long unsigned int step = 0;
    while (word_file >> red >> green >> blue){
        if (red < 0 || green < 0 || blue < 0 || red > max_color || green > max_color || blue > max_color){
            throw std::runtime_error("Invalid color value");
        }
        new_pixel.red = red;
        new_pixel.green = green;
        new_pixel.blue = blue;
        new_image.push_back(new_pixel);
        step+=1;
        if (step == width){
            newer_image.push_back(new_image);
            step = 0;
            new_image.clear();
        }
    }
    if (newer_image.size() < height){
        throw std::runtime_error("Not enough values");
    }
    if (newer_image.size() > height || !(new_image.empty())){
        throw std::runtime_error("Too many values");
    }
    std::vector<Pixel> final_sub = {};
    Image final_image = {};
    for (long unsigned int i = 0; i < width; i++){
        for (long unsigned int j = 0; j < height; j++){
            final_sub.push_back(newer_image[j][i]);
        }
        final_image.push_back(final_sub);
    }
    return {final_image};
}

void output_image(const std::string& file,
                  const Image& pict) {
    std::string line = ""; 
    std::ofstream word_file(file);
    if (pict.size() == 0){
        throw std::invalid_argument("Invalid image");
    }
    if (word_file.eof()){
        throw std::invalid_argument("Invalid filename");
    }
    if (!(word_file.is_open())){
        std::string mess = "Failed to open ";
        throw std::invalid_argument(mess);
    }
    word_file << "P3\n" << pict[0].size() + " " + pict.size() << "\n" << "255\n";
    for (long unsigned int i = 0; i < pict[0].size(); i++){ // Possible problem in not switching rows and columns 
        for (long unsigned int j = 0; j < pict.size(); j++){ //SHOULD BE TRANSPOSED NOW
            word_file << pict[i][j].red << " " << pict[i][j].green << " " << pict[i][j].blue << "\n";
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
        throw std::invalid_argument("Invalid coordinate minus");
    }
    double coords = (s_dim-1)/(t_dim-1) * p_cord;
    // TODO(student): implement mapping function.
    return {coords};
}

Pixel bicubic_interpolation(const Image& pict,
                            double x_old,
                            double y_old) {
    int x = std::trunc(x_old);
    int y = std::trunc(y_old);
    int width = pict.size();
    int height = pict[0].size();
    if (pict.size() == 0){
        throw std::invalid_argument("Invalid image");
    }
    if (x > width || y > height){
        throw std::invalid_argument("Invalid coordinate plus");
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
    if (x > width){
        x_2 = x;
    }
    else {
        x_2 = x + 1;
    }
    if (x > width -1){
        x_3 = x + 1;
    }
    else {
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
    if (y > height){
        y_2 = y;
    }
    else {
        y_2 = y + 1;
    }
    if (y > height){
        y_3 = y + 1;
    }
    else {
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
    Pixel color = bicubic_pixel(rem_y, x_pixels[0], x_pixels[1], x_pixels[2], x_pixels[3]);
    return {color};
}

Image scale_image(const Image& pict,
                  size_t width,
                  size_t height) {
    Image new_image(height, std::vector<Pixel>(width));
    int x_cord = 0;
    int y_cord = 0;
    Pixel pix;
    if (pict.size() == 0){
        throw std::invalid_argument("Invalid image");
    }
    if ((width > MAX_WIDTH) || (height > MAX_HEIGHT)){
        throw std::invalid_argument("Invalid dimension");
    } 
    for (long unsigned int i = 0; i < pict.size(); i++){
        for (long unsigned int j = 0; j < pict[i].size(); j++){
            //std::cout << "here" << "\n";
            x_cord = map_coordinates(pict[i].size(), width, j);
            //std::cout << "1" << "\n";
            y_cord = map_coordinates(pict.size(), height, i);
            //std::cout << "2" << x_cord << y_cord << "\n";
            pix = bicubic_interpolation(pict, x_cord, y_cord);
            //std::cout << "3" << "\n";
            new_image[i][j] = pix;
            std::cout << "4" << "\n";
        }
    }
    // TODO(student): add loops to calculate scaled images
    return {new_image};
}
