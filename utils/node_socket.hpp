#pragma once
#include "imgui.h"
#include "utils.hpp"
#include "node.hpp"

struct Node;
struct NodeSocket{
    // 唯一标识的id
    int id;
    // 节点内的位置序号
    int posIndex;
    // 全局数据
    Context* context;
    // 所属节点
    Node* node;
    // item大小
    ImVec2 size;
    // item位置
    ImVec2 pos;
    // item类型 为 Socket
    ElementType element_type = ElementType::ElementNodeSocket;
    // socket类型，输入socket 或 输出socket
    NodeSocketType socket_type;

    NodeSocket(Context* _context,Node* _node, NodeSocketType _type, int _posIndex);
    void draw();
};