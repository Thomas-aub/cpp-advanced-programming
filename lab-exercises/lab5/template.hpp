#include <iostream>
#include <cstring> 

template <typename T>
void mySwap (T & a, T & b) 
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}


template <typename T>
T myMin (const T & a, const T & b) 
{
    return ( a > b) ? b : a;
}

template <>
const char* myMin (const char* const& a, const char* const& b)
{
    return (strcmp(a,b)) ? b : a;
}

template <int I>
const char* myMin (const char(&a)[I], const char(&b)[I])
{
    return (strcmp(a,b)) ? b : a;
}

template <int I, int J>
const char* myMin (const char(&a)[I], const char(&b)[J]){
    return (strcmp(a,b)) ? b : a;
}
