#pragma once

#include "common.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"

class Quad {
public:
    void init() {
        constexpr float vertices[] = {
            -1.0f, -1.0f, 0.0f, 0.0f,
            +1.0f, -1.0f, 1.0f, 0.0f,
            -1.0f, +1.0f, 0.0f, 1.0f,
            +1.0f, +1.0f, 1.0f, 1.0f,
        };
        m_vertex_buffer.init(vertices, 64);
        constexpr uint8_t indices[] = {
            0, 1, 2, 2, 1, 3,
        };
        m_index_buffer.init(indices, 6);
        m_vertex_array.init();
        glVertexArrayVertexBuffer(m_vertex_array.get_id(), 0, m_vertex_buffer.get_id(), 0, sizeof(float)*4);
        glVertexArrayElementBuffer(m_vertex_array.get_id(), m_index_buffer.get_id());
        glEnableVertexArrayAttrib(m_vertex_array.get_id(), 0);
        glEnableVertexArrayAttrib(m_vertex_array.get_id(), 1);
        glVertexArrayAttribFormat(m_vertex_array.get_id(), 0, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribFormat(m_vertex_array.get_id(), 1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2);
        glVertexArrayAttribBinding(m_vertex_array.get_id(), 0, 0);
        glVertexArrayAttribBinding(m_vertex_array.get_id(), 1, 0);
    }
    
    void render() {
        m_vertex_array.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
    }

private:
    IndexBuffer m_index_buffer;
    VertexArray m_vertex_array;
    VertexBuffer m_vertex_buffer;
};