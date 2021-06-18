//
//  nn_search.h
//  asg2
//
//  Created by Brandon Vincent on 16/09/20.
//  Copyright © 2020 Brandon Vincent. All rights reserved.
//

#ifndef nn_search_h
#define nn_search_h
#define BIG_NUM 9999999999999
#define FIRST_DEPTH 1
#define FALSE 0

#include <stdio.h>
#include "function.h"

void get_input_and_search_nearest(tree_t* tree, char* output_file);
void search_input(tree_t* tree, double coordinate[], char x_cor[], char y_cor[], info_t* nn_search_info, char* output_file);
void nn_search_print(struct node* curr_node, char* output, char x_cor[], char y_cor[]);
void nearest_search(struct node* curr_node, double coordinate[], info_t *info, int depth);
void check_other_node(struct node* prev_node, struct node* curr_node, double coordinate[], info_t *info, int depth);

#endif /* nn_search_h */
