#ifndef IMAGE_H
#define IMAGE_H
#include "imgui.h"
#include "stb_image.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
ImTextureID ImAgeRouteFile(const char* ImagePath);
ImTextureID ImAgeHeadFile(const unsigned char *buf, int len);
#endif
