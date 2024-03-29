#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main() {
	FragTrap a("Emily"), b("James");
	ScavTrap scav("Emily");
	scav.guardGate();
	a.highFivesGuys();
	b.highFivesGuys();
	a.getInfo();
	b.getInfo();

	a.attack(b.getName());
	b.takeDamage(a.getAttackDamage());
	b.beRepaired(5);

	a.getInfo();
	b.getInfo();

	b.attack(a.getName());
	a.takeDamage(b.getAttackDamage());
	a.beRepaired(100);
	a.getInfo();
	b.getInfo();

	while (b.checkPoints()) {
		a.attack(b.getName());
		b.takeDamage(a.getAttackDamage());
	}

	std::cout << "--------------------------------" << std::endl;
	a.getInfo();
	b.getInfo();
	std::cout << "++++++++++" << std::endl;
	std::cout << "Challenge." << std::endl;
	b.attack(a.getName());
	b.beRepaired(777);
	std::cout << "Challenge end." << std::endl;
	std::cout << "++++++++++" << std::endl;
	a.getInfo();
	b.getInfo();
	std::cout << "--------------------------------" << std::endl;
	FragTrap c("Emma"), d("William");
	d.beRepaired(10000000);
	c.getInfo();
	d.getInfo();
	while (c.checkPoints()) {
		c.attack(d.getName());
		d.takeDamage(c.getAttackDamage());
	}
	c.getInfo();
	d.getInfo();
	std::cout << "++++++++++" << std::endl;
	std::cout << "Challenge." << std::endl;
	c.attack(d.getName());
	c.beRepaired(7777);
	std::cout << "Challenge end." << std::endl;
	std::cout << "++++++++++" << std::endl;
	c.getInfo();
	d.getInfo();
	a.highFivesGuys();
	b.highFivesGuys();
	c.highFivesGuys();
	d.highFivesGuys();
	return 0;
}
