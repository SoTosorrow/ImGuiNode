#pragma once

#include "utils/handle.cpp"
#include "utils/scene.hpp"
#include "utils/quad_tree.cpp"
int QuadNode::test_depth = 0;
int main(int, char**) {
    Scene* app = new Scene();
    // auto root = new QuadNode(1, {500,500});
    handle(app);


    return 0;
}