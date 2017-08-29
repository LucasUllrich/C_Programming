/* 
 * File:   main.c
 * Author: Lucas Ullrich
 *
 * Created on 21. April 2017, 10:15
 * Finished on 
 * 
 * Description:
 *	
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define DEBUG


void print_header(FILE *pfOutput, char *line2_1,
        char *line2_2, char *line3) {
  
  char line1[] = "P3";
  
  fputs(line1, pfOutput);
  fputs("\n", pfOutput);
  fputs(line2_1, pfOutput);
  fputs(" ", pfOutput);
  fputs(line2_2, pfOutput);
  fputs("\n", pfOutput);
  fputs(line3, pfOutput);

#ifdef DEBUG
  printf("line1: %s\n"
          "line2: %s %s\n"
          "line3: %s", line1, line2_1, line2_2, line3);
#endif
}

void read_header(FILE *pfInput, FILE *pfOutput, int *end_program, 
        int *psize_x, int *psize_y, int *pmax_value) {
  char *line = NULL;
  size_t line_length = 0;
  char p3_check_buf[3] = "";
  char *psize_x_buf = NULL;
  char *psize_y_buf = NULL;
  char pmax_value_buf[4] = "";
  char *pDummy;
  char *pspace;

  
  int c = 0;
  while(c < 3) {
    getline(&line, &line_length, pfInput);
#ifdef DEBUG
    printf("line: %s\n", line);
    printf("c: %d\n", c);
#endif
    if(line[0] != '#') {
      switch(c) {
        case 0:
          strncpy(p3_check_buf, line, 2);
          if(strcmp(p3_check_buf, "P3")) {
            printf("The given File is not an ASCII PPM!\n");
            *end_program = 0;
            return;
          }
          break;
        case 1:
          pspace = strchr(line, ' ');
          psize_x_buf = (char*)malloc(pspace - line + 1);
          psize_x_buf = strtok(line, " \t\n");
          if(psize_x_buf != NULL) {
            pspace = strchr(line, '\n');
            psize_y_buf = (char*)malloc(pspace - line + 1);
            psize_y_buf = strtok(NULL, " \t\n");
          }
          *psize_x = strtod(psize_x_buf, &pDummy);
          *psize_y = strtod(psize_y_buf, &pDummy);
#ifdef DEBUG
          printf("Pointers in case 1:\n"
                  "psize_x_buf: %s\n"
                  "psize_y_buf: %s\n", psize_x_buf, psize_y_buf);
          printf("Addresses of the pointers in case 1:\n"
          "psize_x_buf: %p\n"
          "psize_y_buf: %p\n"
          "pmax_value_buf: %p\n", psize_x_buf, psize_y_buf, pmax_value_buf);
#endif
          break;
        case 2:
          strncpy(pmax_value_buf, line, strlen(line));
          break;
      }
      c++;
#ifdef DEBUG
          printf("Pointers after c increment:\n"
                  "psize_x_buf: %s\n"
                  "psize_y_buf: %s\n", psize_x_buf, psize_y_buf);
          printf("Addresses of the pointers after c increment:\n"
          "psize_x_buf: %p\n"
          "psize_y_buf: %p\n"
          "pmax_value_buf: %p\n", psize_x_buf, psize_y_buf, pmax_value_buf);
#endif
    }
  }
  
#ifdef DEBUG
  printf("Buf-Variables befor conversion to int:\n"
          "psize_x_buf: %s\n"
          "psize_y_buf: %s\n"
          "pmax_value_buf: %s\n", psize_x_buf, psize_y_buf, pmax_value_buf);
  printf("Addresses of the pointers befor print_header call:\n"
          "psize_x_buf: %p\n"
          "psize_y_buf: %p\n"
          "pmax_value_buf: %p\n", psize_x_buf, psize_y_buf, pmax_value_buf);
#endif
  
  
  *pmax_value = strtod(pmax_value_buf, &pDummy);
  
#ifdef DEBUG
  printf("Read data befor writing:\n"
          "psize_x: \t%d\n"
          "psize_y: \t%d\n"
          "pmax_value: \t%d\n", *psize_x, 
          *psize_y, *pmax_value);
#endif
  
  
  print_header(pfOutput, psize_x_buf, psize_y_buf, 
          pmax_value_buf);
  
  
  free(line);
  
}


void write_pixel(FILE *pfOutput, char red, char green, char blue,
        char factor, char *pcarg) {
  struct spixel_buf {
    char sred[4];
    char sgreen[4];
    char sblue[4];
  } pixel_buf;
  
  int factor_buf = 0;
  
  for(int c = 0; c < strlen(pcarg); c++) {
    switch(pcarg[c]) {
      case 'R':
        if((factor_buf + factor) > red) {
          red = (char)factor_buf;
        } else {
          factor_buf += factor;
        }
        break;
      case 'G':
        if((factor_buf + factor) > green) {
          red = (char)factor_buf;
        } else {
          factor_buf += factor;
        }
        break;
      case 'B':
        if((factor_buf + factor) > blue) {
          red = (char)factor_buf;
        } else {
          factor_buf += factor;
        }
        break;
    }
  }
  
  snprintf(pixel_buf.sred, 3, "%d", red);
  snprintf(pixel_buf.sgreen, 3, "%d", green);
  snprintf(pixel_buf.sblue, 3, "%d", blue);
  
  fputs(pixel_buf.sred, pfOutput);
  fputs(pixel_buf.sgreen, pfOutput);
  fputs(pixel_buf.sblue, pfOutput);
  fputs("\n", pfOutput);
  
}


void reduce_pixels(FILE *pfInput, FILE *pfOutput, int fsize_x, 
        int fsize_y, int factor, char *pcarg) {
  
  struct spixel {
    int red;
    int green;
    int blue;
  } pixel;
  
  struct spixel_buf {
    char sred[4];
    char sgreen[4];
    char sblue[4];
  } pixel_buf;
  
  char color_count = 'R';
  char *read_buf = NULL;
  char *line = NULL;
  size_t line_length = 0;
  
  while(!feof(pfInput)) {
    getline(&line, &line_length, pfInput);
    read_buf = strtok(line, " \t\n");
    while(read_buf != NULL) {
      switch(color_count) {
        case 'R':
          strncpy(pixel_buf.sred, read_buf, strlen(read_buf));
          color_count = 'G';
          break;
        case 'G':
          strncpy(pixel_buf.sgreen, read_buf, strlen(read_buf));
          color_count = 'B';
          break;
        case 'B':
          strncpy(pixel_buf.sblue, read_buf, strlen(read_buf));
          sscanf(pixel_buf.sred, "%d", &pixel.red);
          sscanf(pixel_buf.sgreen, "%d", &pixel.green);
          sscanf(pixel_buf.sblue, "%d", &pixel.blue);
          write_pixel(pfOutput, pixel.red, pixel.green,
                  pixel.blue, factor, pcarg);
          color_count = 'R';
          break;
      }
      read_buf = strtok(NULL, " \t\n");
    }
  }
  
  free(line);
  
}

/*
 * 
 */
int main(int argc, char** argv) {

  int opt;
  char iarg[20] = "";
  char oarg[20] = "";
  char carg[5]  = "";
  int rarg = 0;
  
  FILE *pInput;
  FILE *pOutput;
  int color_values = 0;
  int size_x = 0;
  int size_y = 0;
  int max_value = 0;
  
  while((opt = getopt(argc, argv, ":i:o:r:c:")) != -1) {
    switch(opt) {
      case 'i':
        strncpy(iarg, optarg, 20);
        break;
      case 'o':
        strncpy(oarg, optarg, 20);
        break;
      case 'r':
        for(int i = 0; i < strlen(optarg); i++) {
          if(!isdigit(optarg[i])) {
            // Non numerical value found
            printf("Reduce factor is not numerical!\n");
            return(EXIT_FAILURE);
          }
        }
        sscanf(optarg, "%d", &rarg);
        break;
      case 'c':
        for(int i = 0; i < strlen(optarg); i++) {
          if(!isalpha(optarg[i])) {
            // Non alphabetic character found
            printf("Colors to reduce not alphabetic!\n");
            return(EXIT_FAILURE);
          }
        }
        strncpy(carg, optarg, 5);
        break;
      case ':':
        switch(optopt) {
          case 'c':
            printf("RGB colors selected as default!\n");
            strncpy(carg, "RGB", 3);
            break;
          default:
            fprintf(stderr, "Option requires an argument!\n");
            break;
        }
        break;
      case '?':
        fprintf(stderr, "Option not recognised!\n");
        break;
    }
  }
  
  pInput = fopen(iarg, "r");
  if(pInput == NULL) {
    printf("Input file could not be opened!\n");
    return(EXIT_FAILURE);
  }
  pOutput = fopen(oarg, "w");
  if(pOutput == NULL) {
    printf("Output file could not be created!\n");
    return(EXIT_FAILURE);
  }
  
  read_header(pInput, pOutput, &color_values, &size_x, &size_y, &max_value);
  if(color_values == 0) {
    return(EXIT_FAILURE);
  }
  
  reduce_pixels(pInput, pOutput, size_x, size_y, rarg, carg);
  
  fclose(pInput);
  fclose(pOutput);
  
  return (EXIT_SUCCESS);
}

