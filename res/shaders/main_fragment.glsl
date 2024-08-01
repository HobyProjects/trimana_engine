#version 440 core

layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;

uniform vec4 u_color;

void main()
{
    color = u_color;
}