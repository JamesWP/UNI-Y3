//
//  graph.c
//  tarjan
//
//  Created by James Peach on 08/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#include "graph.h"

void
init_graph(Graph* g, int number_of_nodes)
{
  g->nodes = (Node*) malloc(sizeof(Node) * number_of_nodes);
  if(g->nodes==NULL){
    exit(1);
  }
  g->number_of_nodes = number_of_nodes;
}

void
free_graph(Graph* g)
{
  free(g->nodes);
}


