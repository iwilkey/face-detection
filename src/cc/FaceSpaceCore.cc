#ifndef _FACE_SPACE_CORE_CC_
#define _FACE_SPACE_CORE_CC_

#include "../h/FaceSpaceCore.h"

FaceSpaceWindow * FaceSpaceCore::window = nullptr;
FaceSpaceRenderer * FaceSpaceCore::renderer = nullptr;
EffectEngine * FaceSpaceCore::effect = nullptr;
VideoCapture * FaceSpaceCore::webcam = nullptr;

FaceSpaceCore::FaceSpaceCore() {
    FaceSpaceWindow win(1200, 720);
    this->window = &win;
    FaceSpaceRenderer renderer;
    this->renderer = &renderer;
    VideoCapture cap(0);
    this->webcam = &cap;
    EffectEngine effect;
    this->effect = &effect;
    log(SUCCESS, "FaceSpace initialized.");
    loop();
    terminate();
}

FaceSpaceCore::~FaceSpaceCore() {}

void FaceSpaceCore::loop(void) {
    while(!window->windowShouldClose()) {
        effect->process();
        window->render();
        this_thread::sleep_for(chrono::nanoseconds((unsigned)(1.0f / targetFPS) * 1000000000));
    }
}

Mat FaceSpaceCore::pollWebcam(void) {
    Mat frame;
    if(!getWebcam()->isOpened()) 
        return frame;
    *getWebcam() >> frame;
    return frame;
}

void FaceSpaceCore::log(LogType type, 
                        string message) {
    switch(type) {
        case SUCCESS: cout << "\x1b[32m[FaceSpace SUCCESS]\x1b[0m "; break;
        case NOTICE: cout << "\x1b[33m[FaceSpace NOTICE]\x1b[0m "; break;
        case ERROR: cout << "\x1b[31m[FaceSpace ERROR]\x1b[0m "; break;
        default:;
    }
    cout << message << endl;
}

void FaceSpaceCore::terminate(void) {
    this->webcam->release();
    window->dispose();
    log(SUCCESS, "FaceSpace terminated.");
}

#endif // _FACE_SPACE_CORE_CC_
