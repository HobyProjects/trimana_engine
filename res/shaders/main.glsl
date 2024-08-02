#type vertex
#version 440 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

out vec3 v_position;
out vec4 v_color;

uniform mat4 u_projection_view;
uniform mat4 u_model;

void main()
{
    v_color = a_color;
    v_position = a_position;
    gl_Position = u_projection_view * u_model * vec4(a_position, 1.0);
}

#type fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;

uniform vec4 u_color;

void main()
{
    color = u_color;
}