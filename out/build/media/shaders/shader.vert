#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;

out vec4 normal;
out vec4 color;
out vec4 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 customColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;

subroutine vec4 light_t();

subroutine uniform light_t light;

vec3 getNormal() {
    return normalize(vNormal);
}

vec3 getLightDirection() {
    return normalize(lightPosition - vPosition);
}

vec3 getAmbientLight() {
    return ambientStrength * lightColor;
}

vec3 getDiffuseLight(vec3 lightDirection) {
    return diffuseStrength * max(dot(getNormal(), lightDirection), 0.0f) * lightColor;
}

vec3 getSpecularLight(vec3 lightDirection) {
    vec3 viewDirection = normalize(cameraPosition - vPosition);
    vec3 reflectDirection = reflect(-lightDirection, getNormal());
    return specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0f), 3) * lightColor;  
}

subroutine(light_t)
vec4 noShading() {
    return customColor;
}

subroutine(light_t)
vec4 gouraudShadingAD() {
    vec3 direction = getLightDirection();
    vec3 ambient = getAmbientLight();
    vec3 diffuse = getDiffuseLight(direction);
    vec3 light = (ambient + diffuse);
    return vec4((ambient + diffuse), 1.0f) * customColor;
}

subroutine(light_t)
vec4 gouraudShadingADS() {
    vec3 direction = getLightDirection();
    vec3 ambient = getAmbientLight();
    vec3 diffuse = getDiffuseLight(direction);
    vec3 specular = getSpecularLight(direction);
    vec3 light = (ambient + diffuse + specular);
    return vec4(light, 1.0f) * customColor;
}

void
main() {
    normal = vec4(vNormal, 1.0f);
    fragPos = model * vec4(vPosition, 1.0);
    color = light();

    gl_Position = projection * view * model * vec4(vPosition, 1.0f);
    gl_PointSize = 2.0;
}