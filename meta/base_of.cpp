#include<type_traits>
#include<iostream>

class B {};
class D: public B {};

template <typename T, typename U, bool Enabled = std::is_base_of<T, U>::value> 
class Add;  // 模板的泛化形式（原型）

template <typename T, typename U>
struct Add<T, U, true>
{
   // Blah blah blah
};

template <typename T, typename U>
struct Add<T, U, false>
{
   // Blah blah blah
};

int main(){

    Add<B, D> a;       // 用上面那个特化
    Add<int, float> b; // 用下面那个特化
    return 0;
}

