#include "Dog.hpp"

Dog::Dog( void ) : AAnimal("Dog") { 
    std::cout << "Dog Default constructor called" << std::endl; 
    this->brain = new Brain();
}

Dog::Dog(const Dog & d) : AAnimal(d) { *this = d; }

Dog::~Dog( void ) { 
    delete this->brain;
    std::cout << "Dog Default destructor called" << std::endl; 
};

Dog & Dog::operator= ( const Dog & r)
{
    this->type_ = r.getType();
    this->brain = new Brain();
    return *this;
}

void Dog::makeSound( void ) const {
    std::cout << std::setw(13) << "dog makeSound" << ":" << "woof" << std::endl; 
}
