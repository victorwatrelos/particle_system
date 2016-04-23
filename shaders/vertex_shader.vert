#version 400

uniform mat4 P;

in vec4 in_ParticlePos;

void main()
{
	gl_Position = P * in_ParticlePos;
}  
