//
//  tarjan.c
//  tarjan
//
//  Created by James Peach on 08/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#include "tarjan.h"

/**
 * UNDEFINED_NODE_INDEX special not visited flag against a node
 */
const int UNDEFINED_NODE_INDEX= -1;

/**
 * STACK_ON speciallag against a node
 */
const int STACK_ON = 1;

/**
 * STACK_OFF speciallag against a node
 */
const int STACK_OFF = 0;


void
parse_inputs(Graph* g)
{
  /*char c;
  while((c=getchar())!=EOF){

  }*/
  init_graph(g, 6);
  /*
              S   D
     0        0 | 1 2
    / .       1 | 2
   .   .      2 | 0 3
   1 -.2      3 | 4
       |      4 | 5
       .      5 | 3
       3
      / .
     .   \
    4 -. 5
   */

  // node 0
  g->nodes[0].out_links = (node_index*) malloc(sizeof(node_index)*2);
  g->nodes[0].out_links[0] = 1;
  g->nodes[0].out_links[1] = 2;
  g->nodes[0].number_of_out_links = 2;

  // node 1
  g->nodes[1].out_links = (node_index*) malloc(sizeof(node_index)*1);
  g->nodes[1].out_links[0] = 2;
  g->nodes[1].number_of_out_links = 1;

  // node 2
  g->nodes[2].out_links = (node_index*) malloc(sizeof(node_index)*2);
  g->nodes[2].out_links[0] = 0;
  g->nodes[2].out_links[1] = 3;
  g->nodes[2].number_of_out_links = 2;

  // node 3
  g->nodes[3].out_links = (node_index*) malloc(sizeof(node_index)*1);
  g->nodes[3].out_links[0] = 4;
  g->nodes[3].number_of_out_links = 1;

  // node 4
  g->nodes[4].out_links = (node_index*) malloc(sizeof(node_index)*1);
  g->nodes[4].out_links[0] = 5;
  g->nodes[4].number_of_out_links = 1;

  // node 5
  g->nodes[5].out_links = (node_index*) malloc(sizeof(node_index)*1);
  g->nodes[5].out_links[0] = 3;
  g->nodes[5].number_of_out_links = 1;
}

node_index**
calculate_strongly_connected_components(Graph* g)
{
  Tarjan context;
  context.lowlink = (node_int_map) malloc(sizeof(int) * g->number_of_nodes);
  context.index = (node_int_map) malloc(sizeof(int) * g->number_of_nodes);
  context.stack = (node_int_map) malloc(sizeof(int) * g->number_of_nodes);
  context.onStack = (node_int_map) malloc(sizeof(int) * g->number_of_nodes);
  context.stackPointer = 0;

  for(int i = 0;i<g->number_of_nodes;i++){
    context.index[i] = UNDEFINED_NODE_INDEX;
    context.onStack[i] = STACK_OFF;
  }
  context.dfsnumber = 0;

  // array for holding the lists of indexes for the connected components
  context.connectedComponents = (node_index**) malloc(sizeof(node_index*) * g->number_of_nodes);
  for(int i = 0; i < g->number_of_nodes; i++) context.connectedComponents[i] = NULL;
  context.connectedComponentsIndex = 0; // current index into the array

  for(int i = 0;i<g->number_of_nodes;i++){
    if(context.index[i] == UNDEFINED_NODE_INDEX){
      strong_connect(g, i, &context);
    }
  }

  free(context.lowlink);
  free(context.index);
  free(context.stack);
  free(context.onStack);

  return context.connectedComponents;
}

void
strong_connect(Graph* g, node_index v, Tarjan* context)
{
  context->index[v] = context->dfsnumber;
  context->lowlink[v] = context->dfsnumber;
  context->dfsnumber++;

  // push
  context->stack[context->stackPointer++] = v;
  context->onStack[v] = STACK_ON;

  // for each out edge w (edge from v to w)
  for(int i = 0;i<g->nodes[v].number_of_out_links;i++){
    node_index w = g->nodes[v].out_links[i];
    if(context->index[w]==UNDEFINED_NODE_INDEX){
      strong_connect(g, w, context);
      context->lowlink[v] = MIN(context->lowlink[v],context->lowlink[w]);
    }else if(context->onStack[w]==STACK_ON){
      context->lowlink[v] = MIN(context->lowlink[v],context->index[w]);
    }
  }
  if(context->lowlink[v] == context->index[v]){
    node_index* connectedComponent = (node_index*) malloc(sizeof(node_index)* g->number_of_nodes);
    for(int i = 0; i < g->number_of_nodes; i++) connectedComponent[i] = UNDEFINED_NODE_INDEX;
    int connectedComponentIndex = 0;
    node_index w;
    do{
      // pop
      w = context->stack[--context->stackPointer];
      context->onStack[w] = STACK_OFF;

      connectedComponent[connectedComponentIndex++] = w;
    }while(w!=v);

    context->connectedComponents[context->connectedComponentsIndex++]
      = connectedComponent;
  }
}

void
output_strongly_connected_components(Graph* g, node_index** components)
{
  printf("Output:\n");
  for(int i=0;i< g->number_of_nodes; i++){
    if(components[i]!=NULL){
      for(int j=0;j< g->number_of_nodes; j++){
        if(components[i][j]!=UNDEFINED_NODE_INDEX)
          printf("%d ",components[i][j]);
      }
      printf("\n");
    }
  }
}

