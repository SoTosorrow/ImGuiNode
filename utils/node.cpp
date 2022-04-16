#pragma once

#include "node.hpp"
#include <iostream>

Node::Node(Context* _context,ImVec2 _pos, const char* _name)
    :context(_context),pos(_pos),name(_name){

    this->id = _context->id++;
    this->size = ImVec2(150,60);

    this->input_sockets.push_back(new NodeSocket(this->context, this, NodeSocketType::Input, 0));
    this->input_sockets.push_back(new NodeSocket(this->context, this, NodeSocketType::Input, 1));
    this->input_sockets.push_back(new NodeSocket(this->context, this, NodeSocketType::Output, 0));
}

void Node::draw() {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(
        this->pos + this->context->viewport_move, 
        this->pos + this->size + this->context->viewport_move, 
        IM_COL32(150, 150, 150, 150), 4.0f);

    for(auto* socket : this->input_sockets){
        ImGui::PushID(socket->id);

        // ImGui::SetCursorScreenPos(socket->pos + this->context->viewport_move - ImVec2(5.0f,5.0f));
        // ImGui::InvisibleButton("socket", ImVec2(10.0f,10.0f));

        socket->draw();
        ImGui::PopID();
    }
    // for(auto* socket : this->output_sockets){
    //     socket->draw();
    // }
}
