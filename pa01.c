/*============================================================================
| Assignment: pa01 - Calculate the checksum of an input file given:
| -> the name of the input file,
| -> the checksum size of either 8, 16, or 32 bits
| Author: Jeremiah Registre
| Language: c, c++, Java, go, python, rust
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
| go build pa01.go
| rustc pa01.rs
| To Execute: java -> java pa01 inputFilename.txt checksumSize
| or c++ -> ./pa01 inputFilename.txt checksumSize
| or c -> ./pa01 inputFilename.txt checksumSize
| or go -> ./pa01 inputFilename.txt checksumSize
| or rust -> ./pa01 inputFilename.txt checksumSize
| or python -> python3 pa01.py inputFilename.txt checksumSize
| where inputFilename.txt is the input file
| and checksumSize is either 8, 16, or 32
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
| Class: CIS3360 - Security in Computing - Spring 2025
| Instructor: McAlpin
| Due Date: per assignment
+===========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    // make sure that three arguments are passed (file name, input file, checksum size)
    if (argc != 3) {
        fprintf(stderr, "Be sure to follow this format when running: ./pa01 inputFilename.txt checksumSize");
        return 1;
    }

    // pull and store the input arguments
    char *filename = argv[1];
    int checksumSize = atoi(argv[2]); // the pulled input is a string so i need to cast it to an int

    // check for a valid checksum size
    if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    
}







/*=============================================================================
| I Jeremiah Registre (je138167) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/