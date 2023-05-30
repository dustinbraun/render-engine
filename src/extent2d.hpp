#pragma once

#include <cstdint>

class Extent2D {
public:
    uint32_t m_w;
    uint32_t m_h;


    Extent2D() : m_w(0), m_h(0) {

    }

    Extent2D(uint32_t w, uint32_t h) : m_w(w), m_h(h) {
        
    }
};