#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: Form("ShrubberyCreationForm", 145, 137)
	, target_(target) {
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const& r)
	: Form(r)
	, target_(r.target_) {
	std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(ShrubberyCreationForm const& r) {
	std::cout << "ShrubberyCreationForm assignation operator called" << std::endl;
	if (this != &r) {
		this->target_ = r.target_;
	}
	return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
	if (executor.getGrade() > this->getExecutionGrade()) {
		throw Form::GradeTooLowException("Grade too low to execute form");
	}
	std::string file = this->target_ + "_shrubbery";
	std::ofstream outfile(file.c_str());
	if (!outfile) {
		std::cerr << "file open error" << std::endl;
		return;
	}
	int height = 10;
	int decorationFrequency = 3;
	int trunkWidth = 0;
	int baseWidth = 0;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height - i - 1; ++j) {
			outfile << " ";
		}

		for (int j = 0; j < 2 * i + 1; ++j) {
			if (i % decorationFrequency == 0 && j % 2 == 1 && i > 2) {
				outfile << "o";
			} else {
				outfile << "*";
			}
			if ((i == height - 1) && (j == 2 * i + 1 - 1)) {
				baseWidth = j + 1;
			}
		}
		outfile << std::endl;
	}
	trunkWidth = baseWidth / 3;

	for (int i = 0; i < height / 3; ++i) {
		for (int j = 0; j < ((baseWidth / 2) - (trunkWidth / 2)); ++j) {
			outfile << " ";
		}
		for (int j = 0; j < trunkWidth; ++j) {
			outfile << "|";
		}
		outfile << std::endl;
	}

	outfile.close();
}