#ifndef _FACE_SPACE_RENDERER_H_
#define _FACE_SPACE_RENDERER_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace cv;

class FaceSpaceRenderer {
    public:
        FaceSpaceRenderer();
        ~FaceSpaceRenderer();
        void render(void);
    private:
};

#endif // _FACE_SPACE_RENDERER_H_
