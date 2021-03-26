#pragma once
namespace input
{
enum struct event_type
{
  keyboard,
  mouse,
  quit
};

enum struct mouse_button
{
  none,
  button_left,
  button_right,
  button_middle,
  button_x1,
  button_x2
};

enum struct keyboard_key
{
  none,
  q,
  w,
  e,
  a,
  s,
  d
};

enum struct event_state
{
  none,
  key_down,
  key_up,
  motion
};

struct input_event
{
  event_type type;
  event_state state;
  mouse_button mouse;
  keyboard_key key;
};

// struct keyboard_event
//{
//  event_state state;
//  keyboard_key key;
//};

// struct mouse_event
//{
//  event_state state;
//  mouse_button button;
//};
}  // namespace input
