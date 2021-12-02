#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
// ONLY STAFF IS ALLOWED TO MODIFY, ADD, AND DELETE FILE, OTHERS ARE ONLY AVAILABLE FOR CHECKING DISPLAY
void projectMenu(int power);

//color function
void green();
void red();
void reset();
void cyan();
void darkGreen();
void underlineGreen();
void blue();
void underlineBlue();
void purple();
void yellow();

void main()
{
	int position;
	int power=0; // STAFF ALLOWED TO MODIFY, ADD, AND DELETE AFTER LOGIN

	logo();

	printf("\n\n\n\n%-60s1. Student\n\n\n%-60s2. Staff\n\n\n%-60s3. Others","","","");

	printf("\n\n\n\n\n%-60sSelect your Position > ","");
	scanf("%d", &position);
	system("CLS");

	if (position == 2) {
		loginSystem();
		power = 1;
	}
	loading();
	projectMenu(power);

	system("pause");
}

void projectMenu(int power)
{
	int option;
	char optionToContinue;

	underlineGreen();
	gotoXY(70, 2);
	printf(" MAIN MENU \n\n","");
	green();
	printf("\n%-65s1. Visitor Information\n\n\n%-65s2. Venue Information\n\n\n%-65s3. Adminstrative Staff \n\n\n%-65s4. Visits and Exits\n\n\n%-65s5. Sanitization Records\n\n\n%-65s6. Exit\n\n\n\n\n","","","","","","");
	
	yellow();
	printf("%65sYour option >[ ]\b\b","");
	scanf("%d", &option);

	while (option > 6 || option < 0) {
		red();
		printf("Invalid option. Please enter again.\n");
		printf("%-70sYour option >[ ]\b\b","");
		scanf("%d", &option);
	}
	do {
		system("CLS");
		switch (option) {

		case 1:
			visitorSystem(power);
			system("CLS");
			break;

		case 2:
			venueSystem(power);
			system("CLS");
			break;

		case 3:
			if (power == 1) {
				staffSystem();
				system("CLS");
				break;
			}
			else {
				red();
				printf("You are not allowed to go in staff system");
				reset();
				break;
			}

		case 4:
			visitAndExitSystem(power);
			system("CLS");
			break;

		case 5:
			sanitizationSystem(power);
			system("CLS");
			break;

		case 6:
			printf("Thank you for using our program.");
			exit(-1);
			system("pause");

		default:
			red();
			printf("Error, please type again your choice.");
		}

		printf("\n\n\n\n\n\n\n\n%-60sDo you want to continue to Main Menu? (Y/N) >","");
		rewind(stdin);
		scanf("%c", &optionToContinue);
		system("CLS");

		if (optionToContinue == 'Y' || optionToContinue == 'y') {
			underlineGreen();
			gotoXY(70, 2);
			printf(" MAIN MENU \n\n", "");
			green();
			printf("\n%-65s1. Visitor Information\n\n%-65s2. Venue Information\n\n%-65s3. Adminstrative Staff \n\n%-65s4. Visits and Exits\n\n%-65s5. Sanitization Records\n\n%-65s6. Exit\n\n\n", "", "", "", "", "", "");

			printf("\n%-70sYour option >[ ]\b\b", "");
			scanf("%d", &option);
		}
		else
			printf("Thank you for using our program.");

	} while (optionToContinue == 'Y' || optionToContinue == 'y');
}

void green()
{
	printf("\033[0;32m");
}

void red()
{
	printf("\033[0;31m");
}

void reset()
{
	printf("\033[0;30m");
}

void cyan()
{
	printf("\033[1;36m");
}

void darkGreen()
{
	printf("\033[1;32m");
}

void underlineGreen()
{
	printf("\033[4;32m");
}

void blue()
{
	printf("\033[0;94m");
}

void underlineBlue()
{
	printf("\033[4;94m");
}

void purple()
{
	printf("\033[0;35m");
}

void yellow()
{
	printf("\033[1;34m");
}
