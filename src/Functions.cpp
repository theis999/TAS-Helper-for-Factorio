#include "Functions.h"
#include "utils.h"

bool compare_task_strings(const wxString& str1, const std::string& str2)
{
	if (str1.length() != str2.length()) {
		return false;
	}

	for (int i = 0; i < str1.length(); i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}

	return true;
}

std::string extract_define(std::string building, std::string from_into)
{
	if (from_into == "wreck") {
		return struct_take_put_list.chest;
	}

	if (from_into == "chest") {
		return struct_take_put_list.chest;
	}

	if (from_into == "fuel") {
		return struct_take_put_list.fuel;
	}

	if (building == "Lab") {
		if (from_into == "input") {
			return struct_take_put_list.lab_input;
		}
		else if (from_into == "modules") {
			return struct_take_put_list.lab_modules;
		}
	}

	if (check_input(building, drills_list)) {
		return struct_take_put_list.drill_modules;
	}

	if (from_into == "input") {
		return struct_take_put_list.assembly_input;
	}

	if (from_into == "modules") {
		return struct_take_put_list.assembly_modules;
	}
	if (from_into == "output") {
		return struct_take_put_list.assembly_output;
	}

	return "Not Found";
}

bool check_input(std::string& item, const std::vector<std::string>& all_items)
{
	std::string item_lower = "";
	for (unsigned int i = 0; i < item.size(); i++) {
		item_lower.push_back(std::tolower(item[i]));
	}

	for (auto it = all_items.begin(); it < all_items.end(); it++) {

		std::string check_item_lower = "";

		for (unsigned int i = 0; i < (*it).size(); i++) {
			check_item_lower.push_back(std::tolower((*it)[i]));
		}

		if (item_lower == check_item_lower) {
			item = *it;
			return true;
		}
	}

	return false;
}

void find_coordinates(std::string& x_cord, std::string& y_cord, std::string& direction, std::string& building_size) {
	if (direction == "north" || direction == "North") {
		y_cord = std::to_string(std::stof(y_cord) - std::stof(building_size));

	} else if (direction == "south" || direction == "South") {
		y_cord = std::to_string(std::stof(y_cord) + std::stof(building_size));

	} else if (direction == "east" || direction == "East") {
		x_cord = std::to_string(std::stof(x_cord) + std::stof(building_size));

	} else if (direction == "west" || direction == "West") {
		x_cord = std::to_string(std::stof(x_cord) - std::stof(building_size));
	}
}

void string_capitalized(std::string& string) {
	if (string != "") {
		string[0] = std::toupper(string[0]);
		for (int i = 1; string[i] != '\0'; ++i) {
			string[i] = tolower(string[i]);
		}
	}
}

bool is_number(const std::string& str) {
	for (auto s : str) {
		if (!std::isdigit(s)) {
			return false;
		}
	}

	return true;
}