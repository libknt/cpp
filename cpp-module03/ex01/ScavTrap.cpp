#include "ScavTrap.hpp"

ScavTrap::ScavTrap(const std::string& name)
	: ClapTrap(name) {
	std::cout << "ScavTrap defualt constructor called: " << name << std::endl;
	hit_points_ = 100;
	energy_points_ = 50;
	attack_damage_ = 20;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap defualt destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
	if (!checkPoints())
		return;
	consumeEnergyPoints();
	std::cout << "ScavTrap " << this->getName() << " attacks " << target << ", causing "
			  << this->getAttackDamage() << " points of damage!" << std::endl;
}

void ScavTrap::guardGate() const {
	if (!checkPoints())
		return;
	std::cout << "ScavTrap " << this->getName() << " is now in Gate keeper mode." << std::endl;
}