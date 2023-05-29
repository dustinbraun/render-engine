#pragma once

#include "common.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"

class Vertex {
public:
    float m_px;
    float m_py;
    float m_pz;
    float m_nx;
    float m_ny;
    float m_nz;
    float m_tu;
    float m_tv;
};

class Mesh {
public:
    Mesh() : m_index_count(0) {

    }

    void init(const Vertex* vertices, size_t vertex_count, const uint16_t* indices, size_t index_count) {
        m_index_count = index_count;
        m_vb.init(vertices, sizeof(Vertex)*vertex_count);
        m_ib.init(indices, sizeof(uint16_t)*index_count);
        m_va.init();
        glVertexArrayVertexBuffer(m_va.get_id(), 0, m_vb.get_id(), 0, sizeof(Vertex));
        glVertexArrayElementBuffer(m_va.get_id(), m_ib.get_id());
        glEnableVertexArrayAttrib(m_va.get_id(), 0);
        glEnableVertexArrayAttrib(m_va.get_id(), 1);
        glEnableVertexArrayAttrib(m_va.get_id(), 2);
        glVertexArrayAttribFormat(m_va.get_id(), 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribFormat(m_va.get_id(), 1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3);
        glVertexArrayAttribFormat(m_va.get_id(), 2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*6);
        glVertexArrayAttribBinding(m_va.get_id(), 0, 0);
        glVertexArrayAttribBinding(m_va.get_id(), 1, 0);
        glVertexArrayAttribBinding(m_va.get_id(), 2, 0);
    }

    void init_cube() {
        constexpr Vertex vertices[] = {
            // -----------------------
            { -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, },
            {  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, },
            {  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, },
            {  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, },
            { -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, },
            { -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, },
            // -----------------------
            { -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, },
            {  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f, },
            {  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, },
            {  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, },
            { -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, },
            { -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, },
            // -----------------------
            { -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, },
            { -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, },
            { -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, },
            { -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, },
            { -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, },
            { -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, },
            // -----------------------
            {  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, },
            {  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, },
            {  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, },
            {  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, },
            {  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, },
            {  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, },
            // -----------------------
            { -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, },
            {  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f, },
            {  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, },
            {  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, },
            { -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f, },
            { -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, },
            // -----------------------
            { -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, },
            {  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f, },
            {  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, },
            {  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, },
            { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, },
            { -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, },
        };
        constexpr uint16_t indices[] = {
             0,  1,  2,  3,  4,  5,
             6,  7,  8,  9, 10, 11,
            12, 13, 14, 15, 16, 17,
            18, 19, 20, 21, 22, 23,
            24, 25, 26, 27, 28, 29,
            30, 31, 32, 33, 34, 35,
        };
        init(vertices, 36, indices, 36);
    }

    void init_plane() {
        constexpr Vertex vertices[] = {
            { -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, },
            { +0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, },
            { -0.5f, 0.0f, +0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, },
            { +0.5f, 0.0f, +0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, },
        };
        constexpr uint16_t indices[] = {
            0, 1, 2, 2, 3, 1,
        };
        init(vertices, 4, indices, 6);
    }

    void render() const {
        m_va.bind();
        glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_SHORT, nullptr);
    }

private:
    size_t m_index_count;

    IndexBuffer m_ib;
    VertexBuffer m_vb;
    VertexArray m_va;
};