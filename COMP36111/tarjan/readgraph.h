//
//  readgraph.h
//  tarjan
//
//  Created by James Peach on 14/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#ifndef readgraph_h
#define readgraph_h

#include <stdio.h>

#include "graph.h"

enum input_type {
  node,connection,end
};
struct input_token{
  enum input_type type;
  node_index node;
};

/**
 * represents one input
 * either a new node
 * a connection from a node to another
 * or the end of the input
 */
typedef struct input_token Input_token;

/**
 *  reads input from
 */
Input_token* read_all_input(FILE* f);

/**
 * from_tokens
 *  produces a graph from a list of input tokens
 *
 */
void from_tokens(Graph* g, Input_token* tokens);

/**
 * print_graph
 * prints the given graph g to the stdout
 */
void print_graph(Graph* g);

#endif /* readgraph_h */
