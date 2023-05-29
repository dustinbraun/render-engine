#pragma once

#include "common.hpp"

class Texture2D {
public:
    Texture2D() : m_id(0) {

    }

    ~Texture2D() {
        if (m_id != 0) {
            glDeleteTextures(1, &m_id);
        }
    }

    void init() {
        
    }

private:
    GLuint m_id;
};