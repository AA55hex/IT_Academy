
#include <assert.h>
#include <engine.h>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>
namespace gfx_engine
{
struct gl_bind
{
  GLuint index{0};
  std::string name{""};
  const GLchar* gl_name() const { return name.data(); }
};

int gl_check();
std::string read_shader(const std::string& path)
{
  using namespace std;

  ifstream file{path, ios_base::binary};
  if (!file.is_open())
    {
      std::cerr << path << " - can't find shader" << endl;
      return "";
    }

  string result{};
  const char eof{'\0'};
  getline(file, result, eof);

  return result;
}

GLuint gl_load_shader(GLenum s_type, const std::string source)
{
  GLuint shader{glCreateShader(s_type)};
  gl_check();
  const char* src{source.data()};
  glShaderSource(shader, 1, &src, nullptr);
  gl_check();
  glCompileShader(shader);
  gl_check();

  GLint compiled_status = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled_status);
  if (compiled_status == 0)
    {
      GLint info_len = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
      gl_check();
      std::vector<char> info_chars(static_cast<size_t>(info_len));
      glGetShaderInfoLog(shader, info_len, nullptr, info_chars.data());
      gl_check();
      glDeleteShader(shader);
      gl_check();

      std::string shader_type_name = "vertex";
      std::cerr << "Error compiling shader(vertex)" << std::endl
                << info_chars.data();
    }
  // update for check GL_COMPILE_STATUS
  return shader;
}

GLuint gl_load_program(GLuint v_shader, GLuint f_shader,
                       const std::vector<gl_bind>& binds)
{
  GLenum program{glCreateProgram()};
  gl_check();
  glAttachShader(program, v_shader);
  gl_check();
  glAttachShader(program, f_shader);
  gl_check();
  for (const auto& it : binds)
    {
      glBindAttribLocation(program, it.index, it.gl_name());
      gl_check();
    }
  glLinkProgram(program);
  gl_check();

  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  if (!linked)
    {
      GLint log_length{0};
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
      if (log_length != 0)
        {
          char* info_log{new char[static_cast<unsigned long>(log_length)]};
          std::cerr << "Shader program linker error:" << std::endl
                    << info_log << std::endl;
        }
    }

  glValidateProgram(program);
  gl_check();

  GLint validate_status;
  glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_status);
  gl_check();
  if (validate_status == GL_FALSE)
    {
      GLint infoLen = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
      gl_check();
      std::vector<char> infoLog(static_cast<size_t>(infoLen));
      glGetProgramInfoLog(program, infoLen, nullptr, infoLog.data());
      gl_check();
      std::cerr << "Error linking program:\n" << infoLog.data();
      throw std::runtime_error("error");
    }

  return program;
}

engine::engine() {}
int engine::inicialize()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

  window =
      SDL_CreateWindow("OpenGLTest", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

  gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);

  int glad_status{gladLoadGLES2Loader(SDL_GL_GetProcAddress)};
  if (glad_status != 0)
    {
      std::runtime_error{"gladLoadGLES2Loader - failed"};
    }
  /// Commented for bugs - RenderDoc
  GLuint vertex_buffer = 0;
  glGenBuffers(1, &vertex_buffer);
  gl_check();

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  gl_check();
  GLuint vertex_array_object = 0;
  glGenVertexArrays(1, &vertex_array_object);
  gl_check();
  glBindVertexArray(vertex_array_object);
  gl_check();
  /// Commented for bugs - RenderDoc

  std::string source{read_shader("triangle_test.vert")};
  GLuint v_shader{gl_load_shader(GL_VERTEX_SHADER, source)};

  source = read_shader("triangle_test.frag");
  GLuint f_shader{gl_load_shader(GL_FRAGMENT_SHADER, source)};

  std::vector<gl_bind> binds{{0, "a_position"}, {1, "a_color"}};

  gl_program = gl_load_program(v_shader, f_shader, binds);
  glUseProgram(gl_program);
  gl_check();

  // glReleaseShaderCompiler();

  return 0;
}

int engine::render(const triangle& trg)
{
  glBufferData(GL_ARRAY_BUFFER, sizeof(trg), &trg, GL_STATIC_DRAW);
  gl_check();

  // point to 0-indexed attribute
  glEnableVertexAttribArray(0);
  gl_check();

  GLintptr position_offset{0};
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        reinterpret_cast<void*>(position_offset));
  gl_check();

  // point to 1-index attribute
  glEnableVertexAttribArray(1);
  gl_check();

  position_offset += sizeof(float) * 2;
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        reinterpret_cast<void*>(position_offset));
  gl_check();

  // draw

  glDrawArrays(GL_TRIANGLES, 0, 3);
  gl_check();

  return 0;
}

int engine::swap_buffers()
{
  SDL_GL_SwapWindow(window);
  glClearColor(0.33f, 0.66f, 0.99f, 0.0f);
  gl_check();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gl_check();
  return 0;
}

engine::~engine()
{
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

std::istream& operator>>(std::istream& in, vertex& v)
{
  in >> v.x >> v.y >> v.r >> v.g >> v.b;
  return in;
}

std::istream& operator>>(std::istream& in, triangle& t)
{
  in >> t.vertexes[0] >> t.vertexes[1] >> t.vertexes[2];
  return in;
}

int gl_check()
{
  const GLenum err = glGetError();
  int err_spec{0};
  if (err != GL_NO_ERROR)
    {
      switch (err)
        {
          case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM" << std::endl;
            err_spec = 1;
            break;
          case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE" << std::endl;
            err_spec = 2;
            break;
          case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION" << std::endl;
            err_spec = 4;
            break;
          case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
            err_spec = 8;
            break;
          case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY" << std::endl;
            err_spec = 16;
            break;
        }
      std::cerr << __FILE__ << ':' << __LINE__ << '(' << __FUNCTION__ << ')'
                << std::endl;
      assert(false);
    }
  return err_spec;
}

}  // namespace gfx_engine
