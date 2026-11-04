#include "PhoneBook.hpp"

void PhoneBook::addContact(Contact const & c)
{
	int index = _count % 8;
	_contact[index] = c;
	_count++;
}
PhoneBook::PhoneBook(void) : _count(0)   // liste d'initialisation
{

}

int	PhoneBook::getCount(void) const
{
	return _count;
}

Contact const & PhoneBook::getContact(int index) const
{
	return _contact[index];
}

