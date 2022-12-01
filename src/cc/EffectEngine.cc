#ifndef _EFFECT_ENGINE_CC_
#define _EFFECT_ENGINE_CC_

#include "../h/FaceSpaceCore.h"
#include "../h/EffectEngine.h"

EffectEngine::EffectEngine() {

    isGrayScale = false;
    isSepia = false;
    isSharp = false;
    isPencil = false;
    isDetailEnhance = false;
    isInverted = false;
    brightness = 1.0f;

    sepiaKernel =
            (Mat_<float>(3, 3)
                <<
                0.272, 0.534, 0.131,
                0.349, 0.686, 0.168,
                0.393, 0.769, 0.189);

    sharpenKernel = 
            (Mat_<float>(3, 3)
                <<
                -1, -1, -1,
                -1, 9.5, -1,
                -1, -1, -1);

}

EffectEngine::~EffectEngine() {}

void EffectEngine::gui(void) {
    ImGui::Begin("Effect Engine");
    ImGui::Text("Use the Effect Engine to alter your FaceSpace!");

    ImGui::Separator();
    ImGui::Text("Filtering");
    ImGui::Checkbox("Grayscale", &isGrayScale);
    ImGui::Checkbox("Sepia", &isSepia);
    ImGui::Checkbox("Sharpen", &isSharp);
    ImGui::Checkbox("Pencil sketch", &isPencil);
    ImGui::Checkbox("Enhance detail (HDR)", &isDetailEnhance);
    ImGui::Checkbox("Invert", &isInverted);
    ImGui::SliderFloat("Brightness", &brightness, 0, 5.0f);

    ImGui::End();
}

void EffectEngine::process(void) {

    this->output = FaceSpaceCore::pollWebcam();

    convertScaleAbs(this->output, this->output, brightness);

    if(isGrayScale)
        cvtColor(this->output, this->output, COLOR_BGR2GRAY);
    if(isSepia && !isGrayScale)
        transform(this->output, this->output, sepiaKernel);
    else isSepia = false; // Sepia cannot process during grayscale because of dim change...
    if(isSharp)
        filter2D(this->output, this->output, -1, sharpenKernel);
    if(isPencil && !isGrayScale) {
        Mat bwp;
        pencilSketch(this->output, bwp, this->output, 60, 0.01f, 0.03f); // These functions are not very performant...
    } else isPencil = false;
    if(isDetailEnhance && !isGrayScale) 
        detailEnhance(this->output, this->output, 12, 0.15); // These functions are not very performant...
    else isDetailEnhance = false;
    if(isInverted)
        bitwise_not(this->output, this->output);

}

#endif // _FACE_EFFECT_CC_
