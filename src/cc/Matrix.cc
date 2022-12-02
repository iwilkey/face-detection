#ifndef _MATRIX_CC_
#define _MATRIX_CC_

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static Mat createSquareZeroMatrix(int dim) {
    Mat ret = Mat(dim, dim, CV_32F, 0.0f);
    return ret;
}

static Mat createUniformSquareMatrix(int dim, float value) {
    Mat ret = Mat(dim, dim, CV_32F, value);
    return ret;
}

static void divideMatrixElementsBy(Mat & matrix, float scale) {
    for(int i = 0; i < matrix.rows; i++)
        for(int j = 0; j < matrix.cols; j++)
            matrix.at<float>(i, j) /= scale;
}

static void multiplyMatrixElementsBy(Mat & matrix, float scale) {
    for(int i = 0; i < matrix.rows; i++)
        for(int j = 0; j < matrix.cols; j++)
            matrix.at<float>(i, j) *= scale;
}

static void addToMatrixElementsBy(Mat & matrix, float amount) {
    for(int i = 0; i < matrix.rows; i++)
        for(int j = 0; j < matrix.cols; j++)
            matrix.at<float>(i, j) += amount;
}

static void subtractMatrixElementsBy(Mat & matrix, float amount) {
    for(int i = 0; i < matrix.rows; i++)
        for(int j = 0; j < matrix.cols; j++)
            matrix.at<float>(i, j) -= amount;
}

static void printMatrixContents(Mat matrix) {
    for(int i = 0; i < matrix.rows; i++) {
        cout << '\t';
        for(int j = 0; j < matrix.cols; j++) 
            cout << to_string(matrix.at<float>(i, j)) << " ";
        cout << endl;
    }
}

#endif // _MATRIX_CC_
