//
//  function.h
//  asg2
//
//  Created by Brandon Vincent on 13/09/20.
//  Copyright © 2020 Brandon Vincent. All rights reserved.
//

#ifndef function_h
#define function_h

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "tree.h"

#define SEPARATOR ","
#define EXCEPTION_SIGN "*"
#define QUOTATION_MARK "\""

// to update information
typedef struct {
    kdnode_t* current_node;
    double cur_distance;
    int count;
    int found;
} info_t;


void delete_extra_quot(char str[]);
void edit_row(char str[]);
double find_distance(struct node* node1, double coordinate[]);
struct node* input_row(struct node* node, char row[]);
int count_exceptions(char str[]);
int find_exceptions(char str[]);
void print_node(struct node* cur_node);
void insert_coor(char str[], double coordinates[]);
tree_t* create_empty_tree(void);
kdnode_t* create_node(void);


#endif /* function_h */
