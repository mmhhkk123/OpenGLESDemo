//
// Created by zhzl on 2018/1/31.
//

#ifndef MYAPP1_SHADER_H
#define MYAPP1_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLES2/gl2.h>
#include "gl3stub.h"
#include "glm/glm.hpp"

class Shader
{
public:

    Shader(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            std::stringstream vShaderStream, fShaderStream;
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            return;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 创建着色器，记录着色器ID
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        // 将着色器源码附加到着色器对象
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        // 编译着色器
        glCompileShader(vertex);
        // 检查是否成功编译
        if (!checkCompileErrors(vertex, "VERTEX"))
        {
            glDeleteShader(vertex);
            return;
        }

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        if (!checkCompileErrors(fragment, "FRAGMENT"))
        {
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            return;
        }

        // 创建着色器程序
        ID = glCreateProgram();
        // 将着色器附加到着色器程序
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        // 链接着色器程序
        glLinkProgram(ID);
        // 检查是否成功链接
        checkCompileErrors(ID, "PROGRAM");
        // 删除着色器
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader(const char* vShaderCode, const int vShaderLen, const char* fShaderCode, const int fShaderLen)
    {
        // 创建着色器，记录着色器ID
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        // 将着色器源码附加到着色器对象
        glShaderSource(vertex, 1, &vShaderCode, &vShaderLen);
        // 编译着色器
        glCompileShader(vertex);
        // 检查是否成功编译
        if (!checkCompileErrors(vertex, "VERTEX"))
        {
            glDeleteShader(vertex);
            return;
        }

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, &fShaderLen);
        glCompileShader(fragment);
        if (!checkCompileErrors(fragment, "FRAGMENT"))
        {
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            return;
        }

        // 创建着色器程序
        ID = glCreateProgram();
        // 将着色器附加到着色器程序
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        // 链接着色器程序
        glLinkProgram(ID);
        // 检查是否成功链接
        checkCompileErrors(ID, "PROGRAM");
        // 删除着色器
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use()
    {
         glUseProgram(ID);
    }

    ///////////////// 给着色器中的uniform变量赋值 //////////////////

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        // 参数1：uniform的位置值
        // 参数2：告诉OpenGL发送多少个矩阵
        // 参数3：是否对矩阵进行置换，即交换矩阵的行和列
        // 参数4：矩阵数据，可以使用glm::value_ptr()来变换数据
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    bool checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            // 检查是否编译成功
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                // 获取错误消息
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n" << std::endl;
                return false;
            }
        }
        else
        {
            // 检查链接是否成功
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                // 获取错误消息
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n" << std::endl;
                return false;
            }
        }
        return true;
    }

private:
    unsigned int ID;  // 着色器程序的ID
};

#endif //MYAPP1_SHADER_H
