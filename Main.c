#define _CRT_SECURE_NO_WARNINGS 1 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
enum commands {DISPLAY = 1, QUIT = 0, ADD = 2};

typedef struct {
	int index;
	char* First_name;
	char* Last_name;
} Student;
//Globals
char data_file[MAX_SIZE] = "data.dat";
int students_max_count = 100;
int students_act_count = 0;
int index_buffer;
char First_name_buffer[256];
char Last_name_buffer[256];
Student **students;
//Function declarations
void displayCommands();
void read_students_from_file(char* path);
void add_student(int,char*,char*);
void display_students();

//Main function
int main() {

	char enteredValue[999];
	int thisCommand;
	int running = 1;
	read_students_from_file(data_file);
	while(running) {
		displayCommands();
		scanf("%s", enteredValue);
		thisCommand = atoi(enteredValue);
		puts("\n----------------------------------------------");
		switch(thisCommand) {
		case DISPLAY:
			display_students();
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
	printf("%d - DISPLAY STUDENTS.\n", DISPLAY);
	printf("%d - ADD STUDENT.\n", ADD);
	printf("%d - QUIT.\n", QUIT);
	puts("----------------------------------------------");
}
void add_student(int index, char* First_name, char* Last_name)
{
	int i = 0;
	FILE *fp = NULL;
	for(i=0;i<students_act_count;i++)
	{
		if(students[i]->index == index)
		{
			printf("Already exist");
			return;
		}
	}
	if ((fopen_s(&fp,data_file,"r+"))) {
		printf ("Error in opening file: %s!\n", data_file);
		getchar();
		return ;
	}
	if(fp != NULL) {
		students[students_act_count] = (Student*)malloc(sizeof(Student));
		students[students_act_count]->index = (int)malloc(sizeof(int));
		students[students_act_count]->index = index;
		students[students_act_count]->First_name = (char*)malloc(strlen(First_name)+1);
		strcpy(students[students_act_count]->First_name, First_name);
		students[students_act_count]->Last_name = (char*)malloc(strlen(Last_name)+1);
		strcpy(students[students_act_count]->Last_name, Last_name);
		students_act_count++;
		rewind(fp);
		fprintf(fp,"%d",students_act_count);
		fseek(fp,0,SEEK_END);
		fprintf(fp,"\n%d %s %s", index, First_name, Last_name);
		fclose(fp);
	}
}
void read_students_from_file(char* path) {
	int i = 0;
	int studentCount = 0;
	FILE *fp = NULL;
	if ((fopen_s(&fp,path,"r"))) {
		printf ("Error in opening file: %s!\n", path);
		getchar();
		return ;
	}
	if(fp != NULL) {
		fscanf(fp, "%d", &studentCount);
		students = (Student**)malloc(students_max_count* sizeof(Student*));
		while(students_act_count != studentCount)
		{
			if(students_act_count == students_max_count-1)
			{
				printf("Limit reached");
				fclose(fp);
				return;
			}
			students[students_act_count] = (Student*)malloc(sizeof(Student));
			fscanf(fp, "%d %s %s", &index_buffer, First_name_buffer, Last_name_buffer);
			students[students_act_count]->index = (int)malloc(sizeof(int));
			students[students_act_count]->index = index_buffer;
			students[students_act_count]->First_name = (char*)malloc(strlen(First_name_buffer)+1);
			strcpy(students[students_act_count]->First_name, First_name_buffer);
			students[students_act_count]->Last_name = (char*)malloc(strlen(Last_name_buffer)+1);
			strcpy(students[students_act_count]->Last_name, Last_name_buffer);
			students_act_count++;
		}
		fclose(fp);
	} else {
		puts("Unable to open file for reading!");
	}
}
void display_students(){
	int i=0;
	for(i=0; i<students_act_count; i++)
		printf("%d %s %s\n",students[i]->index,students[i]->First_name, students[i]->Last_name);
}

// testing line for github
