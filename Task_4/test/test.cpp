#include <SDL.h>
#include <SDL_atomic.h>
#include <math.h>
#include <ppm_base.h>
#include <render.h>
#include <algorithm>
#include <iostream>
#include <map>
#include "gfx.h"

double get_step_kfc(double x) { return 1.0 / (1 + std::exp(-x / 2)); }

int main()
{
  const int width{640};
  const int height{480};

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
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

  render::rastered_triangle itp_render{cnv};

  std::map<int, render::vertex> triangle_v{};

  triangle_v[0] = {0, 0, 255, 0, 0, 0, 0};
  triangle_v[1] = {0, 1, 0, 255, 0, 0, 1};
  triangle_v[2] = {1, 1, 0, 0, 255, 1, 1};

  triangle_v[3] = {0, 0, 0, 255, 0, 0, 0};
  triangle_v[4] = {1, 0, 255, 0, 0, 1, 0};
  triangle_v[5] = {1, 1, 255, 0, 0, 1, 1};
  std::vector<int> indexes_v{0, 1, 2, 3, 4, 5};

  void* pixels = cnv.data();
  const int depth = sizeof(render::rgb_color) * 8;
  const int pitch = width * sizeof(render::rgb_color);
  const int rmask = 0x000000ff;
  const int gmask = 0x0000ff00;
  const int bmask = 0x00ff0000;
  const int amask = 0;

  render::canvas texture{ppm::image_manager::load_image("image.ppm")};
  render::canvas key{ppm::image_manager::load_image("key.ppm")};
  render::gfx1 prg{texture, key};
  itp_render.set_gfx_program(prg);

  bool continue_loop{true};

  const int steps{128};
  size_t line_pos_x{0};
  double line_buff{width};
  Uint32 prev_ticks{SDL_GetTicks()};
  Uint32 current_ticks{};
  double max_speed{(width * 2.0) / steps};
  while (continue_loop)
    {
      current_ticks = SDL_GetTicks();
      if ((current_ticks - prev_ticks) >= 10 && line_buff >= 0)
        {
          // double speed_k{get_step_kfc((line_buff / steps) * 7 - 5)};
          double speed_k{std::tanh(line_buff - width / 2.0)};
          line_buff -= static_cast<double>(width) / steps;
          line_pos_x += static_cast<size_t>(max_speed * speed_k);
          prev_ticks = current_ticks;
        }
      SDL_Event e;
      while (SDL_PollEvent(&e))
        {
          if (e.type == SDL_QUIT)
            {
              continue_loop = false;
              break;
            }
        }
      cnv.clear(default_color);
      prg.set_uniforms(
          render::uniforms{0, 0, 0, 0, 0, 0, 0, 0, width, height, line_pos_x});

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
