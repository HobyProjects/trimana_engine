#version 440 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoord;
layout(location = 2) in vec4 a_color;

out vec2 v_texcoord;
out vec4 v_color;

uniform mat4 u_projection_view;
uniform mat4 u_model;

void main()
{
    v_color = a_color;
    v_texcoord = a_texcoord;
    gl_Position = u_projection_view * u_model * vec4(a_position, 1.0);
}