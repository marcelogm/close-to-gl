#version 400 core

in  vec3 color;
in  vec3 normal;

out vec3 fColor;

void
main()
{
    fColor = color * normal;
}