#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <string>


class Contact
{
	private:
		std::string _firstName;
		std::string _lastName;
		std::string _nickname;
		std::string _phoneNumber;
		std::string _darkestSecret;
	public:
		void display(void) const;

	// setter
		void setFirstName(std::string value);
		void setLastName(std::string value);
		void setNickname(std::string value);
		void setPhoneNumber(std::string value);
		void setDarkestSecret(std::string value);

	// getter
		std::string getFirstName(void) const;
		std::string getLastName(void) const;
		std::string getNickname(void) const;
		std::string getPhoneNumber(void) const;
		std::string getDarkestSecret(void) const;
};
#endif
