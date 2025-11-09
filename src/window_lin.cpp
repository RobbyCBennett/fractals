#ifdef __linux


#include <stdlib.h>

#include <GL/glx.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
constexpr int32_t X_EVENT_FOCUS_IN = FocusIn;
constexpr int32_t X_EVENT_FOCUS_OUT = FocusOut;
#undef FocusIn
#undef FocusOut
#undef None

#include "window.hpp"


constexpr int32_t X_MOUSE_BUTTON_BACK = 8;
constexpr int32_t X_MOUSE_BUTTON_FORWARD = 9;


static Display *global_display;
static int32_t global_width, global_height;
static int32_t global_screen;
static XImage *global_image;


static Event event_from_button_down(uint32_t button);
static Event event_from_button_up(uint32_t button);


Context::Context(DeviceId device_)
{
	device = device_;
	// TODO
	(void) context;
	// context = glXCreateContext(device_);
}


Context::~Context()
{
	end();
	// TODO
	// glXDestroyContext(display, context);
}


void Context::begin()
{
	// TODO
	// glXMakeCurrent(display, drawable, context);
}


void Context::end()
{
	// TODO
	// glXMakeCurrent(nullptr, nullptr, nullptr);
}


void Context::swapBuffers()
{
	// TODO
}


Window::Window(const char *name)
{
	int32_t x = 0;
	int32_t y = 0;

	// Open connection with the server
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XOpenDisplay
	global_display = XOpenDisplay(nullptr);
	if (global_display == nullptr) {
		id = 0;
		closed = true;
		return;
	}

	global_screen = XDefaultScreen(global_display);

	global_width = XDisplayWidth(global_display, global_screen);
	global_height = XDisplayHeight(global_display, global_screen);

	x = 1920;
	global_width = 1920;
	global_height = 1920;

	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XCreateSimpleWindow
	id = XCreateSimpleWindow(
		global_display,
		XRootWindow(global_display, global_screen),
		x,
		y,
		(uint32_t) global_width,
		(uint32_t) global_height,
		1,
		XBlackPixel(global_display, global_screen),
		XBlackPixel(global_display, global_screen)
	);

	closed = false;

	// Set the position hint
	XSizeHints* size_hints = XAllocSizeHints();
	size_hints->flags = USPosition;
	size_hints->x = x;
	size_hints->y = y;
	XSetWMNormalHints(global_display, id, size_hints);
	XFree(size_hints);

	// Make the window frameless
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XInternAtom
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XChangeProperty
	Atom wm_hints = XInternAtom(global_display, "_MOTIF_WM_HINTS", false);
	struct {
		unsigned long flags;
		unsigned long functions;
		unsigned long decorations;
		long input_mode;
		unsigned long status;
	} hints = {2, 0, 0, 0, 0};
	XChangeProperty(global_display, id, wm_hints, wm_hints, 32, PropModeReplace, (unsigned char *) &hints, 5);

	// // Make the window fullscreen
	// Atom wm_state = XInternAtom(global_display, "_NET_WM_STATE", true);
	// Atom wm_fullscreen = XInternAtom(global_display, "_NET_WM_STATE_FULLSCREEN", true);
	// XChangeProperty(global_display, id, wm_state, XA_ATOM, 32, PropModeReplace, (unsigned char *) &wm_fullscreen, 1);

	// Set window name
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XStoreName
	XStoreName(global_display, id, name);

	// Process window close event through event handler so XNextEvent does not fail
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XInternAtom
	Atom del_window = XInternAtom(global_display, "WM_DELETE_WINDOW", 0);
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XSetWMProtocols
	XSetWMProtocols(global_display, id, &del_window, 1);

	// Select the kind of events we are interested in
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XSelectInput
	constexpr int64_t EVENT_KINDS =
		ExposureMask | ButtonPressMask | ButtonReleaseMask | FocusChangeMask |
		KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask;
	XSelectInput(global_display, id, EVENT_KINDS);

	// Display the window
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XMapWindow
	XMapWindow(global_display, id);

	// Wait for MapNotify
	while (true) {
		XEvent e;
		// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XNextEvent
		XNextEvent(global_display, &e);
		if (e.type == MapNotify)
			break;
	}

	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XGetImage
	global_image = XGetImage(global_display, id, 0, 0, (uint32_t) global_width, (uint32_t) global_height, AllPlanes, ZPixmap);
}


Context Window::context()
{
	// TODO
	return Context(0);
}


void Window::close()
{
	closed = true;
	// Destroy window
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XDestroyWindow
	XDestroyWindow(global_display, id);
	// Close connection to server
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XCloseDisplay
	XCloseDisplay(global_display);
}


Event Window::event()
{
	using enum EventKind;

	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#Event_Structures
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XNextEvent
	XEvent event;
	XNextEvent(global_display, &event);

	static bool repeating = false;

	if (event.xany.window != id)
		return Event();

	switch (event.type) {
		// Special events

		case ClientMessage:
			close();
			return Event();

		case Expose:
			// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XPutImage
			// XPutImage(global_display, id, DefaultGC(global_display, global_screen), global_image, 0, 0, 0, 0, (unsigned) global_width, (unsigned) global_height);
			return Event();

		// Relayed events

		case ButtonPress:
			return event_from_button_down(event.xbutton.button);

		case ButtonRelease:
			return event_from_button_up(event.xbutton.button);

		case X_EVENT_FOCUS_IN:
			return Event::focus_in();

		case X_EVENT_FOCUS_OUT:
			return Event::focus_out();

		case KeyPress:
			if (repeating)
				return Event::key_repeat((Key) (event.xkey.keycode - 8));
			return Event::key_down((Key) (event.xkey.keycode - 8));

		case KeyRelease: {
			if (XEventsQueued(global_display, QueuedAfterReading)) {
				XEvent next_event;
				XPeekEvent(global_display, &next_event);

				if (next_event.type == KeyPress and
					next_event.xkey.time == event.xkey.time and
					next_event.xkey.keycode == event.xkey.keycode)
				{
					repeating = true;
					return Event();
				}
			}
			repeating = false;
			return Event::key_up((Key) (event.xkey.keycode - 8));
		}

		case MotionNotify:
			return Event::mouse_move(event.xmotion.x, event.xmotion.y);
	}

	return Event();
}


bool Window::is_closed() const
{
	return closed;
}


bool Window::is_created() const
{
	return id;
}


void Window::size(uint32_t &width, uint32_t &height) const
{
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XGetGeometry
	int32_t i32;
	uint32_t u32;
	uint64_t u64;
	XGetGeometry(global_display, id, &u64, &i32, &i32, &width, &height, &u32, &u32);
}


Function get_function(const char *name)
{
	return glXGetProcAddressARB((const unsigned char *) name);
}


static Event event_from_button_down(uint32_t button)
{
	using enum EventKind;
	using enum MouseButton;

	switch (button) {
		case Button1:
			return Event::mouse_button_down(Left);
		case Button2:
			return Event::mouse_button_down(Middle);
		case Button3:
			return Event::mouse_button_down(Right);
		case Button4:
			return Event::mouse_scroll_up();
		case Button5:
			return Event::mouse_scroll_down();
		case X_MOUSE_BUTTON_BACK:
			return Event::mouse_button_down(Back);
		case X_MOUSE_BUTTON_FORWARD:
			return Event::mouse_button_down(Forward);
		default:
			return Event();
	}
}


static Event event_from_button_up(uint32_t button)
{
	using enum EventKind;
	using enum MouseButton;

	switch (button) {
		case Button1:
			return Event::mouse_button_up(Left);
		case Button2:
			return Event::mouse_button_up(Middle);
		case Button3:
			return Event::mouse_button_up(Right);
		case X_MOUSE_BUTTON_BACK:
			return Event::mouse_button_up(Back);
		case X_MOUSE_BUTTON_FORWARD:
			return Event::mouse_button_up(Forward);
		default:
			return Event();
	}
}


#endif // __linux
