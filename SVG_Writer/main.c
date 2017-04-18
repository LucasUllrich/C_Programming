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
 *  -f: Format options (optional) g (with grid), s (with scale)
 *	
 */

/*
#include "main.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEBUG

/*
 * 
 */
int main(int argc, char** argv) {
  
  int opt;
  char iarg[20] = "";
  char sarg[20] = "";
  char farg[20] = "";
  
/*
  FILE *pDataset;
  FILE *pGraph;
  int num_datasets = 0;
  int max_value = 0;
*/
/*
  int data[100] = {};
*/
  
  while((opt = getopt(argc, argv, "i:s:f::")) != -1) {
    switch(opt) {
      case 'i':
        strcpy(iarg, optarg);
        break;
      case 's':
        strcpy(sarg, optarg);
        break;
      case 'f':
        strcpy(farg, optarg);
        break;
      case '?':
        fprintf(stderr, "Usage:\n"
                "\t-i: Input\n"
                "\t-s: Store to\n"
                "\t-f: format: g (Grid), s (Scale), default: -\n");
        break;
    }
  }
  
#ifdef DEBUG
  printf("i: %s\n", iarg);
  printf("s: %s\n", sarg);
  printf("f: %s\n", farg);
#endif
  
/*
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
*/
  
/*
  Read_Data(pDataset, data, &num_datasets, &max_value);
*/
  
  printf("data:\n");
/*
  for(int c = 0; c < sizeof(data); c++) {
    printf("\t%d", data[c]);
  }
*/
  
/*
  Print_Header(num_datasets, max_value);
*/
  
/*
  fclose(pDataset);
  fclose(pGraph);
*/
  
  return (EXIT_SUCCESS);
}

