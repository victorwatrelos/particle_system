#version 400

uniform mat4 P;
uniform mat4 R;

in vec3 in_Position;
in vec3 instancePosition;

out vec3 in_color;

void main()
{
	vec4 trans = vec4(0.0f, 0.0f, -1200.0f, 0.0f);
	gl_Position = P * (vec4((in_Position + instancePosition), 1.0) * R + trans);
	gl_PointSize = 1.0;
	in_color = in_Position.xyz;
}  
