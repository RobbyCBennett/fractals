#ifdef _WIN32


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "window.hpp"


namespace frac {


enum class MissedFocus: uint8_t
{
	None,
	In,
	Out,
};


static constexpr const char WINDOW_CLASS[] = "_";


// TODO remove globals
static bool global_missed_close = false;
static MissedFocus global_missed_focus = MissedFocus::None;


static Event event_from(const MSG &message);
static Event event_from_scroll(const MSG &message);

// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
static int64_t __stdcall handle_message(HWND__ *window, uint32_t message, uint64_t param_a, int64_t param_b);

static void initialize_gui();

static Key key_from(const MSG &message);
static Key key_from(const MSG &message, Key regular_key, Key extended_key);

static uint16_t mouse_button_from(const MSG &message);
static MousePosition mouse_move_from(const MSG &message);


Context::Context(HDC__ *device_)
{
	device = device_;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor
	PIXELFORMATDESCRIPTOR descriptor = {
		sizeof(PIXELFORMATDESCRIPTOR), // Size of this descriptor
		1,                             // Version number
		PFD_DRAW_TO_WINDOW |           // Support window
		PFD_SUPPORT_OPENGL |           // Support OpenGL
		PFD_DOUBLEBUFFER,              // Double buffered
		PFD_TYPE_RGBA,                 // RGBA type
		24,                            // 24-bit color depth
		0, 0, 0, 0, 0, 0,              // Color bits ignored
		0,                             // No alpha buffer
		0,                             // Shift bit ignored
		0,                             // No accumulation buffer
		0, 0, 0, 0,                    // Accumulate bits ignored
		32,                            // 32-bit z-buffer
		0,                             // No stencil buffer
		0,                             // No auxiliary buffer
		PFD_MAIN_PLANE,                // Main layer
		0,                             // Reserved
		0, 0, 0                        // Layer masks ignored
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-choosepixelformat
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat
	int32_t format = ChoosePixelFormat(device, &descriptor);
	SetPixelFormat(device, format, &descriptor);

	context = wglCreateContext(device);
}


Context::Context(Context &&other)
{
	context = other.context;
	device = other.device;
	other.context = nullptr;
	other.device = nullptr;
}


Context Context::operator=(Context &&other)
{
	return Context((Context &&) other);
}


Context::~Context()
{
	end();
	wglDeleteContext(context);
}


void Context::begin()
{
	wglMakeCurrent(device, context);
}


void Context::end()
{
	wglMakeCurrent(nullptr, nullptr);
}


void Context::swap_buffers()
{
	SwapBuffers(device);
}


Window::Window(const char *name)
{
	static bool initialized = false;
	if (not initialized) {
		initialized = true;
		initialize_gui();
	}

	// https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
	constexpr DWORD WINDOW_STYLE = WS_MAXIMIZE | WS_POPUP | WS_VISIBLE;
	window = CreateWindowExA(0, WINDOW_CLASS, name, WINDOW_STYLE, 0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);

	closed = window == nullptr;
}


Window::Window(Window &&other)
{
	window = other.window;
	closed = other.closed;
	other.window = nullptr;
	other.closed = true;
}


Window Window::operator=(Window &&other)
{
	return (Window &&) other;
}


Context Window::context()
{
	return Context(GetDC(window));
}


void Window::close()
{
	closed = true;
	PostQuitMessage(0);
}


Event Window::event()
{
	switch (global_missed_focus) {
		case MissedFocus::None:
			break;
		case MissedFocus::In:
			global_missed_focus = MissedFocus::None;
			return Event::focus_in();
		case MissedFocus::Out:
			global_missed_focus = MissedFocus::None;
			return Event::focus_out();
	}

	// Get a message from the OS or fail
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-msg
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessagea
	MSG message;
	if (GetMessageA(&message, nullptr, 0, 0) <= 0)
		return Event();

	// Properly relay all messages back to the OS
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-translatemessage
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-dispatchmessagea
	TranslateMessage(&message);
	DispatchMessageA(&message);

	if (message.hwnd != window)
		return Event();

	if (global_missed_close) {
		global_missed_close = false;
		closed = true;
	}

	return event_from(message);
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
	// https://learn.microsoft.com/en-us/windows/win32/api/windef/ns-windef-rect
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowrect
	RECT rect;
	GetWindowRect(window, &rect);
	return WindowSize {
		(uint32_t) (rect.right - rect.left),
		(uint32_t) (rect.bottom - rect.top),
	};
}


void *get_function(const char *name)
{
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglgetprocaddress
	return (void *) wglGetProcAddress(name);
}


static Event event_from(const MSG &message)
{
	using enum EventKind;
	using enum MouseButton;

	static bool last_key_event_down = false;
	static Key last_key = 0;

	// Return an event or fail
	switch (message.message) {
		// Key
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN: {
			// return Event::key_down(key_from(message));
			Key key = key_from(message);
			if (key == last_key and last_key_event_down) {
				last_key = key;
				last_key_event_down = true;
				return Event::key_repeat(key);
			}
			last_key = key;
			last_key_event_down = true;
			return Event::key_down(key);
		}
		case WM_KEYUP:
		case WM_SYSKEYUP: {
			last_key = key_from(message);
			last_key_event_down = false;
			return Event::key_up(last_key);
		}

		// Mouse button
		case WM_LBUTTONDOWN:
			return Event::mouse_button_down(Left);
		case WM_LBUTTONUP:
			return Event::mouse_button_up(Left);
		case WM_MBUTTONDOWN:
			return Event::mouse_button_down(Middle);
		case WM_MBUTTONUP:
			return Event::mouse_button_up(Middle);
		case WM_RBUTTONDOWN:
			return Event::mouse_button_down(Right);
		case WM_RBUTTONUP:
			return Event::mouse_button_up(Right);
		case WM_XBUTTONDOWN:
			switch (mouse_button_from(message)) {
				case XBUTTON1:
					return Event::mouse_button_down(Back);
				case XBUTTON2:
					return Event::mouse_button_down(Forward);
				default:
					return Event();
			}
		case WM_XBUTTONUP:
			switch (mouse_button_from(message)) {
				case XBUTTON1:
					return Event::mouse_button_up(Back);
				case XBUTTON2:
					return Event::mouse_button_up(Forward);
				default:
					return Event();
			}

		// Mouse move
		case WM_MOUSEMOVE:
			return Event::mouse_move(mouse_move_from(message));

		// Mouse scroll
		case WM_MOUSEWHEEL:
			return event_from_scroll(message);

		default:
			return Event();
	}
}


static Event event_from_scroll(const MSG &message)
{
	using enum EventKind;

	// Get y from the second lowest 16 bits
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousewheel
	int16_t y = (int16_t) (message.wParam >> 16);
	return (y > 0) ? Event::mouse_scroll_up() : Event::mouse_scroll_down();
}


static int64_t __stdcall handle_message(HWND__ *window_id, uint32_t message, uint64_t param_a, int64_t param_b)
{
	using enum EventKind;

	switch (message) {
		case WM_DESTROY:
			global_missed_close = true;
			PostQuitMessage(0);
			return 0;

		case WM_SETFOCUS:
			global_missed_focus = MissedFocus::In;
			return DefWindowProcA(window_id, message, param_a, param_b);
		case WM_KILLFOCUS:
			global_missed_focus = MissedFocus::Out;
			return DefWindowProcA(window_id, message, param_a, param_b);

		default:
			// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-defwindowproca
			return DefWindowProcA(window_id, message, param_a, param_b);
	}
}


static void initialize_gui()
{
	// Print with UTF-8
	// https://learn.microsoft.com/en-us/windows/console/setconsoleoutputcp
	SetConsoleOutputCP(CP_UTF8);

	// Use the real size and position
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setthreaddpiawarenesscontext
	// https://learn.microsoft.com/en-us/windows/win32/hidpi/dpi-awareness-context
	SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// Parameters to register window classification
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw
	WNDCLASSEXA window_class = {
		.cbSize        = sizeof(WNDCLASSEXA),
		.style         = 0,
		.lpfnWndProc   = handle_message,
		.cbClsExtra    = 0,
		.cbWndExtra    = 0,
		.hInstance     = GetModuleHandleA(nullptr),
		.hIcon         = nullptr,
		.hCursor       = LoadCursorA(nullptr, IDC_ARROW),
		.hbrBackground = CreateSolidBrush(RGB(0, 0, 0)),
		.lpszMenuName  = nullptr,
		.lpszClassName = WINDOW_CLASS,
		.hIconSm       = nullptr,
	};

	// Register window classification
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa
	RegisterClassExA(&window_class);
}


static Key key_from(const MSG &message)
{
	// Constants for modifier keys, where bit 0 is the least significant
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-syskeydown
	//                                            ( Code )( Repeat Count )
	constexpr int64_t KEY_CODE_OF_RIGHT_SHIFT = 0b001101100000000000000000;
	constexpr int64_t REPEAT_COUNT            = 0b000000001111111111111111;
	constexpr int64_t REMOVE_REPEAT_COUNT     = ~REPEAT_COUNT;

	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	switch (message.wParam) {
		case 0x08: return KEY_BACKSPACE;
		case 0x09: return KEY_TAB;
		case 0x0C: return KEY_CLEAR;
		case 0x0D:
			return key_from(message, KEY_ENTER, KEY_KPENTER);
		case 0x10:
			// Remove the lowest 16 bits, then see if the scan code matches
			if (((message.lParam & REMOVE_REPEAT_COUNT) ^ KEY_CODE_OF_RIGHT_SHIFT) == 0)
				return KEY_RIGHTSHIFT;
			else
				return key_from(message, KEY_LEFTSHIFT, KEY_RIGHTSHIFT);
		case 0x11:
			return key_from(message, KEY_LEFTCTRL, KEY_RIGHTCTRL);
		case 0x12:
			return key_from(message, KEY_LEFTALT, KEY_RIGHTALT);
		case 0x13: return KEY_PAUSE;
		case 0x14: return KEY_CAPSLOCK;
		case 0x1B: return KEY_ESC;
		case 0x20: return KEY_SPACE;
		case 0x21: return KEY_PAGEUP;
		case 0x22: return KEY_PAGEDOWN;
		case 0x23: return KEY_END;
		case 0x24: return KEY_HOME;
		case 0x25: return KEY_LEFT;
		case 0x26: return KEY_UP;
		case 0x27: return KEY_RIGHT;
		case 0x28: return KEY_DOWN;
		case 0x2C: return KEY_PRINT;
		case 0x2D: return KEY_INSERT;
		case 0x2E: return KEY_DELETE;
		case 0x2F: return KEY_HELP;
		case 0x30: return KEY_0;
		case 0x31: return KEY_1;
		case 0x32: return KEY_2;
		case 0x33: return KEY_3;
		case 0x34: return KEY_4;
		case 0x35: return KEY_5;
		case 0x36: return KEY_6;
		case 0x37: return KEY_7;
		case 0x38: return KEY_8;
		case 0x39: return KEY_9;
		case 0x41: return KEY_A;
		case 0x42: return KEY_B;
		case 0x43: return KEY_C;
		case 0x44: return KEY_D;
		case 0x45: return KEY_E;
		case 0x46: return KEY_F;
		case 0x47: return KEY_G;
		case 0x48: return KEY_H;
		case 0x49: return KEY_I;
		case 0x4A: return KEY_J;
		case 0x4B: return KEY_K;
		case 0x4C: return KEY_L;
		case 0x4D: return KEY_M;
		case 0x4E: return KEY_N;
		case 0x4F: return KEY_O;
		case 0x50: return KEY_P;
		case 0x51: return KEY_Q;
		case 0x52: return KEY_R;
		case 0x53: return KEY_S;
		case 0x54: return KEY_T;
		case 0x55: return KEY_U;
		case 0x56: return KEY_V;
		case 0x57: return KEY_W;
		case 0x58: return KEY_X;
		case 0x59: return KEY_Y;
		case 0x5A: return KEY_Z;
		case 0x5B: return KEY_LEFTMETA;
		case 0x5C: return KEY_RIGHTMETA;
		case 0x5D: return KEY_APPSELECT;
		case 0x5F: return KEY_SLEEP;
		case 0x60: return KEY_KP0;
		case 0x61: return KEY_KP1;
		case 0x62: return KEY_KP2;
		case 0x63: return KEY_KP3;
		case 0x64: return KEY_KP4;
		case 0x65: return KEY_KP5;
		case 0x66: return KEY_KP6;
		case 0x67: return KEY_KP7;
		case 0x68: return KEY_KP8;
		case 0x69: return KEY_KP9;
		case 0x6A: return KEY_KPASTERISK;
		case 0x6B: return KEY_KPPLUS;
		case 0x6D: return KEY_KPMINUS;
		case 0x6E: return KEY_KPDOT;
		case 0x6F: return KEY_KPSLASH;
		case 0x70: return KEY_F1;
		case 0x71: return KEY_F2;
		case 0x72: return KEY_F3;
		case 0x73: return KEY_F4;
		case 0x74: return KEY_F5;
		case 0x75: return KEY_F6;
		case 0x76: return KEY_F7;
		case 0x77: return KEY_F8;
		case 0x78: return KEY_F9;
		case 0x79: return KEY_F10;
		case 0x7A: return KEY_F11;
		case 0x7B: return KEY_F12;
		case 0x7C: return KEY_F13;
		case 0x7D: return KEY_F14;
		case 0x7E: return KEY_F15;
		case 0x7F: return KEY_F16;
		case 0x80: return KEY_F17;
		case 0x81: return KEY_F18;
		case 0x82: return KEY_F19;
		case 0x83: return KEY_F20;
		case 0x84: return KEY_F21;
		case 0x85: return KEY_F22;
		case 0x86: return KEY_F23;
		case 0x87: return KEY_F24;
		case 0x90: return KEY_NUMLOCK;
		case 0x91: return KEY_SCROLLLOCK;
		case 0xA0: return KEY_LEFTSHIFT;
		case 0xA1: return KEY_RIGHTSHIFT;
		case 0xA2: return KEY_LEFTCTRL;
		case 0xA3: return KEY_RIGHTCTRL;
		case 0xA4: return KEY_LEFTALT;
		case 0xA5: return KEY_RIGHTALT;
		case 0xAD: return KEY_MUTE;
		case 0xAE: return KEY_VOLUMEDOWN;
		case 0xAF: return KEY_VOLUMEUP;
		case 0xB0: return KEY_NEXTSONG;
		case 0xB1: return KEY_PREVIOUSSONG;
		case 0xB2: return KEY_STOPCD;
		case 0xB3: return KEY_PLAYPAUSE;
		case 0xBA: return KEY_SEMICOLON;
		case 0xBB: return KEY_EQUAL;
		case 0xBC: return KEY_COMMA;
		case 0xBD: return KEY_MINUS;
		case 0xBE: return KEY_DOT;
		case 0xBF: return KEY_SLASH;
		case 0xC0: return KEY_GRAVE;
		case 0xDB: return KEY_LEFTBRACE;
		case 0xDC: return KEY_BACKSLASH;
		case 0xDD: return KEY_RIGHTBRACE;
		case 0xDE: return KEY_APOSTROPHE;
		default: return KEY_RESERVED;
	}
}


static Key key_from(const MSG &message, Key regular_key, Key extended_key)
{
	// Constant for modifier keys, where bit 0 is the least significant
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-syskeydown
	//                                     *( Code )( Repeat Count )
	constexpr int64_t EXTENDED_KEY_BIT = 0b1000000000000000000000000;

	return (message.lParam & EXTENDED_KEY_BIT) ? extended_key : regular_key;
}


static uint16_t mouse_button_from(const MSG &message)
{
	// Get the button from the second lowest 16 bits
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-xbuttondown
	return (uint16_t) (message.wParam >> 16);
}


static MousePosition mouse_move_from(const MSG &message)
{
	// Get x from the lowest 16 bits and y from the second lowest 16 bits
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove
	int16_t x = (int16_t) message.lParam;
	int16_t y = (int16_t) ((uint32_t) (message.lParam) >> 16);
	return MousePosition {x, y};
}


} // namespace frac


#endif // _WIN32
