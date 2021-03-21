#include <engine.h>
#include <fstream>
int main()
{
  gfx_engine::engine engine{};
  engine.inicialize();
  gfx_engine::triangle trg{};

  bool continue_loop{true};

  while (continue_loop)
    {
      std::ifstream file("vertexes.txt");
      if (!file.is_open()) break;
      file >> trg;
      engine.render(trg);
      engine.swap_buffers();
    }

  return 0;
}
