#include <stdio.h>

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN 1
	#include <Windows.h>
	#include <gl/GL.h>
#else
	#include <GL/gl.h>
#endif
#define GL_GLEXT_PROTOTYPES 1
#include <glcorearb.h>
#include "window.hpp"


struct Vec2
{
	float x;
	float y;
};


enum ExitCode
{
	Ok,
	ErrorCreateWindow,
};


constexpr const uint8_t VERTEX_SHADER_SOURCE[] = {
	#embed "../out/shaders/vert.vert.spv"
};

constexpr const uint8_t FRAGMENT_SHADER_SOURCE[] = {
	#embed "../out/shaders/frag.frag.spv"
};


int32_t main()
{
	Window window("Fractals");
	if (not window.is_created()) {
		fputs("Failed to create the window\n", stderr);
		return ErrorCreateWindow;
	}

	uint32_t width;
	uint32_t height;
	window.size(width, height);

	Context context = window.context();
	context.begin();

	#define GET_FUNCTION(lower, upper) \
		PFN##upper##PROC lower = (PFN##upper##PROC) get_function(#lower); \
		if (!lower) { \
			fputs("Failed to get OpenGL function " #lower "\n", stderr); \
			return 1; \
		}

	GET_FUNCTION(glAttachShader, GLATTACHSHADER)
	GET_FUNCTION(glBindBuffer, GLBINDBUFFER)
	GET_FUNCTION(glBindVertexArray, GLBINDVERTEXARRAY)
	GET_FUNCTION(glBufferData, GLBUFFERDATA)
	GET_FUNCTION(glBufferSubData, GLBUFFERSUBDATA)
	GET_FUNCTION(glCompileShader, GLCOMPILESHADER)
	GET_FUNCTION(glCreateProgram, GLCREATEPROGRAM)
	GET_FUNCTION(glCreateShader, GLCREATESHADER)
	GET_FUNCTION(glDeleteBuffers, GLDELETEBUFFERS)
	GET_FUNCTION(glDeleteProgram, GLDELETEPROGRAM)
	GET_FUNCTION(glDeleteShader, GLDELETESHADER)
	GET_FUNCTION(glDeleteVertexArrays, GLDELETEVERTEXARRAYS)
	GET_FUNCTION(glEnableVertexAttribArray, GLENABLEVERTEXATTRIBARRAY)
	GET_FUNCTION(glGenBuffers, GLGENBUFFERS)
	GET_FUNCTION(glGenVertexArrays, GLGENVERTEXARRAYS)
	GET_FUNCTION(glGetProgramInfoLog, GLGETPROGRAMINFOLOG)
	GET_FUNCTION(glGetProgramiv, GLGETPROGRAMIV)
	GET_FUNCTION(glGetShaderInfoLog, GLGETSHADERINFOLOG)
	GET_FUNCTION(glGetShaderiv, GLGETSHADERIV)
	GET_FUNCTION(glLinkProgram, GLLINKPROGRAM)
	GET_FUNCTION(glShaderBinary, GLSHADERBINARY)
	GET_FUNCTION(glShaderSource, GLSHADERSOURCE)
	GET_FUNCTION(glSpecializeShader, GLSPECIALIZESHADER)
	GET_FUNCTION(glUseProgram, GLUSEPROGRAM)
	GET_FUNCTION(glVertexAttribPointer, GLVERTEXATTRIBPOINTER)

	#undef GET_FUNCTION

	// Compile vertex shader from SPIR-V
	uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderBinary(1, &vertex_shader, GL_SHADER_BINARY_FORMAT_SPIR_V, VERTEX_SHADER_SOURCE, sizeof(VERTEX_SHADER_SOURCE));
	glSpecializeShader(vertex_shader, "main", 0, nullptr, nullptr);
	int32_t success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
		fprintf(stderr, "Failed to compile vertex shader: %s\n", info_log);
		return 1;
	}

	// Compile fragment shader from SPIR-V
	uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &fragment_shader, GL_SHADER_BINARY_FORMAT_SPIR_V, FRAGMENT_SHADER_SOURCE, sizeof(FRAGMENT_SHADER_SOURCE));
	glSpecializeShader(fragment_shader, "main", 0, nullptr, nullptr);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
		fprintf(stderr, "Failed to compile fragment shader: %s\n", info_log);
		return 1;
	}

	// Link shaders
	uint32_t shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
		fprintf(stderr, "Failed to link shaders: %s\n", info_log);
		return 1;
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// Vet up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		// Triangle 1
		-1, 1,
		1, 1,
		-1, -1,
		// Triangle 2
		-1, -1,
		1, 1,
		1, -1,
	};
	uint32_t vbo, vao, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	// Bind the vertex array object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Note that this is allowed, the call to glVertexAttribPointer registered
	// VBO as the vertex attribute's bound vertex buffer object so afterwards we
	// can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. Modifying other VAOs requires a
	// call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
	// VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	while (not window.is_closed()) {
		using enum EventKind;
		// using enum Key;
		Event event = window.event();
		switch (event.kind) {
			case None:
				break;
			case FocusIn:
			case FocusOut:
				// printf("%s\n", to_string(event.kind));
				break;
			case KeyDown:
			case KeyRepeat:
				// printf("%s: %d\n", to_string(event.kind), (int32_t) event.key);
				if (event.key == KEY_ESC)
					window.close();
				break;
			case KeyUp:
				// printf("%s: %d\n", to_string(event.kind), (int32_t) event.key);
				break;
			case MouseButtonDown:
				// printf("%s: %s\n", to_string(event.kind), to_string(event.button));
				break;
			case MouseButtonUp:
				// printf("%s: %s\n", to_string(event.kind), to_string(event.button));
				break;
			case MouseMove:
				// printf("%s: %d %d\n", to_string(event.kind), event.move.x, event.move.y);
				break;
			case MouseScrollDown:
				// printf("%s\n", to_string(event.kind));
				break;
			case MouseScrollUp:
				// printf("%s\n", to_string(event.kind));
				break;
		}

		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		context.swapBuffers();
	}
	puts("Done");
}
