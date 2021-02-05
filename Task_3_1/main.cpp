#include <iostream>
#include <SDL_version.h>
#include <SDL.h>
#include <experimental/string_view>
#include <vector>
#include <array>
#include <algorithm>
#include <exception>
#include <sstream>
typedef std::experimental::string_view string_view;




//Add KeyboardCode inicialize
struct key_bind
{
	key_bind(SDL_KeyCode keycode, string_view name, SDL_EventType t)
		: key{keycode}, key_name{name}, type{t}
	{}

	key_bind(SDL_KeyCode keycode, string_view name)
		: key_bind(keycode,
				   name,
				   SDL_EventType::SDL_FIRSTEVENT)
	{}

	key_bind(SDL_KeyboardEvent evt)
		: key_bind(static_cast<SDL_KeyCode>(evt.keysym.sym),
				   static_cast<char>(evt.keysym.sym) + "",
				   static_cast<SDL_EventType>(evt.type))
	{}

	key_bind(SDL_KeyboardEvent evt, string_view name)
		: key_bind(static_cast<SDL_KeyCode>(evt.keysym.sym),
				   name,
				   static_cast<SDL_EventType>(evt.type))
	{}

	SDL_KeyCode key;
	string_view key_name;
	SDL_EventType type;
};

int get_version();
std::ostream& operator<<(std::ostream& ost, const SDL_version& version);
int loop();

int main()
{
	get_version();
	loop();
    return 0;
}


bool read_input(std::vector<key_bind>& input);
std::vector<key_bind> update(const std::vector<key_bind>& keys);
std::vector<key_bind> render(const std::vector<key_bind>& keys);

static bool loop_status{true};
int loop()
{
	using namespace std;
	//configure_window
	SDL_Window* const window = SDL_CreateWindow("game-3.1",
												SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED,
												640,
												480,
												SDL_WINDOW_OPENGL);
	vector<key_bind> binds{};

	while(loop_status)
	{
		//read_input
		///get_pressed_buttons
		vector<key_bind> buff{};
		if (read_input(buff))
		{
			binds.insert(binds.end(), buff.begin(), buff.end());
			//update
			///prepare_for_render
			binds = update(binds);
			//render
			///out_updated_info
			binds = binds = render(binds);
		}
	}
	SDL_DestroyWindow(window);
	return 0;
}

void out_keys(std::vector<key_bind> keys, string_view prefix)
{
	using namespace std;
	if(keys.size() != 0)
	{
		cout << prefix;
		cout << keys[0].key_name;
		for(auto it{keys.begin()+1}; it != keys.end(); it++)
			cout << '+' << it->key_name;
		cout << endl;
	}
}
std::vector<key_bind> render(const std::vector<key_bind>& keys)
{
	using namespace std;
	vector<key_bind> downs{};
	vector<key_bind> ups{};
	for(auto it{keys.begin()}; it != keys.end(); it++)
	{
		if(it->type == SDL_KEYDOWN)
			downs.push_back(*it);
		else
			ups.push_back(*it);
	}
	//out_keys(ups, "Released - ");
	out_keys(downs, "Pressed - ");
	vector<key_bind> result{};
	for(const key_bind& buff : keys)
	{
		if(buff.type == SDL_KEYDOWN)
			result.push_back(buff);
	}
	return result;
}

std::vector<key_bind> update(const std::vector<key_bind>& keys)
{
	using namespace std;
	vector<key_bind> ups{};
	vector<key_bind> downs{};
	for(const key_bind& buff : keys)
	{
		if(buff.type == SDL_KEYDOWN)
			downs.push_back(buff);
		else
			ups.push_back(buff);
	}
	for(const key_bind& buff : ups)
	{
		auto it = find_if(downs.begin(), downs.end(),
						  [buff](const key_bind& k){return k.key == buff.key;});
		if(it != downs.end())
			downs.erase(it);
	}
	vector<key_bind> result{};
	result.insert(result.end(), ups.begin(), ups.end());
	result.insert(result.end(), downs.begin(), downs.end());
	return result;
}

//key_bind handle_event(const SDL_Event& event);

bool read_input(std::vector<key_bind>& input)
{
	using namespace std;
	const array<key_bind, 8> binds
	{
		{
			{ SDLK_w, "Up" },
			{ SDLK_a, "Left" },
			{ SDLK_s, "Down" },
			{ SDLK_d, "Right" },
			{ SDLK_LCTRL, "Ctrl" },
			{ SDLK_SPACE, "Space" },
			{ SDLK_ESCAPE, "Escape" },
			{ SDLK_RETURN, "Enter" }
		}
	};
	SDL_Event event{};
	bool updated{false};
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			if(event.key.repeat == 0)
			{
				const auto iterator = find_if(binds.begin(), binds.end(),
											  [&](const key_bind& bind){return bind.key == event.key.keysym.sym;} );
				if(iterator != binds.end())
					input.push_back(key_bind(iterator->key,
									iterator->key_name,
									static_cast<SDL_EventType>(event.type)));
				updated = true;
			}
			break;
		default:
			break;
		}
	}
	return updated;
}

//key_bind handle_event(const SDL_Event& event)
//{
//	using namespace std;
//	const array<key_bind, 8> binds
//	{
//		{
//			{ SDLK_w, "Up" },
//			{ SDLK_a, "Left" },
//			{ SDLK_s, "Down" },
//			{ SDLK_d, "Right" },
//			{ SDLK_LCTRL, "Ctrl" },
//			{ SDLK_SPACE, "Space" },
//			{ SDLK_ESCAPE, "Escape" },
//			{ SDLK_RETURN, "Enter" }
//		}
//	};
//	const auto iterator = find_if(binds.begin(), binds.end(),
//								  [&](const key_bind& bind){return bind.key == event.key.keysym.sym;} );
//	if(iterator != binds.end())
//		return key_bind(iterator->key,
//						iterator->key_name,
//						static_cast<SDL_EventType>(event.type));
//	else
//		return key_bind(iterator->key,
//						"Uncown",
//						static_cast<SDL_EventType>(event.type));
//}


int get_version()
{
	using namespace std;
	SDL_version version_linked{};
	SDL_version version_compiled{};

	SDL_VERSION(&version_compiled);
	SDL_GetVersion(&version_linked);

	cout << "Compiled:\t" << version_compiled
		 << "Linked:\t" << version_linked;
	cout.flush();
	return cout.good();
}
std::ostream& operator<<(std::ostream& ost, const SDL_version& version)
{
	ost << static_cast<int>(version.major)
		<< '.' << static_cast<int>(version.minor)
		<< '.' << static_cast<int>(version.patch)
		<< std::endl;
	return ost;
}
