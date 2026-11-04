#include <cctype>
#include <iostream>

int main(int ac, char **av)
{
	char **s = av; int j, i = 1;

	if (ac == 1)
	  std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	for (i = 1; s[i]; i++)
		for (j = 0; s[i][j]; j++)
			std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(s[i][j])));

	std::cout << std::endl;

	return 0;
}
