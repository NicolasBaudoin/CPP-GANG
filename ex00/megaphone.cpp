#include <iostream>

int main(int ac, char **av)
{
	char **s = av; int j, i = 1;

	if (ac == 1)
	  std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	for (i = 1; s[i]; i++)
		for (j = 0; s[i][j]; j++)
			s[i][j] >= 'a' && s[i][j] <= 'z' ? std::cout << (s[i][j] -= 32) : std::cout << s[i][j];
	std::cout << std::endl;

	return 0;
}
