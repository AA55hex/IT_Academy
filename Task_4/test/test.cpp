#include <SDL.h>
#include <math.h>
#include <ppm_base.h>
#include <render.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include "gfx.h"

int main()
{
  const int width{640};
  const int height{480};

  if (0 != SDL_Init(SDL_INIT_EVERYTHING))
    {
      std::cerr << SDL_GetError() << std::endl;
      return EXIT_FAILURE;
    }

  SDL_Window* window = SDL_CreateWindow(
      "runtime soft render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      width, height, SDL_WINDOW_OPENGL);
  if (window == nullptr)
    {
      std::cerr << SDL_GetError() << std::endl;
      return EXIT_FAILURE;
    }

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
    {
      std::cerr << SDL_GetError() << std::endl;
      return EXIT_FAILURE;
    }

  const render::rgb_color default_color = {0, 0, 0};
  render::canvas cnv{width, height};
  cnv.clear(default_color);

  render::itp_triangle itp_render{cnv};

  std::map<int, render::vertex> triangle_v{};

  triangle_v[0] = {1, 1, 255, 0, 0, 0, 0};
  triangle_v[1] = {1, height - 1, 0, 255, 0, 0, 239};
  triangle_v[2] = {width, height, 0, 0, 255, 319, 239};

  triangle_v[3] = {1, 1, 0, 255, 0, 0, 0};
  triangle_v[4] = {width, 0, 255, 0, 0, 319, 239};
  triangle_v[5] = {width, height, 255, 0, 0, 319, 239};
  std::vector<int> indexes_v{3, 4, 5, 0, 1, 2};

  void* pixels = cnv.data();
  const int depth = sizeof(render::rgb_color) * 8;
  const int pitch = width * sizeof(render::rgb_color);
  const int rmask = 0x000000ff;
  const int gmask = 0x0000ff00;
  const int bmask = 0x00ff0000;
  const int amask = 0;

  render::gfx1 prg{cnv};
  itp_render.set_gfx_program(prg);

  double mouse_x{};
  double mouse_y{};
  double radius{100};

  bool continue_loop = true;

  while (continue_loop)
    {
      SDL_Event e;
      while (SDL_PollEvent(&e))
        {
          if (e.type == SDL_QUIT)
            {
              continue_loop = false;
              break;
            }
          else if (e.type == SDL_MOUSEMOTION)
            {
              mouse_x = e.motion.x;
              mouse_y = e.motion.y;
            }
          else if (e.type == SDL_MOUSEWHEEL)
            {
              radius += e.wheel.y;
            }
        }

      cnv.clear(default_color);
      prg.set_uniforms(render::uniforms{mouse_x, mouse_y, radius});

      itp_render.rastered_draw(triangle_v, indexes_v);
      SDL_Surface* bitmapSurface = SDL_CreateRGBSurfaceFrom(
          pixels, width, height, depth, pitch, rmask, gmask, bmask, amask);

      SDL_Texture* bitmapTex =
          SDL_CreateTextureFromSurface(renderer, bitmapSurface);

      SDL_FreeSurface(bitmapSurface);

      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, bitmapTex, nullptr, nullptr);
      SDL_RenderPresent(renderer);

      SDL_DestroyTexture(bitmapTex);
    }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return EXIT_SUCCESS;
}
