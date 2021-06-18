//
//  nn_search.c
//  asg2
//
//  Created by Brandon Vincent on 16/09/20.
//  Copyright © 2020 Brandon Vincent. All rights reserved.
//

#include "nn_search.h"

// Get input coordinates
void get_input_and_search_nearest(tree_t* tree, char* output_file){
    info_t *nn_search_info;
    nn_search_info = (info_t*)malloc(sizeof(*nn_search_info));
    assert(nn_search_info != NULL);
    
    int c = 0;
    int prev_c = 0;
    int space = 0;
    int index = 0;
    double coordinate[2];
    char x_cor[MAX_CHAR];
    char y_cor[MAX_CHAR];
    char *ptr;
    while ((c = getchar()) != EOF){
        // if reach end
        if (c == '\n'){
            y_cor[index] = '\0';
            index = 0;
            space = 0;
            coordinate[0] = strtod(x_cor, &ptr);
            coordinate[1] = strtod(y_cor, &ptr);
            search_input(tree, coordinate, x_cor, y_cor, nn_search_info, output_file);
        } else if (c == ' '){
            x_cor[index] = '\0';
            index = 0;
            space++;
        } else {
            if (space == 0){
                x_cor[index] = c;
                index++;
            }
            else if (space == 1){
                y_cor[index] = c;
                index++;
            }
        }
        prev_c = c;
    }

    // if no terminating newline
    if (c == EOF && prev_c != '\n'){
        y_cor[index] = '\0';
        coordinate[0] = strtod(x_cor, &ptr);
        coordinate[1] = strtod(y_cor, &ptr);
        search_input(tree, coordinate, x_cor, y_cor, nn_search_info, output_file);
    }
    free(nn_search_info);
}

// prints info of current node to a file
void nn_search_print(struct node* cur_node, char* output, char x_cor[], char y_cor[]){
    FILE* file = fopen(output, "a");
    assert(file);
    while (cur_node != NULL){
        fprintf(file, "%s %s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s || \n",
        x_cor,
        y_cor,
        cur_node->data->census_year,
        cur_node->data->block_id,
        cur_node->data->property_id,
        cur_node->data->base_prop_id,
        cur_node->data->clue_small_area,
        cur_node->data->trading_name,
        cur_node->data->industry_code,
        cur_node->data->industry_desc,
        cur_node->data->x_cor,
        cur_node->data->y_cor,
        cur_node->data->location);
        cur_node = cur_node->next_dup;
    }
    fprintf(file, "\n");
    fclose(file);
}

//initialize searches
void search_input(tree_t* tree, double coordinate[], char x_cor[], char y_cor[], info_t* nn_search_info, char* output_file){
    nn_search_info->current_node = tree->head;
    nn_search_info->cur_distance = BIG_NUM;
    nn_search_info->count = 0;
    nearest_search(tree->head, coordinate, nn_search_info, FIRST_DEPTH);
    nn_search_print(nn_search_info->current_node, output_file, x_cor, y_cor);
    printf("%s %s --> %d\n", x_cor, y_cor, nn_search_info->count);
}

// search the coordinate in the k-d tree
void nearest_search(struct node* curr_node, double coordinate[], info_t *info, int depth){
    info->count = info->count + 1;
    double distance = find_distance(curr_node, coordinate);
    
    // if smaller than curr distance
    if (distance < info->cur_distance){
        info->current_node = curr_node;
        info->cur_distance = distance;
    }
    
    int i = 0;
    // if i = 0, then coordinate is x, if i = 1, then coordinate is y
    if (depth % 2 == 0){
        i = 1;
    }
    
    //find which side is dominant
    if (coordinate[i] > curr_node->coordinates[i]){
        // check right
        if (curr_node->right != NULL){
            nearest_search(curr_node->right, coordinate, info, depth + 1);
        }
        if (curr_node->left != NULL){
            check_other_node(curr_node, curr_node->left, coordinate, info, depth);
        }
    }
    else {
        // check left
        if (curr_node->left != NULL){
            nearest_search(curr_node->left, coordinate, info, depth + 1);
        }
        if (curr_node->right != NULL){
            check_other_node(curr_node, curr_node->right, coordinate, info, depth);
        }
    }
}

// checking other node if it is valid
void check_other_node(struct node* prev_node, struct node* curr_node, double coordinate[], info_t *info, int depth){
    double distance;
    int i = 0;
    // if i = 0, then coordinate is x, if i = 1, then coordinate is y
    if (depth % 2 == 0){
        i = 1;
    }
    
    // checking best possible distance
    distance = sqrt(pow(coordinate[i] - prev_node->coordinates[i], 2));
    // if distance is smalller check
    if (distance < info->cur_distance){
        nearest_search(curr_node, coordinate, info, depth + 1);
    }
    return;
}
