#include <stdio.h> // to use printf and scanf
#include <stdlib.h> // to use malloc
#include <string.h> // to use strlen, strcmp, and strcpy

typedef struct {
    char* first_name;
    char* last_name;
    char middle_initial;
    int age;
    int salary;
    long id_num;
} PERSONNEL_REC;


int compare_id_number(PERSONNEL_REC* p1, PERSONNEL_REC* p2){
    
    if (p1->id_num > p2->id_num){
        return 1;

    } else if (p1->id_num < p2->id_num){
        return -1;

    } else {
        return 0;
    }
}

int compare_name(PERSONNEL_REC* p1, PERSONNEL_REC* p2){

    if(strcmp(p1->last_name, p1->last_name) != 0){
        return strcmp(p1->last_name, p1->last_name);
    } else if (strcmp(p1->first_name, p1->first_name) != 0) {
        return strcmp(p1->first_name, p1->first_name);
    } else {
        if (p1->middle_initial > p2->middle_initial){
            return 1;
        } else if (p1->middle_initial < p2->middle_initial) {
            return -1;
        } else {
            return compare_id_number(p1, p2);
        }
    }
}



int main(){

    return 0;
}