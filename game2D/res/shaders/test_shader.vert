#version 300 es
precision mediump float;

layout(location = 0) in vec2 sprite_position;
layout(location = 1) in vec2 tex_coord;

uniform mat4x4 s_model;

out vec2 v_norm;

void main()
{
    v_norm = tex_coord;
    gl_Position = s_model * vec4(sprite_position, 0, 1);
}
