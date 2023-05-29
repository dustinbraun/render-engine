#version 450

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 vertex_normals;
layout(location = 2) in vec2 vertex_tex_coords;

layout(location = 0) uniform mat4 transform;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

out vec2 var_tex_coords;
out vec3 var_vertex_normals;
out vec3 var_frag_pos;

void main() {
    var_tex_coords = vertex_tex_coords;
    var_vertex_normals = mat3(transpose(inverse(transform))) * vertex_normals;
    var_frag_pos = vec3(transform * vec4(vertex_pos, 1.0));
    gl_Position = projection*view*transform*vec4(vertex_pos.x, vertex_pos.y, vertex_pos.z, 1.0);
}