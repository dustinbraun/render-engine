#include "directional_light_node.hpp"
#include "mesh_node.hpp"
#include "node.hpp"
#include "scene.hpp"

void Scene::render(const Camera& camera) {
    // -----------------------------------------------
    // GEOMETRY PASS
    for (auto node : m_nodes) {
        node->enqueue((*this));
    }
    // -----------------------------------------------
    m_g_buffer.bind_framebuffer();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    // -----------------------------------------------
    m_mesh_program.use();
    glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(camera.m_projection));
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(camera.m_view));
    for (auto mesh : m_mesh_queue) {
        glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mesh->m_transform));
        mesh->m_texture->bind(0);
        mesh->m_mesh->render();
    }
    m_mesh_queue.clear();
    // -----------------------------------------------
    // LIGHT PASS
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquation(GL_ADD);
    // -----------------------------------------------
    m_ambient_light_program.use();
    m_g_buffer.bind_position(0);
    m_g_buffer.bind_normal(1);
    m_g_buffer.bind_diffuse(2);
    m_quad.render();
    // -----------------------------------------------
    for (auto node : m_directional_light_queue) {
        // -----------------------------------------------
        // DEPTH SHADOW PASS
        glViewport(0, 0, m_config.m_shadow_map_extent.m_w, m_config.m_shadow_map_extent.m_h);
        m_shadow_depth_map.bind_framebuffer();
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        for (auto node : m_nodes) {
            node->enqueue_depth((*this));
        }
        // -----------------------------------------------
        m_mesh_depth_program.use();
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(node->m_view_projection));
        
        for (auto mesh : m_mesh_queue) {
            glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mesh->m_transform));
            mesh->m_mesh->render();
        }
        m_mesh_queue.clear();

        glDisable(GL_DEPTH_TEST);
        glViewport(0, 0, m_config.m_screen_extent.m_w, m_config.m_screen_extent.m_h);
        //glViewport(0, 0, 800, 600);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        m_directional_light_program.use();
        m_g_buffer.bind_position(0);
        m_g_buffer.bind_normal(1);
        m_g_buffer.bind_diffuse(2);
        m_shadow_depth_map.bind_texture(3);
        glUniform3f(0, node->m_direction.x, node->m_direction.y, node->m_direction.z);
        glUniform3f(1, node->m_color.x, node->m_color.y, node->m_color.z);
        glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(node->m_view_projection));
        m_quad.render();
    }
    m_directional_light_queue.clear();
}

void Scene::update(float dt) {
    for (auto node : m_nodes) {
        assert(node != nullptr);
        node->update(dt);
    }
}

void Scene::enqueue_mesh(const MeshNode& mesh) {
    m_mesh_queue.push_back(&mesh);
}

void Scene::enqueue_directional_light(const DirectionalLightNode& node) {
    m_directional_light_queue.push_back(&node);
}

void Scene::render_depth(const DirectionalLightNode& node) {
    glViewport(0, 0, 1024, 1024);
    m_shadow_depth_map.bind_framebuffer();
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    float near_plane = 1.0f, far_plane = 100.0f;
    glm::mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 light_view = glm::lookAt(
        (-node.m_direction)*3.0f,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // -----------------------------------------------
    for (auto node : m_nodes) {
        node->enqueue_depth((*this));
    }
    // -----------------------------------------------
    m_mesh_program.use();
    glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(light_projection));
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(light_view));
    
    for (auto mesh : m_mesh_queue) {
        glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mesh->m_transform));
        mesh->m_mesh->render();
    }
    m_mesh_queue.clear();

    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, 800, 600);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}