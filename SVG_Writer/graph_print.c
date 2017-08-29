/*
 *  File:   graph_print.c
 *  Author: Lucas Ullrich
 * 
 *  Created on 20. April 2017 11:26
 */

#include "main.h"


void print_line(int start_x, int start_y, int end_x, int end_y) {
  // <line x1="..." y1="..." x2="..." y2="..."
  //      stroke-width="1" stroke="black" />
  char x1[10] = "";
  char x2[10] = "";
  char y1[10] = "";
  char y2[10] = "";
  sprintf(x1, "%d", start_x);
  sprintf(x2, "%d", end_x);
  sprintf(y1, "%d", start_y);
  sprintf(y2, "%d", end_y);
  
  fputs("<line x1=\"", pGraph);
  fputs(x1, pGraph);
  fputs("\" y1=\"-", pGraph);
  fputs(y1, pGraph);
  fputs("\" x2=\"", pGraph);
  fputs(x2, pGraph);
  fputs("\" y2=\"-", pGraph);
  fputs(y2, pGraph);
  fputs("\" stroke-width=\"1\" stroke=\"black\" />\n", pGraph);
}


void print_rect(int start_x, int start_y, int span_x, int span_y, char stroke,
        char fill) {
  // <rect x="..." y="..." width="..." height="..." stroke="black"
  //    stroke-width="..." fill="..." />
  char x[10] = "";
  char y[10] = "";
  char width[10] = "";
  char height[10] = "";
  char stroke_bold[] = "3";
  char stroke_none[] = "0";
  char fill_none[] = "white";
  char fill_blue[] = "blue";
  sprintf(x, "%d", start_x);
  sprintf(y, "%d", start_y);
  sprintf(width, "%d", span_x);
  sprintf(height, "%d", span_y);
  
  fputs("<rect x=\"", pGraph);
  fputs(x, pGraph);
  fputs("\" y=\"-", pGraph);
  fputs(y, pGraph);
  fputs("\" width=\"", pGraph);
  fputs(width, pGraph);
  fputs("\" height=\"", pGraph);
  fputs(height, pGraph);
  fputs("\" stroke=\"black\" stroke-width=\"", pGraph);
  if(stroke == 'y') {
    fputs(stroke_bold, pGraph);
  } else {
    fputs(stroke_none, pGraph);
  }
  fputs("\" fill=\"", pGraph);
  if(fill == 'y') {
    fputs(fill_blue, pGraph);
  } else {
    fputs(fill_none, pGraph);
  }
  fputs("\" />\n", pGraph);
}


void print_text(int start_x, int start_y, int number) {
  // <text x="..." y="..." font-size="20pt" text-anchor="middle" > 
  //      Scaling-Number </text>
  char x[10] = "";
  char y[10] = "";
  char scaling[10] = "";
  snprintf(x, 9, "%d", start_x);
  snprintf(y, 9, "%d", start_y);
  snprintf(scaling, 9, "%d", number);
  
  fputs("<text x=\"", pGraph);
  fputs(x, pGraph);
  fputs("\" y=\"", pGraph);
  fputs(y, pGraph);
  fputs("\" font-size=\"50\" text-anchor=\"middle\" >", pGraph);
  fputs(scaling, pGraph);
  fputs("</text>\n", pGraph);
}


void print_grid(int num_datasets, int max_value) {
  
  print_rect(0, max_value * 100, num_datasets * 100,
          max_value * 100, 'y', 'n');
  for(int c = 0; c < num_datasets; c++) {
    print_line(c * 100, 0, c * 100, max_value * 100);
  }
  for(int c = 0; c < max_value; c++) {
    print_line(0, c * 100, num_datasets * 100, c * 100);
  }
  printf("Grid printed.\n");
}


void print_scaling(int num_datasets, int max_value) {
  
  /* X-Direction */
  for(int c = 0; c < num_datasets; c++) {
    print_text(50 + c * 100, 50, c + 1);
  }
  /* Y-Direction */
  for(int c = 0; c < max_value; c++) {
    print_text(-50, -35 - c * 100, c + 1);
  }
  printf("Scaling printed.\n");
}


void print_bar(int value, int number) {
  
  print_rect(10 + number * 100, value * 100, 80, value * 100, 'n', 'y');
}
