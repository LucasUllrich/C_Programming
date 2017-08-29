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
  *num_datasets = 0;
  *max_value = 0;

#ifdef DEBUG
  if(pDataset == NULL) {
    printf("Data-File not opened");
  }else {
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
  pdata_buf = strtok(line, " \n");  // Initial read
  
#ifdef DEBUG
  printf("Buf: %s\n", pdata_buf);
#endif

  while(pdata_buf != NULL && *num_datasets < 100) {
    sscanf(pdata_buf, "%d", &data[*num_datasets]);
    
    if(data[*num_datasets] > *max_value) {
      *max_value = data[*num_datasets];
    }
    *num_datasets = *num_datasets + 1;
    pdata_buf = strtok(NULL, " \n");
  }
  
  free(line);
  
#ifdef DEBUG
  printf("End of read routine reached\n");
#endif

}



void print_header(int width_buf, int height_buf) {
  
  char width[20] = "";
  char height[20] = "";
  char height_offset[20] = "";
  width_buf = (width_buf * 100) + 200;  // 90 width for rect + 10 spacing 
      // between the bars and 200 of space on the sides
  height_buf = (height_buf * 100) + 200;// 100 per numerical increase and 100
      // spacing for each side
  sprintf(width, "%d", width_buf);
  sprintf(height, "%d", height_buf);
  height_buf -= 100;
  sprintf(height_offset, "%d", height_buf);
  
  
  fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
          "<svg xmlns=\"http://www.w3.org/2000/svg\"\n"
          "xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
          "version=\"1.1\" baseProfile=\"full\"\n"
          "width=\"", pGraph);
  fputs(width, pGraph);
  fputs("\" height=\"", pGraph);
  fputs(height, pGraph);
  fputs("\"\n"
          "viewBox=\"-100 -", pGraph); // viewBox X-Offset
  fputs(height_offset, pGraph);         // viewBox Y-Offset
  fputs(" ", pGraph);
  fputs(width, pGraph);                 // viewBox X-Size
  fputs(" ", pGraph);
  fputs(height, pGraph);                // viewBox Y-Size
  fputs("\">\n"
          "<title>Graph</title>\n"
          "<desc>Graph generated ob a set of numbers</desc>\n\n", pGraph);
          
#ifdef DEBUG
  printf("Print of header finished\n");
#endif

}
