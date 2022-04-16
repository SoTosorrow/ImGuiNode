#pragma once
#include<vector>
#include "imgui.h"
#include "utils.hpp"
#include "node_socket.hpp"

struct NodeSocket;
struct Node{
    int id;
    ImVec2 pos;
    ImVec2 size;
    Context* context;
    const char* name;
    ElementType element_type = ElementType::ElementNode;

    std::vector<NodeSocket*> input_sockets;
    std::vector<NodeSocket*> output_sockets;

    Node(Context* _context,ImVec2 _pos, const char* _name);
    void draw();

};
