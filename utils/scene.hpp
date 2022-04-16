#pragma once
#include<vector>
#include<unordered_map>

#include "imgui.h"

#include <iostream>
#include "utils.hpp"
#include "node.hpp"



struct Scene{
    Context* context;
    std::vector<Node*> nodes;

    Scene(){
        this->context = new Context();
        this->nodes.push_back(new Node{this->context,ImVec2(300,200),"hello"});
        this->nodes.push_back(new Node{this->context,ImVec2(300,300),"hello"});
        this->nodes.push_back(new Node{this->context,ImVec2(300,300),"hello"});
    }
    void Show(){
        ImGui::Begin("Hello");
        ImGuiIO& io = ImGui::GetIO();

        for(auto node:nodes){
            ImGui::PushID(node->id);
            node->draw();
            // 变化坐标系
            ImGui::SetCursorScreenPos(node->pos + this->context->viewport_move);
            // 建立一个虚拟按钮充当节点的Item
            ImGui::InvisibleButton("node", node->size);
            // 点击事件
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
            {
                std::cout<<"click Node\n";
            }
            // 拖拽事件
            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            {
                std::cout<<node->element_type<<" ";
                node->pos = node->pos + io.MouseDelta;
            }
            ImGui::PopID();
        }

        // 拖曳视图
        if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f)){
            this->context->viewport_move = this->context->viewport_move + io.MouseDelta;
        }

        ImGui::End();
    }
};
