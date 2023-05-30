#include <SDL2/SDL.h>
#include "glew.h"
#include <iostream>

#include "scene.hpp"
#include "mesh.hpp"
#include "mesh_node.hpp"
#include "directional_light_node.hpp"

class MyMeshNode : public MeshNode {
public:
    MyMeshNode(const Mesh & mesh, const Texture2D& texture, const glm::vec3& position) : m_position(position) {
        m_mesh = &mesh;
        m_texture = &texture;
        m_transform = glm::translate(position);
        m_position = position;
        m_rotation = 0.0f;
    }

    void update(float dt) override {
        m_rotation += dt;
        m_transform = glm::translate(m_position)*glm::rotate(m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    float m_rotation;
    glm::vec3 m_position;
};

struct MyLight : public DirectionalLightNode {
public:
    MyLight(
        glm::vec3 direction,
        glm::vec3 color
    ) : DirectionalLightNode(direction, color) {

    }

    void update(float dt) override {
        m_t += dt;
        m_color.r = (sin(m_t) + 1.0f)/2.0f;
        m_color.g = (sin(m_t) + 1.0f)/2.0f;
        m_color.b = (sin(m_t) + 1.0f)/2.0f;
    }

    float m_t = 0.0f;
};

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window * window = SDL_CreateWindow("OGL", 0, 0, 800, 600, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewInit();

    GLint major_version;
    GLint minor_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    std::cout << "OpenGL Version " << major_version << "." << minor_version << std::endl;

    SceneConfig scene_config;
    scene_config.m_screen_extent.m_w = 800;
    scene_config.m_screen_extent.m_h = 600;
    scene_config.m_shadow_map_extent.m_w = 2048;
    scene_config.m_shadow_map_extent.m_h = 2048;

    Scene scene(scene_config);

    Texture2D texture;
    texture.init_from_file("../data/null_texture.bmp");

    Mesh mesh;
    mesh.init_cube();

    Mesh plane_mesh;
    plane_mesh.init_plane();

    MeshNode plane_node(plane_mesh, texture, glm::scale(glm::vec3(10.0f, 10.0f, 10.0f)));
    scene.attach_node(plane_node);

    MyMeshNode node1(mesh, texture, glm::vec3(0.0f, 0.5f, 0.0f));
    scene.attach_node(node1);
    MyMeshNode node2(mesh, texture, glm::vec3(2.0f, 0.5f, 0.0f));
    scene.attach_node(node2);
    MyMeshNode node3(mesh, texture, glm::vec3(-2.0f, 0.5f, 0.0f));
    scene.attach_node(node3);

    DirectionalLightNode light_node1(
        glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f)),
        glm::vec3(0.5f, 0.5f, 0.5f)
    );
    scene.attach_node(light_node1);

    MyLight light_node2(
        glm::normalize(glm::vec3(1.0f, -1.0f, 0.0f)),
        glm::vec3(0.5f, 0.5f, 0.5f)
    );
    scene.attach_node(light_node2);

    Camera camera;
    camera.m_position = glm::vec3(0.0f, 4.0f, 4.0f);
    camera.m_projection = glm::perspective(glm::radians(45.0f), (GLfloat)800 / (GLfloat)600, 1.0f, 150.0f);
    camera.m_view = glm::lookAt(camera.m_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }

        scene.update(0.01f);
        scene.render(camera);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}