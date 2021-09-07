#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;

out vec4 normal;
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 customColor;

uniform vec3 ambientLight;
uniform vec3 lightPosition;

void
main() {
    vec3 lightVector = normalize(lightPosition - vPosition);
    normal = vec4(vNormal, 1.0f);
    
    color = customColor  * dot(lightVector, vNormal);
    gl_Position = projection * view * model * vec4(vPosition, 1.0f);
    gl_PointSize = 2.0;
}