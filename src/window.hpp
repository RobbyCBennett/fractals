#pragma once


#include <stdint.h>

#include "event.hpp"


namespace frac {


struct WindowSize
{
	uint32_t width;
	uint32_t height;
};


// An OpenGL rendering context, made by a Window
class Context
{
public:
	Context(Context &&other);
	Context operator=(Context &&other);

	~Context();

	void begin();
	void end();

	void swap_buffers();

private:
#ifdef _WIN32
	struct HGLRC__ *context;
	struct HDC__ *device;
#else
	struct __GLXcontextRec *context;
	uint64_t drawable;
#endif

	Context(const Context &other) = delete;
	Context operator=(const Context &other) = delete;

	friend class Window;

#ifdef _WIN32
	Context(struct HDC__ *device);
#else
	Context(uint64_t drawable);
#endif
};


class Window
{
public:
	Window(const char *name);

	Window(Window &&other);
	Window operator=(Window &&other);

	Context context();

	void close();

	Event event();

	bool is_closed() const;
	bool is_created() const;

	WindowSize size() const;

private:
#ifdef _WIN32
	struct HWND__ *window;
#else
	uint64_t window;
#endif

	bool closed;

	Window(const Window &other) = delete;
	Window operator=(const Window &other) = delete;
};


void *get_function(const char *name);


} // namespace frac
