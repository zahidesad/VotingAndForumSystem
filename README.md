1) Aim of the project 
This project represents an interactive voting system between administrators and users. In this system, administrators can create various topic titles, categorize them, and enable users to vote by adding specific options. Users can register, update their profile information, and cast votes on designated topic titles.

2)	Program Structs and Relationships

  2.1) The main purpose of use of person struct:
- The person struct represents users in OOP way. Admin and users’ information holds in person struct.

  2.2) The main purpose of use of topic struct:
- Topics represent topics in the system to vote on. This structure holds all topics information.
- Topics have categories. When a topic is created, it must be placed under a category.

  2.3) The main purpose of use of vote struct:
- It was created to keep the votes given to the topics.
- This structure also holds a person (voter) and topic.

  2.4) The main purpose of use of “database.c” file: 
- This file manages all file API integrations (Read, Write, Update, Delete).




3)	Rules

Initially, 1 admin, 2 users, 6 topics and 0 votes are defined in the system by default. You can access the user information from the person.txt file.

1)	Admin Rules

1.1)	Admin can create topics.

1.2)	Admin can close topic. The voting process ends when a topic is closed by the admin.

1.3)	Admin can also make a topic open again.

1.4)	Admin can update topic information.

1.5)	Admin can delete topic. When a topic is deleted, all votes for that topic are also deleted.

1.6)	Admin can see how many votes were cast for which option and their percentages.

1.7)	Admin can see all user information.

1.8)	Admin can delete users. When a user is deleted, his/her votes are also deleted from the system.

2)	Users Rules

2.1)      User can vote.

2.2)      User can see how many votes were cast for which option and their percentages.

2.3)      User can update his/her own information.
