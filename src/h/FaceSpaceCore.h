#ifndef _FACE_SPACE_CORE_H_
#define _FACE_SPACE_CORE_H_

#define VERSION "p1"

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#include "FaceSpaceWindow.h"

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
        static void log(LogType, string);
        inline void setTargetFPS(double fps) { this->targetFPS = fps; }
        inline static FaceSpaceWindow * getWindow(void) { return window; }

    private:
        static FaceSpaceWindow * window;
        double targetFPS = 24.0f;
};

#endif // _FACE_SPACE_CORE_H_
