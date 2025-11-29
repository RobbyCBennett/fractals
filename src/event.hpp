#pragma once


#include "key.hpp"


namespace frac {


enum class EventKind: uint8_t
{
	None,

	FocusIn,
	FocusOut,

	KeyDown,
	KeyRepeat,
	KeyUp,

	MouseButtonDown,
	MouseButtonUp,

	MouseMove,

	MouseScrollDown,
	MouseScrollUp,
};


enum class MouseButton: uint8_t
{
	Left,
	Middle,
	Right,
	Back,
	Forward,
};


struct MousePosition
{
	int32_t x;
	int32_t y;
};


class Event
{
public:
	EventKind kind;

	union {
		Key key;
		MouseButton button;
		MousePosition move;
	};

	Event();
	static Event focus_in();
	static Event focus_out();
	static Event key_down(Key key);
	static Event key_repeat(Key key);
	static Event key_up(Key key);
	static Event mouse_button_down(MouseButton button);
	static Event mouse_button_up(MouseButton button);
	static Event mouse_move(int32_t x, int32_t y);
	static Event mouse_move(MousePosition position);
	static Event mouse_scroll_down();
	static Event mouse_scroll_up();

	operator bool() const;

private:
	Event(EventKind kind);
	Event(EventKind kind, Key key);
	Event(EventKind kind, MouseButton button);
	Event(EventKind kind, MousePosition move);
};


const char *to_string(EventKind kind);
const char *to_string(MouseButton button);


} // namespace frac
