#version 450 core

out vec4 FragColor;

in vec2 coord;

uniform sampler2D text;

void main() {
    FragColor = texture(text, coord);
}