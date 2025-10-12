// provided.  do not edit. do not submit.
#ifndef _PROVIDED_FUNCTIONS_H_
#define _PROVIDED_FUNCTIONS_H_

#include <cstdint>
#include <string>
#include <vector>

// Pixel is a 3-tuple: {red, green, blue}
struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

// Image is a 2D vector of Pixels
using Image = std::vector<std::vector<Pixel>>;
using Matrix = std::vector<std::vector<double>>;

struct Corner {
  size_t x;  // x-coordinate of the corner
  size_t y;  // y-coordinate of the corner
};

struct CornerPair {
  struct Corner image1_corner;  // corner from first image
  struct Corner image2_corner;  // corner from second image
  double error;                 // error estimate for the pair
};

// maximum image width
const size_t MAX_WIDTH = 1920;
// maximum image height
const size_t MAX_HEIGHT = 1080;
// error calculation neighborhood
const unsigned int ERROR_NEIGHBORHOOD_SIZE = 17;
// corner detection Sensitivity factor
const double SENSITIVITY_FACTOR = 0.05;
// corner detection threshold
const double THRESHOLD_RATIO = 0.02;
// radius for non-maxima supresion
const int NMS_RADIUS = 20;

/**
 * Opens and validates a PPM file while populating an `Image`.
 * @param filename name of the PPM file to read from
 * @returns a non-empty `Image` in column-major order
 * @throws `std::runtime_error` if file cannot be opened or is invalid
*/
Image load_image(const std::string& filename);

/**
 * Outputs an `Image` to a PPM file
 * @param filename name of the PPM file to write to
 * @param image a non-empty `Image` in column-major order
 * @throws std::invalid_argument if image is empty or file cannot be opened
 */
void output_image(const std::string& filename, const Image& image);

/**
 * Maps given coordinate to source image for interpolation.
 * @param source_dimension width or height of source image
 * @param target_dimension width or height of target image
 * @param pixel_coordinate X- or Y-coordinate in target image
 * @returns X- or Y-coordinate of the location where the pixel maps in the source image
 * @throws std::invalid_argument if dimensions or coordinate are invalid
 */
double map_coordinates(size_t source_dimension,
                       size_t target_dimension,
                       size_t pixel_coordinate);

/**
 * Calculates the color values of a specific pixel.
 * @param source_image A non-empty `Image` in column major order
 * @param x X-coordinate (column) of where a pixel maps in the source image
 * @param y Y-coordinate (row) of where a pixel maps in the source image
 * @returns a `Pixel`
 * @throws std::invalid_argument if coordinates are invalid
 */
Pixel bicubic_interpolation(const Image& source_image, double x, double y);

/**
 * performs bicubic interpolation on four pixels
 * @param t the decimal part of the coordinate
 * @param p1 first `Pixel` (left-to-right or top-to-bottom order)
 * @param p2 second `Pixel`
 * @param p3 third `Pixel`
 * @param p4 fourth `Pixel`
 * @returns the interpolated `Pixel`
 */
Pixel bicubic_pixel(double t,
                    const Pixel& p1,
                    const Pixel& p2,
                    const Pixel& p3,
                    const Pixel& p4);

/**
 * Calculate the similarity between image sections around two keypoints.
 * Lower error signifies a better match between the two neighborhoods.
 *
 * @param image1 A non-empty 2D vector of Pixels in column-major order.
 * @param image1corner The key point in image1 around which to test neighborhood.
 * @param image2 A non-empty 2D vector of Pixels in column-major order.
 * @param image2corner The key point in image2 around which to test neighborhood.
 * @return A double representing the total error (Sum of Squared Differences).
 */
double error_calculation(const Image& image1,
                         const Corner& image1corner,
                         const Image& image2,
                         const Corner& image2corner);

/**
 * Finds the best matching corner in image2 for each corner in image1 based on neighborhood similarity.
 *
 * @param image1 A non-empty 2D vector of pixels in column-major order for the first image.
 * @param image1corners A vector of `Corner` key points from image1.
 * @param image2 A non-empty 2D vector of pixels in column-major order for the second image.
 * @param image2corners A vector of `Corner` key points from image2 to search for matches.
 * @return A vector of `CornerPair` structs, linking each corner from image1 to its best match in image2.
 */
std::vector<CornerPair> match_corners(const Image& image1,
                                      const std::vector<Corner>& image1corners,
                                      const Image& image2,
                                      const std::vector<Corner>& image2corners);

/**
 * Applies a 3x3 projective transformation matrix to a 2D coordinate.
 *
 * @param H A 3x3 `vector<vector<double>>` representing the inverse transformation matrix
 * required to align image2 corner points with corresponding image1 corner points.
 * @param x The input x-coordinate to be mapped.
 * @param y The input y-coordinate to be mapped.
 * @param[out] mapped_x A reference to a double that will be updated with the transformed x-coordinate.
 * @param[out] mapped_y A reference to a double that will be updated with the transformed y-coordinate.
 */
void map_coordinates(const std::vector<std::vector<double>>& H,
                     size_t x,
                     size_t y,
                     double& mapped_x,
                     double& mapped_y);

/**
 * Warps and stitches two images together using a homography matrix to create a panorama.
 *
 * @param image1 The base image, which acts as the anchor or reference frame for the panorama.
 * @param image2 The second image, which will be warped to align with `image1`.
 * @param H The 3x3 homography matrix that defines the projective transformation to map
 * coordinates from the output image canvas back to the `image2` coordinate space.
 * @return An `Image` object representing the final stitched panoramic image.
 * @note The size of the output canvas is fixed at 1.5 times the dimensions of `image1`,
 * which may not be large enough for all transformations. The blending method is a simple average.
 */
Image merge_images(const Image& image1,
                   const Image& image2,
                   const std::vector<std::vector<double>>& H);


/**
 * Given function: Calculates a 3x3 projective transformation matrix (homography) from matched corner pairs.
 *
 * @param pairs A vector of `CornerPair` structs, representing matched keypoints between two images.
 * @return A 3x3 `std::vector<std::vector<double>>` representing the calculated homography matrix.
 * @throws std::runtime_error If the input vector `pairs` contains fewer than four pairs,
 * which is the minimum required to compute the homography.
 * @note A stable homography estimation requires that the four chosen point pairs are not
 * collinear (i.e., no three points lie on the same straight line).
 */
std::vector<std::vector<double>> transform_estimation(const std::vector<CornerPair>& pairs);

/**
 * Detects corners in a color image using the Harris algorithm.
 *
 * @param color_image The input image in column-major order.
 * @return A vector of detected corner points.
 */
std::vector<Corner> harris_corner_detector(const Image& color_image);

#endif  // _PROVIDED_FUNCTIONS_H_
