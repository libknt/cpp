#include <iostream>

int main(int argc, char** argv) {
	int i;
	char c;

	i = 1;
	if (argc == 1) {
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	while (i < argc) {
		int k = 0;
		while (argv[i][k]) {
			c = toupper(argv[i][k]);
			std::cout << c;
			k++;
		}
		i++;
	}
	std::cout << std::endl;
	return (0);
}
