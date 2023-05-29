#pragma once

#include "common.hpp"

class VertexArray {
public:
    VertexArray() : m_id(0) {
        
    }

    ~VertexArray() {
        if (m_id != 0) {
            glDeleteVertexArrays(1, &m_id);
        }
    }

    void init() {
        glCreateVertexArrays(1, &m_id);
        assert(m_id != 0);
    }

    GLuint
    get_id() const {
        assert(m_id != 0);
        return m_id;
    }

    void bind() const {
        assert(m_id != 0);
        glBindVertexArray(m_id);
    }

private:
    GLuint m_id;
};