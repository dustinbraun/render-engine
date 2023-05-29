#pragma once

#include "common.hpp"

class VertexBuffer {
public:
    VertexBuffer() : m_id(0) {
        
    }

    ~VertexBuffer() {
        if (m_id != 0) {
            glDeleteBuffers(1, &m_id);
        }
    }

    void init(const void * data, size_t size) {
        glCreateBuffers(1, &m_id);
        assert(m_id != 0);
        glNamedBufferStorage(m_id, static_cast<GLsizeiptr>(size), data, GL_DYNAMIC_STORAGE_BIT);
        if (glGetError() != GL_NO_ERROR) {
            throw "Error";
        }
    }

    GLuint
    get_id() const {
        assert(m_id != 0);
        return m_id;
    }

private:
    GLuint m_id;
};