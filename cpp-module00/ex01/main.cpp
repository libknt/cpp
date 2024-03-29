#include "PhoneBook.hpp"
#include <fstream>
#include <limits>
#include <sstream>
#include <unistd.h>

void order_table() {
	std::cout << std::endl;
	std::cout << "Please enter the command" << std::endl;
	std::cout << "ORDER" << std::endl;
	std::cout << "ADD	: save a new contact" << std::endl;
	std::cout << "SEARCH	: display a specfic contact" << std::endl;
	std::cout << "EXIT" << std::endl;
}

void flush_buffer_if_not_empty() {
	if (std::cin.rdbuf()->in_avail())
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int get_cmd(const std::string& s, std::string* cmd) {
	std::cout << s;
	if (!std::getline(std::cin, *cmd)) {
		if (std::cin.eof()) {
			std::cin.clear();
			exit(0);
		} else {
			flush_cin();
			cmd->clear();
		}
		return 1;
	}
	flush_cin();
	return 0;
}

static bool isspace_string(std::string s) {
	for (size_t i = 0; i < s.length(); i++) {
		if (!isspace(s[i]))
			return false;
	}
	return true;
}

std::string get_line(const std::string& mess) {
	std::string tmp;

	for (;;) {
		get_cmd(mess, &tmp);
		if (!tmp.empty() && !isspace_string(tmp))
			break;
	}
	return tmp;
}

void flush_cin() {
	std::cin.clear();
	flush_buffer_if_not_empty();
}

int main() {
	Phonebook book;
	std::string cmd;

	order_table();
	for (;;) {
		if (get_cmd("command >", &cmd))
			continue;

		if (cmd.compare("EXIT") == 0)
			break;
		else if (cmd.compare("ADD") == 0) {
			book.add();
		} else if (cmd.compare("SEARCH") == 0) {
			book.search();
		} else if (cmd.compare("ORDER") == 0) {
			order_table();
		} else {
			std::cout << "Please enter the correct command!" << std::endl << std::endl;
		}
	}
	return 0;
}
