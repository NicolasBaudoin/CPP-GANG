#ifndef ZOMBIE_CPP
# define ZOMBIE_CPP

#include "zombie.hpp"
#include <iostream>

void Zombie::announce(void)
{
	std::cout << "<" + name + ">" << "BraiiiiiiinnnzzzZ..." << std::endl;
}



#endif