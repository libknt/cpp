#ifndef _PHONEBOOK_HPP
#define _PHONEBOOK_HPP
#include "Contact.hpp"
#include <iostream>
#include <sstream>
#include <stdlib.h>

void flush_cin();
int get_cmd(const std::string& s, std::string* cmd);
std::string get_line(const std::string& mess);

class Phonebook {
public:
	Phonebook();
	~Phonebook();
	void add();
	void search();

private:
	Contact contact_[8];
	int get_index();
	int next_index;
	int request_index();
	void display_contact(int index);
};

#endif
