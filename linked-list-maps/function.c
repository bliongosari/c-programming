//
//  function.c
//  asg2
//
//  Created by Brandon Vincent on 13/09/20.
//  Copyright © 2020 Brandon Vincent. All rights reserved.
//

#include "function.h"

// find distance between two points
double find_distance(struct node* node1, double coordinate[]){
    double distance;
    double distance_x = node1->coordinates[0] - (coordinate[0]);
    double distance_y = node1->coordinates[1] - (coordinate[1]);
    distance = sqrt(pow(distance_x, 2) + pow(distance_y, 2));
    return distance;
}

// delete extra quotatiions in csv row
void delete_extra_quot(char str[]){
    int i, j;
    for (i = 0; str[i] != '\0'; i++){
        if (str[i] == '\"' && str[i + 1] == '\"'){
            for (j = i; str[j] != '\0'; j++){
                str[j] = str[j + 1];
            }
            str[j] = '\0';
        }
    }
}

// Edit row so that exceptions in a string is replaced by * instead of '\"'
void edit_row(char str[]){
    for (int i = 1; str[i] != '\0'; i++){
        // if not surrounded by a quotation mark, or presented in location
        if (str[i - 1] != '\"' || str[i + 1] != '\"'){
            if ((str[i] == '\"' && str[i + 1] == ',') ||
                 (str[i] == '\"' && str[i - 1] == ',' && str[i + 1] != '(')){
                str[i] = '*';
            }
        }
    }
    delete_extra_quot(str);
}

// Count quotation marks(in pairs) in a string which indicates an exception in the string
int count_exceptions(char str[]) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '*') {
            count++;
        }
    }
    return count/2;
}


// Find position of exceptions in the formatted string
int find_exceptions(char str[]) {
    int count = 0;
    int position = 0;
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == ','){
            count++;
            if (str[i + 1] == '*'){
                position = count;
                break;
            }
        }
    }
    return position;
}

// printing node (not used)
void print_node(struct node* cur_node){
    printf("(%.9f, %.9f) --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s || \n",
    cur_node->coordinates[0],
    cur_node->coordinates[1],
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
}

// insert coordinates from a string
void insert_coor(char str[], double coordinates[]){
    char x_cor[strlen(str)];
    char y_cor[strlen(str)];
    char *ptr;
    int i = 1;
    int j = 0;
    while (str[i] != ','){
        y_cor[j] = str[i];
        i++;
        j++;
    }
    y_cor[j] = '\0';
    j = 0;
    i += 2;
    
    while (str[i] != ')'){
        x_cor[j] = str[i];
        j++;
        i++;
    }
    x_cor[j] = '\0';
    
    coordinates[0] = strtod(x_cor, &ptr);
    coordinates[1] = strtod(y_cor, &ptr);
    
}

// create empty tree
tree_t* create_empty_tree(void) {
    tree_t *tree;
    tree = (tree_t*)malloc(sizeof(*tree));
    assert(tree != NULL);
    return tree;
}

// create empty node
kdnode_t* create_node(void){
    kdnode_t *cur_node;
    cur_node = (kdnode_t*)malloc(sizeof(*cur_node));
    assert(cur_node != NULL);
    cur_node->left = cur_node->right = cur_node->next_dup = NULL;
    return cur_node;
}

// input row to node
struct node* input_row(struct node* node, char row[]){
    int exceptions = count_exceptions(row);
    int position = 0;
    if (exceptions == 1){
        position = find_exceptions(row);
    }
    
    data_t *temp_data;
    temp_data = (data_t*)malloc(sizeof(*temp_data));
    assert(temp_data != NULL);

    // inputs data into temp_data
    char* census_year = strtok(row, SEPARATOR);
    temp_data->census_year = (char*)malloc(strlen(census_year) + 1);
    assert(temp_data->census_year != NULL);
    strcpy(temp_data->census_year, census_year);
    
    char* block_id = strtok(NULL, SEPARATOR);
    temp_data->block_id = (char*)malloc(strlen(block_id) + 1);
    assert(temp_data->block_id != NULL);
    strcpy(temp_data->block_id, block_id);
    
    char* property_id = strtok(NULL, SEPARATOR);
    temp_data->property_id = (char*)malloc(strlen(property_id) + 1);
    assert(temp_data->property_id != NULL);
    strcpy(temp_data->property_id, property_id);
    
    char* base_prop_id = strtok(NULL, SEPARATOR);
    temp_data->base_prop_id = (char*)malloc(strlen(base_prop_id) + 1);
    assert(temp_data->base_prop_id != NULL);
    strcpy(temp_data->base_prop_id, base_prop_id);
    
    strcpy(temp_data->clue_small_area, strtok(NULL, SEPARATOR));
    
    // if exception present on trading name, seperate using '*', and make it as key
    if (exceptions == 2 || position == 5){
        char* trading_name = strtok(NULL, EXCEPTION_SIGN);
        temp_data->trading_name = (char*)malloc(strlen(trading_name) + 1);
        assert(temp_data->trading_name != NULL);
        strcpy(temp_data->trading_name, trading_name);
    } else {
        char* trading_name = strtok(NULL, SEPARATOR);
        temp_data->trading_name = (char*)malloc(strlen(trading_name) + 1);
        assert(temp_data->trading_name != NULL);
        strcpy(temp_data->trading_name, trading_name);
    }
    
    char* industry_code = strtok(NULL, SEPARATOR);
    temp_data->industry_code = (char*)malloc(strlen(industry_code) + 1);
    assert(temp_data->industry_code != NULL);
    strcpy(temp_data->industry_code, industry_code);
    
    // if extra commas or quotation marks present on industry description, seperate using *
    if (exceptions == 2 || position == 7){
        strcpy(temp_data->industry_desc, strtok(NULL, EXCEPTION_SIGN));
    } else {
        strcpy(temp_data->industry_desc, strtok(NULL, SEPARATOR));
    }
    
    char* x_cor = strtok(NULL, SEPARATOR);
    temp_data->x_cor = (char*)malloc(strlen(x_cor) + 1);
    assert(temp_data->x_cor != NULL);
    strcpy(temp_data->x_cor, x_cor);
    
    char* y_cor = strtok(NULL, SEPARATOR);
    temp_data->y_cor = (char*)malloc(strlen(y_cor) + 1);
    assert(temp_data->y_cor != NULL);
    strcpy(temp_data->y_cor, y_cor);
    
    char* location = strtok(NULL, QUOTATION_MARK);
    strcpy(temp_data->location, location);
    insert_coor(location, node->coordinates);
    
    node->data = temp_data;
    return node;
}
