#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
	int i;
	Zombie *z = new Zombie[N];
	
	i = 0;
	while(i < N)
	{
			z[i].setname(name);
			i++;
	}
	return z;
}
