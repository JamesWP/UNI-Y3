//
//  graph.h
//  tarjan
//
//  Created by James Peach on 08/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <stdlib.h>


typedef int node_index;

struct node_struct
{
  node_index* out_links;
  int number_of_out_links;
};
typedef struct node_struct Node;

struct graph_struct
{
  Node* nodes;
  int number_of_nodes;
};
typedef struct graph_struct Graph;

void init_graph(Graph* g, int number_of_nodes);
void free_graph(Graph* g);
#endif /* graph_h */
