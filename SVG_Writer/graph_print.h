/*
 *  File:   graph_print.h
 *  Author: Lucas Ullrich
 * 
 *  Created on 20. April 2017 11:26
 */


#ifndef GRAPH_PRINT_H
#define GRAPH_PRINT_H

void print_line(int start_x, int start_y, int end_x, int end_y);
void print_rect(int start_x, int start_y, int span_x, int span_y, char stroke,
        char fill);
void print_text(int start_x, int start_y, int number);
void print_grid(int num_datasets, int max_value);
void print_scaling(int num_datasets, int max_value);
void print_bar(int value, int number);

#endif /* GRAPH_PRINT_H */

