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

    // open the file
    FILE *fp = fopen(filename, "r");
    // make sure there was no error when te file was opened
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // i can use a buffer to store the characters in the file
    char buffer[10000]; // REMINDER TO SELF: upper limit might need to be changed but i need to test

    // integer variables to get the characters in the buffer (fgetc returns an unsigned char cast to an int)
    int count = 0;
    int character;

    // put the text characters into the buffer
    while ((character = fgetc(fp)) != EOF) {
        buffer[count++] = character;
    }

    // clsoe the file
    fclose(fp);

    // format the echoed characters so its 80 characters per line (NOTE TO SELF: including '\n' which is ONE character)
    // since the character variable is an int it makes sense to use putchar because it takes an int
    // and writes the character to the standard output
    for (int i = 0; i < count; i++) {
        putchar(buffer[i]);
        if ((i+1) % 80 == 0) { // after every 80 characters (when i = 79, 159, ...) print a newline
            putchar('\n');
        }
    }
    // only add a final newline if the last character wasnt already a newline
    if ((count % 80 != 0) && !(count > 0 && buffer[count - 1] == '\n')) { 
        putchar('\n');
    }

    // for actually calculating the checksum i might need to pad with X first
    int padCount = count;
    // padding isnt needed for 8bit since each ascii character is 8bits in hex
    // so padding logic is only needed for 16 and 32
    // for 16bit two bytes (2 letters) is needed (4 hex characters) so pading is needed is if he padcount isnt divisible by 2
    // for 32bit its 4 bytes (4 letters) so padding is needed if the padcount isnt divisible by 4
    while ((checksumSize == 16 && padCount %2 != 0 ) || (checksumSize ==  32 && padCount %4 != 0)) {
        buffer[padCount++] = 'X';
    }

    // checksum calculation
    unsigned long checksum = 0;
    // 8 bit
    if (checksumSize == 8) {
        for (int i = 0; i < padCount; i++) {
            checksum = checksum + (unsigned char) buffer[i]; // add all the characters
        }
        // mask so i can remove the overflow
        checksum = checksum & 0xFF;
    }
    // 16 bit
    if (checksumSize == 16) {
        for (int i = 0; i < padCount; i = i + 2) {
            // for each two letters, move the left letter over 8 spaces (4 for each hex character) and OR it with the next letter to make one word
            unsigned short word = ((unsigned char) buffer[i] << 8) | (unsigned char) buffer[i+1];
            checksum = checksum + word; // add all the words
        }
        // mask so i can remove the overflow
        checksum = checksum & 0xFFFF;
    }
    // 32 bit
    if (checksumSize == 32) {
        for (int i = 0; i < padCount; i = i + 4) {
            // for each 4 letters, move each letter the necessary amount of spaces and OR it with the next letters to make one word
            unsigned int word = ((unsigned char) buffer[i] << 24) | ((unsigned char) buffer[i+1] << 16) | ((unsigned char) buffer[i+2] << 8) | (unsigned char) buffer[i+3];
            checksum = checksum + word; // add all the words
        }
        // mask so i can remove the overflow
        checksum = checksum & 0xFFFFFFFF;
    }

    // print the output
    printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, checksum, padCount);

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