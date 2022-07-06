#include<iostream>
#include<unordered_map>
#include<type_traits>
#include<vector>

// 用c++实现编译期的反射

template<typename T>
concept TestAble = requires(T a){
    a.test();
};

// 利用模板特化判断传入类型是否含有test函数
template<typename T>
void test_Concept2(T a){
    std::cout<<"no test\n";
}
template<TestAble T>
void test_Concept2(T a){
    a.test();
}

// 利用concetp判断传入类型是否有test函数
template<typename T>
void test_Concept(T a){
    if constexpr (TestAble<T>){
        a.test();
    }else{
        std::cout<<"no test\n";
    }
}

// 利用c11/c14 SFINAE的判断传入类型是否有test函数
template<typename T, typename = void>
struct has_test : std::false_type{};

template<typename T>
struct has_test<T,std::void_t<decltype(std::declval<T>().test())>> : std::true_type{};

template<typename T, typename std::enable_if<has_test<T>::value, int>::type = 0>
void test_SFINAE(T a){
    a.test();
}
template<typename T, typename std::enable_if<!has_test<T>::value, int>::type = 0>
void test_SFINAE(T a){
    std::cout<<"no test\n";
}


// 包含test函数的结构体
struct TestStruct{
    void test(){
        std::cout<<"hello\n";
    }
};

int main(){

    TestStruct a;
    int d;

    test_Concept(a);
    test_Concept(d);
    std::cout<<"\n";

    test_Concept2(a);
    test_Concept2(d);
    std::cout<<"\n";

    test_SFINAE(a);
    test_SFINAE(d);
    // constexpr auto b1 = has_test<TestStruct>::value; // true
    // constexpr auto b2 = has_test<int>::value; // false
    // std::cout<<"\n"<<b1<<" "<<b2;
    std::cout<<std::is_same<int,int>::value;
    std::cout<<std::is_same_v<int,int>;

    return 0;
}

/*
struct Context{
    int id=0;
};

    // std::unordered_map<int ,int> a{};
    // Context* c = new Context{};
    // a.insert({c->id,++c->id});
    // a.insert({c->id,++c->id});
    // for(auto [s,d] : a){
    //     std::cout<<s<<d;
    // }


template <typename T, typename V = void>
struct has_push_back:std::false_type {};

template <typename T>
struct has_push_back<T, 
    void_t<decltype(
        std::declval<T>().push_back(
            std::declval<typename T::value_type>()))>>:std::true_type {};

 */