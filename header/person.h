#ifndef PERSON_H
#define PERSON_H

typedef struct Person
{
    int id;
    char name[30];
    char username[30];
    char password[30]; 
    char mail[50];   
    bool isAdmin;      
}Person;

Person *createPerson(int id, char *name, char *username, char *password, char *mail, bool isAdmin);


#endif