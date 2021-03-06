#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_position = projection * view * model * vec4(position, 1.0f);
	FragPos = vec3(model * vec4(positionm 1.0f)); //Transform the vertex position with the model matrix to get the FragPos in world coords.

	Normal = normal;
	TexCoords = texCoords;
}