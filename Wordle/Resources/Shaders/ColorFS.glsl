#version 330 core



in vec3 vf_Position;
in vec2 vf_TextureCoords;



out vec4 f_Color;



void main()
{
	f_Color = vec4((vf_Position + 1.0f) / 2.0f, 1.0f);
}
