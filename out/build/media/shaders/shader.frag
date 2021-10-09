#version 400 core

in vec4 color;
in vec4 normal;
in vec4 fragPos;
in vec2 texCoord;

out vec4 FragColor;

uniform vec3 ambientLight;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

subroutine vec4 light_t();

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform int useTexture;

uniform sampler2D texture1;

subroutine uniform light_t getLight;

vec3 getNormal() {
    return normalize(vec3(normal));
}

vec3 getLightDirection() {
    return normalize(lightPosition - vec3(fragPos));
}

vec3 getAmbientLight() {
    return ambientStrength * lightColor;
}

vec3 getDiffuseLight(vec3 lightDirection) {
    return diffuseStrength * max(dot(getNormal(), lightDirection), 0.0f) * lightColor;
}

vec3 getSpecularLight(vec3 lightDirection) {
    vec3 viewDirection = normalize(cameraPosition - vec3(fragPos));
    vec3 reflectDirection = reflect(-lightDirection, getNormal());
    return specularStrength * pow(max(dot(viewDirection, reflectDirection), 0.0), 3) * lightColor;  
}

subroutine(light_t)
vec4 noShading() {
    return color;
}

subroutine(light_t)
vec4 phongShading() {
    vec3 direction = getLightDirection();
    vec3 ambient = getAmbientLight();
    vec3 diffuse = getDiffuseLight(direction);
    vec3 specular = getSpecularLight(direction);
    vec3 light = (ambient + diffuse + specular);
    return vec4(light, 1.0f) * color;
}

void main() {
    if (useTexture == 0) {
        FragColor = getLight();
    } else {
        FragColor = getLight() * texture(texture1, texCoord);
    }
}