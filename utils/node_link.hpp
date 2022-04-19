#pragma once

#include "utils.hpp"

struct NodeLink
{
    int id;
    int input_node_id;
    int output_node_id;
    int input_socket_id;
    int output_socket_id;

    NodeLink(Context* _context, int _input_node_id, int _input_socket_id, int _output_node_id, int _output_socket_id);
    void draw();
};
