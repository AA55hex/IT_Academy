#include <assert.h>
#include <engine.h>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>
namespace engine_lib
{
int gl_check();
bool engine::inicialize()
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

  return true;
}

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

GLuint gl_object::get_id() { return id; }
gl_object::gl_object() {}
shader::shader(const std::string& src) : gl_object() {}
}  // namespace engine_lib
