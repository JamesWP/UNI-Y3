#include <stdio.h>

#include "tarjan.h"
#include "graph.h"

int
main(int arvc, char** argv)
{
  Graph g;
  parse_inputs(&g);
  calculate_strongly_connected_components(&g);
  output_strongly_connected_components(&g);
  free_graph(&g);
  return 0;
}