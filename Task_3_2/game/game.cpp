#include <vector>
#include <memory>
#include <iostream>
#include <experimental/string_view>
#include <algorithm>
#include "engine.h"

typedef std::experimental::string_view string_view;
int loop();

int main()
{

	loop();
	return 0;
}

std::vector<task::key_event> update(const std::vector<task::key_event>& keys);
std::vector<task::key_event> render(const std::vector<task::key_event>& keys);

int loop()
{
	using namespace task;
	//configure_windos
	engine& engine = *task::create_engine();
	engine.inicialize();
	std::vector<task::key_event> binds{};
	bool loop_status{true};
	while(loop_status)
	{
		//read_input
		///get_pressed_buttons
		std::vector<task::key_event> buff{};
		if (engine.read_input(buff))
		{
			binds.insert(binds.end(), buff.begin(), buff.end());
			auto it = std::find_if(binds.begin(),binds.end(),
								   [](const task::key_event& evt){return evt.bind.key == task::keyboard::escape; });
			if(it != binds.end())
				break;
			//update
			///prepare_for_render
			binds = update(binds);
			//render
			///out_updated_info
			binds = render(binds);
		}
	}
	return 0;
}


void out_keys(std::vector<task::key_event> keys, string_view prefix)
{
	using namespace std;
	if(keys.size() != 0)
	{
		cout << prefix;
		cout << keys[0].bind.key_name;
		for(auto it{keys.begin()+1}; it != keys.end(); it++)
			cout << '+' << it->bind.key_name;
		cout << endl;
	}
}
std::vector<task::key_event> render(const std::vector<task::key_event>& keys)
{
	using namespace std;
	vector<task::key_event> downs{};
	vector<task::key_event> ups{};
	for(auto it{keys.begin()}; it != keys.end(); it++)
	{
		if(it->type == task::event_type::key_down)
			downs.push_back(*it);
		else
			ups.push_back(*it);
	}
	out_keys(ups, "Released - ");
	out_keys(downs, "Pressed - ");
	vector<task::key_event> result{};
	for(const task::key_event& buff : keys)
	{
		if(buff.type == task::event_type::key_down)
			result.push_back(buff);
	}
	return result;
}

std::vector<task::key_event> update(const std::vector<task::key_event>& keys)
{
	using namespace std;
	vector<task::key_event> ups{};
	vector<task::key_event> downs{};
	for(const task::key_event& buff : keys)
	{
		if(buff.type == task::event_type::key_down)
			downs.push_back(buff);
		else
			ups.push_back(buff);
	}
	for(const task::key_event& buff : ups)
	{
		auto it = find_if(downs.begin(), downs.end(),
						  [buff](const task::key_event& k){return k.bind.key == buff.bind.key;});
		if(it != downs.end())
			downs.erase(it);
	}
	vector<task::key_event> result{};
	result.insert(result.end(), ups.begin(), ups.end());
	result.insert(result.end(), downs.begin(), downs.end());
	return result;
}

