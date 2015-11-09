//
//  tarjan.h
//  tarjan
//
//  Created by James Peach on 08/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#ifndef tarjan_h
#define tarjan_h

#include <stdio.h>
#include "graph.h"
#include "readgraph.h"

/**************   MACROS   ***********/
#define MIN(a,b) (a<b?(a):(b))

/**
 * parse_inputs
 * 
 *  takes a pointer to an uninitialised graph g, and parses input from the
 *  stdin into the graph
 *  @returns nothing
 */
void parse_inputs(Graph* g);

/**
 * calculate_strongly_connected_components
 * 
 *  calculates the strongly connected components of the graph pointed to by g
 *  @returns noting
 */
node_index** calculate_strongly_connected_components(Graph* g);

/**
 * output_strongly_connected_components
 *
 *  outputs to stdout the strongly connected components
 *  @returns nothing
 */
void output_strongly_connected_components(Graph* g, node_index** components);

// a map from integers to nodes and vice versa
typedef int* node_int_map;

/**
 * a struct to store the current state of the algorythm
 */
struct tarjan_struct
{
  // map of node_index to lowlink number
  node_int_map lowlink;

  // map of node_index to dfsnumber
  node_int_map index;

  // stack of nodes
  node_int_map stack;

  node_index stackPointer;

  // map of node_index to ON/OFF
  node_int_map onStack;

  // list of connected components
  node_index** connectedComponents;
  
  // index of next connected component
  int connectedComponentsIndex;

  // the next current dfs number
  int dfsnumber;
};
typedef struct tarjan_struct Tarjan;

/**
 * once a root of a connected component has been discovered, this can then
 * retreive the connected component from the stack
 */
void retreive_connected_component(Graph* g, node_index v, Tarjan* context);

/**
 * the tarjan algorythm
 */
void strong_connect(Graph* g, node_index v, Tarjan* context);

#endif /* tarjan_h */
