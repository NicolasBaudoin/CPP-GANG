#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	private:
		Contact	_contact[8];
		int		_count;

	public:
		PhoneBook(void);
		void	addContact(Contact const & c);
		int		getCount(void) const;
		Contact const & getContact(int index) const;
};

#endif
