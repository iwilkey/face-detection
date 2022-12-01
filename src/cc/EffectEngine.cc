#ifndef _EFFECT_ENGINE_CC_
#define _EFFECT_ENGINE_CC_

#include "../h/FaceSpaceCore.h"
#include "../h/EffectEngine.h"

EffectEngine::EffectEngine() {}

EffectEngine::~EffectEngine() {}

void EffectEngine::gui(void) {
    ImGui::Begin("Effect Engine");
    ImGui::Text("Use the Effect Engine to alter your FaceSpace!");
    ImGui::Separator();
    ImGui::Text("Filtering");
    ImGui::Checkbox("Apply grayscale (dimensional conversion)", &effectState[GRAYSCALE_FILTER_BIT]);
    ImGui::Checkbox("Apply sepia (2D filter)", &effectState[SEPIA_FILTER_BIT]);
    ImGui::Checkbox("Apply sharpening (2D filter)", &effectState[SHARP_FILTER_BIT]);
    ImGui::Checkbox("Apply inverting (logical NOT)", &effectState[INVERTING_FILTER_BIT]);
    ImGui::Checkbox("Apply box blur (2D filter)", &effectState[BOX_BLUR_BIT]);
    ImGui::Checkbox("Apply guassian blur (2D filter)", &effectState[GAUSSIAN_BLUR_BIT]);
    ImGui::Checkbox("Apply edge detection (2D filter)", &effectState[EDGE_DETECTION_BIT]);
    ImGui::Checkbox("Apply custom filter (2D filter)", &effectState[CUSTOM_FILTER_BIT]);
    ImGui::SliderFloat("Brightness", &brightness, 0, 5.0f);
    ImGui::End();
}

void EffectEngine::process(void) {
    this->output = FaceSpaceCore::pollWebcam();
    applyBrightness();

    // These two filters cannot exist together because of dimensional differences.
    if(effectState[GRAYSCALE_FILTER_BIT] && effectState[SEPIA_FILTER_BIT]) {
        effectState[GRAYSCALE_FILTER_BIT] = false;
        effectState[SEPIA_FILTER_BIT] = false;
    }
    
    if(effectState[GRAYSCALE_FILTER_BIT])
        applyGrayscaleFilter();
    if(effectState[SEPIA_FILTER_BIT])
        applySepiaFilter();
    if(effectState[SHARP_FILTER_BIT])
        applySharpFilter();
    if(effectState[INVERTING_FILTER_BIT])
        applyInvertingFilter();
    if(effectState[BOX_BLUR_BIT])
        applyBoxBlurFilter();
    if(effectState[GAUSSIAN_BLUR_BIT])
        applyGaussianBlurFilter();
    if(effectState[EDGE_DETECTION_BIT])
        applyEdgeDetectionFilter();
    if(effectState[CUSTOM_FILTER_BIT])
        applyCustomFilter();

}

void EffectEngine::applyGrayscaleFilter(void) {
    cvtColor(this->output, this->output, COLOR_BGR2GRAY);
}

void EffectEngine::applySepiaFilter(void) {
    transform(this->output, this->output, SEPIA_KERNEL);
}

void EffectEngine::applySharpFilter(void) {
    filter2D(this->output, this->output, -1, SHARPEN_KERNEL);
}

void EffectEngine::applyInvertingFilter(void) {
    bitwise_not(this->output, this->output);
}

void EffectEngine::applyBoxBlurFilter(void) {
    filter2D(this->output, this->output, -1, BOX_BLUR_KERNEL);
}

void EffectEngine::applyGaussianBlurFilter(void) {
    filter2D(this->output, this->output, -1, GAUSSIAN_BLUR_KERNEL);
}

void EffectEngine::applyEdgeDetectionFilter(void) {
    filter2D(this->output, this->output, -1, EDGE_DETECTION_KERNEL);
}

void EffectEngine::applyCustomFilter(void) {
    filter2D(this->output, this->output, -1, customKernel);
}

void EffectEngine::applyBrightness(void) {
    convertScaleAbs(this->output, this->output, brightness);
}

#endif // _EFFECT_ENGINE_CC_
