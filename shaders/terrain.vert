#version 330 core

in vec4 a_pos;
out var_color;

void main(){
  gl_Position = a_pos;
  var_color = vec4(0.0, 1.0, 0.0, 1.0);
}
