/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test.c
 * Author: Lucas
 *
 * Created on 22. Februar 2017, 21:34
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    char *input;
    size_t length = 0;
    
    getline(&input, &length, stdin);
    printf("%s", input);
    return (EXIT_SUCCESS);
}

