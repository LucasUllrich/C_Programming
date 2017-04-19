/*
 *  File:   Basic_r-w.c
 *  Author: Lucas Ullrich
 * 
 *  Created on 18. April 2017 13:32
 */

#include "main.h"

void read_data(FILE *pDataset, int *data, int *num_datasets, 
        int *max_value) {
  
#ifdef DEBUG
  printf("Read_Data routine accessed\n");
#endif
  

  size_t line_length = 0;
  char *line = NULL;
  char *pdata_buf;

#ifdef DEBUG
  if(pDataset == NULL) {
    printf("Data-File not opened");
  }else {
/*
    fprintf(pDataset, "!\n");
*/
    printf("Dataset opened successfully\n");
  }
#endif

  
  getline(&line, &line_length, pDataset);
  if(strlen(line) == 0) {
    printf("No dataset found\n");
    return;     //**** Abbort, no data found
  }
#ifdef DEBUG
  printf("line: %s\n", line);
#endif
  pdata_buf = strtok(line, " \n");
  sscanf(pdata_buf, "%d", &data[*num_datasets]);
  *max_value = data[*num_datasets];
  *num_datasets = 1;
#ifdef DEBUG
  printf("Buf: %s\n", pdata_buf);
  printf("Data: %d\n", data[0]);
#endif

  while(pdata_buf != NULL/* && *num_datasets < 100*/) {
    pdata_buf = strtok(NULL, " \n");
    sscanf(pdata_buf, "%d", &data[*num_datasets]);
#ifdef DEBUG
    printf("Dataset Nr. %d read\n", *num_datasets);
    printf("Dataset-Value: %d\n", data[*num_datasets]);
    printf("databuf: %s\n", pdata_buf);
    printf("Number: %d\n", *num_datasets);
#endif

    if(data[*num_datasets] > *max_value) {
      *max_value = data[*num_datasets];
    }

    *num_datasets = *num_datasets + 1;
    printf(".\n");

    /*
#ifdef DEBUG
    printf("Dataset Nr. %d read\n", *num_datasets);
    printf("Dataset-Value: %d\n", data[*num_datasets]);
    printf("databuf: %s\n", pdata_buf);
    printf("Number: %d\n", *num_datasets);
#endif
*/
  }
#ifdef DEBUG
  printf("End of read routine reached\n");
#endif

}


void print_header(int width, int height) {
  
}
