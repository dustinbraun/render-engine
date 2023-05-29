#version 450

layout(location = 0) out vec4 o_frag_color;

layout(location = 0) in vec2 i_frag_texcoord;

layout(binding = 0) uniform sampler2D u_position;
layout(binding = 1) uniform sampler2D u_normal;
layout(binding = 2) uniform sampler2D u_color;
layout(binding = 3) uniform sampler2D u_shadow_depth;

layout(location = 0) uniform vec3 u_light_direction;
layout(location = 1) uniform vec3 u_light_color;
layout(location = 2) uniform mat4 u_light_view_projection;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(u_shadow_depth, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = 0.0005;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}  

void main() {
    
    vec4 frag_pos_light_space = u_light_view_projection*vec4(texture(u_position, i_frag_texcoord).rgb, 1.0f);

    float shadow = ShadowCalculation(frag_pos_light_space);

    vec3 frag_color = (1.0 - shadow)*texture(u_color, i_frag_texcoord).rgb*max(dot(texture(u_normal, i_frag_texcoord).rgb, -u_light_direction), 0.0)*u_light_color;
    
    o_frag_color = vec4(frag_color, 1.0);


    //o_frag_color = texture(u_shadow_depth, i_frag_texcoord);
}