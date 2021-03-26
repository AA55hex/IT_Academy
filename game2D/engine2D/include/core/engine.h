#pragma once
#include <SDL.h>
#include <string>
namespace sound
{
void audio_callback(void* userdata, Uint8* stream, int len);
}  // namespace sound

namespace engine
{
bool inicialize(int width, int height, std::string title,
                bool gl_debug = false);
void dispose();
namespace audio
{
extern SDL_AudioDeviceID audio_device;
extern SDL_AudioSpec audio_device_spec;
}  // namespace audio

namespace window
{
extern SDL_Window* window;
extern SDL_GLContext gl_context;
extern int height;
extern int width;
}  // namespace window

// class engine
//{
// public:
//  engine();
//  bool inicialize();
//  void dispose();

// private:
//  friend class sound::sound_buffer;
//  friend class render::renderer;
//  struct
//  {
//    SDL_AudioDeviceID audio_device;
//    SDL_AudioSpec audio_device_spec;
//  } audio;
//  struct
//  {
//    SDL_Window* window;
//    SDL_GLContext gl_context;
//    int height;
//    int width;
//  } window;
//};
}  // namespace engine
