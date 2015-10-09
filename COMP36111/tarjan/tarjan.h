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
void calculate_strongly_connected_components(Graph* g);

/**
 * output_strongly_connected_components
 *
 *  outputs to stdout the strongly connected components in the graph g
 *  @returns nothing
 */
void output_strongly_connected_components(Graph* g);

typedef int* node_int_map;

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

  int dfsnumber;
};
typedef struct tarjan_struct Tarjan;

/**
 *
 */
void strong_connect(Graph* g, node_index v, Tarjan* context);

#endif /* tarjan_h */
