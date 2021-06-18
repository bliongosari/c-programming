/*
main.c
Created by Brandon Vincent Liongosari (1094413), bliongosari@student.unimelb.edu.au on 17/09/20

This program stores information from the City of Melbourne Census of Land Use and Employment (CLUE) in a linked list, and set the coordinates as keys
It takes in coordinates in the command line and outputs the closest values to the coordinates
It prints to stdout the amount of comparisons it does
 
To run the program type (in terminal):
   1. make map1
   2. ./map1 dataset.csv outputfile < keyfile
                       or
     ./map1 dataset.csv outputfile, then type in the keys (ctrl+d to end)
*/

#include <stdio.h>
#include "tree.h"
#include "function.h"
#include "nn_search.h"
 
#define MAX_CHAR_LINE 512
#define NUM_ARG 3
#define FIRST_DEPTH 1

int main(int argc, char * argv[]) {
    if (argc != NUM_ARG){
        printf("Wrong amount of command line arguments.\n");
        exit(EXIT_FAILURE);
    }

    char* data_file = argv[1];
    char* output_file = argv[2];

    FILE *data = fopen(data_file, "r");
    FILE *output = fopen(output_file, "w");
    assert(data);
    assert(output);
    
    // clear the output file
    fclose(output);
    // skip header
    char row[MAX_CHAR_LINE];
    fgets(row, MAX_CHAR_LINE, data);
    
    // Getting first row
    fgets(row, MAX_CHAR_LINE, data);
    edit_row(row);
    kdnode_t *head = create_node();
    input_row(head, row);
    // Create empty tree and initializing head
    tree_t *tree = create_empty_tree();
    tree->head = head;
    tree->head->right = tree->head->left  = tree->head->next_dup = NULL;
    
    // inserting data to tree
    while (fgets(row, MAX_CHAR_LINE, data)) {
        kdnode_t *cur_node = create_node();
        edit_row(row);
        input_row(cur_node, row);
        insert_node(tree->head, cur_node, FIRST_DEPTH);
    }
    
    get_input_and_search_nearest(tree, output_file);
    
    free_tree(tree->head);
    free(tree);
    fclose(data);
    
    return 0;
}

