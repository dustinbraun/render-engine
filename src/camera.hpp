#pragma once

#include "common.hpp"

class Camera {
public:
    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::vec3 m_position;
};
