// Distributed two-dimensional Discrete FFT transform
// William Trimmer

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>

#include "Complex.h"
#include "InputImage.h"

constexpr unsigned int NUMTHREADS = 4;

using namespace std;


//undergrad students can assume NUMTHREADS will evenly divide the number of rows in tested images
//graduate students should assume NUMTHREADS will not always evenly divide the number of rows in tested images.
// I will test with a different image than the one given


void Transform1D(Complex* h, int w, Complex* H)
{
    // Implement a simple 1-d DFT using the double summation equation
    // given in the assignment handout.  h is the time-domain input
    // data, w is the width (N), and H is the output array.
    for(int n= 0; n < w; n++) {
        Complex sum(0,0);
        for(int k = 0; k < w; k++) {
            Complex W(cos((2*M_PI*n*k)/w), -sin((2*M_PI*n*k)/w));
            sum = sum + W*h[k];
        }
        H[n] = sum;
    }
}

void InverseTransform1D(Complex *h, int w, Complex* H) {
    for(int n = 0; n < w; n++) {
        Complex sum(0,0);
        for(int k = 0; k < w; k++) {
            Complex W(cos((2*M_PI*n*k)/w), sin((2*M_PI*n*k)/w));
            sum = sum + W*h[k];
        }
        H[n] = sum;
        H[n].real = H[n].real/w;
        H[n].imag = H[n].imag/w;
    }
}

void Transpose(Complex *h, int w, int height) {
    for(int row=0; row < height; row++) {
        for(int column = 0; column < w; column++) {
            if(row < column) {
                Complex temp = h[row*w + column];
                h[row*w + column] = h[column*height + row];
                h[column*height + row] = temp;
            }
        }
    }
}

void createThreadForward(Complex *h, int w, int height, Complex* H) {
    vector<thread*> threads;
    for (int i = 0; i < height; i++) {
        threads.push_back(new thread{Transform1D, h + i*w, w, H + i * w});
    }
    for(auto &t: threads) {
        t->join();
    }
    threads.clear();
}

void createThreadInverse(Complex* h, int w, int height, Complex* H) {
    vector<thread*> threads;
    for (int i = 0; i < height; i++) {
        threads.push_back(new thread{InverseTransform1D, h + i*w, w, H + i * w});
    }

    for(auto &t: threads) {
        t->join();
    }
    threads.clear();
}


void Transform2D(const char* inputFN)
{   // Do the 2D transform here.
    // 1) Use the InputImage object to read in the Tower.txt file and
    //    find the width/height of the input image.
    InputImage image(inputFN);  // Create the helper object for reading the image
    Complex* input = image.GetImageData(); // Get data from image
    int image_height = image.GetHeight(); // obtain height of image
    int image_width = image.GetWidth(); // obtain width of image
    int image_size = image_height * image_width; // obtain size of image (w*h)
    // 2) Create a vector of complex objects of size width * height to hold
    //    values calculated
    Complex* output_1D = new Complex[image_size]; // Complex object to hold results from 1D row transform
    Complex* output_2D = new Complex[image_size]; // Complex object to hold resuts from 1D column transform
    Complex* output_2D_inverse = new Complex[image_size]; //Complex object to hold results from 1D inverse column transform
    Complex* output_1D_inverse = new Complex[image_size]; //Complex object to hold results from 1D inverse row transform
    // 3) Do the individual 1D transforms on the rows assigned to each thread

    createThreadForward(input, image_width, image_height, output_1D);


    // 4) Force each thread to wait until all threads have completed their row calculations
    //    prior to starting column calculations

    // 5) Perform column calculations
    Transpose(output_1D, image_width, image_height);

    createThreadForward(output_1D, image_width, image_height, output_2D);


    // 6) Wait for all column calculations to complete


    // 7) Use SaveImageData() to output the final results
    Transpose(output_2D, image_width, image_height);
    image.SaveImageData("../MyAfter2D.txt", output_2D, image_width, image_height);

    // inverse
    createThreadInverse(output_2D, image_width, image_height, output_2D_inverse);


    // wait to join


    Transpose(output_2D_inverse, image_width, image_height);

    createThreadInverse(output_2D_inverse, image_width, image_height, output_1D_inverse);


    // wait to join


    Transpose(output_1D_inverse, image_width, image_height);

    image.SaveImageDataReal("../MyAfterInverse.txt", output_1D_inverse, image_width, image_height);

}

int main(int argc, char** argv)
{
    string fn("../Tower.txt"); // default file name
    if (argc > 1) fn = string(argv[1]);  // if name specified on cmd line
    Transform2D(fn.c_str()); // Perform the transform.
}



