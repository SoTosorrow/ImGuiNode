#pragma once

#include "node_socket.hpp"
#include <iostream>

NodeSocket::NodeSocket(Context* _context,Node* _node, NodeSocketType _socket_type, int _posIndex){
    this->id = _context->id++;
    this->context = _context;
    this->socket_type = _socket_type;
    this->posIndex = _posIndex;
    this->node = _node;
}

void NodeSocket::draw() {
    auto* draw_list = ImGui::GetWindowDrawList();
    // 加上viewport的全局位置
    this->pos = this->node->pos + 
        ImVec2(((this->socket_type==NodeSocketType::Input)? 0.0f : node->size.x), 
        posIndex * 15.0f + 10.0f) + this->context->viewport_move;
    draw_list->AddCircleFilled(
        this->pos, 
        5, 
        IM_COL32(255, 0, 0, 255)
    );


    // 拖拽事件
    /*
    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        // std::cout<<"Drag NodeSocket";
        
        draw_list->AddBezierCurve(
            this->pos, 
            this->pos + ImVec2(+50, 0), 
            ImGui::GetMousePos() + ImVec2(-50, 0), 
            ImGui::GetMousePos(), 
            IM_COL32(200, 200, 100, 255), 3.0f);
    }
    */
    // if(ImGui::IsMouseReleased(ImGuiMouseButton_Left)){
    //     std::cout<<"release";
    // }

}