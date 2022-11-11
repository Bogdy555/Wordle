#version 330 core



in vec2 vf_Position;



uniform vec2 u_WndSize;
uniform vec2 u_Size;
uniform vec2 u_Position;
uniform vec4 u_Color;



out vec4 f_Color;



void main()
{
	float _Distance = length(vf_Position);

	if (_Distance <= 1.0f)
	{
		f_Color = u_Color;

		return;
	}

	f_Color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
}
