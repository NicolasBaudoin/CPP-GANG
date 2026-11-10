#ifndef ZOMBIE_CPP
# define ZOMBIE_CPP

#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name): _name(name)
{
}

Zombie::~Zombie(void)
{
    std::cout << _name << " s'en va" << std::endl;
}


void Zombie::grogner(void)
{
	std::cout << _name + ":"  << "BraiiiiiiinnnzzzZ..." << std::endl;
}



#endif
