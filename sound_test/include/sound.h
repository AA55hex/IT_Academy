#include <SDL.h>
#include <memory>
#include <vector>

// class isound_meta
//{
//};

// struct iplayback
//{
//  const isound_meta* sound_data;
//  uint32_t current_pos{0};
//  bool is_looped{false};
//  bool is_playing{false};
//};

class wav_sound_meta
{
 public:
  struct wav_playback
  {
    const wav_sound_meta* sound_data;
    uint32_t current_pos{0};
    bool is_looped{false};
    bool is_playing{false};
  };

  wav_sound_meta() {}
  wav_sound_meta(uint8_t* begin, uint32_t duration, SDL_AudioSpec spec);

  std::shared_ptr<wav_playback> play(uint32_t current_pos = 0,
                                     bool is_looped = false);

  uint8_t* begin{nullptr};
  uint32_t duration{0};
  SDL_AudioSpec specification{};

  ~wav_sound_meta();

  wav_sound_meta(wav_sound_meta&&);
  wav_sound_meta& operator=(wav_sound_meta&&);

  wav_sound_meta(wav_sound_meta&) = delete;
  wav_sound_meta& operator=(wav_sound_meta&) = delete;
};

class sound_object
{
};

class sound_manager final
{
 public:
  static bool init();
  static void dispose();

  static void play();
  static void pause();

  static void play_sound(std::shared_ptr<wav_sound_meta::wav_playback> sample);

  static void clear_stream();

  sound_manager() = delete;

 private:
  static void audio_callback(void* userdata, Uint8* stream, int len);

  inline static SDL_AudioDeviceID audio_device;

  inline static std::vector<wav_sound_meta::wav_playback> playback_list;
};

/// 0. sound
/// 1. --playback_layout
/// 2. sound_shell (array of playbacks of one sound)
/// 3. sound_object (array of sound_shells)
/// 4. sount_state (array of sound_objects)
/// 5. sound_manager (get on input)
///
/// 0 - shared only
/// 1-3 - play/pause
/// 5 - attach/detach
///
///
/// --------------------
///
/// 0. sound
///  - play - current state insert ( use manager )
///  - pause (pause all playbacks)
///  - erase_playbacks (erase all playbacks)
/// 1. playback
///  - playing/paused/on_delete
/// 2. state
///  - attach/detach
///  - playback vector
/// 3. manager
///
/// ?? state + manager = sound_manager
