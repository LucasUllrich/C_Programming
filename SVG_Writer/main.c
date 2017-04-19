/* 
 * File:   main.c
 * Author: Lucas Ullrich
 *
 * Created on 18. April 2017, 12:11
 * Finished on 
 * 
 * Description:
 *  This programm writes a SVG file with a given dataset as a graph.
 *  A maximum of 100 values can be processed.
 *  The numbers in the dataset shall be seperated by whitespaces and written in
 *    a single line.
 *  It is callable with the options: i, s and f.
 *  -i: Input file
 *  -s: Name for the SVG file
 *  -f: Format options g (with grid), s (with scale)
 *	
 */

#include "main.h"


/*
 * 
 */
int main(int argc, char** argv) {
  
  int opt;
  char iarg[20] = "";
  char sarg[20] = "";
  char farg[20] = "";
  
  FILE *pDataset;
  FILE *pGraph;
  int num_datasets = 0;
  int max_value = 0;
  int data[100] = {};
  
  while((opt = getopt(argc, argv, "i:s:f:")) != -1) {
    switch(opt) {
      case 'i':
        strncpy(iarg, optarg, 20);
        break;
      case 's':
        strncpy(sarg, optarg, 20);
        break;
      case 'f':
        strncpy(farg, optarg, 20);
        break;
      case '?':
        fprintf(stderr, "Usage:\n"
                "\t-i: Input\n"
                "\t-s: Store to\n"
                "\t-f: format: g (Grid), s (Scale), one must be present\n");
        break;
    }
  }
  
#ifdef DEBUG
  printf("i: %s\n", iarg);
  printf("s: %s\n", sarg);
  printf("f: %s\n", farg);
#endif
  
  pDataset = fopen(iarg, "r");
  if(pDataset == NULL) {
    printf("Dataset could not be opened!\n");
    return(EXIT_FAILURE);
  }
  pGraph = fopen(sarg, "w");
  if(pGraph == NULL) {
    printf("SVG file could not be created!\n");
    return(EXIT_FAILURE);
  }
  
#ifdef DEBUG
  printf("All files opened/created successfully\n");
#endif
  
  read_data(pDataset, data, &num_datasets, &max_value);
  
  printf("datastring:\n");
  for(int c = 0; c < num_datasets; c++) {
    printf("\t%d\n", data[c]);
  }
  
  print_header(num_datasets, max_value);
  
  fclose(pDataset);
  fclose(pGraph);
  
#ifdef DEBUG
  printf("All files closed again");
#endif
  
  return (EXIT_SUCCESS);
}

