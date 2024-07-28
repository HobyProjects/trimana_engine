#version 440 core

layout(location = 0) out vec4 squre_color;

in vec3 v_squre_pos;
in vec4 v_squre_color;

void main()
{
    squre_color = v_squre_color;
}