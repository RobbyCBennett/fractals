#version 460 core


layout (location = 0) uniform double u_aspect_ratio;
layout (location = 1) uniform dvec2 u_offset;
layout (location = 2) uniform double u_zoom;

layout (location = 0) in vec2 i_pos;

layout (location = 0) out vec4 o_color;


// Convert [-1, -1] to [0, 1]
double to_unit(double n)
{
	return (n + 1) * 0.5;
}


void main()
{
	// https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set

	const int MAX_ITERATIONS = 100;

	// Position and zoom
	dvec2 pos_unit = dvec2(to_unit(i_pos.x), to_unit(i_pos.y));
	double x0 = u_zoom * i_pos.x + u_offset.x;
	double y0 = u_zoom * i_pos.y + u_offset.y;
	x0 *= u_aspect_ratio;

	// Iterations to escape fractal
	double x = 0.0;
	double y = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	int i;
	for (i = 0; i < MAX_ITERATIONS; i++) {
		if (x2 + y2 > 4)
			break;
		y = 2 * x * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	double escaped = 1.0 - i * (1.0 / MAX_ITERATIONS);

	// Color
	double gradient = (pos_unit.x + 1 - pos_unit.y) * 0.5;
	double r = escaped * gradient;
	double b = escaped * (1 - gradient);

	o_color = vec4(r, 0, b, 0);
}
