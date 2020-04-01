typedef struct list List;
typedef struct node Node;

typedef struct{
    int enroll_num;
    char name[51];
    float grades[3];
}Student;

/*
* list_create - this function allocates a list
* return - list address
* parameters - void
*/
List *list_create(void);

/*
* push_front - this function insert an element in begin of list
* return - 0 to success and -1 to out of memory
* parameters - list address and student struct
*/
int list_push_front(List *li, Student st);

/*
* push_back - this function insert an element in end of list
* return - 0 to success and -1 to out of memory 
* parameters - list address and student struct
*/
int list_push_back(List *li, Student st);

/*
* list_insert_position - this function insert an element in a position of list
* return - 0 to success and -1 to out of memory 
* parameters - list address , int pos and  student struct
*/
int list_insert_position(List *li, int pos, Student st);

/*
* list_insert - this function insert an element in list
* return - 0 to success and -1 to out of memory 
* parameters - list address , student struct
*/
int list_insert(List *li, Student st);

/*
* list_size - this function returns size of list
* return - -1 to error or size of list
* parameters - list address 
*/
int list_size(List *li);

/*
* list_pop_front - this function remove an element from begin of list
* return - -2 to element not found, -1 to memory violed, 0 to success
* parameters - list address 
*/
int list_pop_front(List *li);

/*
* list_show - this function remove an element from end of list
* return - -2 to element not found, -1 to memory violed, 0 to success
* parameters - list address 
*/
int list_pop_back(List *li);

/*
* list_remove - this function remove an element from list
* return - -2 to element not found, -1 to memory violed, 0 to success
* parameters - list address and int enroll number 
*/
int list_remove(List *li, int enroll);

/*
* list_eraser - this function erase an element in a specified position
* parameters - list address and int position number
* return - -2 to element not found, -1 to memory violed, 0 to success
*/
int list_eraser(List *li, int position);

/*
* list_back - this function find the last lits element
* return - -2 to element not found, -1 to memory violed, 0 to success
* parameters - list address and student address
*/
int list_back(List *li, Student *st);

/* list_front - this function find the first list element
* return - -2 to element not found, -1 to memory violed, 0 to success
* parameters - list address and student address
*/
int list_front(List *li, Student *st);

/*
* list_find - this function find an element by enroll number in list
* return - -2 to element not found, -1 to memory violed, 0 to success
* parameters - list address, student address and int enroll number
*/
int list_find(List *li, Student *st, int enroll);

/* 
* list_fbp - this function find an element by position number in list
* parameters - list address, student address and int position number
* return - -2 to element not found, -1 to memory violed, 0 to success
*/
int list_fbp(List *li, Student *st, int position);

/*
* get_postion - this function get the position of an element and return by reference
* return - -2 to element not found, -1 to memory violed, 0 to success
* parameters - address list, int enroll number and int position number
*/
int list_get_position(List *li, int enroll, int *position);

/*
* list_show - this function show elements in list
* return - void
* parameters - list address 
*/
void list_show(List *li);

/*
* list_free - this function unallocates a list
* return - -1 to out of memory or 0 for success
* parameters - list address
*/ 
int list_free(List *li);