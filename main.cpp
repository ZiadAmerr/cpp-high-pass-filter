#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    // Path to the image in the same directory
    string imagePath = "/Users/ziad/Desktop/Fall24/proj_HPC/proj/lena.png";

    // Load the image in color
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    // Check if the image is loaded successfully
    if (image.empty()) {
        cerr << "Error: Image cannot be loaded. Check the file path!" << endl;
        return -1;
    }

    // Print the first row pixel values as integers (BGR)
    cout << "First row pixel values (B, G, R):" << endl;
    for (int col = 0; col < image.cols; ++col) {
        cv::Vec3b pixel = image.at<cv::Vec3b>(0, col); // Access the first row
        cout << "[" << (int)pixel[0] << ", " << (int)pixel[1] << ", " << (int)pixel[2] << "] ";
    }
    cout << endl;

    return 0;
}
