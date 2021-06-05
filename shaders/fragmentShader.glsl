#version 330 core
in vec3 pos;
in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D aTexture;

void main() {
    FragColor = texture(aTexture, texCoords * vec2(0.5f));
}
