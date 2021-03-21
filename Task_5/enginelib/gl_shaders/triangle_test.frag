#version 300 es
precision mediump float;
in vec2 v_position;
in vec3 v_color;
out vec4 FragColor;
void main()
{
  FragColor = vec4(v_color, 1.0);
}
