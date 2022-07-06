#include <mutex>
#include <iostream>
#include <omp.h>
#include <future>
#include <vector>
#include <unordered_map>
#include <memory>

// #include <xmmintrin.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include"manager.hpp"


#define target 0
#if target
#include"test.cpp"

#else
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2 operator/(const ImVec2& lhs, const int& v) { return ImVec2(lhs.x/v, lhs.y/v); }

struct Context{
    // std::unique_ptr<ImDrawList> draw_list;
    ImDrawList* draw_list;

    Context(){
        draw_list = ImGui::GetWindowDrawList();
    }
};
struct Node{
    int id;
    ImVec2 pos;
    ImVec2 size;
    const char* name;

    Node(int _id, ImVec2 _pos, const char* _name)
        :id(_id),pos(_pos),name(_name){
        this->size = ImVec2(150,60);
    }

    void draw(ImVec2 scrolling) {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        // draw_list->AddCircleFilled()
        draw_list->AddRectFilled(this->pos+scrolling, this->pos+this->size+scrolling, IM_COL32(150, 150, 150, 150), 4.0f);


    }
};
struct NodeLink{
    int id;
    int start_id;
    int end_id;
    ImVec2 start_pos;
    ImVec2 end_pos;
    // Context*
    // Scene*

    // NodeLink(int _id, ImVec2 _start_pos, ImVec2 _end_pos)
    //     :id(_id),start_pos(_start_pos),end_pos(_end_pos){
        
    // }
    
    NodeLink(int _id, int _start_id, int _end_id)
        :id(_id),start_id(_start_id),end_id(_end_id){
        
    }

    void draw(){
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddBezierCurve(
            start_pos, 
            start_pos + ImVec2(+50, 0), 
            end_pos + ImVec2(-50, 0), 
            end_pos, 
            IM_COL32(200, 200, 100, 255), 3.0f);
    
    }
};
struct Scene
{
    // std::vector<std::shared_ptr<Node>> nodes;
    // std::vector<std::shared_ptr<NodeLink>> nodes;
    std::vector<Node*> nodes;
    
    std::vector<NodeLink*> links;
    // 移动屏幕
    ImVec2 scrolling = ImVec2(0.0f, 0.0f);
    // todo 缩放屏幕
    // ImVec2 scale
    ImU32 Col_Gray = IM_COL32(150, 150, 150, 150);
    ImU32 Col_Red = IM_COL32(255, 0, 0, 255);

    Scene() {
        // todo resize the vector
        // this->nodes.push_back(new Node{1,ImVec2(300,200),"hello"});
        this->nodes.emplace_back({1,ImVec2(300,300),"hello"};)
        this->nodes.push_back(new Node{2,ImVec2(300,300),"hello"});
        this->nodes.push_back(new Node{3,ImVec2(300,300),"hello"});
        // this->links.push_back(new NodeLink{10,nodes[0]->pos,nodes[1]->pos});
        this->links.push_back(new NodeLink{10,0,1});
        this->links.push_back(new NodeLink{10,0,2});
    }
    void render() {
        ImGui::Begin("Test");

        // ImGui::BeginChild("node_list", ImVec2(100, 0));
        // ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", scrolling.x, scrolling.y);
        // ImGui::EndChild();

        ImGui::BeginChild("Content", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
    

        ImGuiIO& io = ImGui::GetIO();

        for(auto node:nodes){
            ImGui::PushID(node->id);
            // 建立一个虚拟按钮充当节点的Item
            ImGui::SetCursorScreenPos(node->pos+scrolling);
            
            ImGui::InvisibleButton("node", node->size);
            

            // to learn(ImGuiContext)
            // ImRect bb{node->pos, node->pos+node->size};
            // ImGui::ItemAdd(bb, node->id);

            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
            {
            }
            bool isNodeActive = ImGui::IsItemActive();
            if (isNodeActive && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            {
                std::cout<<node->id;
                node->pos = node->pos + io.MouseDelta;
            }
            node->draw(this->scrolling);
            ImGui::PopID();
        }

        for(auto link:links){
            link->start_pos = nodes[link->start_id]->pos + nodes[link->start_id]->size/2;
            link->end_pos   = nodes[link->end_id]->pos   + nodes[link->end_id]->size/2;
            link->draw();
        }
        // NodeLink* link = new NodeLink(10,nodes[0]->pos,nodes[1]->pos);

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 cursorPos = ImGui::GetCursorScreenPos();
        ImVec2 mousePos = ImGui::GetMousePos();
        // draw_list->AddCircleFilled(cursorPos,3.0f,Col_Red);
        draw_list->AddCircleFilled(mousePos,3.0f,Col_Gray);

        if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f)){
            scrolling = scrolling + io.MouseDelta;
        }
        
        ImGui::EndChild();
        ImGui::End();
    }
};


static void Test(){
    static auto* scene = new Scene();
    // ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiWindowFlags_MenuBar);
    scene->render();
}
#endif

struct Tree{
    Tree(){}
    void show() {
        bool test = true;
        #if target
            ShowExampleAppCustomNodeGraph(&test);
        #else
            Test();
        #endif

    }
};

int main(int, char**) {
    auto t = std::make_unique<Tree>();

    glfwManager manager(std::move(t));
    {
        std::lock_guard guard(manager);
        manager.loop();
    }


    return 0;
}

