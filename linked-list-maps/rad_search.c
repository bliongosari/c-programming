//
//  rad_search.c
//  asg2
//
//  Created by Brandon Vincent on 16/09/20.
//  Copyright © 2020 Brandon Vincent. All rights reserved.
//

#include "rad_search.h"

// Search coordinates in tree recursively
void radius_search(struct node* curr_node, double coordinate[], double radius, info_t *info, int depth, char x_cor[], char y_cor[], char radius_s[], char* output_file){
    if (!curr_node){
        return;
    }
    
    info->count = info->count + 1;
    double distance = find_distance(curr_node, coordinate);
    // if within radius print
    if (distance < radius){
        info->found = 1;
        print_radius_result(curr_node, output_file, x_cor, y_cor, radius_s);
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
            radius_search(curr_node->right, coordinate, radius, info, depth + 1, x_cor, y_cor, radius_s, output_file);
        }
        if (curr_node->left != NULL){
            rad_other_node(curr_node, curr_node->left, coordinate, radius, info, depth, x_cor, y_cor, radius_s, output_file);
        }
    }
    else {
        // check left
        if (curr_node->left != NULL){
            radius_search(curr_node->left, coordinate, radius, info, depth + 1, x_cor, y_cor, radius_s, output_file);
        }
        if (curr_node->right != NULL){
            rad_other_node(curr_node, curr_node->right, coordinate, radius, info, depth, x_cor, y_cor, radius_s, output_file);
        }
    }
}

// checking other node if it is valid
void rad_other_node(struct node* prev_node, struct node* curr_node, double coordinate[], double radius, info_t *info, int depth, char x_cor[], char y_cor[], char radius_s[], char* output_file){
    double distance;
    int i = 0;
    if (depth % 2 == 0){
        i = 1;
    }
    // checking best possible distance
    distance = sqrt(pow(coordinate[i] - prev_node->coordinates[i], 2));
    // if distance is smalller check
    if (distance < radius){
        radius_search(curr_node, coordinate, radius, info, depth + 1, x_cor, y_cor, radius_s, output_file);
    }
    return;
}

// initialize search
void search_input_radius(tree_t* tree, double coordinate[], double radius_d, info_t* rad_info, char x_cor[], char y_cor[], char radius[], char* output_file){
    radius_search(tree->head, coordinate, radius_d, rad_info, FIRST_DEPTH, x_cor, y_cor, radius, output_file);
    FILE* file = fopen(output_file, "a");
    assert(file);
    printf("%s %s %s --> %d \n", x_cor, y_cor, radius, rad_info->count);
    if (rad_info->found == FALSE){
        fprintf(file, "%s %s %s --> NOTFOUND\n", x_cor, y_cor, radius);
    }
    fprintf(file, "\n");
    fclose(file);
}

//printing results to a file
void print_radius_result(struct node* cur_node, char* output, char x_cor[], char y_cor[], char radius[]){
    FILE* file = fopen(output, "a");
    assert(file);
    while (cur_node != NULL){
        fprintf(file, "%s %s %s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s || \n",
        x_cor,
        y_cor,
        radius,
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
    fclose(file);
}

// get input of radius and coordinates
void get_input_and_search_radius(tree_t* tree, char* output_file){
    info_t *rad_info;
    rad_info = (info_t*)malloc(sizeof(*rad_info));
    assert(rad_info != NULL);
    rad_info->count = 1;
    rad_info->found = FALSE;
    
    int c = 0;
    int prev_c = 0;
    int space = 0;
    int index = 0;
    double coordinate[2];
    double radius_d;
    char x_cor[MAX_CHAR];
    char y_cor[MAX_CHAR];
    char radius[MAX_CHAR];
    char *ptr;
    
    while ((c = getchar()) != EOF){
        if (c == '\n'){
            radius[index] = '\0';
            index = 0;
            space = 0;
            coordinate[0] = strtod(x_cor, &ptr);
            coordinate[1] = strtod(y_cor, &ptr);
            radius_d = strtod(radius, &ptr);
            rad_info->count = 1;
            rad_info->found = FALSE;
            search_input_radius(tree, coordinate, radius_d, rad_info, x_cor, y_cor, radius, output_file);
        } else if (c == ' '){
            if (space == 0){
                x_cor[index] = '\0';
            }
            else if (space == 1){
                y_cor[index] = '\0';
            }
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
            else if (space == 2){
                radius[index] = c;
                index++;
            }
        }
        prev_c = c;
    }
    
    if (c == EOF && prev_c != '\n'){
        radius[index] = '\0';
        coordinate[0] = strtod(x_cor, &ptr);
        coordinate[1] = strtod(y_cor, &ptr);
        radius_d = strtod(radius, &ptr);
        rad_info->count = 1;
        rad_info->found = FALSE;
        search_input_radius(tree, coordinate, radius_d, rad_info, x_cor, y_cor, radius, output_file);
    }
    free(rad_info);
}
