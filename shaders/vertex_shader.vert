#version 400

uniform mat4 P;

in vec3 in_Position;
//in vec3 instancePosition;

out vec3 in_color;

void main()
{
	//gl_Position = P * vec4((in_Position + instancePosition), 1.0);
	//gl_Position = P * vec4((in_Position), 1.0);
	gl_Position = vec4((in_Position), 1.0);
	in_color = in_Position.xyz;
}  
