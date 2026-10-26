#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <algorithm>
#include <exception>

class ItemNotFound : public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "Exception: Item not found";
        }
};

template <typename T>
typename T::iterator easyfind(T& container, int target)
{

    for(typename T::iterator current = container.begin(); current != container.end(); current++)
    {
        if(*current == target)
            return current;    
    }
    throw ItemNotFound();
}


#endif
