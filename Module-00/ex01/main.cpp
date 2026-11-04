#include <string>
#include <iostream>
#include "PhoneBook.hpp"
#include "search.hpp"


static void	errorTitleInfo(int mode)
{	switch (mode)
	{
		case 0:
			std::cout << "First name cannot be empty. Try again: ";
			break ;
		case 1:
			std::cout << "Last name cannot be empty. Try again: ";
			break ;
		case 2:
			std::cout << "Nickname cannot be empty. Try again: ";
			break ;
		case 3:
			std::cout << "Phone number cannot be empty. Try again: ";
			break ;
		case 4:
			std::cout << "Darkest secret cannot be empty. Try again: ";
			break ;
	}
}

static void showTitleInfo(int mode)
{
	switch (mode)
	{
		case 0:
			std::cout << "First name: ";
			break ;
		case 1:
			std::cout << "Last name: ";
			break ;
		case 2:
			std::cout << "Nickname: ";
			break ;
		case 3:
			std::cout << "Phone number: ";
			break ;
		case 4:
			std::cout << "Darkest secret: ";
			break ;
	}
}


static void	addInfoContact(std::string &value, int mode)
{
		showTitleInfo(mode);
		std::getline(std::cin, value);
		while (value.empty())
		{
			errorTitleInfo(mode);
			std::getline(std::cin, value);
		}

}


static void	createContact(PhoneBook *book)
{
	std::string firstName;
	std::string lastName;
	std::string nickname;
	std::string phoneNumber;
	std::string darkestSecret;
	Contact		c;

	addInfoContact(firstName, 0);
	addInfoContact(lastName, 1);
	addInfoContact(nickname, 2);
	addInfoContact(phoneNumber, 3);
	addInfoContact(darkestSecret, 4);

	c.setFirstName(firstName);
	c.setLastName(lastName);
	c.setNickname(nickname);
	c.setPhoneNumber(phoneNumber);
	c.setDarkestSecret(darkestSecret);

	book->addContact(c);
}

int main()
{
	PhoneBook book;
	std::string command;

	while (true)
	{
		std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, command))
		{
			std::cout << std::endl;
			break ;
		}
		if (command == "ADD")
		{
			createContact(&book);
		}
		else if (command == "SEARCH")
		{
			searchCommand(book);
		}
		else if (command == "EXIT")
			break ;
	}

	return 0;
}
