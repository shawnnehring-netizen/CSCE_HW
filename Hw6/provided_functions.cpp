// provided.  do not edit. do not submit.
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include "functions.h"

// helper function for bicubic interpolation
double p(double x1, double x2, double x3, double x) {
    return (x - x1) * (x - x2) * (x - x3);
}

// performs bicubic interpolation on four color values
uint8_t bicubic_color(double t, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4) {
    double x1 = -t - 1;
    double x2 = -t;
    double x3 = 1 - t;
    double x4 = 2 - t;

    double color = (p(x2, x3, x4, 0) * c1 / p(x2, x3, x4, x1)) +
                   (p(x1, x3, x4, 0) * c2 / p(x1, x3, x4, x2)) +
                   (p(x1, x2, x4, 0) * c3 / p(x1, x2, x4, x3)) +
                   (p(x1, x2, x3, 0) * c4 / p(x1, x2, x3, x4));

    if (color < 0)
        return 0;
    else if (color > 255)
        return 255;
    else
        return std::round(color);
}

// uses color interpolation to interpolate full pixel
Pixel bicubic_pixel(double t, const Pixel& p1, const Pixel& p2, const Pixel& p3, const Pixel& p4) {
    uint8_t red = bicubic_color(t, p1.red, p2.red, p3.red, p4.red);
    uint8_t green = bicubic_color(t, p1.green, p2.green, p3.green, p4.green);
    uint8_t blue = bicubic_color(t, p1.blue, p2.blue, p3.blue, p4.blue);
    return {red, green, blue};
}

// Helper functions for tansform estimation.
Matrix transpose(const Matrix& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        // Return an empty matrix if input is empty
        return {};
    }

    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    // Create the transposed matrix with swapped dimensions
    Matrix result(cols, std::vector<double>(rows));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

Matrix multiply(const Matrix& A, const Matrix& B) {
    if (A.empty() || A[0].empty() || B.empty() || B[0].empty()) {
        // Return empty if any matrix is empty
        return {};
    }

    size_t rowsA = A.size();
    size_t colsA = A[0].size();
    size_t rowsB = B.size();
    size_t colsB = B[0].size();

    // The number of columns in A must equal the number of rows in B
    if (colsA != rowsB) {
        throw std::invalid_argument("Matrix dimensions are incompatible for multiplication.");
    }

    // Initialize the result matrix with zeros
    Matrix result(rowsA, std::vector<double>(colsB, 0.0));

    // Perform the multiplication
    for (size_t i = 0; i < rowsA; ++i) {
        for (size_t j = 0; j < colsB; ++j) {
            for (size_t k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

std::vector<double> solve_linear_system(std::vector<std::vector<double>>& A, std::vector<double>& B) {
    size_t n = A.size();

    // --- Input Validation ---
    if (n == 0 || A[0].size() != n || B.size() != n) {
        throw std::invalid_argument("Invalid input: Matrix A must be square and dimensions must match vector B.");
    }

    // --- Forward Elimination with Partial Pivoting ---
    for (size_t i = 0; i < n; ++i) {
        // Find the pivot row (the one with the largest element in the current column)
        size_t pivot_row = i;
        for (size_t k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[pivot_row][i])) {
                pivot_row = k;
            }
        }

        // Swap the current row with the pivot row
        A[i].swap(A[pivot_row]);
        std::swap(B[i], B[pivot_row]);

        // Check for singularity
        if (std::abs(A[i][i]) < 1e-10) {
            throw std::runtime_error("Matrix is singular or nearly singular; no unique solution exists.");
        }

        // Eliminate the lower rows
        for (size_t k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            B[k] -= factor * B[i];
            for (size_t j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

    // --- Back Substitution ---
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; ++j) {
            sum += A[i][j] * x[j];
        }
        x[i] = (B[i] - sum) / A[i][i];
    }

    return x;
}

Matrix estimate_H(const std::vector<CornerPair>& p) {
    if (p.size() < 4) {
        throw std::runtime_error("not enough matched pairs");
    }

    size_t N = p.size()*2;
    Matrix A(N, std::vector<double>(8, 0));
    Matrix B(p.size()*2, std::vector<double>(1, 0));

    for (size_t i = 0; i < p.size(); i+=1) {
        A.at(2*i).at(0) = p.at(i).image1_corner.x;
        A.at(2*i).at(1) = p.at(i).image1_corner.y;
        A.at(2*i).at(2) = 1;
        A.at(2*i).at(6) = -static_cast<double>(p.at(i).image1_corner.x) * p.at(i).image2_corner.x;
        A.at(2*i).at(7) = -static_cast<double>(p.at(i).image1_corner.y) * p.at(i).image2_corner.x;
        B.at(2*i).at(0) = p.at(i).image2_corner.x;

        A.at(2*i+1).at(3) = p.at(i).image1_corner.x;
        A.at(2*i+1).at(4) = p.at(i).image1_corner.y;
        A.at(2*i+1).at(5) = 1;
        A.at(2*i+1).at(6) = -static_cast<double>(p.at(i).image1_corner.x) * p.at(i).image2_corner.y;
        A.at(2*i+1).at(7) = -static_cast<double>(p.at(i).image1_corner.y) * p.at(i).image2_corner.y;
        B.at(2*i+1).at(0) = p.at(i).image2_corner.y;
    }

    Matrix A_transpose = transpose(A);
    Matrix C = multiply(A_transpose , A);
    Matrix D = multiply(A_transpose , B);

    std::vector<double> b = {   D.at(0).at(0), D.at(1).at(0), D.at(2).at(0), D.at(3).at(0),
                                D.at(4).at(0), D.at(5).at(0), D.at(6).at(0), D.at(7).at(0)};


    std::vector<double> sol = solve_linear_system(C, b);

    Matrix H = {{sol.at(0), sol.at(1), sol.at(2)},
                {sol.at(3), sol.at(4), sol.at(5)},
                {sol.at(6), sol.at(7), 1}};

    return H;
}

std::vector<std::vector<double>> transform_estimation(const std::vector<CornerPair>& pairs) {
    const size_t PAIRS = 4;
    size_t n = pairs.size();

    if (n < PAIRS) {
        throw std::runtime_error("not enough matched pairs");
    }

    std::vector<std::vector<double>> bestH;;
    size_t best_inlier_count = 0;
    size_t attempts = 0;
    while (attempts < (5*n)) {
        std::vector<CornerPair> p;
        if (attempts == 0) {
            for (size_t i = 0; i < PAIRS; i++) {
                p.push_back(pairs.at(i));
            }
        } else {
            std::vector<bool> used(n, false);
            while (p.size() < 4) {
                size_t index = static_cast<size_t>(rand() % n);
                if (used.at(index)) {
                    continue;
                }
                p.push_back(pairs.at(index));
                used.at(index) = true;
            }
        }
        std::vector<std::vector<double>> H;
        try {
            H = estimate_H(p);
            std::vector<CornerPair> in_liers;
            for (auto match : pairs) {
                double mx, my;
                map_coordinates(H, match.image1_corner.x, match.image1_corner.y, mx, my);
                double dx = mx - match.image2_corner.x;
                double dy = my - match.image2_corner.y;
                if ((dx * dx) + (dy * dy) < 100) {
                    in_liers.push_back(match);
                }
            }
            if (best_inlier_count < in_liers.size()) {
                best_inlier_count = in_liers.size();
                bestH = H;
            }
        }
        catch(...) {
            std::cout << "catch and ignore singularity\n";
        }

        if (best_inlier_count > ((2*n)/3)) {
            break;
        }

        attempts++;
    }

    return bestH;
}


// --- Internal Grayscale Image Representation ---
// Helper struct to handle grayscale processing with a flat memory layout.
struct GrayscaleImage {
    int width, height;
    std::vector<double> data;

    GrayscaleImage(int w, int h) : width(w), height(h), data(w * h, 0.0) {}

    // Get pixel value with boundary check (zero-padding)
    double at(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return 0.0;
        }
        // Use standard row-major indexing for the internal flat vector
        return data[y * width + x];
    }

    // Set pixel value
    void set(int x, int y, double value) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            data[y * width + x] = value;
        }
    }
};

// --- Core Algorithm Functions ---

/**
 * @brief Performs 2D convolution on a grayscale image.
 */
GrayscaleImage convolve(const GrayscaleImage& input, const std::vector<std::vector<double>>& kernel) {
    GrayscaleImage output(input.width, input.height);
    int kernel_h = kernel.size();
    int kernel_w = kernel[0].size();
    int kernel_center_y = kernel_h / 2;
    int kernel_center_x = kernel_w / 2;

    for (int y = 0; y < input.height; ++y) {
        for (int x = 0; x < input.width; ++x) {
            double sum = 0.0;
            for (int ky = 0; ky < kernel_h; ++ky) {
                for (int kx = 0; kx < kernel_w; ++kx) {
                    int ix = x + kx - kernel_center_x;
                    int iy = y + ky - kernel_center_y;
                    sum += input.at(ix, iy) * kernel[ky][kx];
                }
            }
            output.set(x, y, sum);
        }
    }
    return output;
}

/**
 * @brief Generates a 2D Gaussian kernel for blurring.
 */
std::vector<std::vector<double>> generate_gaussian_kernel(int size, double sigma) {
    std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
    double sum = 0.0;
    int center = size / 2;
    const double PI = 3.14159265358979323846;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int rel_x = x - center;
            int rel_y = y - center;
            kernel[y][x] = exp(-(rel_x * rel_x + rel_y * rel_y) / (2.0 * sigma * sigma)) / (2.0 * PI * sigma * sigma);
            sum += kernel[y][x];
        }
    }

    // Normalize the kernel
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            kernel[y][x] /= sum;
        }
    }
    return kernel;
}

std::vector<Corner> harris_corner_detector(const Image& color_image) {
    if (color_image.empty() || color_image[0].empty()) {
        // Return empty for an empty image
        return {};
    }

    // --- Step 0: Convert RGB to Grayscale ---
    int width = color_image.size();
    int height = color_image[0].size();
    GrayscaleImage gray_image(width, height);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            // Accessing column-major image: image[column][row]
            const auto& pixel = color_image[x][y];
            double gray_value = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
            gray_image.set(x, y, gray_value);
        }
    }

    // --- Step 1: Compute Gradients (Ix, Iy) using Sobel operators ---
    const std::vector<std::vector<double>> sobel_x = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const std::vector<std::vector<double>> sobel_y = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    GrayscaleImage Ix = convolve(gray_image, sobel_x);
    GrayscaleImage Iy = convolve(gray_image, sobel_y);

    // --- Step 2: Compute products of derivatives ---
    GrayscaleImage Ixx(width, height), Iyy(width, height), Ixy(width, height);
    for (size_t i = 0; i < gray_image.data.size(); ++i) {
        Ixx.data[i] = Ix.data[i] * Ix.data[i];
        Iyy.data[i] = Iy.data[i] * Iy.data[i];
        Ixy.data[i] = Ix.data[i] * Iy.data[i];
    }

    // --- Step 3: Apply Gaussian blur ---
    std::vector<std::vector<double>> gauss_kernel = generate_gaussian_kernel(5, 1.0);
    GrayscaleImage Sxx = convolve(Ixx, gauss_kernel);
    GrayscaleImage Syy = convolve(Iyy, gauss_kernel);
    GrayscaleImage Sxy = convolve(Ixy, gauss_kernel);

    // --- Step 4: Calculate Harris response R ---
    GrayscaleImage response_map(width, height);
    double max_response = 0.0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double sxx = Sxx.at(x, y);
            double syy = Syy.at(x, y);
            double sxy = Sxy.at(x, y);

            double det = (sxx * syy) - (sxy * sxy);
            double trace = sxx + syy;
            double r = det - SENSITIVITY_FACTOR * (trace * trace);

            // Only consider positive responses as potential corners
            if (r > 0) {
                response_map.set(x, y, r);
                if (r > max_response) {
                    max_response = r;
                }
            }
        }
    }

    // --- Step 5: Thresholding and Non-Maximum Suppression ---
    std::vector<Corner> corners;
    double response_threshold = max_response * THRESHOLD_RATIO;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double current_response = response_map.at(x, y);
            if (current_response > response_threshold) {
                bool is_local_max = true;
                // Check the NMS window
                for (int ny = -NMS_RADIUS; ny <= NMS_RADIUS; ++ny) {
                    for (int nx = -NMS_RADIUS; nx <= NMS_RADIUS; ++nx) {
                        if (response_map.at(x + nx, y + ny) > current_response) {
                            is_local_max = false;
                            break;
                        }
                    }
                    if (!is_local_max) break;
                }
                if (is_local_max) {
                    corners.push_back({static_cast<size_t>(x), static_cast<size_t>(y)});
                }
            }
        }
    }
    return corners;
}
