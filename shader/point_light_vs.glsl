#version 450

layout(location = 0) in vec2 i_vertex_position;
layout(location = 1) in vec2 i_vertex_texcoord;

layout(location = 0) out vec2 o_texcoord;

void main() {
    o_texcoord = i_vertex_texcoord;
    gl_Position = vec4(i_vertex_position, 0.0f, 1.0);
}