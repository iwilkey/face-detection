#ifndef _EFFECT_ENGINE_H_
#define _EFFECT_ENGINE_H_

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define GAUSSIAN_MATRIX_CONSTANT 1 / 256.0f

#define FILTER_COUNT 8
#define GRAYSCALE_FILTER_BIT 0x00
#define SEPIA_FILTER_BIT 0x01
#define SHARP_FILTER_BIT 0x02
#define INVERTING_FILTER_BIT 0x03
#define BOX_BLUR_BIT 0x04
#define GAUSSIAN_BLUR_BIT 0x05
#define EDGE_DETECTION_BIT 0x06
#define CUSTOM_FILTER_BIT 0x07

class EffectEngine {
    public:
        EffectEngine();
        ~EffectEngine();

        void process(void);
        void gui(void); // ImGui calls only...
        inline Mat * poll(void) { return &output; }

    private:

        void applyGrayscaleFilter(void);
        void applySepiaFilter(void);
        void applySharpFilter(void);
        void applyInvertingFilter(void);
        void applyBoxBlurFilter(void);
        void applyGaussianBlurFilter(void);
        void applyEdgeDetectionFilter(void);
        void applyCustomFilter(void);
        void applyBrightness(void);

        // Output image to renderer...
        Mat output;

        // Common kernels...
        const Mat SEPIA_KERNEL =
            (Mat_<float>(3, 3)
                <<
                0.272, 0.534, 0.131,
                0.349, 0.686, 0.168,
                0.393, 0.769, 0.189);
        const Mat SHARPEN_KERNEL = 
            (Mat_<float>(3, 3)
                <<
                -1, -1,  -1,
                -1, 9.5, -1,
                -1, -1,  -1);
        const Mat BOX_BLUR_KERNEL = 
            (Mat_<float>(3, 3)
                <<
                (1 / 9.0f), (1 / 9.0f), (1 / 9.0f),
                (1 / 9.0f), (1 / 9.0f), (1 / 9.0f),
                (1 / 9.0f), (1 / 9.0f), (1 / 9.0f));
        const Mat GAUSSIAN_BLUR_KERNEL = 
            (Mat_<float>(5, 5)
                <<
                (GAUSSIAN_MATRIX_CONSTANT * 1), (GAUSSIAN_MATRIX_CONSTANT * 4),  (GAUSSIAN_MATRIX_CONSTANT * 6),  (GAUSSIAN_MATRIX_CONSTANT * 4),  (GAUSSIAN_MATRIX_CONSTANT * 1),
                (GAUSSIAN_MATRIX_CONSTANT * 4), (GAUSSIAN_MATRIX_CONSTANT * 16), (GAUSSIAN_MATRIX_CONSTANT * 24), (GAUSSIAN_MATRIX_CONSTANT * 16), (GAUSSIAN_MATRIX_CONSTANT * 4),
                (GAUSSIAN_MATRIX_CONSTANT * 6), (GAUSSIAN_MATRIX_CONSTANT * 24), (GAUSSIAN_MATRIX_CONSTANT * 36), (GAUSSIAN_MATRIX_CONSTANT * 24), (GAUSSIAN_MATRIX_CONSTANT * 6),
                (GAUSSIAN_MATRIX_CONSTANT * 4), (GAUSSIAN_MATRIX_CONSTANT * 16), (GAUSSIAN_MATRIX_CONSTANT * 24), (GAUSSIAN_MATRIX_CONSTANT * 16), (GAUSSIAN_MATRIX_CONSTANT * 4),
                (GAUSSIAN_MATRIX_CONSTANT * 1), (GAUSSIAN_MATRIX_CONSTANT * 4),  (GAUSSIAN_MATRIX_CONSTANT * 6),  (GAUSSIAN_MATRIX_CONSTANT * 4),  (GAUSSIAN_MATRIX_CONSTANT * 1));
        const Mat EDGE_DETECTION_KERNEL = 
            (Mat_<float>(3, 3)
                <<
                -1, -1, -1,
                -1,  8, -1,
                -1, -1, -1);
        // Init as identity kernel...
        Mat customKernel =
            (Mat_<float>(3, 3)
                <<
                0, 0, 0,
                0, 1, 0,
                0, 0, 0);

        // Effect states
        bool effectState[FILTER_COUNT] = { false };
        float brightness = 1.0f;
};

#endif // _EFFECT_ENGINE_H_
