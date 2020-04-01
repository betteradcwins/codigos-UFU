#ifndef matix_h
#define matix_h

#include <stdlib.h>
#include <stdio.h>

typedef struct matrix Matrix;

int matrix_bdimension(char* argv, int* col, int* lin);
int matrix_dimension(char* argv, int* col, int* lin);
Matrix* matrix_create(int col, int lin);
int matrix_fill(Matrix* mx, char* argv);
int matrix_fillwb(Matrix* mx, char* argv);
int matrix_to_file(Matrix* mx, char* argv);
int matrix_show(Matrix* mx);
int matrix_free(Matrix* mx);
int matrix_thresh(Matrix* mx, int thr);
Matrix* matrix_related(Matrix* mx);
int matrix_maze(Matrix* mx);
 
#endif