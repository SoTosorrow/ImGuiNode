#pragma once

#include "node_link.hpp"

NodeLink::NodeLink(Context* _context, int _input_node_id, int _input_socket_id, int _output_node_id, int _output_socket_id){
    this->id = _context->id++;
    this->input_node_id = _input_node_id;
    this->input_socket_id = _input_socket_id;
    this->output_node_id = _output_node_id;
    this->output_socket_id = _output_socket_id;
}

void NodeLink::draw(){

}