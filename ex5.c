/*
ranit delevkovitz
205781701
83-120-03
ex5
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

struct Person {
	char *name;
	char id;
	int kids;
	char **kidsName;
	struct Person*next;
}
typedef Person;

/*
Function name: Clean
Input: person1 in type of struct person
Output: free the dynamic assignments
The function operaion: for all the person free all the string we made with dynamic assignments and than free the struct
*/
void Clean(Person* person1)
{
	int i;
	Person* temp;
	Person* nextPerson;
	//while we didnt reach to the last one
	while (person1->next != person1)
	{
		//copy the pointer to the next person
		temp = person1->next;
		nextPerson = temp->next;
		//free the name and the kids
		free(temp->name);
		for (i = 0; i < temp->kids; i++)
			free(temp->kidsName[i]);
		//if there is any kids
		if (temp->kids > 0)
			free(temp->kidsName);
		free(temp);
		person1->next = nextPerson;
	}
	//if we reach to the last person left in the game
	free(person1->name);
	for (i = 0; i < person1->kids; i++)
		free(person1->kidsName[i]);
	//if he has kids free their dynamic assignment
	if (person1->kids > 0)
		free(person1->kidsName);
	free(person1);
}
/*
Function name: FaildName
Input: person1 in type of struct person
Output: free the dynamic assignments
The function operaion: if the dynamic assignments of the name fail the function free his struct
*/
void FaildName(Person* person1)
{
	free(person1);
}
/*
Function name: FaildKidsPointer
Input: person1 in type of struct person
Output: free the dynamic assignments
The function operaion: if the dynamic assignments of the strings of pointers to the kids
fail the function free the person name and struct
*/
void FaildKidsPointer(Person* person1)
{
	free(person1->name);
	free(person1);
}
/*
Function name: FaildKidsName
Input: person1 in type of struct person,place i
Output: free the dynamic assignments
The function operaion: if the dynamic assignments of the kids string fail the function free the person name,
the pointers string of the kids and his struct
*/
void FaildKidsName(Person* person1, int i)
{
	while (i != 0)
		free(person1->kidsName[i]);
	free(person1->kidsName);
	free(person1->name);
	free(person1);
}

/*
Function name: InputName
Input: string msg
Output: name of person\kid
The function operaion: gets name from the user, and puts in dynamic assignments
*/
char*InputName(char msg[])
{
	printf("%s", msg);
	char buffer[80];
	//asks for name
	scanf("%s", buffer);
	char*name = (char*)malloc(strlen(buffer) + 1 * (sizeof(char)));
	//if the dynamic assignment faild
	if (name == NULL)
	{
		Clean(name);
		exit(1);
	}
	//copy the string to the person name
	strcpy(name, buffer);
	return name;
}
/*
Function name: NewPerson
Input: person * head
Output: person1 type of struct Person
The function operaion: the function build new struct in person1
*/
Person* NewPerson(Person*head)
{
	int i;
	char str[20];
	char buffer[80];
	Person*person1 = (Person*)malloc(sizeof(Person));
	//if the dynamic assignment faild
	if (NULL == person1)
	{
		Clean(head);
		exit(1);
	}
	//get the person name,id and num of kids
	printf("name:\n");
	scanf("%s", buffer);
	person1->name = (char*)malloc(strlen(buffer) + 1 * (sizeof(char)));
	//if the dynamic assignment faild
	if (person1->name == NULL)
	{
		FaildName(person1);
		Clean(head);
		exit(1);
	}
	//copy the string to the person name
	strcpy(person1->name, buffer);
	printf("id:\n");
	scanf("%d", &person1->id);
	printf("num of kids:\n");
	scanf("%d", &person1->kids);
	if (person1->kids == 0)
		person1->kidsName = NULL;
	else
		//if there are kids build a string for their names
	{
		person1->kidsName = (char**)malloc(sizeof(char*)*(person1->kids));
		if (NULL == person1->kidsName)
		{
			FaildKidsPointer(person1);
			Clean(head);
			exit(1);
		}
		//get the kids names
		for (i = 0; i < person1->kids; i++)
		{
			printf("kid number %d name:\n", i + 1);
			//asks for name
			scanf("%s", buffer);
			person1->kidsName[i] = (char*)malloc(strlen(buffer) + 1 * (sizeof(char)));
			if (person1->kidsName[i] == NULL)
			{
				FaildKidsName(person1, i);
				Clean(head);
				exit(1);
			}
			//copy the string to the person name
			strcpy(person1->kidsName[i], buffer);
		}
	}
	//define the next person null 
	person1->next = NULL;
	return person1;
}
/*
Function name: FirstPerson
Input: nothing
Output: person1 type of struct Person
The function operaion: the function build new struct for the first person
*/
Person* FirstPerson()
{
	int i;
	char str[20];
	char buffer[80];
	Person*person1 = (Person*)malloc(sizeof(Person));
	//if the dynamic assignment faild
	if (NULL == person1)
		exit(1);
	//get the person name,id and num of kids
	printf("name:\n");
	scanf("%s", buffer);
	person1->name = (char*)malloc(strlen(buffer) + 1 * (sizeof(char)));
	//if the dynamic assignment faild
	if (person1->name == NULL)
	{
		FaildName(person1);
		exit(1);
	}
	//copy the string to the person name
	strcpy(person1->name, buffer);
	printf("id:\n");
	scanf("%d", &person1->id);
	printf("num of kids:\n");
	scanf("%d", &person1->kids);
	if (person1->kids == 0)
		person1->kidsName = NULL;
	else
		//if there are kids build a string for their names
	{
		person1->kidsName = (char**)malloc(sizeof(char*)*(person1->kids));
		if (NULL == person1->kidsName)
		{
			FaildKidsPointer(person1);
			exit(1);
		}
		//get the kids names
		for (i = 0; i < person1->kids; i++)
		{
			printf("kid number %d name:\n", i + 1);
			//asks for name
			scanf("%s", buffer);
			person1->kidsName[i] = (char*)malloc(strlen(buffer) + 1 * (sizeof(char)));
			if (person1->kidsName[i] == NULL)
			{
				FaildKidsName(person1, i);
				exit(1);
			}
			//copy the string to the person name
			strcpy(person1->kidsName[i], buffer);
		}
	}
	//define the next person null 
	person1->next = NULL;
	return person1;
}
/*
Function name: InitTheHungerGame
Input: nothing
Output: the first person in type of Person struct
The function operaion: the funcion asks the user for persons and send them to NewPerson function
*/
Person* InitTheHungerGame()
{
	int choise;
	Person*head = NULL;
	Person*tail = NULL;
	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &choise);
	//if the user want to add the first person 
	if (choise == 1)
	{
		head = FirstPerson();
		tail = head;
	}
	else
		return head;
	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &choise);
	//if the user want to add another person get in the loop
	while (choise == 1)
	{
		//init the next person and define him to be the last ine
		tail->next = NewPerson(head);
		tail = tail->next;
		printf("Add a person to the game? 1 for yes, 0 for no\n");
		scanf("%d", &choise);
	}
	//make a pointer from the last person to the first person
	tail->next = head;
	return head;
}
/*
Function name: KillPerson
Input: person1 and head int type of strct Person
Output: the next person
The function operaion: the funcion free all the dynamic assignment and move hes pointer to the killer
*/
Person*KillPerson(Person*person1, Person*head)
{
	int i;
	Person*temp = person1->next;
	//print who kills who
	printf("%s kills %s ", head->name, person1->name);
	//free the kiled name and if he has kids free them too
	free(person1->name);
	for (i = 0; i < person1->kids; i++)
	{
		printf("and %s ", person1->kidsName[i]);
		free(person1->kidsName[i]);
	}
	printf("\n");
	if (person1->kids > 0)
		free(person1->kidsName);
	//free the struct
	free(person1);
	return temp;
}
/*
Function name: LetTheHungerGameBegin
Input: head type of Person struct
Output: head
The function operaion: the function start from the head and kill his right person,
than the bext person after the killes became the head
*/
Person*LetTheHungerGameBegin(Person*head)
{
	if (head == NULL)
		return NULL;
	//while the next person isnt himself kill the right neighbours
	while (head->next != head)
	{
		head->next = KillPerson(head->next, head);
		head = head->next;
	}
	return head;
}
 int main()
 {
 //define the first person and the winner
 Person*head = NULL;
 Person*winner = NULL;
 head = InitTheHungerGame();
 winner = LetTheHungerGameBegin(head);
 //if the user didnt play return 0
 if (winner == NULL)
 return 0;
 printf("%s stayin alive!!\n", winner->name);
 //clean the dynamic assignment of the winner
 Clean(winner);
 return 0;
 }