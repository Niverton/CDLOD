<VERTEX>
#version 300 es

//in
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec2 charSize;
layout (location = 4) in uint channel;
//out
flat out uint frag_channel;
out vec3 frag_position;
out vec4 frag_color;
out vec2 frag_texCoord;
out vec2 frag_charSize;
//
//
void main()
{
  frag_position = position;
  frag_color = color;
  frag_texCoord = texCoord;
  frag_charSize = charSize;
  frag_channel = channel;
}
</VERTEX>
<FRAGMENT>
#version 300 es

//IN
flat in uint frag_channel;
in highp vec4 frag_color;
in highp vec2 frag_texCoord;

uniform sampler2D fontTex;

out highp vec4 outColor;

void main()
{
  highp float tValue = texture( fontTex, frag_texCoord )[frag_channel];
  if( tValue < 1.0/255.0 ) {
    discard;
  }
  highp vec4 textureColor = frag_color*tValue;
  outColor = textureColor;
}
</FRAGMENT>
