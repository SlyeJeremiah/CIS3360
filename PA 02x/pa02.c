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

    // open the plaintext file
    FILE *pfp = fopen(plainFile, "r");
    // make sure there was no error when the file was opened
    if (pfp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // buffer to store the characters (assigment said 10k is cool)
    char plainBuffer[10000];
    // keep track of the num of characters
    int plainLength = 0;
    int character;

    while ((character = fgetc(plainFile)) != EOF) {
        // test to see if the character is uppercase and if it is
        // make it lowercase
        if (character >= 'A' && character <= 'Z') {
            character = character + ('a' - 'A'); 
            // ascii trick to add 32 to to the character making it lowercase (the upper and lower are 32 apart)
        }

        // test if the character is lowercase and if it is add it to the buffer
        if (character >= 'a' && character <= 'z') {
            plainBuffer[plainLength++] = character;
        }
    }

    // now i have to pad if the length of the buffer isnt a multiple of n
    int leftOver = plainLength % n;
    if (leftOver != 0) {
        // its easier to find how much to pad instead of looping
        // the padding and then testing to see if its a multiple of n
        int padCount = n - leftOver; // the leftover will always be less than n bc of the math (never negative)
        for (int i = 0; i < padCount; i++) {
            plainBuffer[plainLength++] = 'x';
        }
    }

    // echo the plain text
    printf("\nPlaintext:\n");
    for (int i = 0; i < plainLength; i++) {
        putchar(plainBuffer[i]);
        if ((i+1) % 80 == 0) { // after every 80 characters (when i = 79, 159, ...) print a newline
            putchar('\n');
        }
    }
    // only add a final newline if the last character wasnt already a newline
    if (plainLength % 80 != 0) {
        putchar('\n');
    }

    // another trick to map a to 0, b to 1, etc is just subtracting whatever letter by a
    // and to get a letter back is to add a (a is 97 in ascii)
    char cipherBuffer[10000];
    for (int i = 0; i < plainLength; i = i + n) {
        // jumping by n gives the right block sizes
        // martix mult: i have to multiply the rows of the key matrix
        // by the cols of the plaintext matrix
        for (int row = 0; row < n; row++) {
            int sum = 0;
            for (int col = 0; col < n; col++) {
                int plainValue = plainBuffer[i + col] - 'a'; // chages the letter to a number
                sum = sum + keyMatrix[row][col] * plainValue;
            }
           cipherBuffer[i + row] = (sum % 26) + 'a'; // change the num to a letter 
        }
    }

    // echo the cipher text
    printf("\nCiphertext:\n");
    for (int i = 0; i < plainLength; i++) {
        putchar(cipherBuffer[i]);
        if ((i+1) % 80 == 0) { // after every 80 characters (when i = 79, 159, ...) print a newline
            putchar('\n');
        }
    }
    // only add a final newline if the last character wasnt already a newline
    if (plainLength % 80 != 0) {
        putchar('\n');
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