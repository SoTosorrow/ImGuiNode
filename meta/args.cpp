template<typename ... Ts>
void f(Ts ... args)
{
    if constexpr(sizeof... (args) > 0)
        f1(args..);
    else
        f1(default_arg);
}