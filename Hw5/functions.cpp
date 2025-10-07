#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include "functions.h"
#include <vector>
Image load_image(const std::string&) {
    // TODO(student): implement image loading

    return {};
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
        }
    }
    // TODO(student): add loops to calculate scaled images
    return {};
}
