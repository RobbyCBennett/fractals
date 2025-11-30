#ifdef __linux


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


namespace frac {


constexpr int32_t X_MOUSE_BUTTON_BACK = 8;
constexpr int32_t X_MOUSE_BUTTON_FORWARD = 9;


// TODO remove globals
// TODO close display with XCloseDisplay
static Display *global_display = nullptr;


static Event event_from_button_down(uint32_t button);
static Event event_from_button_up(uint32_t button);


Context::Context(uint64_t drawable_)
{
	static int visual_attribs[] = {
		GLX_X_RENDERABLE,  True,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,   GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
		GLX_RED_SIZE,      8,
		GLX_GREEN_SIZE,    8,
		GLX_BLUE_SIZE,     8,
		GLX_ALPHA_SIZE,    8,
		GLX_DEPTH_SIZE,    24,
		GLX_STENCIL_SIZE,  8,
		GLX_DOUBLEBUFFER,  True,
		0
    };
	int frame_buffer_config_count;
	GLXFBConfig *frame_buffer_configs = glXChooseFBConfig(global_display, DefaultScreen(global_display), visual_attribs, &frame_buffer_config_count);
	if (!frame_buffer_configs) {
		context = nullptr;
		drawable = 0;
		return;
	}
	int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
	for (int i = 0; i < frame_buffer_config_count; i++) {
		XVisualInfo *vi = glXGetVisualFromFBConfig(global_display, frame_buffer_configs[i]);
		if (vi) {
			int samp_buf, samples;
			glXGetFBConfigAttrib(global_display, frame_buffer_configs[i], GLX_SAMPLE_BUFFERS, &samp_buf);
			glXGetFBConfigAttrib(global_display, frame_buffer_configs[i], GLX_SAMPLES, &samples);
			if (best_fbc < 0 or (samp_buf and samples > best_num_samp)) {
				best_fbc = i;
				best_num_samp = samples;
			}
			if (worst_fbc < 0 or (!samp_buf and samples < worst_num_samp)) {
				worst_fbc = i;
				worst_num_samp = samples;
			}
		}
		XFree(vi);
	}
	GLXFBConfig best_frame_buffer_config = frame_buffer_configs[ best_fbc ];
	XFree(frame_buffer_configs);
	XVisualInfo *visual_info = glXGetVisualFromFBConfig(global_display, best_frame_buffer_config);

	context = glXCreateContext(global_display, visual_info, nullptr, true);
	drawable = drawable_;
}


Context::Context(Context &&other)
{
	context = other.context;
	drawable = other.drawable;
	other.context = nullptr;
	other.drawable = 0;
}


Context Context::operator=(Context &&other)
{
	return (Context &&) other;
}


Context::~Context()
{
	end();
	glXDestroyContext(global_display, context);
}


void Context::begin()
{
	glXMakeCurrent(global_display, drawable, context);
}


void Context::end()
{
	glXMakeCurrent(nullptr, 0, nullptr);
}


void Context::swap_buffers()
{
	glXSwapBuffers(global_display, drawable);
}


Window::Window(const char *name)
{
	int32_t x = 0;
	int32_t y = 0;

	// Open connection with the server
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XOpenDisplay
	if (global_display == nullptr)
		global_display = XOpenDisplay(nullptr);
	if (global_display == nullptr) {
		window = 0;
		closed = true;
		return;
	}

	int32_t screen = XDefaultScreen(global_display);

	int32_t width = XDisplayWidth(global_display, screen);
	int32_t height = XDisplayHeight(global_display, screen);

	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XCreateSimpleWindow
	window = XCreateSimpleWindow(
		global_display,
		XRootWindow(global_display, screen),
		x,
		y,
		(uint32_t) width,
		(uint32_t) height,
		1,
		XBlackPixel(global_display, screen),
		XBlackPixel(global_display, screen)
	);

	closed = false;

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
	XChangeProperty(global_display, window, wm_hints, wm_hints, 32, PropModeReplace, (unsigned char *) &hints, 5);

	// Set window name
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XStoreName
	XStoreName(global_display, window, name);

	// Process window close event through event handler so XNextEvent does not fail
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XInternAtom
	Atom del_window = XInternAtom(global_display, "WM_DELETE_WINDOW", 0);
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XSetWMProtocols
	XSetWMProtocols(global_display, window, &del_window, 1);

	// Select the kind of events we are interested in
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XSelectInput
	constexpr int64_t EVENT_KINDS =
		ExposureMask | ButtonPressMask | ButtonReleaseMask | FocusChangeMask |
		KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask;
	XSelectInput(global_display, window, EVENT_KINDS);

	// Display the window
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XMapWindow
	XMapWindow(global_display, window);

	// Wait for MapNotify
	while (true) {
		XEvent e;
		// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XNextEvent
		XNextEvent(global_display, &e);
		if (e.type == MapNotify)
			break;
	}
}


Window::Window(Window &&other)
{
	window = other.window;
	closed = other.closed;
	other.window = 0;
	other.closed = true;
}


Window Window::operator=(Window &&other)
{
	return (Window &&) other;
}


Context Window::context()
{
	return Context(window);
}


void Window::close()
{
	closed = true;
	// Destroy window
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XDestroyWindow
	XDestroyWindow(global_display, window);
}


Event Window::event()
{
	using enum EventKind;

	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#Event_Structures
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XNextEvent
	XEvent event;
	XNextEvent(global_display, &event);

	static bool repeating = false;

	if (event.xany.window != window)
		return Event();

	switch (event.type) {
		// Special events

		case ClientMessage:
			close();
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
	return window;
}


WindowSize Window::size() const
{
	// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#XGetGeometry
	uint64_t u64;
	int32_t i32;
	uint32_t width;
	uint32_t height;
	uint32_t u32;
	XGetGeometry(global_display, window, &u64, &i32, &i32, &width, &height, &u32, &u32);
	return WindowSize {width, height};
}


void *get_function(const char *name)
{
	return (void *) glXGetProcAddressARB((const unsigned char *) name);
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


} // namespace frac


#endif // __linux
