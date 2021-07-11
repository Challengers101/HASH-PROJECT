#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>

struct student
{
	char Student_name[100];
    int Student_ID;
    int date[3];                        //in the format dd/mm/yy
	int Student_score_of_last_year;
};
typedef struct student student;     //for convenience

student create_student(char name[], int ID, int day, int month, int year, int score)
{
	// a function to define a student.
	student result;
	strcpy(result.Student_name, name);
	result.Student_ID = ID;
	result.date[0] = day;
	result.date[1] = month;
	result.date[2] = year;
	result.Student_score_of_last_year = score;
	return result;
}

struct Node
{
    student studentD;    //a struct that represent the data of the student in the node
    struct Node *next;   //a pointer to the next node in the list
};
typedef struct Node node;   //for convenience

int const N = 100;  //the size of the chained hash table 
node *chain[10];   //the chained hash table

unsigned int Hash(char *str)
{
    /*
    Polynomial rolling hash function
    hash = (s[0]*P^0 + s[1]*P^1 + s[2]*P^2 + ... + s[n-1]P^(n-1))%m
    s[0], s[1], s[2] … s[n-1] are the values assigned to each character 
    in English alphabet (a=1, b=2, … ,z=26). 
    */
    int p = 53;
    int m = 1e9 + 9;
    unsigned long long hash_val = 0;

    for (int i = 0; i < strlen(str); i++) 
    {
        hash_val = hash_val + (str[i] - 'a' + 1) * pow(p,i);
    }
    hash_val = hash_val%m;

    return hash_val%N; //hash % the number of elemnts in the table
}

void init_array()
{
    /*
    initialize the table
    */
    for(int i = 0; i < N; i++)
        chain[i] = NULL;
}

void insertinhash(student s)
{
    //create a newnode with s
    node *newNode = malloc(sizeof(node));
    newNode->studentD = s;
    newNode->next = NULL;

    //calculate hash key
    int key = Hash(newNode->studentD.Student_name);

    //check if chain[key] is empty
    if(chain[key] == NULL)
        chain[key] = newNode;
    //collision
    else
    {
        //add the node at the end of chain[key].
        node *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

int searchinhash(student s)
{
    int key = Hash(s.Student_name);
    node *temp = chain[key];
    //search in the linked list
    while(temp)
    {
        if(strcmp(temp->studentD.Student_name,s.Student_name) == 0)
            return 1; //if found return 1
        temp = temp->next;
    }
    return 0; //if not found return 0
}

int deleteinhash(student s)
{
    int key = Hash(s.Student_name);
    node *temp = chain[key], *prev;
    if (temp != NULL && strcmp(temp->studentD.Student_name,s.Student_name) == 0) 
    {
        chain[key] = temp->next; // Changed head
        free(temp); // free old head
        return 1;
    }
    while (temp != NULL && strcmp(temp->studentD.Student_name,s.Student_name) != 0) 
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return 0;
    prev->next = temp->next;
 
    free(temp); // Free memory
}

void printhash()
{
    for(int i = 0; i < N; i++)
    {
        node *temp = chain[i];
        printf("chain[%d]-->",i);
        while(temp)
        {
            printf(" %s -->",temp->studentD.Student_name);
            temp = temp->next;
        }
        printf(" NULL\n");
    }
}

void fillhash()
{
    char name[10];
    char shows [] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    int length = strlen(shows);
    for(int i = 0; i<N; i++)
    {
        sprintf(name, "%c%c%c%c", shows[i%length], shows[i^2%length], shows[i^3%length], shows[i^4%length]);
        student s = create_student(name, 406, 23,7,2000, 84);
        insertinhash(s);
    }
}

int main()
{
    
    init_array();
    // student s1 = create_student("mahmoud", 406, 23,7,2000, 84);
    // insertinhash(s1);
    // student s2 = create_student("mohamed", 406, 23,7,2000, 84);
    // insertinhash(s2);
    // student s3 = create_student("ahmed", 406, 23,7,2000, 84);
    // insertinhash(s3);
    // student s4 = create_student("khaled", 406, 23,7,2000, 84);
    // insertinhash(s4);
    // student s5 = create_student("adham", 406, 23,7,2000, 84);
    // insertinhash(s5);
    // student s6 = create_student("abdelrahman", 406, 23,7,2000, 84);
    // insertinhash(s6);
    // printhash();
    // int x = searchinhash(create_student("hbasd", 406, 23,7,2000, 84));
    // printf("\n\n%d\n\n", x);
    // int y = deleteinhash(s6);
    // printf("\n\n%d\n\n", y);
    // printhash();
    fillhash();
    printhash();
    return 0;
}