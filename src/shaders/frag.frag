// https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set

#version 460 core

layout (location = 0) in vec2 in_pos;

layout (location = 0) out vec4 out_color;

const int MAX_ITERATIONS = 100;

const vec2 MANDELBROT_RANGE_X = vec2(-2.00, 0.47);
const vec2 MANDELBROT_RANGE_Y = vec2(-1.12, 1.12);

vec2 pos_to_unit(vec2 pos)
{
	return vec2(
		(pos.x + 1) / 2,
		(pos.y + 1) / 2
	);
}

float unit_to_range(vec2 range, float pos)
{
	return mix(range.x, range.y, pos);
}

void main()
{
	// Position and zoom
	const vec2 offset = {-0.9, 0.26};
	const float zoom = 0.02;
	vec2 pos_unit = pos_to_unit(in_pos);
	float x0 = unit_to_range(MANDELBROT_RANGE_X * zoom + offset.x, pos_unit.x);
	float y0 = unit_to_range(MANDELBROT_RANGE_Y * zoom + offset.y, pos_unit.y);

	// Iterations to escape fractal
	float x = 0.0;
	float y = 0.0;
	float x2 = 0.0;
	float y2 = 0.0;
	int i;
	for (i = 0; i < MAX_ITERATIONS; i++) {
		if (x2 + y2 > 4)
			break;
		y = 2 * x * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	float escaped = 1.0 - i * (1.0 / MAX_ITERATIONS);

	// Color
	float gradient = (pos_unit.x + 1 - pos_unit.y) / 2;
	float r = escaped * gradient;
	float b = escaped * (1 - gradient);

	out_color = vec4(r, 0, b, 0);
}
