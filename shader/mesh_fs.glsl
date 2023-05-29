#version 450

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec3 out_normal;
layout(location = 2) out vec3 out_diffuse;

in vec2 var_tex_coords;
in vec3 var_vertex_normals;
in vec3 var_frag_pos;

//layout(binding=0) uniform sampler2D diffuse_texture;

void main() {
    out_normal = normalize(var_vertex_normals);
    out_position = var_frag_pos;
    out_diffuse = vec3(1.0, 0.0, 0.0); //texture(diffuse_texture, var_tex_coords).rgb;
}