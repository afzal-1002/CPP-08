#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <iterator>
#include <exception>

class Span
{
    private:
        std::vector<int>    numbers;
        unsigned int        maxSize;
        Span(void);                     // private: a Span always needs N

    public:
        Span(unsigned int n);
        Span(const Span& copy);
        Span& operator=(const Span& rhs);
        ~Span(void);

        void            addNumber(int number);
        unsigned int    shortestSpan(void) const;
        unsigned int    longestSpan(void) const;
        unsigned int    size(void) const;       // How many numbers are stored
        unsigned int    capacity(void) const;   // How many numbers can be stored in total
        int             operator[](unsigned int index) const; // Access a number by index, throws std::out_of_range if index is invalid

        // Add many numbers in one call, from any container's iterators.
        // It is a template, so it must be written in the header.
        template <typename InputIterator>
        void addRange(InputIterator first, InputIterator last)
        {
            unsigned long count = std::distance(first, last);

            if (numbers.size() + count > maxSize)
                throw SpanFullException();
            numbers.insert(numbers.end(), first, last);
        }

        class SpanFullException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class NotEnoughNumbersException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
};

#endif
