#ifndef _FACE_SPACE_WINDOW_CC_
#define _FACE_SPACE_WINDOW_CC_

#include "../h/FaceSpaceCore.h"
#include "../h/FaceSpaceWindow.h"

FaceSpaceWindow::FaceSpaceWindow(const unsigned width, 
                                 const unsigned height) {
    Point2i dimm(width, height);
    this->dim = dimm;
    FaceSpaceCore::log(NOTICE, "Starting FaceSpace window construction...");
    if(!glfwInit()) {
        FaceSpaceCore::log(ERROR, "GLFW could not be initialized.");
        exit(-1);
    }
    FaceSpaceCore::log(SUCCESS, "GLFW initialized.");
    FaceSpaceCore::log(NOTICE, "Creating window handle...");
    windowHandle = glfwCreateWindow(width, height, "FaceSpace", nullptr, nullptr);
    FaceSpaceCore::log(NOTICE, "Making GL context current...");
    glfwMakeContextCurrent(windowHandle);
    FaceSpaceCore::log(NOTICE, "Setting VSync to true...");
    glfwSwapInterval(1);
    FaceSpaceCore::log(NOTICE, "Initializing gl3w...");
    gl3wInit();
    printf("\tOpenGL version %s using GLSL version 120\n", glGetString(GL_VERSION));
    IMGUI_CHECKVERSION();
    FaceSpaceCore::log(NOTICE, "Creating ImGui context...");
    ImGui::CreateContext();
    FaceSpaceCore::log(NOTICE, "Initializing GLFW for ImGui...");
    ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
    FaceSpaceCore::log(NOTICE, "Initializing OpenGL for ImGui...");
    ImGui_ImplOpenGL3_Init("#version 120");
    FaceSpaceCore::log(SUCCESS, "FaceSpace window successfully created.");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

FaceSpaceWindow::~FaceSpaceWindow() {}

void FaceSpaceWindow::render(void) {
    glfwPollEvents();
    FaceSpaceCore::getRenderer()->render();
}

void FaceSpaceWindow::dispose(void) {
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

#endif //  _FACE_SPACE_WINDOW_CC_
