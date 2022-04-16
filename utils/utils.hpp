#pragma once

#include "imgui.h"

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2 operator/(const ImVec2& lhs, const int& v) { return ImVec2(lhs.x/v, lhs.y/v); }

struct Context{
    int id=0;
    ImVec2 viewport_move =ImVec2(0.0f, 0.0f);
    ImVec2 viewport_scale;
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

template<typename T>
concept DrawAble = requires(T a){
    a.draw();
};

template<typename T>
concept HandleAble = true;