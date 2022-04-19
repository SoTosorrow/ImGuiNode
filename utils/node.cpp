#pragma once

#include "node.hpp"
#include <iostream>

Node::Node(Context* _context,ImVec2 _pos, const char* _name)
    :context(_context),pos(_pos),name(_name){

    this->id = _context->id++;
    this->size = ImVec2(150,60);

    this->input_sockets.insert({std::to_string(this->context->id), new NodeSocket(this->context, this, NodeSocketType::Input, 0)});
    this->input_sockets.insert({std::to_string(this->context->id), new NodeSocket(this->context, this, NodeSocketType::Input, 1)});
    // this->output_sockets.insert({this->context->id, new NodeSocket(this->context, this, NodeSocketType::Output, 0)});
}

void Node::draw() {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(
        this->pos + this->context->viewport_move, 
        this->pos + this->size + this->context->viewport_move, 
        IM_COL32(150, 150, 150, 150), 4.0f);

    // for(auto* socket : this->output_sockets){
    //     socket->draw();
    // }
}
