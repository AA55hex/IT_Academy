#include <algorithm>
#include <experimental/string_view>
#include <iostream>
#include <memory>
#include <vector>
#include "engine.h"

typedef std::experimental::string_view string_view;
int loop();

int main()
{
  loop();
  return 0;
}

bool escape_status();

std::vector<engine_lib::key_event> update(
    const std::vector<engine_lib::key_event>& keys);
std::vector<engine_lib::key_event> render(
    const std::vector<engine_lib::key_event>& keys);

int loop()
{
  using namespace engine_lib;
  // configure_windos
  engine engine{};
  engine.inicialize();
  std::vector<engine_lib::key_event> binds{};
  bool loop_status{true};
  while (loop_status)
    {
      // read_input
      /// get_pressed_buttons
      std::vector<engine_lib::key_event> buff{};
      if (engine.read_input_list(buff) != 0)
        {
          binds.insert(binds.end(), buff.begin(), buff.end());
          auto it = std::find_if(binds.begin(), binds.end(),
                                 [](const engine_lib::key_event& evt) {
                                   return evt.bind.key == keyboard::escape;
                                 });
          if (it != binds.end()) break;
          binds = update(binds);
        }
    }
  return 0;
}

void out_keys(std::vector<engine_lib::key_event> keys, string_view prefix)
{
  using namespace std;
  if (keys.size() != 0)
    {
      cout << prefix;
      cout << keys[0].bind.key_name;
      for (auto it{keys.begin() + 1}; it != keys.end(); it++)
        cout << '+' << it->bind.key_name;
      cout << endl;
    }
}

std::vector<engine_lib::key_event> render(
    const std::vector<engine_lib::key_event>& keys)
{
  using namespace std;
  vector<engine_lib::key_event> downs{};
  vector<engine_lib::key_event> ups{};
  for (auto it{keys.begin()}; it != keys.end(); it++)
    {
      if (it->type == engine_lib::event_type::key_down)
        downs.push_back(*it);
      else
        ups.push_back(*it);
    }
  out_keys(ups, "Released - ");
  out_keys(downs, "Pressed - ");
  vector<engine_lib::key_event> result{};
  for (const engine_lib::key_event& buff : keys)
    {
      if (buff.type == engine_lib::event_type::key_down) result.push_back(buff);
    }
  return result;
}

std::vector<engine_lib::key_event> update(
    const std::vector<engine_lib::key_event>& keys)
{
  using namespace std;
  vector<engine_lib::key_event> ups{};
  vector<engine_lib::key_event> downs{};
  for (const engine_lib::key_event& buff : keys)
    {
      if (buff.type == engine_lib::event_type::key_down)
        downs.push_back(buff);
      else
        ups.push_back(buff);
    }
  for (const engine_lib::key_event& buff : ups)
    {
      auto it = find_if(downs.begin(), downs.end(),
                        [buff](const engine_lib::key_event& k) {
                          return k.bind.key == buff.bind.key;
                        });
      if (it != downs.end()) downs.erase(it);
    }
  vector<engine_lib::key_event> result{};
  result.insert(result.end(), ups.begin(), ups.end());
  result.insert(result.end(), downs.begin(), downs.end());
  return result;
}
