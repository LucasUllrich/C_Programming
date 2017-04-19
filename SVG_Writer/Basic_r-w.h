/*
 *  File:   Basic_r-w.h
 *  Author: Lucas Ullrich
 * 
 *  Created on 18. April 2017 13:59
 */


#ifndef BASIC_R_W_H
#define BASIC_R_W_H

void read_data(FILE *pDataset, int *data, int *num_datasets, int *max_value);
void print_header(int width, int height);

#endif /* BASIC_R_W_H */

