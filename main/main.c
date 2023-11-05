#include <stdio.h>
#include <stdlib.h>
#include "../src/database.c"
#include "../src/person.c"
#include "../src/topic.c"
#include "../src/vote.c"

int main() {
    /*Person admin = createPerson(0,"Zahid" , "zahid", "zahidesad","zahid@gmail.com",true);              
    Person user = createPerson(1,"Emirhan" , "emirhan", "emirhansoylu","emirhan@gmail.com",false);
    */
    readPerson();
    printf("Name of admin : %s\n",users[0].name);

    printf("ID of user : %d\n",users[1].id);
    printf("Name of user : %s\n",users[1].name);
    printf("Username of user : %s\n",users[1].username);
    printf("Mail of user : %s\n",users[1].mail);

    printf("User count : %d\n" , userCount);

    
    
    
    

    return 0;
}