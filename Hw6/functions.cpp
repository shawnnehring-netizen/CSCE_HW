#include <cmath>
#include <iostream>
#include <vector>
#include "functions.h"

double error_calculation(const Image&,
                         const Corner&,
                         const Image&,
                         const Corner&) {
    // TODO(student): Complete error calculation function.
    return 0;
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
