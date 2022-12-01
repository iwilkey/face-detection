#ifndef _EFFECT_ENGINE_H_
#define _EFFECT_ENGINE_H_

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class EffectEngine {
    public:
        EffectEngine();
        ~EffectEngine();

        void process(void);
        void gui(void); // ImGui calls only...
        inline Mat * poll(void) { return &output; }

    private:
        // Output image to renderer
        Mat output;

        // Kernels
        Mat sepiaKernel;
        Mat sharpenKernel;

        // Effect states
        bool isGrayScale;
        bool isSepia;
        bool isSharp;
        bool isPencil;
        bool isDetailEnhance;
        bool isInverted;
        float brightness;
};

#endif // _FACE_EFFECT_H_
