#ifndef _FACE_SPACE_RENDERER_CC_
#define _FACE_SPACE_RENDERER_CC_

#include "../h/FaceSpaceCore.h"
#include "../h/FaceSpaceRenderer.h"

FaceSpaceRenderer::FaceSpaceRenderer() {}

FaceSpaceRenderer::~FaceSpaceRenderer() {}

void FaceSpaceRenderer::render(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    FaceSpaceCore::getEffectEngine()->gui();
    
    ImGui::Begin("Your FaceSpace");

    bool shouldRender = true;
    if(!FaceSpaceCore::getWebcam()->isOpened()) {
        ImGui::Text("No webcam available!");
        shouldRender = false;
    }

    if(shouldRender) {
        GLuint texture;
        glGenTextures( 1, &texture );
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        Mat frame = *FaceSpaceCore::getEffectEngine()->poll();
        cvtColor(frame, frame, COLOR_BGR2RGBA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame.cols, frame.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame.data);
        ImVec2 viewport = ImGui::GetContentRegionAvail();
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture)), viewport);
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(FaceSpaceCore::getWindow()->getWindowHandle());
}

#endif // _FACE_SPACE_RENDERER_CC_
