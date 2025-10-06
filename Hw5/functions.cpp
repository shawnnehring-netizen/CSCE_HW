#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include "functions.h"

Image load_image(const std::string&) {
    // TODO(student): implement image loading
    return {};
}

void output_image(const std::string&,
                  const Image&) {
    // TODO(student): implement writing image to file
}

double map_coordinates(size_t,
                       size_t,
                       size_t) {
    // TODO(student): implement mapping function.
    return {};
}

Pixel bicubic_interpolation(const Image&,
                            double,
                            double) {
    // TODO(student): Implement bicubic interpolation
    return {};
}

Image scale_image(const Image&,
                  size_t,
                  size_t) {
    // TODO(student): add loops to calculate scaled images
    return {};
}
