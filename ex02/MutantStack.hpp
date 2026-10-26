#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

/*
 * std::stack is an "adapter": it stores its elements in a real container
 * (std::deque by default) kept in a PROTECTED member called `c`.
 * By inheriting from std::stack we can reach `c` and expose its iterators.
 * Everything else (push, pop, top, size, empty) is inherited unchanged.
 */
template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
    private:
        typedef std::stack<T, Container> BaseStack;

    public:
        MutantStack(void) : BaseStack() {}
        MutantStack(const MutantStack& copy) : BaseStack(copy) {}
        MutantStack& operator=(const MutantStack& rhs)
        {
            if (this != &rhs)
                BaseStack::operator=(rhs);
            return *this;
        }
        ~MutantStack(void) {}

        // Borrow the iterator types of the underlying container
        typedef typename Container::iterator                iterator;
        typedef typename Container::const_iterator          const_iterator;
        typedef typename Container::reverse_iterator        reverse_iterator;
        typedef typename Container::const_reverse_iterator  const_reverse_iterator;

        // `this->` is required: `c` lives in a base class that depends on T
        iterator                begin(void)         { return this->c.begin(); }
        iterator                end(void)           { return this->c.end(); }
        const_iterator          begin(void) const   { return this->c.begin(); }
        const_iterator          end(void) const     { return this->c.end(); }
        reverse_iterator        rbegin(void)        { return this->c.rbegin(); }
        reverse_iterator        rend(void)          { return this->c.rend(); }
        const_reverse_iterator  rbegin(void) const  { return this->c.rbegin(); }
        const_reverse_iterator  rend(void) const    { return this->c.rend(); }
};

#endif
