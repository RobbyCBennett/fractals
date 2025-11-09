#version 460 core

layout (location = 0) in vec2 in_pos;

layout (location = 0) out vec2 out_pos;

void main()
{
	gl_Position = vec4(in_pos.x, in_pos.y, 0.0, 1.0);
	out_pos = in_pos;
}
