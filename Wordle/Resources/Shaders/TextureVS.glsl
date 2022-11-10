#version 330 core



layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec2 v_TextureCoords;



out vec3 vf_Position;
out vec2 vf_TextureCoords;



void main()
{
	vf_Position = v_Position;
	vf_TextureCoords = v_TextureCoords;

	gl_Position = vec4(v_Position, 1.0f);
}
