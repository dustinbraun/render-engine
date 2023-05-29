#pragma once

#include "camera.hpp"
#include "common.hpp"
#include "program.hpp"
#include "quad.hpp"
#include "g_buffer.hpp"
#include "shadow_depth_map.hpp"

class DirectionalLightNode;
class MeshNode;
class Node;

class Scene {
public:
    Scene() : m_g_buffer(800, 600) {
        m_quad.init();
        m_shadow_depth_map.init();
        m_ambient_light_program.init(
            "../shader/ambient_light_vs.glsl",
            "../shader/ambient_light_fs.glsl"
        );
        m_mesh_program.init(
            "../shader/mesh_vs.glsl",
            "../shader/mesh_fs.glsl"
        );
        m_mesh_depth_program.init(
            "../shader/mesh_depth_vs.glsl",
            "../shader/mesh_depth_fs.glsl"
        );
        m_directional_light_program.init(
            "../shader/directional_light_vs.glsl",
            "../shader/directional_light_fs.glsl"
        );
    }

    void render(const Camera& camera);

    void update(float dt);

    void attach_node(Node& node) {
        m_nodes.push_back(&node);
    }

    void enqueue_mesh(const MeshNode& mesh);

    void enqueue_directional_light(const DirectionalLightNode& node);

private:
    GBuffer m_g_buffer;

    ShadowDepthMap m_shadow_depth_map;

    Quad m_quad;

    Program m_mesh_program;

    Program m_mesh_depth_program;

    Program m_ambient_light_program;

    Program m_directional_light_program;

    std::vector<const MeshNode*> m_mesh_queue;

    std::vector<const DirectionalLightNode*> m_directional_light_queue;

    std::vector<Node*> m_nodes;


    void render_depth(const DirectionalLightNode& node);
};