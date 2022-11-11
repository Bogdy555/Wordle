#version 330 core



layout (location = 0) in vec2 v_Position;



uniform vec2 u_WndSize;
uniform vec2 u_Size;
uniform vec2 u_Position;
uniform vec4 u_Color;



out vec2 vf_Position;



void main()
{
	vf_Position = v_Position * u_Size + u_Position;

	gl_Position = vec4((v_Position * u_Size + u_Position) / u_WndSize * 2.0f - 1.0f, 0.0f, 1.0f);
}
