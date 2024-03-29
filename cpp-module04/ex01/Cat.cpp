#include "Cat.hpp"

Cat::Cat(void)
	: Animal("Cat") {
	std::cout << "Cat Default constructor called" << std::endl;
	this->brain = new Brain();
}

Cat::Cat(const Cat& c)
	: Animal(c) {
	*this = c;
}

Cat::~Cat(void) {
	delete this->brain;
	std::cout << "Cat Default destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& r) {
	if (this != &r) {
		this->type_ = r.getType();
		this->brain = new Brain(*r.brain);
	}
	return *this;
}

void Cat::makeSound(void) const {
	std::cout << "the cat is meowing. meow meow!" << std::endl;
}