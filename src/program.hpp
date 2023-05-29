#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

#include "common.hpp"

class Program {
public:
    Program() : m_name(0) {

    }

    void init(const char * vs_path, const char * fs_path) {
        GLuint vs = create_shader(GL_VERTEX_SHADER, read_file(vs_path));
        GLuint fs = create_shader(GL_FRAGMENT_SHADER, read_file(fs_path));
        m_name = glCreateProgram();
        glAttachShader(m_name, vs);
        glAttachShader(m_name, fs);
        glLinkProgram(m_name);
        GLint linked;
        glGetProgramiv(m_name, GL_LINK_STATUS, &linked);
        if (linked == GL_FALSE) {
            GLint info_size;
            glGetProgramiv(m_name, GL_INFO_LOG_LENGTH, &info_size);
            std::vector<GLchar> info_log(info_size);
            GLsizei info_log_size;
            glGetShaderInfoLog(m_name, static_cast<GLsizei>(info_log.size()), &info_log_size, info_log.data());
            info_log.push_back('\0');
            std::cout << info_log.data() << std::endl;
        }
    }

    GLuint get_name() const {
        return m_name;
    }

    GLuint get_id() const {
        return m_name;
    }

    void use() {
        glUseProgram(m_name);
    }

private:
    GLuint m_name;


    static GLuint create_shader(GLenum type, const std::string & source) {
        GLuint shader = glCreateShader(type);
        assert(shader != 0);
        const GLchar * source_data = source.data();
        GLint source_size = static_cast<GLint>(source.size());
        glShaderSource(shader, 1, &source_data, &source_size);
        glCompileShader(shader);
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE) {
            GLint info_size;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_size);
            std::vector<GLchar> info_log(info_size);
            GLsizei info_log_size;
            glGetShaderInfoLog(shader, static_cast<GLsizei>(info_log.size()), &info_log_size, info_log.data());
            info_log.push_back('\0');
            std::cout << info_log.data() << std::endl;
        }
        return shader;
    }

    static std::string read_file(const char * path) {
        std::ifstream t(path);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        return str;
    }
};
