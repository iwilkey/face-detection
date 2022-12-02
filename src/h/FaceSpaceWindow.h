#ifndef _FACE_SPACE_WINDOW_H_
#define _FACE_SPACE_WINDOW_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace cv;

class FaceSpaceWindow {
    public:
        FaceSpaceWindow(const unsigned, 
                        const unsigned);
        ~FaceSpaceWindow();

        inline unsigned getWindowWidth(void) { return dim.x; }
        inline unsigned getWindowHeight(void) { return dim.y; }
        inline GLFWwindow * getWindowHandle(void) { return windowHandle; }
        inline bool windowShouldClose(void) { return glfwWindowShouldClose(windowHandle); }

        void render(void);
        void dispose(void);

    private:
        Point2i dim;
        GLFWwindow * windowHandle = nullptr;
};

#endif // _FACE_SPACE_WINDOW_H_
