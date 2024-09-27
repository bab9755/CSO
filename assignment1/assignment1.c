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

int compare_age(PERSONNEL_REC* p1, PERSONNEL_REC* p2){ 
    if(p1->age > p2->age){
        return 1;
    } else if (p1->age < p2->age){
        return  -1;
    } else {
        return compare_name(p1, p2);
    }
}

int compare_salary(PERSONNEL_REC* p1, PERSONNEL_REC* p2)
{
    if(p1->salary > p2->salary){
        return 1;
    } else if (p1->salary < p2->salary){
        return  -1;
    } else {
        return compare_name(p1, p2);
    }
}

PERSONNEL_REC* new_record(char* first_name, char* last_name, char middle_initial, int age, int salary, long id_num){
    PERSONNEL_REC* record = malloc(sizeof(PERSONNEL_REC));
    record->first_name = malloc((strlen(first_name) + 1) * sizeof(char)); // Allocate memory for first_name
    record->last_name = malloc((strlen(last_name) + 1) * sizeof(char));   // Allocate memory for last_name
    strcpy(record->first_name, first_name); // Copy first_name into allocated memory
    strcpy(record->last_name, last_name);   // Copy last_name into allocated memory
    record->age = age;
    record->salary = salary;
    record->middle_initial = middle_initial;
    record->id_num = id_num;

    return record;
    

}


PERSONNEL_REC* read_record(){
    char* last_name = malloc(100*sizeof(char));
    char* first_name = malloc(100*sizeof(char));
    char middle_initial;
    int age, salary;
    long id_num;

    printf("Enter the records in the following order: (first_name last_name, middle_initial age salary id_num): \n");
    
    while (1){
        printf("Input: ");
        if(scanf("%99s %99s %c %d %d %ld", last_name, first_name, &middle_initial, &age, &salary, &id_num) != 6){
            break;
        }
    }
    PERSONNEL_REC* record = malloc(sizeof(PERSONNEL_REC));
    record = new_record(first_name, last_name, middle_initial, age, salary, id_num);

    printf("You created a new record with first name %99s and id number %ld: ", first_name, id_num);

    return record;
}


int main(){
    read_record();
    return 0;
}