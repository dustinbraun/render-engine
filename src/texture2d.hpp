#pragma once

#include "common.hpp"
#include "extent2d.hpp"
#include "stb_image.h"

class Texture2D {
public:
    Texture2D() : m_id(0) {

    }

    ~Texture2D() {
        if (m_id != 0) {
            glDeleteTextures(1, &m_id);
        }
    }

    void init(const Extent2D& extent, GLenum format) {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glTextureStorage2D(m_id, 1, format, extent.m_w, extent.m_h);
    }

    void init_from_file(const char * path) {
        int width, height, nrChannels;
        unsigned char * data = stbi_load(path, &width, &height, &nrChannels, 0);
        Extent2D extent;
        extent.m_w = width;
        extent.m_h = height;
        init(extent, GL_RGB8);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureSubImage2D(m_id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    void bind(GLuint unit) const {
        glBindTextureUnit(unit, m_id);
    }

private:
    GLuint m_id;
};