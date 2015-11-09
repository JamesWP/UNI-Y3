//
//  main.c
//  tarjan
//
//  Created by James Peach on 08/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//
#include <stdio.h>

#include "tarjan.h"
#include "graph.h"


int
main(int arvc, char** argv)
{
  Graph g;
  parse_inputs(&g);
  node_index** components = calculate_strongly_connected_components(&g);
  output_strongly_connected_components(&g, components);
  free_graph(&g);
  free(components);
  return 0;
}
