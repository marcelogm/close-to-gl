#version 400 core

layout( location = 0 ) in vec2 vPosition;
layout( location = 1 ) in vec2 aTexCoord;

out vec2 coord;

void
main()
{
    gl_Position = vec4(vPosition, 0.0f, 1.0f);
    coord = aTexCoord;
}