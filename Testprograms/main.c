/* 
 * File:   main.c
 * Author: Lucas Ullrich
 *
 * Created on 26. April 2017, 21:12
 * Finished on 
 * 
 * Description:
 *	
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/*
 * 
 */
int main(int argc, char** argv) {

  char symbol;
  long height;
  char *pbuf;
  char *number;
  
  pbuf = (char*)malloc(2);
  number = (char*)malloc(strlen(argv[2]));
  if(pbuf == NULL || number == NULL) {
    printf("Failed to allocate memory!\n");
    return(EXIT_FAILURE);
  }
  
  if(argc != 3) {
    printf("Not enough arguments!\n"
            "user guide: muster.exe [symbol] [height]\n");
  }
  
  symbol = argv[1][0];

/*
  printf("%s\n", argv[2]);
  
  printf("pbuf-address: %p\n"
          "pbuf-value: %s\n"
          "argv: %p\n", pbuf, pbuf, argv[2]);
*/
  strncpy(number, argv[2], strlen(argv[2]));
  height = strtol(number, &pbuf, 0);
  if(pbuf == argv[2] || *pbuf != '\0') {
    printf("Error converting number!\n");
    return(EXIT_FAILURE);
  }
  
  printf("height: %ld\n", height);
  
  signed int i;
  for(i = 0; i < height; i++) {
    for(int c = 0; c <= i; c++) {
      printf("%c", symbol);
    }
    printf("\n");
  }
  
  for(i = --height; i >= 0; i--) {
    for(int c = 0; c < i; c++) {
      printf("%c", symbol);
    }
    printf("\n");
  }
  
  free(pbuf);
  pbuf = NULL;
  
  return (EXIT_SUCCESS);
}

