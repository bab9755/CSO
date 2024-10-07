#include <stdio.h> // to use printf and scanf
#include <stdlib.h> // to use malloc
#include <string.h> // to use strlen, strcmp, and strcpy

#define FORWARD 0
#define BACKWARD 1
typedef struct  PERSONNEL_REC{
    char* first_name;
    char* last_name;
    char middle_initial;
    int age;
    int salary;
    long id_num;
} PERSONNEL_REC;

typedef struct NODE{
    PERSONNEL_REC* record;
    struct NODE *left, *right;

} NODE;
typedef struct CELL{
    struct CELL *next, *prev;
    PERSONNEL_REC *record;
} CELL;



NODE *name_root, *age_root, *id_root, *salary_root; //the roots of the different trees
CELL *head = NULL;

int compare_id_number(PERSONNEL_REC* p1, PERSONNEL_REC* p2){
    
    if (p1->id_num > p2->id_num){
        printf("%s has higher ID number than %s\n", p1->first_name, p2->first_name);
        return 1;

    } else if (p1->id_num < p2->id_num){
        return -1;
        printf("%s has lower ID number than %s\n", p1->first_name, p2->first_name);
    } else {
        return 0;
    }
}

int compare_name(PERSONNEL_REC* p1, PERSONNEL_REC* p2){

    if(strcmp(p1->last_name, p1->last_name) != 0){
        printf("%s and %s are different\n", p1->last_name, p2->last_name);
        return strcmp(p1->last_name, p1->last_name);
    } else if (strcmp(p1->first_name, p1->first_name) != 0) {
        printf("%s and %s are different\n", p1->first_name, p2->first_name);
        return strcmp(p1->first_name, p1->first_name);
    } else {
        if (p1->middle_initial > p2->middle_initial){
            printf("%s with middle initial %c is greater than %s with middle initial %c\n", p1->first_name, p1->middle_initial, p2->first_name, p2->middle_initial);
            return 1;
        } else if (p1->middle_initial < p2->middle_initial) {
            printf("%s with middle initial %c is smaller than %s with middle initial %c\n", p1->first_name, p1->middle_initial, p2->first_name, p2->middle_initial);
            return -1;
        } else {
            return compare_id_number(p1, p2);
        }
    }
}

int compare_age(PERSONNEL_REC* p1, PERSONNEL_REC* p2){ 
    if(p1->age > p2->age){
        printf("%s is older than %s\n", p1->first_name, p2->first_name);
        return 1;
    } else if (p1->age < p2->age){
        printf("%s is younger than %s\n", p1->first_name, p2->first_name);
        return  -1;
    } else {
        return compare_name(p1, p2);
    }
}

int compare_salary(PERSONNEL_REC* p1, PERSONNEL_REC* p2)
{
    if(p1->salary > p2->salary){
        printf("%s is richer than %s\n", p1->first_name, p2->first_name);
        return 1;
    } else if (p1->salary < p2->salary){
        printf("%s is poorer than %s\n", p1->first_name, p2->first_name);
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
    char* last_name = malloc(10*sizeof(char));
    char* first_name = malloc(10*sizeof(char));
    char middle_initial;
    int age, salary;
    long id_num;

    printf("Enter the records in the following order: (first_name last_name, middle_initial age salary id_num): \n");
    

    printf("Input: ");

    int inputs = scanf("%99s %99s %c %d %d %ld", last_name, first_name, &middle_initial, &age, &salary, &id_num);
    if (inputs != 6){
        printf("There were one or more missing arguments in your input, stopping to read...\n");
        return NULL;
    }


    
    PERSONNEL_REC* record = malloc(sizeof(PERSONNEL_REC));
    record = new_record(first_name, last_name, middle_initial, age, salary, id_num);

    printf("You created a new record with first name %s and id number %ld: \n", first_name, id_num);

    return record;
}

void print_record(PERSONNEL_REC* personnel){
    printf("This is the personal information about Personnel with ID number %ld: \n", personnel->id_num);
    printf("First Name: %s \n Last Name: %s \n Middle Initial: %c \n Age: %d \n Salary: %d \n", personnel->first_name, personnel->last_name, personnel->middle_initial, personnel->age, personnel->salary);
}

void insert_personnel_record(NODE** root, PERSONNEL_REC* record, int (*fun_ptr)(PERSONNEL_REC*, PERSONNEL_REC*)){
    if ((*root)){
        printf("The current root is personenl with name %s\n", (*root)->record->first_name);
    } else{
        printf("The current tree is empty\n");
    }
    
    printf("CURRENT ENTIRING THE RECORD FOR %s\n", record->first_name);

    NODE* node = malloc(sizeof(NODE)); //this is what is being inserted into the tree
    node->record = malloc(sizeof(PERSONNEL_REC));
    memcpy(node->record, record, sizeof(PERSONNEL_REC));
    if (!(*root)){ //if the tree is empty set the new node to the root
        *root = node;
        printf("CURRENT RECORD FOR %s SAVED AS ROOT OF THE TREE.\n", (*root)->record->first_name);
        return;
    }
    NODE* current_node = malloc(sizeof(NODE)); //we keep a current node variable which is going to be initialized as the root
    
    current_node = *root;
    while (1){
        printf("CURRENT NODE IS %s\n", current_node->record->first_name);
        if (fun_ptr(current_node->record, node->record) > 0){ //checking if our key is smaller than our current node
            if(!current_node->left) { //check if the left of the current node is vacant
                printf("INSERTING %s ON THE LEFT OF %s\n", node->record->first_name, current_node->record->first_name);
                current_node->left = node; //insert our node there and exit
                break;
            } else {
                current_node = current_node->left; //otherwise set that left node as our current node
            }
        } else if (fun_ptr(current_node->record, node->record) < 0){ // else check if our key is greater than the current ndoe
            if(!current_node->right) { //check the right and insert the node accordingly or keep the right node as our current node.
            printf("INSERTING %s ON THE RIGHT OF %s\n", node->record->first_name, current_node->record->first_name);
                current_node->right = node;
                break;
            } else {
                current_node = current_node->right;
            }
        }

    }
    printf("added %s to a tree\n", node->record->first_name);

}

void traverse_and_print_records(NODE** root){
    if(!(*root) || !(*root)->record){ //base case
        return;
    }
    traverse_and_print_records(&((*root)->left)); // recursively traverse the left tree
    print_record((*root)->record); //print the current record
    traverse_and_print_records(&((*root)->right)); //recursively traverse the right tree

}


void insert_record_in_list(PERSONNEL_REC* record){
    printf("Currently processing list entry for %s\n", record->first_name);
    CELL* new_cell =  malloc(sizeof(CELL));
    new_cell->record = malloc(sizeof(PERSONNEL_REC));
    memcpy(new_cell->record, record, sizeof(PERSONNEL_REC));
    
    //init the current cell to the head of the list

    
    
    
    if (!head) {
        head = new_cell;
        head->next = head;
        head->prev = head;
        printf("The head was empty. Setting %s as the head.\n", record->first_name);
        return;
    } else {

        CELL* last = head->prev;
        new_cell->next = head;
        new_cell->prev = last;
        last->next = new_cell;
        head->prev = new_cell;
        printf("Inserted %s at the end of the list.\n", record->first_name);
        
    }
    
}

void insert_from_tree_into_list(NODE** root){


    if(!(*root) || !(*root)->record){ //base case
        return;
    }
    insert_from_tree_into_list(&((*root)->left)); // recursively traverse the left tree
    insert_record_in_list((*root)->record); //insert the given record into a tree
    insert_from_tree_into_list(&((*root)->right)); //recursively traverse the right tree

}

void print_list(int direction) {
    

    if (!head) {
        printf("List is empty.\n");
        return;
    }

    CELL* current = (direction == FORWARD) ? head : head->prev;
    do {
        print_record(current->record);
        current = (direction == FORWARD) ? current->next : current->prev;
    } while (current != ((direction == FORWARD) ? head : head->prev));
    
}

void print_n_records(int n){
    if (!head){
        printf("The list is empty, cannot print records.\n");
        return;
    }
    CELL* current = head;
    int counter = n;
    do {
        print_record(current->record);
        counter--;
        current = current->next;

    } while (current != head && counter);
}


int main(){
    while(1) {
        //create a new record from the command line
        PERSONNEL_REC* record = malloc(sizeof(PERSONNEL_REC));
        record = read_record();

        if (!record) {
            printf("No record was saved, exiting input entry.\n");
            break;
        }
        //insert into the name tree
        insert_personnel_record(&name_root, record, compare_name);
        //insert into age tree
        insert_personnel_record(&age_root, record, compare_age);
        //insert into id tree
        insert_personnel_record(&id_root, record, compare_id_number);
        //insert into salary tree
        insert_personnel_record(&salary_root, record, compare_salary);
        //free the mememoy to start from scratch at the next iteration of the loop
        free(record);
        printf("===================================================================\n");

    }
        printf("SORTED BY NAME:\n");
        traverse_and_print_records(&name_root);
        printf("===================================================================\n");
        printf("SORTED BY AGE:\n");
        traverse_and_print_records(&age_root);
        printf("===================================================================\n");
        printf("SORTED BY ID:\n");
        traverse_and_print_records(&id_root);
        printf("===================================================================\n");
        printf("SORTED BY SALARY:\n");
        traverse_and_print_records(&salary_root);
        printf("===================================================================\n");

        printf("INSERTING THE RECORDS INTO THE DOUBLY LINKED LIST.\n");
        insert_from_tree_into_list(&name_root);
        printf("===================================================================\n");

        printf("PRINTING LIST IN THE FORWARD DIRECTION\n");
        print_list(FORWARD);
        printf("===================================================================\n");

        printf("PRINTING LIST IN THE BACKWARD DIRECTION:\n");
        print_list(BACKWARD);
        printf("===================================================================\n");

        printf("PRINTING THE FIRST 120 RECORDS\n");
        print_n_records(120);
        printf("===================================================================\n");
    return 0;
}