#include <mpi.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;
using namespace cv;

// Define constants for filter size and number of nodes
#define FILTER_SIZE 3 // Must be an odd number
#define NUM_NODES 4   // Number of nodes to use
#define PATH "/Users/ziad/Desktop/Fall24/proj_HPC/proj/lena.png"

// Assert filter size is odd
static_assert(FILTER_SIZE % 2 == 1, "Error: Filter size must be an odd number");

// Function to generate a high-pass filter matrix dynamically
vector<vector<int>> generateHighPassFilter(int size)
{
    int centerValue = size * size - 1;
    vector<vector<int>> kernel(size, vector<int>(size, -1));
    kernel[size / 2][size / 2] = centerValue;
    return kernel;
}

// Function to apply the kernel on a specific pixel
double applyKernel(const Mat &image, const vector<vector<int>> &kernel, int x, int y)
{
    int kernelSize = kernel.size();
    int half = kernelSize / 2;
    double sum = 0.0;

    for (int i = -half; i <= half; ++i)
    {
        for (int j = -half; j <= half; ++j)
        {
            int row = min(max(x + i, 0), image.rows - 1);
            int col = min(max(y + j, 0), image.cols - 1);
            sum += image.at<uchar>(row, col) * kernel[i + half][j + half];
        }
    }

    return sum;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != NUM_NODES)
    {
        if (rank == 0) {
            cout << "Number of nodes is " << NUM_NODES << ".\n";
            cerr << "Error: Number of nodes must be " << NUM_NODES << ".\n";
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const char *imagePath = PATH;
    Mat image;
    int rows, cols;

    // Generate the high-pass filter kernel dynamically
    vector<vector<int>> kernel = generateHighPassFilter(FILTER_SIZE);

    // Step 1: Read the image only on rank 0
    if (rank == 0)
    {
        image = imread(imagePath, IMREAD_GRAYSCALE);
        if (image.empty())
        {
            cerr << "Error: Image cannot be loaded!\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        rows = image.rows;
        cols = image.cols;
        cout << "Image Loaded: " << rows << "x" << cols << endl;
    }

    // Step 2: Broadcast image dimensions to all nodes
    MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cols, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Step 3: Distribute image data to all nodes
    int localRows = rows / size;
    int remainingRows = rows % size;

    int startRow = rank * localRows + min(rank, remainingRows);
    int endRow = startRow + localRows + (rank < remainingRows ? 1 : 0);

    int localHeight = endRow - startRow;
    Mat localImage(localHeight, cols, CV_8UC1);

    if (rank == 0)
    {
        for (int i = 0; i < size; ++i)
        {
            int localStart = i * localRows + min(i, remainingRows);
            int localEnd = localStart + localRows + (i < remainingRows ? 1 : 0);
            if (i == 0)
                localImage = image(Range(localStart, localEnd), Range::all()).clone();
            else
            {
                Mat part = image(Range(localStart, localEnd), Range::all());
                MPI_Send(part.data, part.rows * part.cols, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD);
            }
        }
    }
    else
    {
        MPI_Recv(localImage.data, localHeight * cols, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Step 4: Apply the high-pass filter to the local part
    Mat localOutput(localHeight, cols, CV_8UC1, Scalar(0));

    for (int i = 0; i < localHeight; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            double newValue = applyKernel(localImage, kernel, i, j);
            localOutput.at<uchar>(i, j) = saturate_cast<uchar>(newValue);
        }
    }

    // Step 5: Gather the processed image
    Mat output;
    if (rank == 0)
    {
        output = Mat(rows, cols, CV_8UC1);
        localOutput.copyTo(output(Range(startRow, endRow), Range::all()));
        for (int i = 1; i < size; ++i)
        {
            int localStart = i * localRows + min(i, remainingRows);
            int localEnd = localStart + localRows + (i < remainingRows ? 1 : 0);
            Mat part(localEnd - localStart, cols, CV_8UC1);
            MPI_Recv(part.data, part.rows * part.cols, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            part.copyTo(output(Range(localStart, localEnd), Range::all()));
        }
    }
    else
    {
        MPI_Send(localOutput.data, localHeight * cols, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }

   // Step 6: Save the output image
    if (rank == 0)
    {
        if (output.empty())
        {
            cerr << "Error: Output image is empty, cannot save!" << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        imwrite("/Users/ziad/Desktop/Fall24/proj_HPC/proj/output.png", output);
        cout << "Filtered image saved as output.png" << endl;
    }


    MPI_Finalize();
    return 0;
}
