#version 330 core



in vec2 vf_Position;



uniform vec2 u_WndSize;
uniform vec2 u_Size;
uniform vec2 u_Position;
uniform vec4 u_Color;



out vec4 f_Color;



void main()
{
	f_Color = u_Color;
}
