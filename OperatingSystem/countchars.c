/*

    Program Name: Count Non-Whitespace Characters in an input text File
    Author: Jose Jobins
    Date: 09/14/2025

    

    Description:
    This program counts the number of non-whitespace characters
    in a given input text file. 
    there are two options:
        -s inputfile         → display result on screen
        -f inputfile outfile → write result to an output file
    
    Limitations:
    - Assumes input file exists and is readable.
    - Not full error handling 
    - Only counts spaces, tabs and newlines, any  non ASCII white space isn't counted

    Critical code and Data declarations:
    - Uses <ctype.h> isspace() to detect whitespace.
    - Main function parses arguments and dispatches to logic.
    - fopen() and fgetc() are used for file input and outputs.
 */
// header files that are needed
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    
    // Checks minimum arguments

    if (argc < 3) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s -s inputfile\n", argv[0]);
        fprintf(stderr, "  %s -f inputfile outputfile\n", argv[0]);
        return 1;
    }



    FILE *infile, *outfile = NULL;
    int count = 0;
    int ch;


    // Opens input file
    infile = fopen(argv[2], "r");
    if (infile == NULL) {
        perror("Error opening input file");
        return 1;
    }


    // Count non-whitespace characters using isspace() 
    while ((ch = fgetc(infile)) != EOF) {
        if (!isspace(ch)) {
            count++;
        }
    }
    fclose(infile);


    // Handle -s option for screen output
    if (strcmp(argv[1], "-s") == 0) {
        printf("Non-whitespace characters: %d\n", count);
    }


    // Handle -f option for file output
    else if (strcmp(argv[1], "-f") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Output file not specified for -f option\n");
            return 1;
        }
        outfile = fopen(argv[3], "w");
        if (outfile == NULL) {
            perror("Error opening output file");
            return 1;
        }
        fprintf(outfile, "Non-whitespace characters: %d\n", count);
        fclose(outfile);
    }
    else {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
