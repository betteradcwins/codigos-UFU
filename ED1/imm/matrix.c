#include "matrix.h"
#include "stack.h"
#include "point.h"
#include "queue.h"

#define ERROR_WHILE_READING -3
#define ERROR_WHILE_WRITING -4
#define SUCCESS 0 

struct matrix{
    int col;
    int lin;
    int *data;
};


/* Reads the dimension from a binary file */
int matrix_bdimension(char* argv, int* col, int* lin){
    FILE* file = fopen(argv, "rb");
    if(!file)
        return ERROR_WHILE_READING;

    fread(lin, sizeof(int), 1, file);
    fread(col, sizeof(int), 1, file);
    
    fclose(file);
    return SUCCESS;
}

/* Reads the dimenson from a text file */
int matrix_dimension(char* argv, int* col, int* lin){
    FILE* file = fopen(argv, "r");
        if(!file)
            return ERROR_WHILE_READING;

    char ch;
    *lin += 1;
    *col += 1;

    while(fscanf(file, "%c", &ch) != EOF){
        if(ch == '\t' && *lin == 1)
            *col += 1;
        if(ch == '\n')
            *lin += 1;
    }

    fclose(file);
    return SUCCESS;
}

/* Allocates an array with cols*rows size after that return it */
Matrix* matrix_create(int col, int lin){
    Matrix* mx = NULL;
    mx = malloc(sizeof(Matrix));
    
    if(!mx)
        return NULL;
    
    mx->data = calloc(lin*col, sizeof(int));

    if(!mx->data)
        return NULL;

    mx->col = col;
    mx->lin = lin;
    return mx;
}


/* Reads data from a binary file and saves it on an array */ 
int matrix_fillwb(Matrix* mx, char* argv){
    if(!mx)
        return -1;
    
    FILE* file = fopen(argv, "rb");
        if(!file)
            return ERROR_WHILE_READING;
        
        fread(&mx->lin, sizeof(int), 1, file);
        fread(&mx->col, sizeof(int), 1, file);
        fread(mx->data, sizeof(int), mx->lin*mx->col, file);

    fclose(file);
    return SUCCESS;
}

/* Reads data from a text file and saves it on an array */
int matrix_fill(Matrix* mx, char* argv){
    if(!mx)
        return -1;

    FILE* file = fopen(argv, "r");
        if(!file)
            return ERROR_WHILE_READING;

        for(int i = 0; i < mx->lin*mx->col; i++)
            fscanf(file, "%d", &mx->data[i]);

    fclose(file);
    return SUCCESS;
}

/* Writes the data of an array on a binary file */
int matrix_to_file(Matrix* mx, char* argv){
    if(!mx)
        return -1;
    
    FILE* file = fopen(argv, "wb");
        if(!file)
            return ERROR_WHILE_WRITING;

    fwrite(&mx->lin, sizeof(int), 1, file);
    fwrite(&mx->col, sizeof(int), 1, file);
    fwrite(mx->data, sizeof(int), mx->lin*mx->col, file);
    
    fclose(file);
    return SUCCESS;
}


/* Makes the threshold of an array data */
int matrix_thresh(Matrix* mx, int thr){
    if(!mx)
        return -1;
    
    for(int i = 0; i < mx->lin*mx->col; i++){
        if(mx->data[i] > thr)
            mx->data[i] = 1;
        else
            mx->data[i] = 0;
    }

    return SUCCESS;    
}


/* Prints the array data */
int matrix_show(Matrix* mx){
    if(!mx)
        return -1;
    
    for(int i = 0; i < mx->lin; i++){
        for(int j = 0; j < mx->col; j++)
            printf("%-3d ", mx->data[(i * mx->col) + j]);
        printf("\n");
    }
    
    return 0;
}

/* Unallocates the array */
int matrix_free(Matrix* mx){
    if(!mx)
        return -1;
    
    free(mx->data);
    free(mx);
    return SUCCESS;
}

/* Verifies the neighborhood of a position in an array */
int matrix_neighborhood(Queue* qu, Matrix* mx, Matrix* mx_rot, Point pc, int i, int j){
    Point p;
    p.x = pc.x+i;
    p.y = pc.y+j;
    if(mx->data[(p.x * mx->col) + p.y] == 1 && mx_rot->data[(p.x * mx->col) + p.y] == 0)
        queue_push(qu, p);
}


/* Verifies the related components in an array */
Matrix* matrix_related(Matrix* mx){
    if(!mx)
        return NULL;
    
    Matrix* mx_rot = matrix_create(mx->col, mx->lin);
    if(!mx_rot)
        return NULL;

    Queue* qu = queue_create();
    if(!qu)
        return NULL;

    int label = 1;
    Point pc;

    for(int i = 0; i < mx->lin; i++){
        for(int j = 0; j < mx->col; j++){
            if(mx->data[(i * mx->col) + j] == 1 && mx_rot->data[(i * mx->col) + j] == 0){
                pc.x = i;
                pc.y = j;
                queue_push(qu, pc);

                while(!queue_empty(qu)){
                    queue_front(qu, &pc);
                    if(mx->data[(pc.x * mx->col) + pc.y] == 1 && mx_rot->data[(pc.x * mx->col) + pc.y] == 0){
                        if(pc.x != 0)
                            matrix_neighborhood(qu, mx, mx_rot, pc, -1, 0);
                        if(pc.x != mx->lin-1)
                            matrix_neighborhood(qu, mx, mx_rot, pc, 1, 0);

                        if(pc.y != 0)
                            matrix_neighborhood(qu, mx, mx_rot, pc, 0, -1);
                        if(pc.y != mx->col-1)
                            matrix_neighborhood(qu, mx, mx_rot, pc, 0, 1);
                    }
                    mx_rot->data[(pc.x * mx->col) + pc.y] = label;
                    queue_pop(qu);
                }
                label++;            
            }
        }
    }
    queue_free(qu);
    return mx_rot;
}


int matrix_walk_in_maze(Stack* st, Matrix* mx, Point pc, int i, int j){
    Point p;
    p.x = pc.x+i;
    p.y = pc.y+j;
    if(mx->data[(p.x * mx->col) + p.y] == 1){
        stack_push(st, p);
        return 1;
    } else 
        return 0;
}


/* Finds the exit of a maze */
int matrix_maze(Matrix* mx){
    if(!mx)
        return -1;

    Stack* st = stack_create();
    if(!st)
        return -1;
    
    Stack* st2 = stack_create();
    if(!st2)
        return -1;

    Point p[2];
    Point atual;
    int c = 0;    
    
    for(int i = 0; i < mx->lin && c < 2; i++){
        for(int j = 0; j < mx->col && c < 2; j++){
            if(i == 0 || i == mx->lin-1 || j == 0 || j == mx->col-1){
                if(mx->data[(i * mx->col) + j] == 1){
                    p[c].x = i;
                    p[c].y = j;
                    c++;
                }
            }
        }
    }

    if(c != 2)
        return -1;
    
    int i = 0;
    atual = p[0];
    mx->data[(atual.x * mx->col) + atual.y] = 2;
    stack_push(st, atual);
    while(atual.x != p[1].x || atual.y != p[1].y){
        i = 0;
        mx->data[(atual.x * mx->col) + atual.y] = 2;
        if(atual.x != 0)
            i += matrix_walk_in_maze(st, mx, atual, -1, 0);
        if(atual.x != mx->lin-1)
            i += matrix_walk_in_maze(st, mx, atual, 1, 0);
        if(atual.y != 0)
            i += matrix_walk_in_maze(st, mx, atual, 0, -1);
        if(atual.y != mx->col-1)
            i += matrix_walk_in_maze(st, mx, atual, 0, 1);

        if(i > 1){
            stack_push(st2, atual);
            for( ; i > 1; i--)
                stack_pop(st);
            stack_top(st, &atual);
        } else if(i == 0){
            stack_top(st2, &p[0]);
            while(atual.x != p[0].x || atual.y != p[0].y){
                mx->data[(atual.x * mx->col) + atual.y] = 3;
                stack_pop(st);
                stack_top(st, &atual);
            }
            stack_pop(st2);
        } else
            stack_top(st, &atual);
        
    }
    mx->data[(atual.x * mx->col) + atual.y] = 2;

    for(int i = 0; i < mx->col*mx->lin; i++){
        if(mx->data[i] > 2)
            mx->data[i] = 1;
    }
    
    free(st2);
    free(st);
    return 0;
}
