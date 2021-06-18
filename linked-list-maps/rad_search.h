//
//  rad_search.h
//  asg2
//
//  Created by Brandon Vincent on 16/09/20.
//  Copyright © 2020 Brandon Vincent. All rights reserved.
//

#ifndef rad_search_h
#define rad_search_h
#define BIG_NUM 9999999999999
#define FIRST_DEPTH 1
#define FALSE 0

#include <stdio.h>
#include "function.h"

void get_input_and_search_radius(tree_t* tree, char* output_file);
void search_input_radius(tree_t* tree, double coordinate[], double radius_d, info_t* rad_info, char x_cor[], char y_cor[], char radius[], char* output_file);
void print_radius_result(struct node* cur_node, char* output, char x_cor[], char y_cor[], char radius[]);
void radius_search(struct node* curr_node, double coordinate[], double radius, info_t *info, int depth, char x_cor[], char y_cor[], char radius_s[], char* output_file);
void rad_other_node(struct node* prev_node, struct node* curr_node, double coordinate[], double radius, info_t *info, int depth, char x_cor[], char y_cor[], char radius_s[], char* output_file);


#endif /* rad_search_h */
