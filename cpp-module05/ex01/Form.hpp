#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>
#include <sstream>
#include <string>

class Bureaucrat;

class Form {
private:
	const std::string name_;
	bool isSigned_;
	const int sigingGrade_;
	const int executionGrade_;

public:
	Form(const std::string& name, int sigingGrade);
	Form(const std::string& name, int sigingGrade, int executionGrade);
	Form(const Form& r);
	~Form();
	Form& operator=(const Form& f);
	const std::string getName() const;
	bool getIsSigned() const;
	int getSigingGrade() const;
	int getExecutionGrade() const;
	void beSigned(const Bureaucrat& b);

	class GradeTooHighException : public std::exception {
		const char* message_;

	public:
		explicit GradeTooHighException(const char* message)
			: message_(message) {}
		virtual const char* what() const throw() { return message_; }
	};

	class GradeTooLowException : public std::exception {
		const char* message_;

	public:
		explicit GradeTooLowException(const char* message)
			: message_(message) {}
		virtual const char* what() const throw() { return message_; }
	};
};

std::ostream& operator<<(std::ostream& os, const Form& obj);

#endif
