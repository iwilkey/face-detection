cmake_minimum_required(VERSION 2.10)

# FaceSpace sources...
set(src ${CMAKE_SOURCE_DIR}/src)
set(cc ${src}/cc)
set(h ${src}/h)
set(pb-src 
    ${h}/FaceSpaceWindow.h
    ${h}/FaceSpaceCore.h
    ${h}/FaceSpaceRenderer.h
    ${h}/EffectEngine.h

    ${cc}/Invoke.cc
    ${cc}/FaceSpaceCore.cc
    ${cc}/FaceSpaceWindow.cc
    ${cc}/FaceSpaceRenderer.cc
    ${cc}/Matrix.cc
    ${cc}/EffectEngine.cc
)

# ImGui sources...
find_package(Git)
execute_process(
  COMMAND ${GIT_EXECUTABLE} clone "https://github.com/ocornut/imgui.git" -b v1.72b
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
set(IMGUI_DIR ${CMAKE_CURRENT_BINARY_DIR}/imgui)
set(imgui_files
  ${IMGUI_DIR}/imconfig.h
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui.h
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_internal.h
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/imstb_rectpack.h
  ${IMGUI_DIR}/imstb_textedit.h
  ${IMGUI_DIR}/imstb_truetype.h
)
set(imgui_impl_files
  ${IMGUI_DIR}/examples/imgui_impl_glfw.h
  ${IMGUI_DIR}/examples/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/examples/imgui_impl_opengl3.h
  ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp
)

set(gl3w
  ${IMGUI_DIR}/examples/libs/gl3w/GL/gl3w.c
)

project(FaceSpace)
add_executable(FaceSpace ${pb-src} ${imgui_files} ${imgui_impl_files} ${gl3w})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "FaceSpace")
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)

# GLFW sources...
include(ExternalProject)
ExternalProject_Add(
  glfw PREFIX glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3
  CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
    "-DCMAKE_BUILD_TYPE=Release"
    "-DGLFW_BUILD_DOCS=OFF"
    "-DGLFW_BUILD_EXAMPLES=OFF"
    "-DGLFW_BUILD_TESTS=OFF"
)
ExternalProject_Get_Property(glfw INSTALL_DIR)
set(GLFW_DIR ${INSTALL_DIR})
set(GLFW_INCLUDE_DIR ${GLFW_DIR}/include)
set(GLFW_LIBRARIES   ${GLFW_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(FaceSpace glfw)
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/examples)
include_directories(${IMGUI_DIR}/examples/libs/gl3w)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
target_link_libraries(FaceSpace "-framework Cocoa")
target_link_libraries(FaceSpace "-framework IOkit")
target_link_libraries(FaceSpace "-framework CoreVideo")
target_link_libraries(FaceSpace ${OpenCV_LIBS})
target_link_libraries(FaceSpace ${OPENGL_LIBRARIES})
target_link_libraries(FaceSpace ${GLFW_LIBRARIES})

