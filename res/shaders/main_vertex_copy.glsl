#version 440 core

layout(location = 0) in vec3 a_squre_position;
layout(location = 1) in vec4 a_squre_color;

out vec3 v_squre_pos;
out vec4 v_squre_color;

void main()
{
    v_squre_color = a_squre_color;
    v_squre_pos = a_squre_position;
    gl_Position = vec4(a_squre_position, 1.0);
}