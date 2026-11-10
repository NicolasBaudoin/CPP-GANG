#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>

class Zombie
{
	private:
		std::string _name;

	public:
        Zombie(std::string _name);
        ~Zombie(void);
        void grogner(void);
};

Zombie* newZombie(std::string name);  

#endif
