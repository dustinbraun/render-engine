#version 450

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 vertex_normals;
layout(location = 2) in vec2 vertex_tex_coords;

layout(location = 0) uniform mat4 transform;
layout(location = 1) uniform mat4 view_projection;

void main() {
    gl_Position = view_projection*transform*vec4(vertex_pos.x, vertex_pos.y, vertex_pos.z, 1.0);
}