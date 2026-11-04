#include "Contact.hpp"
#include <iostream>

// DISPLAY

void Contact::display(void) const
{
	std::cout << "First name: "<< _firstName << std::endl;
	std::cout << "Last name: "<< _lastName << std::endl;
	std::cout << "Nickname: "<< _nickname << std::endl;
	std::cout << "Phone number: "<< _phoneNumber << std::endl;
	std::cout << "Darkest secret: "<<_darkestSecret << std::endl;
}

// SETTER
void Contact::setFirstName(std::string value)
{
	_firstName = value;
}

void Contact::setLastName(std::string value)
{
	_lastName = value;
}
void Contact::setNickname(std::string value)
{
	_nickname = value;
}
void Contact::setPhoneNumber(std::string value)
{
	_phoneNumber = value;
}
void Contact::setDarkestSecret(std::string value)
{
	_darkestSecret = value;
}

// GETTER
std::string Contact::getFirstName(void) const
{
	return _firstName;
}
std::string Contact::getLastName(void) const
{
	return _lastName;
}
std::string Contact::getNickname(void) const
{
	return _nickname;
}
std::string Contact::getPhoneNumber(void) const
{
	return _phoneNumber;
}
std::string Contact::getDarkestSecret(void) const
{
	return _darkestSecret;
}
