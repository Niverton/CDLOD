#version 330 core

in vec3 a_pos;
out vec4 var_color;

void main(){
  gl_Position = vec4(a_pos, 1.0);
  var_color = vec4(0.0, 1.0, 0.0, 1.0);
}
