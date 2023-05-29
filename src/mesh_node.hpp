#pragma once

#include "common.hpp"
#include "mesh.hpp"
#include "node.hpp"
#include "scene.hpp"

class MeshNode : public Node {
public:
    const Mesh* m_mesh;
    glm::mat4 m_transform;

    MeshNode() : m_mesh(nullptr), m_transform(glm::translate(glm::vec3(0.0f, 0.0f, 0.0f))) {

    }

    MeshNode(const Mesh& mesh, const glm::mat4& transform) : m_mesh(&mesh), m_transform(transform) {
        
    }

    void enqueue(Scene& scene) override {
        scene.enqueue_mesh((*this));
    }

    void enqueue_depth(Scene& scene) override {
        scene.enqueue_mesh((*this));
    }
};