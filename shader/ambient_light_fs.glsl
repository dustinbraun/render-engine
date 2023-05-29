#version 450

layout(location = 0) out vec4 o_frag_color;

layout(location = 0) in vec2 i_frag_texcoord;

layout(binding = 0) uniform sampler2D u_position;
layout(binding = 1) uniform sampler2D u_normal;
layout(binding = 2) uniform sampler2D u_diffuse;

layout(location = 0) uniform vec3 u_color;

void main() {
    o_frag_color = texture(u_diffuse, i_frag_texcoord)*0.2;
    //o_frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}