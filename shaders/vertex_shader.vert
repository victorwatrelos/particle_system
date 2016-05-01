#version 400

uniform mat4 P;
uniform mat4 R;
uniform vec4 T;

in vec4 in_Position;
in float in_Dist;

out vec4 in_color;

void main()
{
	gl_Position = P * (vec4((in_Position.xyz), 1.0) * R + T);
	gl_PointSize = 2.0;
	in_color = vec4(1.0, 1.0 * in_Dist, 0.0, 1.0);
}  
