#include "Span.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

static void title(const std::string& text)
{
    std::cout << std::endl << "===== " << text << " =====" << std::endl;
}

// 1. Exact example from the subject: must print 2 and 14
static void testSubject()
{
    title("Subject example");
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
}

// 2. Adding when full must throw
static void testFull()
{
    title("Adding to a full Span");
    Span sp(2);
    try
    {
        sp.addNumber(1);
        sp.addNumber(2);
        std::cout << "Added 2 numbers to Span(2)" << std::endl;
        sp.addNumber(3);
        std::cout << "ERROR: this line should not print" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

// 3. Zero or one number: no span possible
static void testNotEnough()
{
    title("Not enough numbers");
    Span empty(5);
    try
    {
        std::cout << empty.shortestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Empty -> Exception: " << e.what() << std::endl;
    }

    Span one(5);
    one.addNumber(42);
    try
    {
        std::cout << one.longestSpan() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "One number -> Exception: " << e.what() << std::endl;
    }
}

// 4. Duplicates, negatives and extreme values
static void testEdgeCases()
{
    title("Edge cases");
    Span dup(3);
    dup.addNumber(7);
    dup.addNumber(7);
    dup.addNumber(20);
    std::cout << "Duplicates 7 7 20 -> shortest: " << dup.shortestSpan()
              << ", longest: " << dup.longestSpan() << std::endl;

    Span neg(4);
    neg.addNumber(-10);
    neg.addNumber(-3);
    neg.addNumber(5);
    neg.addNumber(100);
    std::cout << "Negatives -10 -3 5 100 -> shortest: " << neg.shortestSpan()
              << ", longest: " << neg.longestSpan() << std::endl;

    Span ext(2);
    ext.addNumber(INT_MIN);
    ext.addNumber(INT_MAX);
    std::cout << "INT_MIN and INT_MAX -> longest: " << ext.longestSpan()
              << " (expected 4294967295)" << std::endl;
}

// 5. addRange from different containers
static void testAddRange()
{
    title("addRange");
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(50);
    vec.push_back(25);

    std::list<int> lst;
    lst.push_back(100);
    lst.push_back(48);

    int array[] = {200, 300};

    Span sp(7);
    sp.addRange(vec.begin(), vec.end());   // from a vector
    sp.addRange(lst.begin(), lst.end());   // from a list
    sp.addRange(array, array + 2);         // from a plain array
    std::cout << "Stored " << sp.size() << "/" << sp.capacity() << " numbers" << std::endl;
    std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest: " << sp.longestSpan() << std::endl;

    try
    {
        sp.addRange(vec.begin(), vec.end());   // 7 + 3 > 7
        std::cout << "ERROR: this line should not print" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Range too big -> Exception: " << e.what() << std::endl;
    }
}

// 6. Copy and assignment make independent copies
static void testCopy()
{
    title("Copy constructor and assignment");
    Span original(5);
    original.addNumber(1);
    original.addNumber(10);

    Span copy(original);
    copy.addNumber(11);

    Span assigned(1);
    assigned = original;

    std::cout << "original size: " << original.size()
              << ", copy size: " << copy.size()
              << ", assigned size: " << assigned.size() << std::endl;
    std::cout << "copy shortest: " << copy.shortestSpan()
              << ", original shortest: " << original.shortestSpan() << std::endl;
}

// 7. Big tests: 10,000 and 100,000 random numbers
static void testBig(unsigned int count)
{
    std::cout << std::endl << "===== " << count << " random numbers =====" << std::endl;
    std::vector<int> random;
    for (unsigned int i = 0; i < count; i++)
        random.push_back(std::rand());

    Span sp(count);
    sp.addRange(random.begin(), random.end());   // one call, no loop of addNumber
    std::cout << "Stored: " << sp.size() << std::endl;
    std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest: " << sp.longestSpan() << std::endl;
}

int main()
{
    std::srand(std::time(NULL));

    testSubject();
    testFull();
    testNotEnough();
    testEdgeCases();
    testAddRange();
    testCopy();
    testBig(10000);
    testBig(100000);
    return 0;
}
