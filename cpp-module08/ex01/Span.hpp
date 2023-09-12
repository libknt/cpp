#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <list>
#include <exception>
#include <algorithm>
#include <climits>

class Span
{
private:
    std::vector<int> v_;

public:
    Span(unsigned int n);
    ~Span();
    void checkMaxSize(unsigned int len);
    void addNumber(int number);
    unsigned int shortestSpan();
    unsigned int longestSpan();
    void printContainer();

    template <typename T>
    void containerInsert(T v2) {
        checkMaxSize(v2.size());
        v_.insert(v_.end(), v2.begin(), v2.end());
    }
    
};

class SizeOverFlowException : public std::exception {
    public:
        virtual const char* what() const throw() { return "already Max elements stored"; }
};

class SpanException : public std::exception {
    public:
        virtual const char* what() const throw() { return "There are no numbers stored, or only one."; }
};

#endif