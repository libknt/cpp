#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
# include <exception>

class Bureaucrat
{

    private:
        const std::string name_;
        int grade_;

    public:
        Bureaucrat(std::string name, int grade);
 		Bureaucrat(const Bureaucrat & r);
        ~Bureaucrat();
		Bureaucrat & operator=(const Bureaucrat & b);
        const std::string getName() const;
        int getGrade() const;
        void upgrade(int n);
        void downgrade(int n);
        
        class GradeTooHighException : public std::exception
        {
            const char *message_;

            public:
                explicit GradeTooHighException( const char *message ): message_(message) {}
                const char* whatMessage() const { return message_; }
        };

        class GradeTooLowException : public std::exception
        {
            const char *message_;

            public:
                explicit GradeTooLowException( const char *message ): message_(message) {}
                const char* whatMessage() const { return message_; }
        };
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj);

#endif