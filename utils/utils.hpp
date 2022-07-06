#pragma once

#include "imgui.h"
#include <string>
#include <type_traits>

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2 operator/(const ImVec2& lhs, const int& v) { return ImVec2(lhs.x/v, lhs.y/v); }

struct Context{
    int id=0;
    ImVec2 viewport_move =ImVec2(0.0f, 0.0f);
    ImVec2 viewport_scale;
    int last_node_id=-1;
    int last_socket_id=-1;
    int current_node_id=-1;
    int current_socket_id=-1;
    int link_state=0;   // 0无状态，1连线中

};

enum NodeSocketType{
    Input,
    Output,
};

enum ElementType{
    ElementNode,
    ElementNodeSocket,
    ElementNodeLink,
};

enum MouseType{
    MouseMoving,
    MouseDown,
    MouseUp,
    MouseDragingLink,
};

template<typename T>
concept DrawAble = requires(T a){
    a.draw();
};

template<typename T>
concept HandleAble = true;

template<typename T>
concept ShowAble = requires(T a){
    a.Show();
};

// 转换字符串
template<typename T>
std::string toString(T a) noexcept{
    if constexpr (std::is_same_v<T, std::string>)
        return a;
    else
        return std::to_string(a);
}



template<typename T>
constexpr T absolute(T arg) {
   return arg < 0 ? -arg : arg;
}

template<typename T>
constexpr auto precision_threshold = T(0.000001);

template<typename T>
constexpr bool float_close_enough(T a, T b) {
    if constexpr (std::is_floating_point_v<T>) // << !!
        return absolute(a - b) < precision_threshold<T>;
    else
        return a == b;
}