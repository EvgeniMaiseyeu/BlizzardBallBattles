#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D fboTexture;

void main( ) {
    vec4 origColor = texture(fboTexture, TexCoord);
    float brightness = (origColor.r * 0.2126) + (origColor.g * 0.7152) + (origColor.b * 0.0722);
    //if (length(origColor) > 0.3 && (origColor.r > 0.3 && origColor.g > 0.3 && origColor.b > 0.3)) {
    //    brightness /= 100.0;
    //}
    color = origColor + brightness;
}