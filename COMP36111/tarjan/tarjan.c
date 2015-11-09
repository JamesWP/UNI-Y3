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

#define STDIN

void
parse_inputs(Graph* g)
{
#ifdef STDIN
  FILE* file = stdin;
#else
  FILE* file = fopen("testinput.txt","r");
#endif
  Input_token* tokens = read_all_input(file);
  from_tokens(g,tokens);
  if(file!=stdin) fclose(file);
  printf("Input:\n");
  print_graph(g);
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

// Shorthand definitions for common algo functions

// get vertex's index
#define I(v) (context->index[v])
// get low link
#define LL(v) (context->lowlink[v])
// the curent depth first number
#define DFS (context->dfsnumber)
// push vertex into stack
#define PUSH(v) ({context->stack[context->stackPointer++] = v; context->onStack[v] = STACK_ON;})
// pops a vertex off the stack into w
#define POP(w) ({w = context->stack[--context->stackPointer];context->onStack[w] = STACK_OFF;})
// is vertex on stack
#define ONSTACK(w) (context->onStack[w]==STACK_ON)
// get the i'th outlink of vertex v
#define OUTLINK(v,i) (g->nodes[v].out_links[i])
// the number of outlinks of v
#define OUTLINKS(v) (g->nodes[v].number_of_out_links)
// if the node has an assigned dfs number
#define HASDFS(w) (context->index[w]==UNDEFINED_NODE_INDEX)


void
retreive_connected_component(Graph* g, node_index v, Tarjan* context){
  node_index* connectedComponent = (node_index*) malloc(sizeof(node_index)* g->number_of_nodes);
  for(int i = 0; i < g->number_of_nodes; i++) connectedComponent[i] = UNDEFINED_NODE_INDEX;
  int connectedComponentIndex = 0;
  node_index w;
  do{
    POP(w);
    connectedComponent[connectedComponentIndex++] = w;
  }while(w!=v);

  context->connectedComponents[context->connectedComponentsIndex++]
    = connectedComponent;
}

void
strong_connect(Graph* g, node_index v, Tarjan* context)
{
  I(v) = DFS;
  LL(v)= DFS;
  DFS++;

  PUSH(v);

  // for each out edge w (edge from v to w)
  for(int i = 0;i<OUTLINKS(v);i++){
    node_index w = OUTLINK(v, i);
    if(HASDFS(w)){
      strong_connect(g, w, context);
      LL(v) = MIN(LL(v),LL(w));
    }else if(ONSTACK(w)){
      LL(v) = MIN(LL(v),I(w));
    }
  }

  if(LL(v) == I(v)) retreive_connected_component(g, v, context);
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

