#version 460 core

layout (location = 0) in vec2 i_pos;

layout (location = 0) out vec2 o_pos;

void main()
{
	gl_Position = vec4(i_pos.x, i_pos.y, 0.0, 1.0);
	o_pos = i_pos;
}
