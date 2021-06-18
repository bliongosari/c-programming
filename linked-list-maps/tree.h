//
//  tree.h
//  asg2
//
//  Created by Brandon Vincent on 13/09/20.
//  Copyright © 2020 Brandon Vincent. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAX_CHAR 128

typedef struct node kdnode_t;

typedef struct {
    char* census_year;
    char* block_id;
    char* property_id;
    char* base_prop_id;
    char clue_small_area[MAX_CHAR];
    char* industry_code;
    char* trading_name;
    char industry_desc[MAX_CHAR];
    char* x_cor;
    char* y_cor;
    char location[MAX_CHAR];
} data_t;


typedef struct {
    kdnode_t* head;
} tree_t;

struct node {
    double coordinates[2];
    data_t* data;
    kdnode_t* left;
    kdnode_t* right;
    kdnode_t* next_dup;
};

struct node* make_new_node(double coordinates[]);
void insert_node(struct node* head, struct node* curr_node, int depth);
void insert_duplicate(struct node* head, struct node* curr_node);
int compare(double d1[], double d2[]);
void free_tree(struct node* head);
void free_node(struct node* node);

#endif /* tree_h */
