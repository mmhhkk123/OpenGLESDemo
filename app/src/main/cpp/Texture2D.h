//
// Created by zhzl on 2018/3/1.
//

#ifndef MYAPP1_TEXTURE2D_H
#define MYAPP1_TEXTURE2D_H

#include <GLES2/gl2.h>
#include "gl3stub.h"

class Texture2D
{
public:
    Texture2D() : Width(0), Height(0)
    , Internal_Format(GL_RGB), Image_Format(GL_RGB)
    , Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT)
    , Filter_Min(GL_LINEAR), Filter_Mag(GL_LINEAR)
    {
        glGenTextures(1, &ID);
    }

    void Generate(GLuint width, GLuint height, unsigned char* data)
    {
        Width = width;
        Height = height;

        glBindTexture(GL_TEXTURE_2D, ID);
        // 参数2：纹理指定多级渐远纹理级别
        // 参数6：总是设为0，历史遗留问题
        // 参数8：源图的数据类型
        // 参数9：源图的数据
        glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, Width, Height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Mag);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    GLuint ID;
    GLuint Width, Height;       // 纹理的宽度和高度
    GLuint Internal_Format;     // 纹理存储格式
    GLuint Image_Format;        // 源图的存储格式
    GLuint Wrap_S;              // 纹理环绕方式 S 轴
    GLuint Wrap_T;              // 纹理环绕方式 T 轴
    GLuint Filter_Min;          // 纹理过滤方式 缩小（Minify）
    GLuint Filter_Mag;          // 纹理过滤方式 放大（Magnify）
};

#endif //MYAPP1_TEXTURE2D_H
