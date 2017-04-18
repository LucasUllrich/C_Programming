/*
 *  File:   Basic_r-w.c
 *  Author: Lucas Ullrich
 * 
 *  Created on 18. April 2017 13:32
 */

#include "main.h"

int buf_to_dec(char *data_buf) {
  int dec = 0;
  for(int c = 0; c <= strlen(data_buf); c++) {
    dec += 10 * (strlen(data_buf) - c) * (data_buf[c] - 48);
  }
  return dec;
}

void Read_Data(FILE *pDataset, int *data, int *num_datasets, int *max_value) {
  
#ifdef DEBUG
  printf("Read_Data routine accessed");
#endif
  
  size_t line_length = 0;
  char *line;
  char *pdata_buf;
  
#ifdef DEBUG
  if(pDataset == NULL) {
    printf("Data-File not opened");
  }else {
    fprintf(pDataset,"!\n");
  }
#endif
  
  getline(&line, &line_length, pDataset);
  if(strlen(line) == 0) {
    printf("No dataset found\n");
    return;     //**** Abbort, no data found
  }
#ifdef DEBUG
  printf("%s", line);
#endif
  pdata_buf = strtok(line, " ");
  data[*num_datasets] = buf_to_dec(pdata_buf);
  *max_value = data[*num_datasets];
  *num_datasets = 1;
  while(data != NULL && *num_datasets < 100) {
    pdata_buf = strtok(NULL, " ");
    data[*num_datasets] = buf_to_dec(pdata_buf);
    if(data[*num_datasets] > *max_value) {
      *max_value = data[*num_datasets];
    }
    *num_datasets = *num_datasets + 1;
  }
}


void Print_Header(int width, int height) {
  
}
