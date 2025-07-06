/*============================================================================
| Assignment: pa02 - Encrypting a plaintext file using the Hill cipher
|
| Author: Jeremiah Registre
| Language: c, c++, Java, go, python, rust
| To Compile: javac pa02.java
| gcc -o pa02 pa02.c
| g++ -o pa02 pa02.cpp
| go build pa02.go
| rustc pa02.rs
| To Execute: java -> java pa02 kX.txt pX.txt
| or c++ -> ./pa02 kX.txt pX.txt
| or c -> ./pa02 kX.txt pX.txt
| or go -> ./pa02 kX.txt pX.txt
| or rust -> ./pa02 kX.txt pX.txt
| or python -> python3 pa02.py kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Summer 2025
| Instructor: McAlpin
| Due Date: per assignment
+===========================================================================*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9 // ill use this to make a matrix of the max size and not worry about allocating memory

int main(int argc, char **argv) {
    
    // make sure that three arguments are passed (file name, encryption key file, plaintext file)
    if (argc != 3) {
        return 1;
    }
    
    // pull and store the input arguments
    char *keyFile = argv[1];
    char *plainFile = argv[2];

    // validate the arguments
    if (argv[1][0] != 'k' || argv[2][0] != 'p') {
        fprintf(stderr, "The command line input should be in the form of ./pa02 kX.txt pX.txt");
        return 1;
    }

    // open the key file
    FILE *kfp = fopen(keyFile, "r");
    // make sure there was no error when the file was opened
    if (kfp == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // get the matrix size
    int n;
    fscanf(keyFile, "%d", &n); // reads the first integer and assigns that num to n

    // get the values in the matrix
    int keyMatrix[MAX][MAX]; // a 9 by 9 matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(keyFile, "%d", &keyMatrix[i][j]); // set the values from the file into the matrix
        }
    }
    fclose(keyFile);

    // echo the key matrix
    printf("\nKey matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", keyMatrix[i][j]);
        }
        printf("\n");
    }


    
    
    
    
    
    
    
    return 0;
}



/*=============================================================================
| I Jeremiah Registre (je138167) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/