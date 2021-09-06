#version 400 core

layout( location = 0 ) in vec4 vPosition;

out vec4 color;

uniform vec4 customColor;

void
main()
{
    color = customColor;
    gl_Position = vPosition;
    gl_PointSize = 2.0;
}