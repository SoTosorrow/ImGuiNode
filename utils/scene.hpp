#pragma once
#include<vector>
#include<unordered_map>
#include<string>
#include <iostream>
#include <math.h> // fmodf

#include "imgui.h"
#include "utils.hpp"
#include "node.hpp"
#include "node_link.hpp"



struct Scene{
    Context* context;
    std::unordered_map<std::string, Node*> nodes;
    std::unordered_map<std::string, NodeLink*> node_links;
    bool open_menu = false;

    Scene(){
        this->context = new Context();
        this->nodes.insert({std::to_string(this->context->id), new Node{this->context,ImVec2(300,200),"hello"}});
        this->nodes.insert({std::to_string(this->context->id), new Node{this->context,ImVec2(300,200),"hello"}});
        this->nodes.insert({std::to_string(this->context->id), new Node{this->context,ImVec2(300,200),"hello"}});
        for (auto [a,a2] : this->nodes){
            std::cout<<a<<" "<<a2->id<<"\n";
            for (auto [b,b2] : a2->input_sockets){
                std::cout<<b<<" "<<b2->id<<"\n";
            }
        }
        // std::cout<<std::endl;
        // std::cout<<this->nodes[3]->id;
        // for(int i=0;i<1000;i++){
        //     this->nodes.push_back(new Node{this->context,ImVec2(i,i),"hello"});
        // }
    }
    void AddNodeLink(){

        this->node_links.insert({
            std::to_string(this->context->id), 
            new NodeLink{this->context,
                this->context->last_node_id,
                this->context->last_socket_id,
                this->context->current_node_id,
                this->context->current_socket_id}});
        
    }
    void Show(){
        ImGui::Begin("Hello");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGuiIO& io = ImGui::GetIO();
        auto* draw_list = ImGui::GetWindowDrawList();


        ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
        float GRID_SZ = 64.0f;
        ImVec2 win_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_sz = ImGui::GetWindowSize();
        for (float x = fmodf(this->context->viewport_move.x, GRID_SZ); x < canvas_sz.x; x += GRID_SZ)
            draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_sz.y) + win_pos, GRID_COLOR);
        for (float y = fmodf(this->context->viewport_move.y, GRID_SZ); y < canvas_sz.y; y += GRID_SZ)
            draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_sz.x, y) + win_pos, GRID_COLOR);


        for(auto [node_id,node]:nodes){
            ImGui::PushID(node->id);
                        node->draw();

            for(auto [socket_id, socket] : node->input_sockets){
                ImGui::PushID(socket->id);

                socket->draw();

                ImGui::SetCursorScreenPos(socket->pos - ImVec2(5.0f,5.0f));
                ImGui::InvisibleButton("socket", ImVec2(10.0f,10.0f));
                if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
                {
                    // draw_list->AddCircleFilled(ImGui::GetMousePos(),10.0f,IM_COL32(0,0,255,255));
                    std::cout<<socket->id<<" ";
                    if(this->context->link_state == 0){
                        this->context->last_node_id = node->id;
                        this->context->last_socket_id = socket->id;
                        this->context->link_state = 1;
                    }else{
                        this->context->current_node_id = node->id;
                        this->context->current_socket_id = socket->id;
                        this->context->link_state = 0;
                        // do
                        this->AddNodeLink();
                    }
                }
                if (ImGui::IsItemHovered())
                {
                    draw_list->AddRectFilled(socket->pos - ImVec2(5.0f,5.0f), socket->pos + ImVec2(10.0f,10.0f), IM_COL32(0,255,0,255));
                    // std::cout<<this->id;
                }
                ImGui::PopID();
            }
            


            // 变化坐标系
            ImGui::SetCursorScreenPos(node->pos + this->context->viewport_move);
            // 建立一个虚拟按钮充当节点的Item
            ImGui::InvisibleButton("node", node->size);
            // 点击事件
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
            {
                std::cout<<node->id<<" ";
            }
            // 拖拽事件
            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            {
                // std::cout<<node->element_type<<" ";
                node->pos = node->pos + io.MouseDelta;
            }

            ImGui::PopID();
        }

        for(auto [node_link_id,node_link]:node_links){
            ImGui::PushID(node_link->id);

            auto last_pos = this->nodes[std::to_string(node_link->input_node_id)]->input_sockets[std::to_string(node_link->input_socket_id)]->pos;
            auto current_pos = this->nodes[std::to_string(node_link->output_node_id)]->input_sockets[std::to_string(node_link->output_socket_id)]->pos;
            auto* draw_list = ImGui::GetWindowDrawList();
            draw_list->AddBezierCurve(
                last_pos, 
                last_pos + ImVec2(+50, 0), 
                current_pos + ImVec2(-50, 0), 
                current_pos, 
                IM_COL32(200, 200, 100, 255), 3.0f);
            ImGui::PopID();
        }

        // Scene Events
        if (ImGui::IsMouseClicked(1)){
            this->nodes.insert({std::to_string(this->context->id), new Node{this->context,ImVec2(ImGui::GetMousePos().x,ImGui::GetMousePos().y),"hello"}});
            this->open_menu = !this->open_menu;
            std::cout<<ImGui::GetMousePos().x<<" "<<ImGui::GetMousePos().y<<"\n";
        }
        if(this->open_menu){
            ImGui::OpenPopup("context_menu");
        }
        // 拖曳视图
        if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f)){
            this->context->viewport_move = this->context->viewport_move + io.MouseDelta;
        }

        ImGui::End();
    }
};
