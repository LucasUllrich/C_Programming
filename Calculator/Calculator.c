/*
 * Filename: Calculator.c 
 *
 * Author: Lucas
 * 
 *	Date: 2017-01-18
 *  Finished:
 *
 * Description:
 *  This userfriendly calculator should be able to take 2 numbers and perform
 *    basic operations with them.
 *    - Addition (+)
 *    - Substraction (-)
 *    - Multiplication (*)
 *    - Division (/)
 *    - n-th power of (**)
 *    - n-th root of (_/)
 *    - number1 in percent to number2 (%)
 *    - The previous result shall be execcible by "Ans"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LENGTH 100
//#define DEBUG


void Print_Error(char *error) {
  if(strcmp(error, "Num1")) {
    printf("Nummer 1 fehlt.\n");

  }else if(strcmp(error, "Num2")) {
    printf("Nummer2 fehlt.\n");

  }else if(strcmp(error, "DivBy0")) {
    printf("Divisor ist '0'.\n");

  }else if(strcmp(error, "Imag")) {
    printf("Die Wurzel ist negativ\n");

  }
}


char *Evaluate_Operation(char *input, int length) {

#ifdef DEBUG
  printf("Length: %d\n", length);
#endif

  if(strcspn(input, "+") < length) {
    return "+";
  }else if(strcspn(input, "-") < length) {
    return "-";
  }else if(strcspn(input, "*") < length) {
    if(input[(strcspn(input, "*") + 1)] == '*') {
      return "**";
    }
    return "*";
  }else if(strcspn(input, "/") < length) {
    if(input[(strcspn(input, "_") + 1)] == '/') {
      return "_/";
    }
    return "/"; 
  }else if(strcspn(input, "%") < length) {
    return "%";
  }else if(strcspn(input, "Ans") < length) {
    return "Ans";
  }else {
    return "Error_0";
  }
}

double Calculate(double number1, double number2, char *operation) {
  if(!strcmp(operation, "+")) {
    return (number1 + number2);

  }else if(!strcmp(operation, "-")) {
    return(number1 - number2);

  }else if(!strcmp(operation, "*")) {
    return (number1 * number2);

  }else if(!strcmp(operation, "/")) {
    if(number2 == 0) {
      Print_Error("DivBy0");
      return 0;
    }
    return (number1 / number2);

  }else if(!strcmp(operation, "**")) {
    return (pow(number1, number2));

  }else if(!strcmp(operation, "_/")) {
    if(number2 < 0) {
      Print_Error("Imag");
      return 0;
    }
    return (pow(1/number2, number1));

  }else if(!strcmp(operation, "%")) {
    return((number1 / number2) * 100);
  }else {
    return 0;
  }
}


int main(int argc, char **argv) {
  char input[MAX_INPUT_LENGTH];
  char *pDummy;
  char *snumber1, *snumber2;
  double number1 = 0, number2 = 0;
  char *operation;
  char *sout;
  int length;
  double Ans = 0;
  int error = 0;

  while(1) {
    printf("Geben Sie Ihre Rechnung ein: \n");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    length = strlen(input);
    fflush(stdin);

#ifdef DEBUG
    printf("%s\n", input);
#endif

    if(strcspn(input, " ") == length) {
      printf("Bitte geben Sie die Rechnung mit ' ' (Leerzeichen) ein!.\n");
      continue;
    }
    if(input[(strcspn(input, " ") + 2)] != ' ') {
      printf("Bitte geben Sie die Rechnung mit ' ' (Leerzeichen) ein!.\n");
      continue;
    }

    operation = Evaluate_Operation(input, length);

#ifdef DEBUG
    printf("Operation: %s!\n", operation);
#endif

    snumber1 = strtok(input, " ");
    number1 = strtod(snumber1, &pDummy);
    while(sout != NULL) {
      snumber2 = sout;
      sout = strtok(NULL, " ");
    }
    number2 = strtod(snumber2, &pDummy);

    if(strspn(snumber1, "0123456789") == 0 && strcmp(snumber1, "Ans") != 0) {
      Print_Error("Num1");
      error = 1;
    }
    if(strspn(snumber2, "0123456789") == 0 && strcmp(snumber2, "Ans") != 0) {
      Print_Error("Num2");
      error = 1;
    }

    if(!strcmp(snumber1, "Ans")) {
      number1 = Ans;
    } else if(!strcmp(snumber2, "Ans")) {
      number2 = Ans;
    }

    if(error != 1) {
      Ans = Calculate(number1, number2, operation);
      printf("Ans = %lf\n", Ans);
    }
    
    error = 0;

#ifdef DEBUG
    printf("snumber1: %s!\n", snumber1);
    printf("number1: %lf!\n", number1);
    printf("snumber2: %s!\n", snumber2);
    printf("number2: %lf!\n", number2);
#endif

    
  }

  return 0;
}

/*
 * TODO's
 *
 *  Check if numbers are actually numbers or if a letter is mixed in
 *    Would be done by searching for a letter in snumber1 and snumebr2
 */
