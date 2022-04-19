#include <unordered_map>
#include <map>
#include <string>
#include <iostream>
#include <math.h>
#include <random>
#include "imgui.h"


struct Vec2{
    float x;
    float y;

    bool operator < (const Vec2 &a)const
    {
        if (x == a.x)   return y < a.y;
        else return x < a.x;
    }

};

struct QuadNode{

    std::unordered_map<std::string, QuadNode*> nodes;
    // 如果值是普通类型，为了性能就不删除了，是自定义类型就定义指针，分裂的时候move
    std::map<Vec2,float> values; 

    Vec2 center;
    int depth;
    float width = 200;
    bool is_split = false;
    static int test_depth;

    QuadNode( int _depth=1, Vec2 _center = Vec2{300,300}):depth(_depth),center(_center){}

    void insert(Vec2 vec, float value){
        if(this->is_split){
            if (vec.x < this->center.x && vec.y < this->center.y)
                this->nodes.at("NorthWest")->insert(vec, value);
            if (vec.x > this->center.x && vec.y < this->center.y)
                this->nodes.at("NorthEast")->insert(vec, value);
            if (vec.x < this->center.x && vec.y > this->center.y)
                this->nodes.at("SouthWest")->insert(vec, value);
            if (vec.x > this->center.x && vec.y > this->center.y)
                this->nodes.at("SouthEast")->insert(vec, value);
            return;
        }
        this->values.insert({vec,value});

        if(this->values.size() >= 4) {
            this->is_split = true;
            int d = this->depth;
            float temp_x = this->width/(std::pow(2,d)) * 1.0f;
            float temp_y = this->width/(std::pow(2,d)) * 1.0f;
            // x向右增长 y向下增长
            // 西北 左上
            this->nodes.insert({"NorthWest",new QuadNode(this->depth+1, Vec2{this->center.x-temp_x, this->center.y-temp_y})});
            // 东北 右上
            this->nodes.insert({"NorthEast",new QuadNode(this->depth+1, Vec2{this->center.x+temp_x, this->center.y-temp_y})});
            // 西南 左下
            this->nodes.insert({"SouthWest",new QuadNode(this->depth+1, Vec2{this->center.x-temp_x, this->center.y+temp_y})});
            // 东南 右下
            this->nodes.insert({"SouthEast",new QuadNode(this->depth+1, Vec2{this->center.x+temp_x, this->center.y+temp_y})});
            QuadNode::test_depth = this->depth + 1;

            for(auto [vec2, v] : values){
                this->insert(vec2, value);
            }

        }
    }
    void print(){
        if(this->is_split){
            this->nodes.at("NorthWest")->print();
            this->nodes.at("NorthEast")->print();
            this->nodes.at("SouthWest")->print();
            this->nodes.at("SouthEast")->print();
            return;
        }
        if(this->values.size()>0)
            std::cout<<"\n"<<this->center.x << "-"<<this->center.y<<": "<<this->values.size()<<"> "<<this->depth<<"\n";

    }
    void Show(){
        ImGui::Begin("Quad");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        auto* draw_list = ImGui::GetWindowDrawList();
        ImU32 GRID_BORDER = IM_COL32(0, 255, 0, 255);
        draw_list->AddLine(ImVec2(this->center.x - this->width, this->center.y - this->width), ImVec2(this->center.x - this->width, this->center.y + this->width), GRID_BORDER);
        draw_list->AddLine(ImVec2(this->center.x - this->width, this->center.y - this->width), ImVec2(this->center.x + this->width, this->center.y - this->width), GRID_BORDER);
        draw_list->AddLine(ImVec2(this->center.x - this->width, this->center.y + this->width), ImVec2(this->center.x + this->width, this->center.y + this->width), GRID_BORDER);
        draw_list->AddLine(ImVec2(this->center.x + this->width, this->center.y - this->width), ImVec2(this->center.x + this->width, this->center.y + this->width), GRID_BORDER);

        this->draw();

        if (ImGui::IsMouseClicked(0)){
            if(ImGui::GetMousePos().x > this->center.x - this->width && 
                ImGui::GetMousePos().x < this->center.x + this->width &&
                ImGui::GetMousePos().y > this->center.y - this->width &&
                ImGui::GetMousePos().y < this->center.y + this->width)
                this->insert({ImGui::GetMousePos().x,ImGui::GetMousePos().y},5);
        }
        if(ImGui::IsMouseClicked(1)){
            for(int i=0;i<10000;i++){
                float temp = i*0.01f;
                float rx = rand() % 400;
                float ry = rand() % 400;
                this->insert({this->center.x - this->width+rx,this->center.x - this->width+ry},5);
            }
            std::cout<<QuadNode::test_depth<<"\n";
        }
        ImGui::End();
    }

    void TestShow(){
        ImGui::Begin("Test Draw");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        auto* draw_list = ImGui::GetWindowDrawList();
        ImU32 GRID_BORDER = IM_COL32(0, 255, 0, 255);
        draw_list->AddLine(ImVec2(this->center.x - this->width, this->center.y - this->width), ImVec2(this->center.x - this->width, this->center.y + this->width), GRID_BORDER);
        draw_list->AddLine(ImVec2(this->center.x - this->width, this->center.y - this->width), ImVec2(this->center.x + this->width, this->center.y - this->width), GRID_BORDER);
        draw_list->AddLine(ImVec2(this->center.x - this->width, this->center.y + this->width), ImVec2(this->center.x + this->width, this->center.y + this->width), GRID_BORDER);
        draw_list->AddLine(ImVec2(this->center.x + this->width, this->center.y - this->width), ImVec2(this->center.x + this->width, this->center.y + this->width), GRID_BORDER);

        for(int i=0;i<30000;i++){
            float tempx = i*0.01f + this->center.x - this->width;
            float tempy = i*0.01f + this->center.y - this->width;
            // draw_list->AddCircleFilled(ImVec2(tempx,tempy),3.0f,IM_COL32(255, 0, 0, 255));
            draw_list->AddRectFilled(ImVec2(tempx,tempy),ImVec2(tempx+0.1f,tempy+0.1f),IM_COL32(255, 0, 0, 255));
        }

        ImGui::End();
    }

    void draw(){

        auto* draw_list = ImGui::GetWindowDrawList();
        ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 255);
        float leng = this->width/(std::pow(2,this->depth-1)) * 1.0f;

        if(this->is_split){
            draw_list->AddLine(ImVec2(this->center.x, this->center.y - leng), ImVec2(this->center.x, this->center.y + leng), GRID_COLOR);
            draw_list->AddLine(ImVec2(this->center.x - leng, this->center.y), ImVec2(this->center.x + leng, this->center.y), GRID_COLOR);
            this->nodes.at("NorthWest")->draw();
            this->nodes.at("NorthEast")->draw();
            this->nodes.at("SouthWest")->draw();
            this->nodes.at("SouthEast")->draw();
            return;
        }
        // if(this->values.size()>0)
            // std::cout<<"\n"<<this->center.x << "-"<<this->center.y<<": "<<this->values.size()<<"> "<<this->depth<<"\n";
        for ( auto [vec2, v] : values){
            // draw_list->AddCircleFilled(ImVec2(vec2.x,vec2.y),3.0f,IM_COL32(255, 0, 0, 255));
            draw_list->AddRectFilled(ImVec2(vec2.x,vec2.y),ImVec2(vec2.x+2.0f,vec2.y+2.0f),IM_COL32(255, 0, 0, 255));
        }
    }
};

/*
    四叉树点 1w 60 fps, 2w 37fps, 3w 25fps
    单纯画点 1w 70 fps, 2w 50fps, 3w 40fps
    四叉方块 1w 140fps, 2w 70fps, 3w 63fps, 10w 27fps 20w 19fps

*/
