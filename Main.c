#define _CRT_SECURE_NO_WARNINGS 1 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
enum commands {READ_LIST = 1, QUIT = 0, ADD = 2};

typedef struct {
	int index;
	char* First_name;
	char* Last_name;
} Student;

//Globals
int studentCount = 0;
char data_file[MAX_SIZE] = "data.dat";
int index_buffer;
char First_name_buffer[256];
char Last_name_buffer[256];
Student **students;
//Function declarations
void displayCommands();
void readList();
void add_student(int,char*,char*);

//Main function
int main() {

	char enteredValue[999];
	int thisCommand;
	int running = 1;
	while(running) {
		displayCommands();
		scanf("%s", enteredValue);
		thisCommand = atoi(enteredValue);
		puts("\n----------------------------------------------");
		switch(thisCommand) {
		case READ_LIST:
			readList();
			break;
		case QUIT:
			running = 0;
			break;
		case ADD:
			scanf("%d%s%s",&index_buffer,First_name_buffer,Last_name_buffer);
			add_student(index_buffer,First_name_buffer,Last_name_buffer);
			break;
		default:
			puts("Wrong command!");
			break;
		}
	}
	system("pause");
	return 0;
}

void displayCommands() {
	puts("\n---------------------------------------------");
	puts("Enter a command number:");
	printf("%d - READ STUDENTS FROM FILE.\n", READ_LIST);
	printf("%d - ADD STUDENT.\n", ADD);
	printf("%d - Quit.\n", QUIT);
	puts("----------------------------------------------");
}
void add_student(int index, char* First_name, char* Last_name)
{
	int i = 0;
	FILE *fp = NULL;
	if ((fopen_s(&fp,data_file,"a+"))) {
		printf ("Error in opening file: %s!\n", data_file);
		getchar();
		return ;
	}
	if(fp != NULL) {
		fscanf(fp, "%d", &studentCount);
		for(i=0;i<studentCount;i++)
		{
			fscanf(fp, "%d %s %s", &index_buffer, First_name_buffer, Last_name_buffer);
				if(index_buffer == index)
				{
					printf("Already exist");
					return;
				}
		}
		fprintf(fp,"\n%d %s %s", index, First_name, Last_name);
		studentCount++;
		fseek (fp, 0, SEEK_SET);
		fprintf(fp,"%d",studentCount);
		fclose(fp);
	}
}
void readList() {
	int i = 0;
	int counter = 0;
	FILE *fp = NULL;
	if ((fopen_s(&fp,data_file,"a+"))) {
		printf ("Error in opening file: %s!\n", data_file);
		getchar();
		return ;
	}
	if(fp != NULL) {
		fscanf(fp, "%d", &studentCount);
		students = (Student**)malloc(studentCount * sizeof(Student*));
		while(counter != studentCount)
		{
			students[counter] = (Student*)malloc(sizeof(Student));
			fscanf(fp, "%d %s %s", &index_buffer, First_name_buffer, Last_name_buffer);
			students[counter]->index = (int)malloc(sizeof(int));
			students[counter]->index = index_buffer;
			students[counter]->First_name = (char*)malloc(strlen(First_name_buffer)+1);
			strcpy(students[counter]->First_name, First_name_buffer);
			students[counter]->Last_name = (char*)malloc(strlen(Last_name_buffer)+1);
			strcpy(students[counter]->Last_name, Last_name_buffer);
			counter++;
		}
		fclose(fp);
		for(i=0; i<studentCount; i++)
			printf("%d %s %s\n",students[i]->index,students[i]->First_name, students[i]->Last_name);
	} else {
		puts("Unable to open file for reading!");
	}
}