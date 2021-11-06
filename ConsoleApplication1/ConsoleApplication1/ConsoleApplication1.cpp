#include <functional>
#include <iostream>

void my_print() {}

template<typename... Types>
void my_print(const Types&... args)
{
    
}
template<typename T, typename... Types>
void my_print(const T& first_arg, const Types&... args)
{
    std::cout << first_arg <<" "<<sizeof...(args)<< std::endl;
    my_print(args...);
}

int main()
{
    my_print(1,2,3,"123", 1.1);
    return 0;
}