#include "search.hpp"
#include "PhoneBook.hpp"
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <cstdlib>

static const int COLUMN_WIDTH = 10;


static std::string truncate(std::string const &s)
{
	if (s.length() > 10)
		return s.substr(0, 9) + ".";
	else
		return s;
}

static void printCell(std::string const &text)
{
	std::cout << std::setw(COLUMN_WIDTH) << std::right << text;
}

static void printCell(int value)
{
	std::cout << std::setw(COLUMN_WIDTH) << std::right << value;
}

static void createUI(PhoneBook const &book, int total)
{

	printCell("index");
	std::cout << "|";
	printCell("first name");
	std::cout << "|";
	printCell("last name");
	std::cout << "|";
	printCell("nickname");
	std::cout << std::endl;

	for (int i = 0; i < total; i++)
	{
		Contact const &c = book.getContact(i);
		printCell(i);
		std::cout << "|";
		printCell(truncate(c.getFirstName()));
		std::cout << "|";
		printCell(truncate(c.getLastName()));
		std::cout << "|";
		printCell(truncate(c.getNickname()));
		std::cout << std::endl;

	}
}

void	searchContact(const PhoneBook &book, int total)
{
	std::string input;
	std::cout << "Enter index: ";
	std::getline(std::cin, input);
	int index = std::atoi(input.c_str());
	if (index < 0 || index >= total)
		std::cout << "Invalid index." << std::endl;
	else
		book.getContact(index).display();
}

void searchCommand(const PhoneBook &book)
{
	int	total = book.getCount();
	if (total > 8)
		total = 8;
	createUI(book, total);
	searchContact(book, total);
}
