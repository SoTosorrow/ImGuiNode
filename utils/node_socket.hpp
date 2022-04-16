#pragma once
#include "imgui.h"
#include "utils.hpp"
#include "node.hpp"

struct Node;
struct NodeSocket{
    int id;
    int posIndex;
    Context* context;
    Node* node;
    ImVec2 size;
    ImVec2 pos;
    
    ElementType element_type = ElementType::ElementNodeSocket;
    NodeSocketType socket_type;

    NodeSocket(Context* _context,Node* _node, NodeSocketType _type, int _posIndex);
    void draw();
};