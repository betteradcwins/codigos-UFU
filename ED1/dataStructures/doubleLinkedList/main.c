#include <stdio.h>
#include <stdlib.h>
#include "tadlistDL.h"
#include <string.h>

void menu1(void);
void menu2(void);
void student_fill(Student *st);
void show_student(Student st);
void verify_error(int error);

int main(void){
    char choose = '\0';
    int enroll = 0;
    int error = 0;
    int pos = 0;

    List *li = NULL;
    li = list_create();
    Student st;

    while(choose == '\0'){
        menu1();

        printf("\nChoose an option: ");
        setbuf(stdin, NULL);
        scanf("%c", &choose);
        getchar();

        switch (choose){
            case '1':
                student_fill(&st);
                error = list_push_front(li, st);
                verify_error(error);
                printf("\nSize of list is %d\n", list_size(li));
                choose = '\0';;
                break;
            
            case '2':
                student_fill(&st);
                error = list_push_back(li, st);
                verify_error(error);
                printf("\nSize of list is %d\n", list_size(li));
                choose = '\0';
                break;
            
            case '3':
                printf("\nReport a position to insert the student: ");
                setbuf(stdin, NULL);
                scanf("%d", &pos);
                getchar();

                student_fill(&st);
                error = list_insert_position(li, pos, st);
                verify_error(error);
                printf("\nSize of list is %d\n", list_size(li));
                choose = '\0';
                break;
            
            case '4':
                student_fill(&st);
                error = list_insert(li, st);
                verify_error(error);
                printf("\nSize of list is %d\n", list_size(li));
                choose = '\0';
                break;
            
            case '5':
                printf("Do you sure about it? (Y/n) ");
                setbuf(stdin, NULL);
                scanf("%c", &choose);
                getchar();

                if(choose == 'Y' || choose == 'y'){
                    error = list_pop_front(li);
                    verify_error(error);
                    printf("\nSize of list is %d\n", list_size(li));                   
                }
                choose = '\0';
                break;

            case '6':
                printf("Do you sure about it? (Y/n) ");
                setbuf(stdin, NULL);
                scanf("%c", &choose);
                getchar();

                if(choose == 'Y' || choose == 'y'){
                    error = list_pop_back(li);
                    verify_error(error);
                    printf("\nSize of list is %d\n", list_size(li));                   
                }
                choose = '\0';
                break;

            case '7':
                printf("Do you sure about it? (Y/n) ");
                setbuf(stdin, NULL);
                scanf("%c", &choose);
                getchar();

                if(choose == 'Y' || choose == 'y'){
                    printf("\nReport the enroll number: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &enroll);
                    getchar();

                    error = list_remove(li, enroll);
                    verify_error(error);
                    printf("\nSize of list is %d\n", list_size(li));                   
                }
                choose = '\0';
                break;

            case '8':
                printf("Do you sure about it? (Y/n) ");
                setbuf(stdin, NULL);
                scanf("%c", &choose);
                getchar();

                if(choose == 'Y' || choose == 'y'){
                    printf("\nReport the enroll number: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &enroll);
                    getchar();

                    list_get_position(li, enroll, &pos);
                    error = list_eraser(li, pos);
                    verify_error(error);
                    printf("\nSize of list is %d\n", list_size(li));                   
                }
                choose = '\0';
                break;

            case '9':
                list_show(li);
                
                printf("\nPress [ENTER] button to continue");
                setbuf(stdin,NULL);
                scanf("%c", &choose);
                if(choose != '\n')
                    getchar();
            
                choose = '\0';
                break;

            case '0':
                while(choose == '0'){
                    menu2();    

                    printf("\nChoose an option: ");
                    setbuf(stdin, NULL);
                    scanf("%c", &choose);
                    getchar();

                    switch (choose){
                        case '1':
                            printf("\nData about first student in list is\n");
                            error = list_front(li, &st);
                            if(!error)
                                show_student(st);
                            verify_error(error);
                            choose = '0';
                            break;
                        
                        case '2':
                            printf("\nData about last student in list is\n");
                            error = list_back(li, &st);
                            if(!error)
                                show_student(st);
                            verify_error(error);
                            choose = '0';
                            break;
                        
                        case '3':
                            printf("\nReport a position: ");
                            setbuf(stdin, NULL);
                            scanf("%d", &pos);
                            getchar();

                            printf("\nData about the student is\n");
                            error = list_fbp(li, &st, pos);
                            if(!error)
                                show_student(st);
                            verify_error(error);
                            choose = '0';
                            break;
                        
                        case '4':
                            printf("\nReport the enroll number: ");
                            setbuf(stdin, NULL);
                            scanf("%d", &enroll);
                            getchar();

                            printf("\nData about the student is\n");
                            error = list_find(li, &st, enroll);
                            if(!error)
                                show_student(st);
                            verify_error(error);
                            choose = '0';
                            break;
                        
                        case '5':
                            printf("\nSize of list is %d\n", list_size(li));
                            
                            printf("\nPress [ENTER] button to continue");
                            setbuf(stdin,NULL);
                            scanf("%c", &choose);
                            if(choose != '\n')
                                getchar();
                            
                            choose = '0';
                            break;
                        
                        case '6':
                            printf("\nReport the enroll number: ");
                            setbuf(stdin, NULL);
                            scanf("%d", &enroll);
                            getchar();
                            
                            error = list_get_position(li, enroll, &pos);
                            if(!error)
                                printf("\nThis enroll number is %d element in list", pos);
                            verify_error(error);
                            choose = '0';
                            break;
                        
                        case '7':
                            list_show(li);
                    
                            printf("\nPress [ENTER] button to continue");
                            setbuf(stdin,NULL);
                            scanf("%c", &choose);
                            if(choose != '\n')
                                getchar();
                        
                            choose = '0';
                            break;
                        
                        case '0':
                            choose = '\0';
                            break;
                        
                        case 'q':
                            error = list_free(li);
                            verify_error(error);
                            printf("\nGood bye!!\n");
                            return 0;
                            break;

                        default:
                            printf("\n%c is not an option!\n", choose);
                            choose = '0';
                            break;
                    }
                }
                choose = '\0';
                break;

            case 'q':
                error = list_free(li);
                verify_error(error);
                printf("\nGood bye!!\n");
                return 0;
                break;

            default:
                printf("\n%c is not an option!\n", choose);
                choose = '\0';
                break;
        }
    }
    return 0;
}

void menu1(void){
    puts("===============================================");
    puts("             MANAGE A STUDENTS LIST");
    puts("===============================================");
    puts("Options:");
    puts("1 - To insert a student in begin of list");
    puts("2 - To insert a student in end of list");
    puts("3 - To insert a student in a position of list");
    puts("4 - To insert a student in list");
    puts("5 - To remove a student from begin of list");
    puts("6 - To remove a student from end of list");
    puts("7 - To remove a student from list");
    puts("8 - To eraser a student from list");
    puts("9 - To show the list");
    puts("0 - To next page");
    puts("q - To quit");
}

void menu2(void){
    puts("===============================================");
    puts("             MANAGE A STUDENTS LIST");
    puts("===============================================");
    puts("Options:");
    puts("1 - To find a student in begin of list");
    puts("2 - To find a student in end of list");
    puts("3 - To find a student in a position of list");
    puts("4 - To find a student in list");
    puts("5 - To show size of list");
    puts("6 - To get the position of a student");
    puts("7 - To show the list");
    puts("0 - To previous page");
    puts("q - To quit");
}

void student_fill(Student *st){
    puts("\nReport the data of student\n");
    
    printf("Name: ");
    setbuf(stdin,NULL);
    fgets(st->name,sizeof(st->name),stdin);
    st->name[strcspn(st->name, "\n")] = '\0';

    printf("Enroll number: ");
    setbuf(stdin,NULL);
    scanf("%d", &st->enroll_num);
    getchar();

    for(int i = 0; i < 3; i++){
        printf("Grade(%d): ", i+1);
        setbuf(stdin,NULL);
        scanf("%f", &st->grades[i]);
        getchar();
    }

    return;
}

void verify_error(int error){
    char a = '\0';
    
    if(error == 0)
        printf("\nSuccess! no had errors\n");
    else if(error == -1)
        printf("\nOcurred a fail! violed memory\n");
    else if(error == -2)
        printf("\nOcurred a fail! element not found\n");
    
    printf("\nPress [ENTER] button to continue");
    setbuf(stdin,NULL);
    scanf("%c", &a);
    if(a != '\n')
        getchar();
    
    return;
}

void show_student(Student st){
        printf("\nData of student\n");        
        puts("------------------------------------------");
        printf("Name: %s\n", st.name);
        printf("Enroll number: %d\n", st.enroll_num);
        for(int i = 0; i < 3; i++)
            printf("Grade(%d): %.2f\n", i+1, st.grades[i]);
        puts("------------------------------------------");
        printf("\n");
}