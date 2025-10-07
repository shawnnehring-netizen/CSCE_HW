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
        if (step == width){
            newer_image.push_back(new_image);
            step = 0;
            new_image.clear();
        }
        step+=1;
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
        throw std::invalid_argument("Invalid coordinate");
    }
    double coords = (s_dim-1)/(t_dim-1) * p_cord;
    // TODO(student): implement mapping function.
    return {coords};
}

Pixel bicubic_interpolation(const Image& pict,
                            double x,
                            double y) {
    if (pict.size() == 0){
        throw std::invalid_argument("Invalid image");
    }
    if (x > pict.size() || y > pict[0].size()){
        throw std::invalid_argument("Invalid coordinate");
    }
    // TODO(student): Implement bicubic interpolation

    double new_x = x/2.0;
    double new_y = y/2.0;
    std::vector<Pixel> x_pixels = {};
    double rem_x = new_x - x/2;
    double rem_y = new_y - y/2;
    for (int j = 0; j < 4; j++){
        Pixel count1x = pict[x/2-1][new_y-1+j];
        Pixel count2x = pict[x/2][new_y-1+j];
        Pixel count3x = pict[x/2+1][new_y-1+j];
        Pixel count4x = pict[x/2+2][new_y-1+j];
        Pixel x1 = bicubic_pixel(rem_x, count1x, count2x, count3x, count4x);
        x_pixels.push_back(x1);
    }
    Pixel color = bicubic_pixel(rem_y, x_pixels[0], x_pixels[1], x_pixels[2], x_pixels[3]);
    return {color};
}

Image scale_image(const Image& pict,
                  size_t width,
                  size_t height) {
    Image new_image = {};
    int x_cord = 0;
    int y_cord = 0;
    Pixel pix;
    if (pict.size() == 0){
        throw std::invalid_argument("Invalid image");
    }
    if ((width > 0 && width <= MAX_WIDTH) || (height > 0 && height <= MAX_HEIGHT)){
        throw std::invalid_argument("Invalid dimension");
    } 
    for (long unsigned int i = 0; i < pict.size(); i++){
        for (long unsigned int j = 0; j < pict[i].size(); j++){
            x_cord = map_coordinates(pict[i].size(), width, j);
            y_cord = map_coordinates(pict.size(), height, i);
            pix = bicubic_interpolation(pict, x_cord, y_cord);
            new_image[i][j] = pix;
        }
    }
    // TODO(student): add loops to calculate scaled images
    return {new_image};
}
