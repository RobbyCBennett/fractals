#include "event.hpp"


namespace frac {


using enum EventKind;


Event::Event()
{
	kind = None;
}


Event Event::focus_in()
{
	return Event(FocusIn);
}


Event Event::focus_out()
{
	return Event(FocusOut);
}


Event Event::key_down(Key key)
{
	return Event(KeyDown, key);
}


Event Event::key_repeat(Key key)
{
	return Event(KeyRepeat, key);
}


Event Event::key_up(Key key)
{
	return Event(KeyUp, key);
}


Event Event::mouse_button_down(MouseButton button)
{
	return Event(MouseButtonDown, button);
}


Event Event::mouse_button_up(MouseButton button)
{
	return Event(MouseButtonUp, button);
}


Event Event::mouse_move(int32_t x, int32_t y)
{
	return Event(MouseMove, MousePosition {x, y});
}


Event Event::mouse_move(MousePosition position)
{
	return Event(MouseMove, position);
}


Event Event::mouse_scroll_down()
{
	return Event(MouseScrollDown);
}


Event Event::mouse_scroll_up()
{
	return Event(MouseScrollUp);
}


Event::operator bool() const
{
	return kind != None;
}


Event::Event(EventKind kind_)
{
	kind = kind_;
}


Event::Event(EventKind kind_, Key key_)
{
	kind = kind_;
	key = key_;
}


Event::Event(EventKind kind_, MouseButton button_)
{
	kind = kind_;
	button = button_;
}


Event::Event(EventKind kind_, MousePosition move_)
{
	kind = kind_;
	move = move_;
}


const char *to_string(EventKind kind)
{
	using enum EventKind;
	switch (kind) {
		case None:
			return "None";
		case FocusIn:
			return "Focus in";
		case FocusOut:
			return "Focus out";
		case KeyDown:
			return "Key down";
		case KeyRepeat:
			return "Key repeat";
		case KeyUp:
			return "Key up";
		case MouseButtonDown:
			return "Mouse button down";
		case MouseButtonUp:
			return "Mouse button up";
		case MouseMove:
			return "Mouse move";
		case MouseScrollDown:
			return "Mouse scroll down";
		case MouseScrollUp:
			return "Mouse scroll up";
	}
	return "ERROR: Uninitialized event kind";
}


const char *to_string(MouseButton button)
{
	using enum MouseButton;
	switch (button) {
		case Left:
			return "Left";
		case Middle:
			return "Middle";
		case Right:
			return "Right";
		case Back:
			return "Back";
		case Forward:
			return "Forward";
	}
	return "ERROR: Uninitialized mouse button";
}


} // namespace frac
