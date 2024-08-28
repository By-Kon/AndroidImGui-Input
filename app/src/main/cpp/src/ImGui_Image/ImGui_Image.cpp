//
// Created by Administrator on 2023/9/27.
//

#include "ImGui_Image.h"

ImTextureID ImGui_Image::LoadTexture(const char* filepath)
{
    int width, height, channels;
    unsigned char* image_data = stbi_load(filepath, &width, &height, &channels, 0);
    if (!image_data)
    {
        // 图片加载失败，处理错误
        // 这里可以添加错误处理逻辑
        return 0;
    }

    // 创建纹理
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);

    // 释放图片数据
    stbi_image_free(image_data);

    return (ImTextureID)(intptr_t)texture_id;
}