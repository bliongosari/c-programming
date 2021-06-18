//
//  tree.c
//  asg2
//
//  Created by Brandon Vincent on 13/09/20.
//  Copyright © 2020 Brandon Vincent. All rights reserved.
//

#include "tree.h"

// make new node and input the coordinates into the node
struct node* make_new_node(double coordinates[]){
    kdnode_t *node = (kdnode_t*)malloc(sizeof(*node));
    assert(node != NULL);
    node->coordinates[0] = coordinates[0];
    node->coordinates[1] = coordinates[1];
    node->left = node->right = node->next_dup = NULL;
    return node;
}

// insert node to the tree (recursive)
void insert_node(struct node* head, struct node* curr_node, int depth){
    int i = 0;
    // if exact duplicates
    if (compare(head->coordinates, curr_node->coordinates) == 1){
        insert_duplicate(head, curr_node);
        return;
    }
    
    if (depth % 2 == 0){
        i = 1;
    }
    
    if (head->coordinates[i] < curr_node->coordinates[i]){
        if (head->right == NULL){
            head->right = curr_node;
            return;
        }
        // if not empty, go right
        insert_node(head->right, curr_node, depth+1);
    } else {
        
        if (head->left == NULL){
            head->left = curr_node;
            return;
        }
        // if not empty, go left
        insert_node(head->left, curr_node, depth+1);
    }
    
    return;
}

// insert instances of duplicates like linked list
void insert_duplicate(struct node* head, struct node* curr_node){
    while (head->next_dup != NULL){
        head = head->next_dup;
    }
    head->next_dup = curr_node;
}

// comparing two doubles
int compare(double d1[], double d2[]){
    double epsilon = 0.0000001f;
    if (fabs(d1[0] - d2[0]) < epsilon && fabs(d1[1] - d2[1]) < epsilon){
        return 1;
        
    }
    return 0;
}

// freeing tree
void free_tree(struct node* node) {
    if (node == NULL) {
        return;
    }
    while (node->next_dup != NULL){
        kdnode_t* temp_node = node->next_dup;
        node->next_dup = node->next_dup->next_dup;
        free_node(temp_node);
        free(temp_node);
    }
    free_tree(node->left);
    free_tree(node->right);
    free_node(node);
    free(node);
}

// freeing data in the node
void free_node(struct node* node){
    assert(node);
    free(node->data->census_year);
    free(node->data->block_id);
    free(node->data->property_id);
    free(node->data->base_prop_id);
    free(node->data->industry_code);
    free(node->data->trading_name);
    free(node->data->x_cor);
    free(node->data->y_cor);
    free(node->data);
 
}
