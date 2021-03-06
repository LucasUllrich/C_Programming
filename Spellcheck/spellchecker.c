/*
 * File:   spellchecker.c
 * Author: Lucas Ullrich
 *
 * Created on 2. März 2017, 20:55
 * Finished on
 *
 * Description:
 *  Mutated vowls are possibly counted es wrong words due to encoding issues in
 *  the dictionary (encoding in ANSI, console uses UTF-8)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG

/*
 *
 */
int main(int argc, char** argv) {
  if(argc != 3) {
    printf("Geben Sie die richtige Anzahl an Parametern an (2)!\n");
    return(EXIT_FAILURE); //Wrong number of parameters, quit program
  }

  int line_length = 80;
  char dict_word[line_length];
  char line[line_length];
  char *word;
  fpos_t dict_start;
  int linecount = 0;
  int wordcount_correct = 0;
  int wordcount_incorrect = 0;

  FILE * pdict;
  FILE * pcheckfile;
  
  pdict = fopen(argv[1], "rt");
  pcheckfile = fopen(argv[2], "rt");
  
  if(pdict == '\0' || pcheckfile == '\0') {
    printf("Eines der Dokumente konnte nicht geoeffnet werden. Versuchen Sie "
            "es erneut.\n");
  }
  
  
  do {    //Filtering comment lines
    fgetpos(pdict, &dict_start);
    fgets(dict_word, line_length, pdict);
  } while(dict_word[0] == '%' && !feof(pdict));
  
  while(!feof(pcheckfile)) {
    fgets(line, line_length, pcheckfile);
    linecount++;
    if(line[0] == '\n' || line[0] == '\0') {
      continue;
    }
    word = strtok(line, " ,;.\t:");
    do {
      fsetpos(pdict, &dict_start);
      while(!feof(pdict)) {
        fgets(dict_word, line_length, pdict);
        dict_word[strlen(dict_word) - 1] = '\0';
        if(!strcmp(word, dict_word)) {
          // Word is correct, next word.
          wordcount_correct++;
          break;
        }
      }
      if(feof(pdict)) {
        // Word incorrect, note line and word
        wordcount_incorrect++;
        printf("%d: %s\n", linecount, word);
      }
      word = strtok(NULL, " ,;.\t:!\n");
    } while(word != NULL);
  }
  
  printf("Correct words: \t%d\n", wordcount_correct);
  printf("Wrong words: \t%d\n", wordcount_incorrect);
  
/*
 * load single lines with fgets for strtok and simultaniously count the lines
 * strtok -> truncate string until specified character is found
 * scan every single word if it is present in the dict.
 * read the single lines of the dict to get the correct words
 * start over with the next word
*/

  fclose(pdict);
  fclose(pcheckfile);
  
#ifdef DEBUG
  printf("line = %s\n", line);
#endif
  return (EXIT_SUCCESS);
}
