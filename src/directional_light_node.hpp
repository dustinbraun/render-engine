#pragma once

#include "common.hpp"
#include "node.hpp"
#include "scene.hpp"

class DirectionalLightNode : public Node {
public:
    DirectionalLightNode(
        const glm::vec3& direction,
        const glm::vec3& color
    ) : m_direction(direction), m_color(color) {
        float near_plane = 0.1f;
        float far_plane = 20.0f;
        glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, near_plane, far_plane);
        glm::mat4 view = glm::lookAt(
            (-m_direction)*5.0f,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        m_view_projection = projection*view;
    }

    void enqueue(Scene& scene) override {
        scene.enqueue_directional_light((*this));
    }

    glm::vec3 m_direction;
    glm::vec3 m_color;
    glm::mat4 m_view_projection;
};