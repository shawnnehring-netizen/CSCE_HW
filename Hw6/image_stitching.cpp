// provided.  do not edit. do not submit.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "functions.h"

int main() {
  // declare variables
  std::string image1_file;
  std::string image2_file;
  std::string image1_corners_file;
  std::string image2_corners_file;

  // accept filenames and load data
  std::cout << "Input image1 filename: ";
  std::cin >> image1_file;
  Image image1 = load_image(image1_file);

  std::cout << "Input image2 filename: ";
  std::cin >> image2_file;
  Image image2 = load_image(image2_file);

  std::cout << "Start image stitching..." << std::endl;

  // Key point detection
  std::vector<Corner> image1_corners = harris_corner_detector(image1);
  std::vector<Corner> image2_corners = harris_corner_detector(image2);

  // Key point matches
  std::vector<CornerPair> matched_corners = match_corners(image1, image1_corners,
                                                          image2, image2_corners);

  // Estimate transform
  Matrix transformation_matrix = transform_estimation(matched_corners);

  // Transform and merge images
  Image merged = merge_images(image1, image2, transformation_matrix);

  output_image("merged.ppm", merged);
  std::cout << "Finished image stitching..." << std::endl;
  std::cout << "Output is stored in merged.ppm" << std::endl;

  // exit without errors
  return 0;
}
