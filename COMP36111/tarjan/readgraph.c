//
//  readgraph.c
//  tarjan
//
//  Created by James Peach on 14/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#include "readgraph.h"

#define LINE_SIZE 30

Input_token* read_all_input(FILE* f){
  Input_token* tokens = (Input_token*) malloc(sizeof(Input_token)*100);
  int tokens_index = 0;
  Input_token* curent_token;
  char line_buffer[LINE_SIZE];
  while(fgets(line_buffer,LINE_SIZE,f)!=0){
    int node_number,line_buffer_offset=0,read_chars = 0;
    if(0==(sscanf(line_buffer+line_buffer_offset, "%d%n",&node_number,&read_chars))){
      continue;
    }
    line_buffer_offset+=read_chars;

    curent_token = &tokens[tokens_index++];
    curent_token->node = node_number;
    curent_token->type = node;

    while(sscanf(line_buffer+line_buffer_offset, "%d%n",&node_number,&read_chars)>0){
      line_buffer_offset+=read_chars;

      curent_token = &tokens[tokens_index++];
      curent_token->node = node_number;
      curent_token->type = connection;
    }
  }
  curent_token = &tokens[tokens_index];
  curent_token->node = 0;
  curent_token->type = end;

  int i=0;
  while(tokens[i].type!=end){
    printf("Token %10s %4d \n",tokens[i].type==connection? "connection":"node", tokens[i].node);
    i++;
  }

  return tokens;
}

int find_max_node(Input_token* tokens){
  if(tokens[0].type!=node) return 0;

  int max_node = tokens[0].node;
  int index = 1;
  while(tokens[index].type != end){
    if(tokens[index].type==node && tokens[index].node > max_node)
      max_node = tokens[index].node;
    index++;
  }
  return max_node;
}

void from_tokens(Graph* g, Input_token* tokens){

  node_index max_node_index = find_max_node(tokens);

  init_graph(g, max_node_index+1);

  int index = 0;
  Input_token* curentToken = &tokens[index++];
  node_index currentNode = 0;
  while(curentToken->type!=end){
    if(curentToken->type == node){
      currentNode = curentToken->node;
      g->nodes[currentNode].number_of_out_links = 0;
    }else if(curentToken->type == connection)
      g->nodes[currentNode].number_of_out_links++;

    curentToken = &tokens[index++];
  }
  for(int i=0;i < g->number_of_nodes;i++){
    g->nodes[i].out_links = (node_index*) malloc(sizeof(node_index)*g->nodes[i].number_of_out_links);
  }
  index = 0;
  curentToken = &tokens[index++];
  int curentTokenOutIndex = 0;
  while(curentToken->type!=end){
    if(curentToken->type == node){
      currentNode = curentToken->node;
      curentTokenOutIndex = 0;
    }else if(curentToken->type == connection)
      g->nodes[currentNode].out_links[curentTokenOutIndex++] = curentToken->node;
    curentToken = &tokens[index++];
  }

  return;
}

void print_graph(Graph* g){
  for(int i=0;i<g->number_of_nodes;i++){
    printf("%d ",i);
    for(int j=0;j<g->nodes[i].number_of_out_links;j++){
      printf("%d ",g->nodes[i].out_links[j]);
    }
    printf("\n");
  }
}

