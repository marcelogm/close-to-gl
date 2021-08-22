#version 400 core

in  vec4 color;
in  vec4 normal;

out vec4 fColor;

void
main()
{
    fColor = -((normal.x + normal.y + normal.z) / 3) * color;
}