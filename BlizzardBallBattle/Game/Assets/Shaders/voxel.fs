#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;

void main( ) {
    //0.2543 == 0.25
    float newX = floor(TexCoord.x * 50.0f) / 50.0f;
    float newY = floor(TexCoord.y * 50.0f) / 50.0f;
    vec2 voxelTexCoord = vec2(newX, newY);
    color = texture(ourTexture1, voxelTexCoord);
}