/*
*@brief Imm works with images in the text file format or imm file format.
*
*    It opens an image in the text file format or imm file format and shows the pixels values on the screen,
*   converts an image in the text file format to imm file format, makes the thresholding of imm file, finds
*   related components in a image and last but not least shows the way out of a maze.
*
*@date 06/07/2019 ~ 20/08/2019
*@author Breno Henrique de Oliveira Ferreira
*@author Bruno Matos Salvarani
*@author Samuel Augusto
*@warning
*/

/*libs headers*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
/*libs headers end*/

/*defines*/
#define NO_ARGUMENT -3
#define INVALID_EXTENSION -2
#define SUCCESS 0
/*difenes end*/

/*prototypes*/
int open(char* argv);
int convert(char* arg1, char* arg2);
int segment(int argc, char** argv);
int cc(char* arg1, char* arg2);
int lab(char* arg1, char* arg2);
/*prototypes end*/

int main(int argc, char** argv){
    int error = 0;

    if(argc < 2){ /*Verifies if an argument was reported*/
        printf("It is necessary an argument.\n");
        printf("\nUsage: ./imm <command>\n");
        printf("\nCommands\n");
        printf("\n\t-open: opens an image and shows the pixels values on the screen.\n");
        printf("\t-convert: converts an image in the text file format to the imm file format.\n");
        printf("\t-segment: makes the thresholding of imm file.\n");
        printf("\t-cc: detects the related components.\n");
        printf("\t-lab: shows the path to be traversed in a maze.\n");
    } 
    else if(!strcmp(argv[1], "-open"))
        error = open(argv[2]);
    else if(!strcmp(argv[1], "-convert"))
        error = convert(argv[2], argv[3]);
    else if(!strcmp(argv[1], "-segment"))
        error = segment(argc, argv);
    else if(!strcmp(argv[1], "-cc"))
        error = cc(argv[2], argv[3]);
    else if(!strcmp(argv[1], "-lab"))
        error = lab(argv[2], argv[3]);
    else{
        printf("Invalid argument!\n");
        printf("\nUsage: ./imm <command>\n");
        printf("\t-open, -convert, -segment, -cc or -lab\n");
    }

    return error;
}

/*
* @brief Copies extension of a file for a array
* @param Char array
* @return Char array address
*/
char* extensionCopy(char* argv){
    int length = strlen(argv);
    char* extension = calloc(4,sizeof(char));

    if(length >= 5){
        for(int i = 3; i >= 0; i--)
            extension[i] = argv[--length];
    }

    return extension;
}

int open(char* argv){
    if(!argv)
        return NO_ARGUMENT;
    
    char* extension = extensionCopy(argv);
    int str = 0;
    int col = 0;
    Matrix* mx = NULL;
        
    if(!strcmp(extension, ".txt")){ /*Verifies if is a text file format*/
        free(extension);
        
        matrix_dimension(argv, &col, &str);
        mx = matrix_create(col, str);
        matrix_fill(mx, argv);
        matrix_show(mx);
        matrix_free(mx);

        return SUCCESS;
    
    } else if(!strcmp(extension, ".imm")){ /*Verifies if is a binary file format*/
        free(extension);

        /*Shows data from binary file format*/
        matrix_bdimension(argv, &col, &str);
        mx = matrix_create(col, str);
        matrix_fillwb(mx, argv);
        matrix_show(mx);
        matrix_free(mx);
        
        return SUCCESS;
    }

    free(extension);
    return INVALID_EXTENSION;
}

int convert(char* arg1,char* arg2){
    if(!arg1 || !arg2)
        return NO_ARGUMENT;
    
    char* extension = extensionCopy(arg1);
    
    if(!strcmp(extension, ".txt")){ /*Verifies first argument extension*/
        free(extension);

        extension = extensionCopy(arg2);
        if(!strcmp(extension, ".imm")){ /*Verifies second argument extension*/
            free(extension);

            int str = 0;
            int col = 0;    
            Matrix* mx = NULL;
            Matrix* mx2 = NULL;
            
            /*Read data from the text file format*/
            matrix_dimension(arg1, &col, &str);
            mx = matrix_create(col, str);
            matrix_fill(mx, arg1);
            /*Write data in the binary file format*/
            matrix_to_file(mx, arg2);
            matrix_free(mx);

            return SUCCESS;
        }
    }

    free(extension);
    return INVALID_EXTENSION;
}

int segment(int argc, char** argv){
    if(argc < 5)
        return NO_ARGUMENT;
    
    char* extension = extensionCopy(argv[3]);
    int col = 0;
    int str = 0;

    Matrix* mx = NULL;
    if(!strcmp(extension, ".imm")){ /*Verifies first argument extension*/
        free(extension);

        extension = extensionCopy(argv[4]);
        if(!strcmp(extension, ".imm")){ /*Verifies second argument extension*/
            free(extension);
            
            /*Read data from the binary file format*/
            matrix_bdimension(argv[3], &col, &str);
            mx = matrix_create(col, str);
            matrix_fillwb(mx, argv[3]);
            matrix_thresh(mx, atoi(argv[2]));
            /*Write data in the binary file format*/
            matrix_to_file(mx, argv[4]);
            matrix_free(mx);

            return SUCCESS;
        }
    }

    free(extension);
    return INVALID_EXTENSION;
}

int cc(char* arg1, char* arg2){
    if(!arg1 || !arg2)
        return NO_ARGUMENT;
    
    char* extension = extensionCopy(arg1);
    int col = 0;
    int str = 0;
    Matrix* mx = NULL;
    Matrix* mx2 = NULL;

    if(!strcmp(extension, ".imm")){
        free(extension);

        extension = extensionCopy(arg2);
        if(!strcmp(extension, ".imm")){
            free(extension);

            /*Read data from the binary file format*/
            matrix_bdimension(arg1, &col, &str);
            mx = matrix_create(col, str);
            matrix_fillwb(mx, arg1);
            /*Find related components and write data in the binary file format*/
            mx2 = matrix_related(mx);
            matrix_to_file(mx2, arg2);
            matrix_free(mx);
            matrix_free(mx2);

            return SUCCESS;
        }
    }

    free(extension);
    return INVALID_EXTENSION;
}

int lab(char* arg1, char* arg2){
     if(!arg1 || !arg2)
        return NO_ARGUMENT;
    
    char* extension = extensionCopy(arg1);
    int col = 0;
    int str = 0;
    Matrix* mx = NULL;

    if(!strcmp(extension, ".txt")){
        free(extension);

        extension = extensionCopy(arg2);
        if(!strcmp(extension, ".imm")){
            free(extension);

            matrix_dimension(arg1, &col, &str);
            mx = matrix_create(col, str);
            matrix_fill(mx, arg1);

            matrix_maze(mx);
            matrix_to_file(mx, arg2);
            matrix_free(mx);

            return SUCCESS;
        }
    }

    free(extension);
    return INVALID_EXTENSION;
}