#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../header/person.h"

int insertPerson(Person person);

Person *createPerson(int id, char *name, char *username, char *password, char *mail, bool isAdmin){
    Person *person = (Person *)malloc(sizeof(Person));
    person->id =id;
    strcpy(person->name, name);
    strcpy(person->username, username);
    strcpy(person->password, password);
    strcpy(person->mail, mail);
    person->isAdmin = isAdmin;
    insertPerson(*person);
    users[userCount] = *person;
    userCount++;
    return person;
}
