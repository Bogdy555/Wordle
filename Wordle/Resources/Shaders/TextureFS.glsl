#version 330 core



in vec2 vf_Position;
in vec2 vf_TextureCoords;



uniform vec2 u_WndSize;
uniform vec2 u_Size;
uniform vec2 u_Position;
uniform sampler2D u_Texture;
uniform vec2 u_TextureMultiplier;
uniform vec2 u_TextureOffset;



out vec4 f_Color;



void main()
{
	f_Color = texture(u_Texture, vf_TextureCoords);
}
