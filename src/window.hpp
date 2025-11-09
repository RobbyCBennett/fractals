#pragma once


#include <stdint.h>

#include "event.hpp"


#ifdef _WIN32
	using ContextId = struct HGLRC__*;
	using DeviceId = struct HDC__*;
	using WindowId = struct HWND__*;
#else
	using ContextId = struct __GLXcontextRec *;
	using DeviceId = uint64_t;
	using WindowId = uint64_t;
#endif


using Function = void (*)();


class Context
{
public:
	~Context();

	void begin();
	void end();

	void swapBuffers();

private:
	DeviceId device;
	ContextId context;

	Context(const Context &other) = delete;
	Context operator=(const Context &other) = delete;

	Context(Context &&other) = delete;
	Context operator=(Context &&other) = delete;

	friend class Window;

	Context(DeviceId device);
};


class Window
{
public:
	Window(const char *name);

	Context context();

	void close();

	Event event();

	bool is_closed() const;
	bool is_created() const;

	void size(uint32_t &width, uint32_t &height) const;

private:
	WindowId id;
	bool closed;

	Window(const Window &other) = delete;
	Window operator=(const Window &other) = delete;
};


Function get_function(const char *name);
