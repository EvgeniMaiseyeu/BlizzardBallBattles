#version 410 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 transform;
uniform float aspectRatio;
uniform vec2 lightPoint;

void main() {
	vec4 pos = transform * vec4(position, 1.0);
	pos.y *= aspectRatio;
    vec4 dif = pos - vec4(lightPoint, 0.0, 0.0);
	gl_Position = pos + dif / 20.0;
	TexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}
