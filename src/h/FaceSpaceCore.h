#ifndef _FACE_SPACE_CORE_H_
#define _FACE_SPACE_CORE_H_

#define VERSION "p1"

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#include "FaceSpaceWindow.h"
#include "FaceSpaceRenderer.h"
#include "EffectEngine.h"

enum LogType {
    SUCCESS,
    NOTICE,
    ERROR
};

class FaceSpaceCore {
    public:
        FaceSpaceCore();
        ~FaceSpaceCore();

        void loop(void);
        void terminate(void);
        static void log(LogType, 
                        string);
        static Mat pollWebcam(void);
        inline void setTargetFPS(double fps) { this->targetFPS = fps; }
        inline static FaceSpaceWindow * getWindow(void) { return window; }
        inline static FaceSpaceRenderer * getRenderer(void) { return renderer; }
        inline static EffectEngine * getEffectEngine(void) { return effect; }
        inline static VideoCapture * getWebcam(void) { return webcam; }

    private:
        static FaceSpaceWindow * window;
        static FaceSpaceRenderer * renderer;
        static EffectEngine * effect;
        static VideoCapture * webcam;
        double targetFPS = 60.0f;
};

#endif // _FACE_SPACE_CORE_H_
