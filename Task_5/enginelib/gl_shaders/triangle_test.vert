#version 300 es
precision mediump float;
layout (location = 0) in vec2 a_position;
layout (location = 1) in vec3 a_color;
out vec2 v_position;
out vec3 v_color;
void main()
{
    v_position = a_position;
    v_color = a_color;
    gl_Position = vec4(a_position, 0.0, 1.0);
}
