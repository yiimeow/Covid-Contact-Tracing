#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#pragma warning (disable : 4996)

struct Name
{
	char surName[10], lastName[11];
};

struct ID
{
	char dept;
	int number;
};

typedef struct
{

	char position[11], faculty[5], password[7], contactNumber[13], email[15];
	struct Name name;
	struct ID id;

}Staff;

// 210 * 7
#define MAX_NUMBER 1470 
#define ADMIN_DEPT 'Z'
#define ADMIN_NUMBER 100
#define ADMIN_PSW "ABCDEF"

void addStaff();
void displayList1();
void displayList2();
void displayList3();
void displayList4();
void displayList5();
void modifyStaff();
void deleteStaff();
void loginSystem();
void search();

void sample();

// display Function

void displayDetails(int a, int b);

//Menu
void displayMenu();
void facultyMenu();


//validation
int checkContactNumber(char contactNum[13]);
int checkID(char dept, int number);
int checkEmail(char checkEmail[11]);


//design
void loading();
void line();
void line2(int number);
void cornerTopLeft();
void cornerTopRight();
void connectionRight();
void connectionLeft();
void connection1();
void connection2();
void connection3();
void cornerBotomLeft();
void cornerBotomRight();

void space(int number);
void logo();

//table
void displayHeading();
void displayEnd(int a);


int staffReadFile(Staff displayFaculty[MAX_NUMBER]);

/*
	A	=	Faculty of Social Science and Humanities (FSSH)
	B	=	Faculty of Applied Sciences (FOAS)
	C	=	Faculty of Computing and Information Technology (FOCS)
	D	=	Faculty of Accountancy, Finance & Business (FAFB)
	E	=	Faculty of Engineering and Technology (FOET)
	F	=	Faculty of Built Environment (FOBE)
	G	=	Faculty of Communication and Creative Industries (FCCI)
*/

/*
	ID			: Z100
	PASSWORD	: ABCDEF
*/
void staffSystem()
{
	int selection;
	char thank[20] = "T h a n k   y o u .";
	do
	{
		space(30);
		cornerTopLeft();
		line2(41);
		cornerTopRight();
		printf("\n");

		space(30);
		line();
		printf("                Main Menu                ");
		line();
		printf("\n");

		space(30);
		connectionLeft();
		line2(41);
		connectionRight();
		printf("\n");

		space(30);
		line();
		printf("            1. Add Staff                 ");
		line();
		printf("\n");

		space(30);
		line();
		printf("            2. Display Staff             ");
		line();
		printf("\n");

		space(30);
		line();
		printf("            3. Modify Staff              ");
		line();
		printf("\n");

		space(30);
		line();
		printf("            4. Delete Staff              ");
		line();
		printf("\n");

		space(30);
		line();
		printf("            5. Search Staff              ");
		line();
		printf("\n");


		space(30);
		line();
		printf("            0. Exit                      ");
		line();
		printf("\n");

		space(30);
		cornerBotomLeft();
		line2(41);
		cornerBotomRight();
		printf("\n");

		space(30);
		printf("Enter Selection > ");
		scanf("%d", &selection);

		system("CLS"); //clear UI

		if (selection == 1)
		{
			addStaff();
		}
		else if (selection == 2)
		{
			displayMenu();
		}
		else if (selection == 3)
		{
			modifyStaff();
		}
		else if (selection == 4)
		{
			deleteStaff();
		}
		else if (selection == 5)
		{
			search();
		}
		else if (selection == 0)
		{
			printf("\n\n\n");
			space(40);
			srand(time(NULL));
			for (int a = 0; a < 20; a++)
			{
				printf("\033[0;3%dm", rand() % 6 + 1);
				printf("%c", thank[a]);
			}
			reset();
			printf("\n\n\n");
			system("pause");
		}
		else
			printf("Error, Please Try Again\n");

		system("CLS");

	} while (selection != 0);
}


void sample()
{
	printf("\n");
	cornerTopLeft();
	line2(39);
	cornerTopRight();
	printf("\n");
	
	line();
	printf("               *Sample*                ");
	line();
	printf("\n");
	
	line();
	space(38);
	line();
	printf("\n");
	
	line();
	printf("  Enter ID              > A001         ");
	line();
	printf("\n");
	
	line();
	printf("  Enter Name            > James Ng     ");
	line();
	printf("\n");

	line();
	printf("  Enter Position        > Manager      ");
	line();
	printf("\n");
	
	line();
	printf("  Enter Faculty/Dept    > FSSH         ");
	line();
	printf("\n");
	
	line();
	printf("  Enter Password        > Abc012       ");
	line();
	printf("\n");
	
	line();
	printf("  Enter Contact Number  > 012-3456789  ");
	line();
	printf("\n");
	
	cornerBotomLeft();
	line2(39);
	cornerBotomRight();
	printf("\n\n");
}

// Function 1
void addStaff()
{
	Staff s;
	char answer, openFile;

	int countRecord = 0, a = 0, key, code;

	FILE* binary;
	binary = fopen("staff.dat", "rb");
	if (binary == NULL)
	{
		printf("Error, cannot open the staff.dat file.\n");
		exit(-1);

	}
	fclose(binary);

	
	cornerTopLeft();
	line2(39);
	cornerTopRight();
	printf("\n");
	
	line();
	printf("          Add Staff Program            ");
	line();
	printf("\n");
	cornerBotomLeft();
	line2(39);
	cornerBotomRight();
	printf("\n");

	sample();

	do
	{
		facultyMenu();

		do
		{
			printf("Enter ID              > ");
			rewind(stdin);
			scanf("%c%d", &s.id.dept, &s.id.number);
			key = checkID(s.id.dept, s.id.number);

		} while (key != 0);

		printf("Enter Surname         > ");
		rewind(stdin);
		scanf("%s", &s.name.surName);

		printf("Enter Last Name       > ");
		rewind(stdin);
		scanf("%[^\n]", &s.name.lastName);

		//filter
		int z = 0;
		strcpy(s.email, s.name.lastName);
		for (int a = 0; a < 10; a++)
		{
			s.email[a] = tolower(s.email[a]);
			z++;
		}

		for (int i = 0; i < z; i++)
		{
			if (s.email[i] == ' ')
			{
				for (int b = i; b < z; b++)
				{
					s.email[b] = s.email[b + 1];
				}
			}
		}

		key = checkEmail(s.email);
		if (key == 0)
		{
			z = 0;
			strcpy(s.email, s.name.surName);
			for (int a = 0; a < 10; a++)
			{
				s.email[a] = tolower(s.email[a]);
				z++;
			}

		}

		printf("Enter Email           > %s@tarc.edu.my\n", s.email);

		if (s.id.dept == 'A')
			strcpy(s.faculty, "FSSH");
		else if (s.id.dept == 'B')
			strcpy(s.faculty, "FOAS");
		else if (s.id.dept == 'C')
			strcpy(s.faculty, "FOCS");
		else if (s.id.dept == 'D')
			strcpy(s.faculty, "FAFB");
		else if (s.id.dept == 'E')
			strcpy(s.faculty, "FOET");
		else if (s.id.dept == 'F')
			strcpy(s.faculty, "FOBE");
		else
			strcpy(s.faculty, "FCCI");

		printf("Enter Faculty/Dept    > %s\n", s.faculty);

		do
		{
			red();
			printf("1. Manager    2. Lecturer    3. Tutor\n");
			reset();

			printf("Enter Position        > ");
			scanf("%d", &code);

			if (code == 1)
				strcpy(s.position, "Manager");
			else if (code == 2)
				strcpy(s.position, "Lecturer");
			else if (code == 3)
				strcpy(s.position, "Tutor");
			else
				printf("Error, Please Enter Again.\n");

		} while (code != 1 && code != 2 && code != 3);


		printf("Enter Password        > ");
		rewind(stdin);
		scanf("%s", &s.password);

		do
		{
			printf("Enter Contact Number  > ");
			rewind(stdin);
			scanf("%s", &s.contactNumber);

			key = checkContactNumber(s.contactNumber);
		} while (key == 1);

		binary = fopen("staff.dat", "ab");
		if (!binary)
		{
			printf("Error, cannot open the file.\n");
			exit(-1);
		}

		fwrite(&s, sizeof(Staff), 1, binary);
		fclose(binary);
		countRecord++;


		printf("\n");
		printf("Add More ?\nPress Y to add more > ");
		rewind(stdin);
		scanf("%c", &answer);

		printf("\n\n");

	} while (answer == 'y' || answer == 'Y');
	fclose(binary);

	printf("%d record are succefull add into staff.dat file.\n", countRecord);

	system("pause");
}
// Function 2
void modifyStaff()
{
	Staff r, s[MAX_NUMBER];
	int countStaff = staffReadFile(s);
	char answer;
	int selection, key, code;
	char pwd[7];

	FILE* modify;

	do
	{
		cornerTopLeft();
		line2(55);
		cornerTopRight();
		printf("\n");

		line();
		printf("                     Modify Program                    ");
		line();
		printf("\n");

		cornerBotomLeft();
		line2(55);
		cornerBotomRight();
		printf("\n");
		
		printf("Enter ID > ");
		rewind(stdin);
		scanf("%c%d", &r.id.dept, &r.id.number);

		for (int a = 0; a < countStaff; a++)
		{
			if (s[a].id.dept == r.id.dept && s[a].id.number == r.id.number)
			{
				do
				{
					cyan();
					printf("\nStaff ID = %c%03d\n", s[a].id.dept, s[a].id.number);
					reset();

					cornerTopLeft();
					line2(44);
					cornerTopRight();
					printf("\n");
					

					line();
					printf("  Name            > %9s %-12s  ", s[a].name.surName, s[a].name.lastName);
					line();
					printf("\n");

					line();
					printf("  Position        > %-22s  ", s[a].position);
					line();
					printf("\n");

					line();
					printf("  Faculty/Dept    > %-22s  ", s[a].faculty);
					line();
					printf("\n");

					line();
					printf("  Password        > %-22s  ", s[a].password);
					line();
					printf("\n");

					line();
					printf("  Contact Number  > %-22s  ", s[a].contactNumber);
					line();
					printf("\n");

					line();
					printf("  Email           > %10s@tarc.edu.my  ", s[a].email);
					line();
					printf("\n");

					cornerBotomLeft();
					line2(44);
					cornerBotomRight();
					printf("\n");

					darkGreen();
					printf("\nModify Menu:\n");
					printf("1. Position \n2. Password \n3. Contact Number \n0. Return To Main Menu\n");
					reset();

					printf("\nSelection > ");
					scanf("%d", &selection);
					printf("\n");
					if (selection == 1)
					{

						do
						{
							red();
							printf("1. Manager    2. Lecturer    3. Tutor\n");
							reset();
							printf("Enter Position        > ");
							scanf("%d", &code);

							if (code == 1)
								strcpy(r.position, "Manager");
							else if (code == 2)
								strcpy(r.position, "Lecturer");
							else if (code == 3)
								strcpy(r.position, "Tutor");
							else
								printf("Error, Please Enter Again.\n");

						} while (code != 1 && code != 2 && code != 3);


						printf("Are you sure want to modify your Position ? \nPress Y to continue > ");
						rewind(stdin);
						scanf("%c", &answer);

						if (answer == 'Y' || answer == 'y')
						{
							strcpy(s[a].position, r.position);
							green();
							printf("Modify Position Succefull.\n");
							reset();
						}
						else
						{
							red();
							printf("Modify Position Canceled.\n");
							reset();
						}

					}
					else if (selection == 2)
					{
						do
						{
							printf("Enter New Password       > ");
							rewind(stdin);
							scanf("%s", &r.password);

							printf("Recomform New Password   > ");
							rewind(stdin);
							scanf("%s", &pwd);

							if (strcmp(r.password, pwd) != 0)
							{
								printf("Error, password not match.\n");
							}

						} while (strcmp(r.password, pwd) != 0);

						printf("\nAre you sure want to modify your Password ? \nPress Y to continue > ");
						rewind(stdin);
						scanf("%c", &answer);

						if (answer == 'Y' || answer == 'y')
						{
							strcpy(s[a].password, pwd);
							green();
							printf("Modify Password Succefull.\n");
							reset();
						}
						else
						{
							red();
							printf("Modify Password Canceled.\n");
							reset();
						}

					}
					else if (selection == 3)
					{
						do
						{
							printf("Enter Contact Number > ");
							rewind(stdin);
							scanf("%s", &r.contactNumber);

							key = checkContactNumber(r.contactNumber);
						} while (key == 1);

						printf("Are you sure want to modify your Contact Number ? \nPress Y to continue > ");
						rewind(stdin);
						scanf("%c", &answer);

						if (answer == 'Y' || answer == 'y')
						{
							strcpy(s[a].contactNumber, r.contactNumber);
							green();
							printf("Modify Contact Number Succefull.\n");
							reset();
						}
						else
						{
							red();
							printf("Modify Contact Number Canceled.\n");
							reset();
						}

					}
					else if (selection == 0)
					{
						green();
						printf("Thank You, Your Modifly is updated...\n\n");
						reset();
					}
					else
					{
						red();
						printf("\nInvalid, Please enter again... \n\n");
						reset();
					}
					_sleep(1700);
					system("CLS");

				} while (selection != 0);


				modify = fopen("staff.dat", "wb");

				for (int i = 0; i < countStaff; i++)
				{
					fwrite(&s[i], sizeof(Staff), 1, modify);
				}
				fclose(modify);
				break;

			}
			else if (a == countStaff - 1)
			{
			printf("Error, Cannot find the %c%03d ID in staff.dat file.\n\n", r.id.dept, r.id.number);
			}
		}

		printf("\nContinue to Modify other account ?\nPress Y to continue > ");
		rewind(stdin);
		scanf("%c", &answer);
		printf("\n");

	} while (answer == 'y' || answer == 'Y');
	printf("\n");
}
// Function 3
void deleteStaff()
{
	Staff r, s[MAX_NUMBER];
	int countStaff = staffReadFile(s);
	char answer;

	cornerTopLeft();
	line2(44);
	cornerTopRight();
	printf("\n");
	
	line();
	printf("               Delete Program               ");
	line();
	printf("\n");

	cornerBotomLeft();
	line2(44);
	cornerBotomRight();
	printf("\n");

	do
	{
		printf("Enter Staff ID > ");
		rewind(stdin);
		scanf("%c%d", &r.id.dept, &r.id.number);


		for (int a = 0; a < countStaff; a++)
		{
			if (s[a].id.dept == r.id.dept && s[a].id.number == r.id.number)
			{
				cyan();
				printf("\nStaff ID = %c%03d\n", s[a].id.dept, s[a].id.number);
				reset();

				cornerTopLeft();
				line2(44);
				cornerTopRight();
				printf("\n");
				

				line();
				printf("  Name            > %9s %-12s  ", s[a].name.surName, s[a].name.lastName);
				line();
				printf("\n");

				line();
				printf("  Position        > %-22s  ", s[a].position);
				line();
				printf("\n");

				line();
				printf("  Faculty/Dept    > %-22s  ", s[a].faculty);
				line();
				printf("\n");

				line();
				printf("  Password        > %-22s  ", s[a].password);
				line();
				printf("\n");

				line();
				printf("  Contact Number  > %-22s  ", s[a].contactNumber);
				line();
				printf("\n");

				line();
				printf("  Email           > %10s@tarc.edu.my  ", s[a].email);
				line();
				printf("\n");

				cornerBotomLeft();
				line2(44);
				cornerBotomRight();
				printf("\n");

				printf("Are you sure want to delete ?\nPress Y to delete > ");
				rewind(stdin);
				scanf("%c", &answer);

				if (answer == 'y' || answer == 'Y')
				{
					countStaff--;
					for (int i = a; i < countStaff; i++)
					{
						s[i].id.dept = s[i + 1].id.dept;
						s[i].id.number = s[i + 1].id.number;
						strcpy(s[i].name.surName, s[i + 1].name.surName);
						strcpy(s[i].name.lastName, s[i + 1].name.lastName);
						strcpy(s[i].position, s[i + 1].position);
						strcpy(s[i].faculty, s[i + 1].faculty);
						strcpy(s[i].contactNumber, s[i + 1].contactNumber);
						strcpy(s[i].email, s[i + 1].email);
					}

					FILE* binary;
					binary = fopen("staff.dat", "wb");
					if (!binary)
					{
						printf("Error, cannot find the staff.dat file.\n");
						exit(-1);
					}

					for (int b = 0; b < countStaff; b++)
					{
						fwrite(&s[b], sizeof(Staff), 1, binary);
					}

					fclose(binary);
					red();
					printf("\nThe Staff Detail has been deleted...\n");
					reset();
					break;
				}
				else
				{
					darkGreen();
					printf("Delete has been Canceled...\n");
					reset();
					break;
				}

			}
			else if (a == countStaff - 1)
			{
				printf("Error, Cannot find the %c%03d ID in staff.dat file.\n\n", r.id.dept, r.id.number);
			}

		}
		printf("Continue to Delete Staff ?\nPress Y to continue > ");
		rewind(stdin);
		scanf("%c", &answer);

	} while (answer == 'y' || answer == 'Y');

}
// Function 4
void displayMenu()
{
	int code;
	do
	{
		cornerTopLeft();
		line2(30);
		cornerTopRight();
		printf("\n");

		line();
		printf("          Display Menu        ");
		line();
		printf("\n");

		connectionLeft();
		line2(30);
		connectionRight();
		printf("\n");

		line();
		printf("   1. Display All             ");
		line();
		printf("\n");

		line();
		printf("   2. Display Faculty List    ");
		line();
		printf("\n");

		line();
		printf("   3. Display Manager List    ");
		line();
		printf("\n");

		line();
		printf("   4. Display Lecturer List   ");
		line();
		printf("\n");

		line();
		printf("   5. Display Tutorial List   ");
		line();
		printf("\n");

		line();
		printf("   0. Return To Main Menu     ");
		line();
		printf("\n");

		cornerBotomLeft();
		line2(30);
		cornerBotomRight();
		printf("\n");

		printf("Please Enter Your Selection > ");
		rewind(stdin);
		scanf("%d", &code);

		system("CLS");

		switch (code)
		{
		case 1:
			displayList1();
			break;
		case 2:
			displayList2();
			break;
		case 3:
			displayList3();
			break;
		case 4:
			displayList4();
			break;
		case 5:
			displayList5();
			break;
		case 0:
			break;
		default:
			red();
			printf("\n\nError, Please enter again...\n");
			reset();
			_sleep(1000);
			break;
		}

		system("CLS");
	} while (code != 0);

}

void displayList1()
{
	Staff s;
	int a = 1;

	FILE* read;
	read = fopen("staff.dat", "rb");
	if (!read)
	{
		printf("Error , cannot open staff.dat file.\n");
		exit(-1);
	}

	
	space(24);
	cornerTopLeft();
	line2(80);
	cornerTopRight();
	printf("\n");

	
	space(24);
	line();
	printf("                                    All List                                    ");
	line();
	printf("\n");

	
	space(24);
	cornerBotomLeft();
	line2(80);
	cornerBotomRight();
	printf("\n");

	displayHeading();
	while (fread(&s, sizeof(Staff), 1, read) != 0)
	{

		connectionLeft();
		line2(8);
		connection3();
		line2(10);
		connection3();
		line2(26);
		connection3();
		line2(16);
		connection3();
		line2(13);
		connection3();
		line2(14);
		connection3();
		line2(20);
		connection3();
		line2(27);
		connectionRight();
		printf("\n");

		line();
		printf("   %-2d   ", a);
		line();
		printf("   %c%03d   ", s.id.dept, s.id.number);
		line();
		printf("   %10s %-9s   ", s.name.surName, s.name.lastName);
		line();
		printf("   %-10s   ", s.position);
		line();
		printf("   %-7s   ", s.faculty);
		line();
		printf("    %-6s    ", s.password);
		line();
		printf("    %-12s    ", s.contactNumber);
		line();
		printf("  %10s@tarc.edu.my   ", s.email);
		line();
		printf("\n");

		a++;
	}
	displayEnd(a);
	

	system("pause");

}

void displayList2()
{
	Staff s, displayFaculty[MAX_NUMBER];
	int countStaff = staffReadFile(displayFaculty);
	char code, ans;

	do
	{
		int b = 1;
		facultyMenu();
		printf("Pleas Enter Your Selection > ");
		rewind(stdin);
		scanf("%c", &code);

		while (code != 'A' && code != 'B' && code != 'C' && code != 'D' && code != 'E' && code != 'F' && code != 'G')
		{
			printf("Error, Please Enter Again.\n");

			printf("Pleas Enter Your Selection > ");
			rewind(stdin);
			scanf("%c", &code);
		}

		system("CLS");

		space(24);
		cornerTopLeft();
		line2(80);
		cornerTopRight();
		printf("\n");
		
		space(24);
		line();
		if (code == 'A')
		{
			printf("                  Faculty of Social Science and Humanities (FSSH)               ");
		}
		else if (code == 'B')
		{
			printf("                          Faculty of Applied Sciences (FOAS)                    ");
		}
		else if (code == 'C')
		{
			printf("              Faculty of Computing and Information Technology (FOCS)            ");
		}
		else if (code == 'D')
		{
			printf("                  Faculty of Accountancy, Finance & Business (FAFB)             ");
		}
		else if (code == 'E')
		{
			printf("                       Faculty of Engineering and Technology (FOET)             ");
		}
		else if (code == 'F')
		{
			printf("                          Faculty of Built Environment (FOBE)                   ");
		}
		else
		{
			printf("               Faculty of Communication and Creative Industries (FCCI)          ");
		}

		line();
		printf("\n");

		space(24);
		cornerBotomLeft();
		line2(80);
		cornerBotomRight();
		printf("\n");


		displayHeading();

		for (int a = 0; a < countStaff; a++)
		{
			if (code == displayFaculty[a].id.dept)
			{
				displayDetails(a, b);
				b++;
			}
		}
		displayEnd(b);

	

		system("pause");
		system("CLS");

		printf("Did you want continue to display other faculty?\nPress Y to continue > ");
		rewind(stdin);
		scanf("%c", &ans);

		system("CLS");

	} while (ans == 'Y');

}

void displayList3()
{
	Staff s, displayFaculty[MAX_NUMBER];
	int countStaff = staffReadFile(displayFaculty), b = 1;
		
	space(24);
	cornerTopLeft();
	line2(80);
	cornerTopRight();
	printf("\n");

	
	space(24);
	line();
	printf("                                   Manager List                                 ");
	line();
	printf("\n");

	space(24);
	cornerBotomLeft();
	line2(80);
	cornerBotomRight();
	printf("\n");


	displayHeading();

	for (int a = 0; a < countStaff; a++)
	{
		if (strcmp(displayFaculty[a].position, "Manager") == 0)
		{
			displayDetails(a, b);
			b++;

		}
	}
	displayEnd(b);



	system("pause");
}

void displayList4()
{
	Staff s, displayFaculty[MAX_NUMBER];
	int countStaff = staffReadFile(displayFaculty), b = 1;

	space(24);
	cornerTopLeft();
	line2(80);
	cornerTopRight();
	printf("\n");
	
	space(24);
	line();
	printf("                                   Lecturer List                                ");
	line();
	printf("\n");

	space(24);
	cornerBotomLeft();
	line2(80);
	cornerBotomRight();
	printf("\n");

	displayHeading();

	for (int a = 0; a < countStaff; a++)
	{
		if (strcmp(displayFaculty[a].position, "Lecturer") == 0)
		{
			displayDetails(a, b);
			b++;
		}
	}
	displayEnd(b);



	system("pause");

}

void displayList5()
{
	Staff s, displayFaculty[MAX_NUMBER];
	int countStaff = staffReadFile(displayFaculty), b = 1;

	space(24);
	cornerTopLeft();
	line2(80);
	cornerTopRight();
	printf("\n");
	
	space(24);
	line();
	printf("                                        Tutor List                              ");
	line();
	printf("\n");

	space(24);
	cornerBotomLeft();
	line2(80);
	cornerBotomRight();
	printf("\n");

	displayHeading();

	for (int a = 0; a < countStaff; a++)
	{
		if (strcmp(displayFaculty[a].position, "Tutor") == 0)
		{
			displayDetails(a, b);
			b++;
		}
	}
	displayEnd(b);



	system("pause");

}

void displayHeading()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	printf("\n                                                                                                                              Data : %2d-%2d-%4d   \n", t.wDay, t.wMonth, t.wYear);

	cornerTopLeft();
	line2(8);
	connection1();
	line2(10);
	connection1();
	line2(26);
	connection1();
	line2(16);
	connection1();
	line2(13);
	connection1();
	line2(14);
	connection1();
	line2(20);
	connection1();
	line2(27);
	cornerTopRight();
	printf("\n");
	
	line();
	printf("   No   ");
	line();
	printf("    ID    ");
	line();
	printf(" %10sName%10s ", " ", " ");
	line();
	printf("    Position    ");
	line();
	printf("   Faculty   ");
	line();
	printf("   Password   ");
	line();
	printf("   Contact Number   ");
	line();
	printf("           Email           ");
	line();
	printf("\n");


}

void displayEnd(int a)
{
	cornerBotomLeft();
	line2(8);
	connection2();
	line2(10);
	connection2();
	line2(26);
	connection2();
	line2(16);
	connection2();
	line2(13);
	connection2();
	line2(14);
	connection2();
	line2(20);
	connection2();
	line2(27);
	cornerBotomRight();
	printf("\n");

	darkGreen();
	printf("Total Record > %d\n", a - 1);
	reset();
}

void displayDetails(int a, int b)
{
	Staff s, displayFaculty[MAX_NUMBER];
	int countStaff = staffReadFile(displayFaculty);

	connectionLeft();
	line2(8);
	connection3();
	line2(10);
	connection3();
	line2(26);
	connection3();
	line2(16);
	connection3();
	line2(13);
	connection3();
	line2(14);
	connection3();
	line2(20);
	connection3();
	line2(27);
	connectionRight();
	printf("\n");


	line();
	printf("   %-2d   ", b);
	line();
	printf("   %c%03d   ", displayFaculty[a].id.dept, displayFaculty[a].id.number);
	line();
	printf("   %10s %-9s   ", displayFaculty[a].name.surName, displayFaculty[a].name.lastName);
	line();
	printf("   %-10s   ", displayFaculty[a].position);
	line();
	printf("   %-7s   ", displayFaculty[a].faculty);
	line();
	printf("    %-6s    ", displayFaculty[a].password);
	line();
	printf("    %-12s    ", displayFaculty[a].contactNumber);
	line();
	printf("  %10s@tarc.edu.my   ", displayFaculty[a].email);
	line();
	printf("\n");

}
// Function 5
void search()
{
	Staff r,s[MAX_NUMBER];
	int countStaff = staffReadFile(s);
	char ans;

	cornerTopLeft();
	line2(56);
	cornerTopRight();
	printf("\n");

	line();
	printf("                    Search Function                     ");
	line();
	printf("\n");

	cornerBotomLeft();
	line2(56);
	cornerBotomRight();
	printf("\n");

	do
	{
		printf("Enter ID > ");
		rewind(stdin);
		scanf("%c%d", &r.id.dept, &r.id.number);

		for (int a = 0; a < countStaff; a++)
		{
			if (s[a].id.dept == r.id.dept && s[a].id.number == r.id.number)
			{
				cyan();
				printf("\nStaff ID = %c%03d\n", s[a].id.dept, s[a].id.number);
				reset();

				cornerTopLeft();
				line2(44);
				cornerTopRight();
				printf("\n");
				

				line();
				printf("  Name            > %9s %-12s  ", s[a].name.surName, s[a].name.lastName);
				line();
				printf("\n");

				line();
				printf("  Position        > %-22s  ", s[a].position);
				line();
				printf("\n");

				line();
				printf("  Faculty/Dept    > %-22s  ", s[a].faculty);
				line();
				printf("\n");

				line();
				printf("  Password        > %-22s  ", s[a].password);
				line();
				printf("\n");

				line();
				printf("  Contact Number  > %-22s  ", s[a].contactNumber);
				line();
				printf("\n");

				line();
				printf("  Email           > %10s@tarc.edu.my  ", s[a].email);
				line();
				printf("\n");

				cornerBotomLeft();
				line2(44);
				cornerBotomRight();
				printf("\n");
				break;
			}
			else if (a == countStaff - 1)
			{
				red();
				printf("Error, cannot find this ID\n");
				reset();
			}
		}

		printf("Want to search other ID ? Press 'Y' to continue > ");
		rewind(stdin);
		scanf("%c", &ans);


	} while (ans == 'y' || ans == 'Y');



}

void facultyMenu()
{
	cornerTopLeft();
	line2(10);
	connection1();
	line2(60);
	cornerTopRight();
	printf("\n");

	line();
	printf("   Code   ");
	line();
	printf("                         Faculty                            ");
	line();
	printf("\n");


	connectionLeft();
	line2(10);
	cyan();
	printf("%c", 216);
	reset();
	line2(60);
	connectionRight();
	printf("\n");
	

	line();
	printf("    A     ");
	line();
	printf("  Faculty of Social Science and Humanities (FSSH)           ");
	line();
	printf("\n");

	line();
	printf("    B     ");
	line();
	printf("  Faculty of Applied Sciences (FOAS)                        ");
	line();
	printf("\n");

	line();
	printf("    C     ");
	line();
	printf("  Faculty of Computing and Information Technology (FOCS)    ");
	line();
	printf("\n");

	line();
	printf("    D     ");
	line();
	printf("  Faculty of Accountancy, Finance & Business (FAFB)         ");
	line();
	printf("\n");

	line();
	printf("    E     ");
	line();
	printf("  Faculty of Engineering and Technology (FOET)              ");
	line();
	printf("\n");

	line();
	printf("    F     ");
	line();
	printf("  Faculty of Built Environment (FOBE)                       ");
	line();
	printf("\n");

	line();
	printf("    G     ");
	line();
	printf("  Faculty of Communication and Creative Industries (FCCI)   ");
	line();
	printf("\n");

	cornerBotomLeft();
	line2(10);
	connection2();
	line2(60);
	cornerBotomRight();
	printf("\n");

}

// Function 6
void loginSystem()
{
	Staff r, s[MAX_NUMBER];

	int pointer = 1;
	int countStaff = 0;
	char openFile, psw;
	int key = 0, i;
	char error[20] = "Opps, Sorry User...", error2[28] = "We cannot find the file...", error3[35] = "Would you like to create a file ?";

	FILE* read;
	read = fopen("staff.dat", "rb");
	if (!read)
	{
		for (int a = 0; a < 20; a++)
		{
			printf("%c", error[a]);
			_sleep(30);
		}
		printf("\n");
		for (int a = 0; a < 28; a++)
		{
			printf("%c", error2[a]);
			_sleep(30);
		}
		printf("\n");
		for (int a = 0; a < 35; a++)
		{
			printf("%c", error3[a]);
			_sleep(30);
		}
		printf("\n");
		printf("Press Y to open file > ");
		rewind(stdin);
		scanf("%c", &openFile);

		if (openFile == 'Y' || openFile == 'y')
		{
			read = fopen("staff.dat", "wb");
			system("CLS");
			printf("\n\n");
			space(38);
			printf("The file is created...\n");
			space(30);
			printf("Please use the Admin ID to login...\n");
			space(37);
			cornerTopLeft();
			line2(20);
			cornerTopRight();
			printf("\n");
			space(37);
			line();
			printf("  Staff ID : ");
			darkGreen();
			printf("%c%d   ", ADMIN_DEPT, ADMIN_NUMBER);
			reset();
			line();
			printf("\n");
			space(37);
			line();
			printf("  Password : ");
			darkGreen();
			printf("%s ", ADMIN_PSW);
			reset();
			line();
			printf("\n");
			space(37);
			cornerBotomLeft();
			line2(20);
			cornerBotomRight();
			printf("\n\n");
		
		}
		else
		{
			exit(-1);
		}

	}

	while (fread(&r, sizeof(Staff), 1, read) != 0)
	{

		s[countStaff].id.dept = r.id.dept;
		s[countStaff].id.number = r.id.number;
		strcpy(s[countStaff].name.surName, r.name.surName);
		strcpy(s[countStaff].name.lastName, r.name.lastName);
		strcpy(s[countStaff].position, r.position);
		strcpy(s[countStaff].faculty, r.faculty);
		strcpy(s[countStaff].password, r.password);
		strcpy(s[countStaff].contactNumber, r.contactNumber);
		strcpy(s[countStaff].email, r.email);
	
		countStaff++;
		pointer = 2;
	}
	fclose(read);

	do
	{
		i = 0;
		printf("\n\n");
		space(30);
		printf("Enter Your ID       : ");
		rewind(stdin);
		scanf("%c%d", &r.id.dept, &r.id.number);
		space(30);
		printf("Enter Your Password : ");
		while (1)
		{
			rewind(stdin);
			psw = getch();

			if (psw == '\r')
			{
				r.password[i] = '\0';
				break;
			}
			else if (psw == '\b')
			{
				if (i > 0)
				{
					i--;
					printf("\b \b");
				}

			}
			else
			{
				printf("*");
				r.password[i] = psw;
				i++;
			}
		}
		printf("\n\n");
		if (pointer == 1)
		{
			if (r.id.dept == ADMIN_DEPT && r.id.number == ADMIN_NUMBER)
			{
				space(40);
				if (strcmp(r.password, ADMIN_PSW) == 0)
				{
					darkGreen();
					printf("Login Successfull...\n");
					reset();
					key = 0;
				}
				else
				{
					red();
					printf("Wrong Password, Try Again...\n");
					reset();
					key = 1;
				}

			}
			else
			{
				space(40);
				red();
				printf("Wrong ID, Try Again...\n");
				reset();
				key = 1;
			}
		}
		else if (r.id.dept == ADMIN_DEPT && r.id.number == ADMIN_NUMBER)
		{
			space(40);
			if (strcmp(r.password, ADMIN_PSW) == 0)
			{
				darkGreen();
				printf("Login Successfull...\n");
				reset();
				key = 0;
			}
			else
			{
				red();
				printf("Wrong Password, Try Again...\n");
				reset();
				key = 1;
			}

		}
		else 
		{
			space(40);
			for (int a = 0; a < countStaff; a++)
			{
				if (r.id.dept == s[a].id.dept && r.id.number == s[a].id.number)
				{
					
					if (strcmp(r.password, s[a].password) == 0)
					{
						darkGreen();
						printf("Login Successfull...\n");
						reset();
						key = 0;
						break;
					}
					else
					{
						red();
						printf("Wrong Password, Try Again...\n");
						reset();
						key = 1;
						break;
					}
				}
				else if (a == countStaff - 1)
				{
					
					red();
					printf("Wrong ID, Try Again...\n");
					reset();
					key = 1;
				}
			}
		}
		_sleep(300);
		system("CLS");

	} while (key == 1);

}

//checking
int checkContactNumber(char contactNum[13])
{
	Staff staff, check[MAX_NUMBER];
	int key;
	FILE* r;
	r = fopen("staff.dat", "rb");
	if (!r)
	{
		printf("Error..\n");
		exit(-1);
	}
	int a = 0;
	while (fread(&staff, sizeof(Staff), 1, r) != 0)
	{
		strcpy(check[a].contactNumber, staff.contactNumber);
		a++;
	}
	fclose(r);


	if (strlen(contactNum) == 11 || strlen(contactNum) == 12)
	{
		key = 0;
	}
	else// if less then 11 or 12
	{
		printf("The contact number is invalid. Please Enter Again.\n");
		return 1;
	}

	if (strlen(contactNum) == 11)
	{
		for (int g = 0; g < 11; g++)
		{
			if (g == 3 && contactNum[g] == '-')
			{

			}
			else if (isalpha(contactNum[g]) != 0) // != 0 mean is alpha			== 0 mean not alpha
			{
				printf("Error, This is not a Contact Number\n");
				return 1;
			}
			else
			{
				key = 0;
			}
		}
	}
	else
	{
		for (int g = 0; g < 12; g++)
		{
			if (g == 3 && contactNum[g] == '-')
			{

			}
			else if (isalpha(contactNum[g]) != 0)
			{
				printf("Error, This is not a Contact Number\n");
				return 1;
			}
			else
			{
				key = 0;
			}
		}
	}
	
	if (a == 0)
		a = 1;

	for (int b = 0; b < a; b++)
	{
		if (strcmp(contactNum, check[b].contactNumber) == 0)//if same contact number
		{
			printf("Contact Number is exist.\nPlease try again.\n");
			return 1;
			break;
		}
		else if (key == 0 && b == a - 1)
			return 0;
	}

}

int checkID(char dept, int number)
{
	Staff s, check[MAX_NUMBER];
	int a = 0, key, key1;

	FILE* checking;
	checking = fopen("staff.dat", "rb");
	if (!checking)
	{
		printf("Error, cannot find the staff.dat file.\n");
		exit(-1);
	}

	while (fread(&s, sizeof(Staff), 1, checking) != 0)
	{
		check[a].id.dept = s.id.dept;
		check[a].id.number = s.id.number;
		a++;
	}
	fclose(checking);


	if (dept == 'A' || dept == 'B' || dept == 'C' || dept == 'D' || dept == 'E' || dept == 'F' || dept == 'G')
	{
		key = 0;
	}
	else
	{
		key = 1;
	}

	if (number >= 1 && number <= 210)
	{
		key1 = 0;
	}
	else
	{
		key1 = 1;
	}

	if (key == 1 || key1 == 1)
	{
		printf("The Staff ID is not applieble.\n");
		return 1;
	}

	if (a == 0)
		a = 1;

	for (int b = 0; b < a; b++)
	{

		if (check[b].id.dept == dept && check[b].id.number == number)
		{
			printf("Your ID is already exist.\n");
			return 1;
		}
		else if (b == a - 1 )
		{
			return 0;
		}

	}

}

int checkEmail(char checkEmail[11])
{
	Staff r, s[MAX_NUMBER];
	int countStaff = 0, pointer = 1;

	FILE* binary;
	binary = fopen("staff.dat", "rb");
	if (!binary)
	{
		printf("Error , cannot open staff.dat file.\n");
		exit(-1);
	}

	while (fread(&r, sizeof(Staff), 1, binary) != 0)
	{
		s[countStaff].id.dept = r.id.dept;
		s[countStaff].id.number = r.id.number;
		strcpy(s[countStaff].name.surName, r.name.surName);
		strcpy(s[countStaff].name.lastName, r.name.lastName);
		strcpy(s[countStaff].position, r.position);
		strcpy(s[countStaff].faculty, r.faculty);
		strcpy(s[countStaff].password, r.password);
		strcpy(s[countStaff].contactNumber, r.contactNumber);
		strcpy(s[countStaff].email, r.email);
		pointer = 2;
		countStaff++;
	}

	if (pointer == 1)
		return 1;
	else
	{
		for (int a = 0; a < countStaff; a++)
		{
			if (strcmp(s[a].email, checkEmail) == 0)
			{
				return 0; //false
			}
			else if (a == countStaff - 1)
			{
				return 1; //true
			}
		}
	}
	

}

//design
void loading()
{
	char loadSym[] = "|/-\\";
	int a = 0;
	srand(time(NULL));
	for (int i = 0; i <= 100; i+=4)
	{
		printf("\033[1;3%dm", rand() % 6 + 1);

		printf("\n\n\n\n\n\n\n%60s", " ");
		printf("%c", loadSym[a++]);
		printf("Loading...    %3d %%\n", i);
		_sleep(5);
		if (a == strlen(loadSym))
		{
			a = 0;
		}
		system("CLS");
	}
}

void logo()
{
	char word[] = "Welcome to TARUC MySejahtera System....";
	int a = 0;
	printf("\n\n");

	system("COLOR FB");


	printf("%30s  *************************************************************************************************************** \n", " ");
	printf("%30s **                                                                                                             **\n", " ");
	printf("%30s **  TTTTTTTTTTTTTTTT          AAAAA              RRRRRRRRRRRRR        UU            UU        CCCCCCCCCCCCC    **\n", " ");
	printf("%30s **         TT                AA   AA             RR          RR       UU            UU       CCC               **\n", " ");
	printf("%30s **         TT               AA     AA            RR          RR       UU            UU     CC                  **\n", " ");
	printf("%30s **         TT              AA       AA           RR          RR       UU            UU     CC                  **\n", " ");
	printf("%30s **         TT             AA         AA          RRRRRRRRRRRRR        UU            UU     CC                  **\n", " ");
	printf("%30s **         TT            AAAAAAAAAAAAAAA         RR RR                UU            UU     CC                  **\n", " ");
	printf("%30s **         TT           AA             AA        RR    RR             UU            UU     CC                  **\n", " ");
	printf("%30s **         TT          AA               AA       RR       RR          UU            UU     CC                  **\n", " ");
	printf("%30s **         TT         AA                 AA      RR         RR          UU        UU         CCC               **\n", " ");
	printf("%30s **         TT        AA                   AA     RR           RR          UUUUUUUU            CCCCCCCCCCCCC    **\n", " ");
	printf("%30s **                                                                                                             **\n", " ");
	printf("%30s  *************************************************************************************************************** \n", " ");


	printf("\n\n%70s", " ");

	for (int i = 0; i < 39; i++)
	{
		printf("%c", word[a++]);
		_sleep(30);

	}

	_sleep(1000);
	system("CLS");
	system("COLOR F0");
	
}

//symbol
void line()
{
	cyan();
	printf("%c", 179);
	reset();
}
void line2(int number)
{
	cyan();

	for (int a = 0; a < number; a++)
	{
		printf("%c", 205);
	}

	reset();
}
void cornerTopLeft()
{
	cyan();
	printf("%c", 213);
	reset();
}
void cornerTopRight()
{
	cyan();
	printf("%c", 184);	
	reset();
}
void connectionLeft()
{
	cyan();
	printf("%c", 198);
	reset();
}
void connectionRight()
{
	cyan();
	printf("%c", 181);
	reset();
}
void connection1()
{
	cyan();
	printf("%c", 209);
	reset();
}
void connection2()
{
	cyan();
	printf("%c", 207);
	reset();
}
void connection3()
{
	cyan();
	printf("%c", 216);
	reset();
}
void cornerBotomLeft()
{
	cyan();
	printf("%c", 212);
	reset();
}
void cornerBotomRight()
{
	cyan();
	printf("%c", 190);
	reset();
}
void space(int number)
{
	for (int a = 0; a <= number; a++)
	{
		printf("%c", ' ');
	}
}


int staffReadFile(Staff displayFaculty[MAX_NUMBER])
{
	Staff s;
	int countStaff = 0;

	FILE* read;
	read = fopen("staff.dat", "rb");
	if (!read)
	{
		printf("Error , cannot open staff.dat file.\n");
		exit(-1);
	}


	while (fread(&s, sizeof(Staff), 1, read) != 0)
	{
		displayFaculty[countStaff].id.dept = s.id.dept;
		displayFaculty[countStaff].id.number = s.id.number;
		strcpy(displayFaculty[countStaff].name.surName, s.name.surName);
		strcpy(displayFaculty[countStaff].name.lastName, s.name.lastName);
		strcpy(displayFaculty[countStaff].position, s.position);
		strcpy(displayFaculty[countStaff].faculty, s.faculty);
		strcpy(displayFaculty[countStaff].password, s.password);
		strcpy(displayFaculty[countStaff].contactNumber, s.contactNumber);
		strcpy(displayFaculty[countStaff].email, s.email);

		countStaff++;
	}
	fclose(read);
	return countStaff;
}