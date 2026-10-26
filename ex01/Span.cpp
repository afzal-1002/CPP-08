#include "Span.hpp"

/* ---------- Orthodox Canonical Form ---------- */

Span::Span(void) : numbers(), maxSize(0)
{
}

Span::Span(unsigned int n) : numbers(), maxSize(n)
{
}

Span::Span(const Span& copy) : numbers(copy.numbers), maxSize(copy.maxSize)
{
}

Span& Span::operator=(const Span& rhs)
{
    if (this != &rhs)
    {
        numbers = rhs.numbers;
        maxSize = rhs.maxSize;
    }
    return *this;
}

Span::~Span(void)
{
}



void Span::addNumber(int number)
{
    if (numbers.size() >= maxSize)
        throw SpanFullException();
    numbers.push_back(number);
}

// Biggest distance = largest number - smallest number. O(n)
unsigned int Span::longestSpan(void) const
{
    if (numbers.size() < 2)
        throw NotEnoughNumbersException();

    int min = *std::min_element(numbers.begin(), numbers.end());
    int max = *std::max_element(numbers.begin(), numbers.end());

    // Convert BEFORE subtracting, so INT_MAX - INT_MIN does not overflow.
    return static_cast<unsigned int>(max) - static_cast<unsigned int>(min);
}

// Smallest distance: sort a copy, then the closest pair is always
// two neighbours. O(n log n) instead of comparing every pair O(n^2).
unsigned int Span::shortestSpan(void) const
{
    if (numbers.size() < 2)
        throw NotEnoughNumbersException();

    std::vector<int> sorted(numbers);
    std::sort(sorted.begin(), sorted.end());

    unsigned int shortest = static_cast<unsigned int>(sorted[1]) - static_cast<unsigned int>(sorted[0]);
    for (std::vector<int>::size_type i = 2; i < sorted.size(); i++)
    {
        unsigned int gap = static_cast<unsigned int>(sorted[i]) - static_cast<unsigned int>(sorted[i - 1]);
        if (gap < shortest)
            shortest = gap;
    }
    return shortest;
}

unsigned int Span::size(void) const
{
    return numbers.size();
}

unsigned int Span::capacity(void) const
{
    return maxSize;
}

int Span::operator[](unsigned int index) const
{
    return numbers.at(index);
}

const char* Span::SpanFullException::what() const throw()
{
    return "Span is full: cannot add more numbers";
}

const char* Span::NotEnoughNumbersException::what() const throw()
{
    return "Not enough numbers: need at least 2 to find a span";
}
