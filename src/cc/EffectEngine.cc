#ifndef _EFFECT_ENGINE_CC_
#define _EFFECT_ENGINE_CC_

#include <algorithm>
#include "../h/FaceSpaceCore.h"
#include "../h/EffectEngine.h"
#include "Matrix.cc"

EffectEngine::EffectEngine() {
    BOX_BLUR_KERNEL = createUniformSquareMatrix(BOX_FILTER_KERNAL_SIZE, 1.0f);
    divideMatrixElementsBy(BOX_BLUR_KERNEL, BOX_FILTER_KERNAL_SIZE * BOX_FILTER_KERNAL_SIZE);
}

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
    ImGui::Text("Custom kernel creator");
    ImGui::PushItemWidth(100);
    int index = 0;
    for(int i = 0; i < 3; i++) {
        string i1 = "##" + to_string(index);
        string i2 = "##" + to_string(index + 1);
        string i3 = "##" + to_string(index + 2);
        ImGui::InputFloat(i1.c_str(), &customKernelArray[index]);
        ImGui::SameLine();
        ImGui::InputFloat(i2.c_str(), &customKernelArray[index + 1]);
        ImGui::SameLine();
        ImGui::InputFloat(i3.c_str(), &customKernelArray[index + 2]);
        index += 3;
    }
    ImGui::PopItemWidth();
    if(ImGui::Button("Reset")) 
        for(int k = 0; k < 9; k++)
            customKernelArray[k] = (k != 4) ? 0.0f : 1.0f;
    ImGui::Checkbox("Apply custom kernel (2D filter)", &effectState[CUSTOM_FILTER_BIT]);

    ImGui::SliderFloat("Brightness", &brightness, 0, 100.0f);
    ImGui::SliderFloat("Contrast", &contrast, 0, 5.0f);
    ImGui::Separator();
    ImGui::Text("Face Detection");
    ImGui::Checkbox("Show bounding rectangle", &showFaceDetection);
    ImGui::SliderFloat("Scale factor", &scale, 1.0f, 4.0f);
    ImGui::SliderInt("Minimum neighbors", &neighbors, 0, 10);
    ImGui::SliderInt("Minimum object size", &minSize, 0, 1200);
    ImGui::SliderInt("Maximum object size", &maxSize, 0, 1200);
    ImGui::End();
}

void EffectEngine::process(void) {
    this->output = FaceSpaceCore::pollWebcam();

    detectFace();
    applyWeight();

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
    if(showFaceDetection)
        rectangle(this->output, face, Scalar(0, 255, 0), 2);
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
    customKernel = Mat(3, 3, CV_32F, &customKernelArray);
    filter2D(this->output, this->output, -1, customKernel);
}

void EffectEngine::applyWeight(void) {
    addWeighted(this->output, this->contrast, this->output, 0, this->brightness, this->output);
}

bool compareRectArea(Rect r1, Rect r2) {
    return r1.area() < r2.area();
}

void EffectEngine::detectFace() {
    // Create a normalized, gray-scale version of the captured image..
    Mat grayFrame;
    cvtColor(this->output, grayFrame, COLOR_BGR2GRAY);
    equalizeHist(grayFrame, grayFrame);
    // Detect the features in the normalized, gray-scale version of the
    // image. I don't need to clear the previously-found features because the
    // detectMultiScale method will clear before adding new features...
    classifier.detectMultiScale(grayFrame, 
        features, 
        this->scale, // Parameter specifying how much the image size is reduced at each image scale.
        this->neighbors, // Parameter specifying how many neighbors each candidate rectangle should have to retain it.
        0 | CASCADE_SCALE_IMAGE,  // Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
        Size(this->minSize, this->maxSize)); // Minimum object size, maximum object size. All other objects are ignored.
    // Sort the found features by area in decreasing order...
    sort(features.begin(), features.end(), compareRectArea);
    // Save the face rect as the largest feature.
    face = features[0];
}

#endif // _EFFECT_ENGINE_CC_
