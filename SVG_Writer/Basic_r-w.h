/*
 *  File:   Basic_r-w.h
 *  Author: Lucas Ullrich
 * 
 *  Created on 18. April 2017 13:59
 */


#ifndef BASIC_R_W_H
#define BASIC_R_W_H

int buf_to_dec(char *data_buf);
void Read_Data(FILE *pDataset, int *data, int *num_datasets, int *max_value);
void Print_Header(int width, int height);

#endif /* BASIC_R_W_H */

