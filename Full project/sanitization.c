#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#pragma warning (disable : 4996)


struct Date
{
	int day, month, year;
};

struct Time
{
	int h, m;
};

typedef struct
{
	struct Date date;
	struct Time startTime, endTime;
	char venue[10], company[30], contact[13];
	char name[15];

} Sanitization;

void sanitizationSystem(int power);
int sanitizationMenu();
void addSanitizationRecord(int power);
void searchSanitizationRecord();
void modifySanitizationRecord(int power);
void displaySanitizationRecord();
void sanitizationReport();
void deleteSanizationRecord(int power);


//validation
int sanitizationCheckContactNumber(char contactNum[13]);


#define MAXIMUM 50
void sanitizationSystem(int power)
{
	int choice;
	
	do
	{
		choice = sanitizationMenu();

		switch (choice)
		{
		case 1:
			addSanitizationRecord(power);
			break;

		case 2:
			displaySanitizationRecord();
			break;

		case 3:
			searchSanitizationRecord();
			break;

		case 4:
			modifySanitizationRecord(power);
			break;

		case 5:
			deleteSanizationRecord(power);
			break;

		case 6:
			sanitizationReport();
			break;

		case 7:
			printf("\tThank You.\n");
			break;
		}

	} while (choice != 7);



}

int sanitizationMenu()
{
	int choice;

	printf("\n\tWelcome to our Sanitization Record ! \n\n");
	printf("\t**********************************\n");
	printf("\t*            Menu                *\n");
	printf("\t* ============================== *\n");
	printf("\t* 1. Add Sanitization Record     *\n");
	printf("\t* 2. Display Sanitization Record *\n");
	printf("\t* 3. Search Sanitization Record  *\n");
	printf("\t* 4. Modify Sanitization Record  *\n");
	printf("\t* 5. Delete Sanitization Record  *\n");
	printf("\t* 6. Report                      *\n");
	printf("\t* 7. Exit                        *\n");
	printf("\t**********************************\n");

	printf("\tChoose a number : ");
	scanf("%d", &choice);
	printf("\n");
	switch (choice)
	{
	case 1:
		return 1;
		break;

	case 2:
		return 2;
		break;

	case 3:
		return 3;
		break;

	case 4:
		return 4;
		break;

	case 5:
		return 5;
		break;

	case 6:
		return 6;
		break;
	case 7:
		return 7;
		break;
	default:
		printf("\tError, Please Enter Valid Code.\n");
	}



}

void addSanitizationRecord(int power)
{
	if (power == 1) {

		char ans;
		int i;
		int key;
		Sanitization sani;

		FILE* fsanitizationRecord;
		fsanitizationRecord = fopen("fsanitizationRecord.bin", "ab");
		if (fsanitizationRecord == NULL)
		{
			printf("\tError open the files \n");
			exit(-1);
		}

		printf("\tHow many Company Details you would like to add : ");
		//printf("Enter company details : ");
		scanf("%d", &i);

		for (int a = 0; a < i; a++)
		{
			printf("\n\t Company Details : %d\n", a + 1);
			printf("\t -------------------");
			printf("\n\t Date (dd-mm-yyyy): ");
			scanf("%d-%d-%d", &sani.date.day, &sani.date.month, &sani.date.year);


			printf("\t Start time (hh:mm) : ");
			scanf("%d:%d", &sani.startTime.h, &sani.startTime.m);


			printf("\t End time (hh:mm) : ");
			scanf("%d:%d", &sani.endTime.h, &sani.endTime.m);

			printf("\n\tExample venue --> *library *canteen *toilet\n\n");
			printf("\t Venue  : ");
			rewind(stdin);
			scanf("%s", &sani.venue);


			printf("\t Company: ");
			rewind(stdin);
			scanf(" %[^\n]", &sani.company);


			printf("\t Name : ");
			rewind(stdin);
			scanf(" %[^\n]", &sani.name);

			do
			{
				printf("\t Contact (???-????????): ");
				scanf("%s", &sani.contact);
				key = checkContactNumber(sani.contact);
			} while (key != 0);


			printf("\n\t---------------------------------------------------------\n");
			fwrite(&sani, sizeof(Sanitization), 1, fsanitizationRecord);
		}


		fclose(fsanitizationRecord);
	}
	else {
		red();
		printf("You are not allowed to add!");
		reset();
	}
}

void displaySanitizationRecord()
{
	Sanitization sani;
	SYSTEMTIME t;
	GetLocalTime(&t);

	FILE* fsanitizationRecord;
	fsanitizationRecord = fopen("fsanitizationRecord.bin", "rb");
	if (fsanitizationRecord == NULL)
	{
		printf("\tError open the files \n");
		exit(-1);
	}
	
	printf("\t                                Sanitization Record - as at %d/%d/%d\n\n", t.wDay, t.wMonth, t.wYear);
	printf("\t    -------------------------------------------------------------------------------------------------\n");
	printf("\t   Date      Start Time     End Time       Venue             Company             Name            Contact\n");
	printf("\t========== %3 ============ %3 =========== %3 ============== %3 =================== %3 ============== %3 =================\n", " ", " ", " ", " ", " "," ");

	while (fread(&sani, sizeof(Sanitization), 1, fsanitizationRecord) != 0)
	{
		           //date          //time       //time       venue      company   name    contact
		printf("\t%2d-%2d-%4d %3s %02d:%02d %7s %02d:%02d %6s %5s  %7s %-10s %7s %4s %10s %-13s\n", sani.date.day, sani.date.month, sani.date.year, " ", sani.startTime.h, sani.startTime.m, " ", sani.endTime.h, sani.endTime.m, " ", sani.venue, " ", sani.company, " ", sani.name, " ", sani.contact);
	}
	fclose(fsanitizationRecord);

}

void searchSanitizationRecord()
{
	Sanitization sani[MAXIMUM], read;
	char name[15], ans;
	int count = 0;
	SYSTEMTIME t;
	GetLocalTime(&t);

	FILE* fsanitizationRecord;
	fsanitizationRecord = fopen("fsanitizationRecord.bin", "rb");
	if (fsanitizationRecord == NULL)
	{
		printf("\t Error open the files \n");
		exit(-1);
	}

	while (fread(&read, sizeof(Sanitization), 1, fsanitizationRecord) != 0)
	{
		sani[count].date.day = read.date.day;
		sani[count].date.month = read.date.month;
		sani[count].date.year = read.date.year;
		sani[count].startTime.h = read.startTime.h;
		sani[count].startTime.m = read.startTime.m;
		sani[count].endTime.h = read.endTime.h;
		sani[count].endTime.m = read.endTime.m;
		strcpy(sani[count].venue, read.venue);
		strcpy(sani[count].company, read.company);
		strcpy(sani[count].contact, read.contact);
		strcpy(sani[count].name, read.name);

		count++;
	}
	fclose(fsanitizationRecord);


	do
	{

		printf("\tEnter name to search : ");
		rewind(stdin);
		scanf("%[^\n]", &name);


		
	
		printf("\t                                Sanitization Record - as at %d/%d/%d\n\n", t.wDay, t.wMonth, t.wYear);
		printf("\t    -------------------------------------------------------------------------------------------------\n");
		printf("\n\t   Date      Start Time     End Time       Venue             Company             Name            Contact\n");
		printf("\t========== %3 ============ %3 =========== %3 ============== %3 =================== %3 ============== %3 =================\n", " ", " ", " ", " ", " ", " ");

		for (int i = 0; i < count; i++)
		{
			if (strcmp(name, sani[i].name) == 0)
			{
				/*fwrite(&sani, sizeof(Sanitization), 1, fsanitizationRecord);*/

				printf("\t%2d-%2d-%4d %3s %02d:%02d %7s %02d:%02d %6s %5s  %7s %-10s %7s %4s %10s %-13s\n", sani[i].date.day, sani[i].date.month, sani[i].date.year, " ", sani[i].startTime.h, sani[i].startTime.m, " ", sani[i].endTime.h, sani[i].endTime.m, " ", sani[i].venue, " ", sani[i].company, " ", sani[i].name, " ", sani[i].contact);

			}
			else
			{
				
			}
			/*printf("Do you want to add list? : \n");
			scanf("%c", &add);
			rewind("stdin");*/


		}
		printf("\n\t Do you want to search other Record ? Yes = y  No = n\n\n");
		printf("\tANS : ");
		rewind(stdin);
		scanf("%c", &ans);

	} while (ans == 'y');
}

void modifySanitizationRecord(int power)
{
	if (power == 1) {

		int count = 0;
		char ans, name[15];
		int chosen;
		SYSTEMTIME t;
		GetLocalTime(&t);

		FILE* fsanitizationRecord;
		fsanitizationRecord = fopen("fsanitizationRecord.bin", "rb");
		if (fsanitizationRecord == NULL)
		{
			printf("\t Error open the files \n");
			exit(-1);
		}

		Sanitization sani[MAXIMUM], read;

		while (fread(&read, sizeof(Sanitization), 1, fsanitizationRecord) != 0)
		{
			sani[count].date.day = read.date.day;
			sani[count].date.month = read.date.month;
			sani[count].date.year = read.date.year;
			sani[count].startTime.h = read.startTime.h;
			sani[count].startTime.m = read.startTime.m;
			sani[count].endTime.h = read.endTime.h;
			sani[count].endTime.m = read.endTime.m;
			strcpy(sani[count].venue, read.venue);
			strcpy(sani[count].company, read.company);
			strcpy(sani[count].contact, read.contact);
			strcpy(sani[count].name, read.name);

			count++;
		}
		fclose(fsanitizationRecord);


		/*
		printf("***********************\n");
		printf(" Sanitization Record - as at %d %d %d\n\n", t.wDay, t.wMonth, t.wYear);

		printf(" Date %10s  Start Time %s End Time %s Venue %s Company %s Name %s Contact\n", " ", " ", " ", " ", " ");
		printf(" =====%10s ===========%s===========%s=======%s======%s=========%s========\n", " ", " ", " ", " ", " ");
		*/
		do
		{
			printf("\tEnter name to search : ");
			rewind(stdin);
			scanf("%[^\n]", &name);

			for (int a = 0; a < count; a++)
			{
				if (strcmp(name, sani[a].name) == 0)
				{
					do
					{
						printf("\n\t.~.~.~.~.~.~.~\n");
						printf("\t. 1. Venue   .\n");
						printf("\t. 2. Contact .\n");
						printf("\t. 3. Exit    .\n\n");
						printf("\t.~.~.~.~.~.~.~\n");

						printf("\tWhich one you want to modify? : ");
						scanf("%d", &chosen);

						if (chosen == 1)
						{
							printf("\n\t Modify venue > ");
							rewind(stdin);
							scanf("%s", &read.venue);

							printf("\tComfirm to modify? Yes(y) or No(n)? > ");
							rewind(stdin);
							scanf("%c", &ans);

							if (ans == 'y' || ans == 'Y')
							{
								strcpy(sani[a].venue, read.venue);
							}
							else
							{
								printf("\tModify cancle.\n");
							}

						}
						else if (chosen == 2)
						{
							printf("\t modify contact > ");
							rewind(stdin);
							scanf("%s", &read.contact);

							printf("\tComfirm to modify? Yes(y) or No(n)? > ");
							rewind(stdin);
							scanf("%c", &ans);

							if (ans == 'y' || ans == 'Y')
							{
								strcpy(sani[a].contact, read.contact);
							}
							else
							{
								printf("\tModify cancle.\n");
							}
						}
						else if (chosen == 3)
						{
							printf("\n\tModify Succefull\n");
						}
						else
						{
							printf("\tPlease Enter Valid Number \n");
						}

					} while (chosen != 3);
				}
			}

			fsanitizationRecord = fopen("fsanitizationRecord.bin", "wb");
			if (fsanitizationRecord == NULL)
			{
				printf("Error open the files \n");
				exit(-1);
			}

			for (int b = 0; b < count; b++)
			{
				fwrite(&sani[b], sizeof(Sanitization), 1, fsanitizationRecord);
			}
			fclose(fsanitizationRecord);

			printf("\n\tWould you like to modifty other record ? Yes(y) No(n) > ");
			rewind(stdin);
			scanf("%c", &ans);

		} while (ans == 'y');
	}

	else {
		red();
		printf("You are not allowed to modify!");
		reset();
	}
}

//validation
int sanitizationCheckContactNumber(char contactNum[13])
{

	int key;
	int a = 0;



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
			else if (g == 11)
			{
				return 0;
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
			else if (g == 11)
			{
				return 0;
			}
		}
	}

}

void deleteSanizationRecord(int power)
{
	if (power == 1) {

		Sanitization sani[MAXIMUM], read;
		int count = 0;
		char name[15];

		FILE* fsanitizationRecord;
		fsanitizationRecord = fopen("fsanitizationRecord.bin", "rb");
		if (fsanitizationRecord == NULL)
		{
			printf("File error cannot open\n");
			system("pause");
			exit(-1);
		}
		while (fread(&read, sizeof(Sanitization), 1, fsanitizationRecord) != 0)
		{
			sani[count].date.day = read.date.day;
			sani[count].date.month = read.date.month;
			sani[count].date.year = read.date.year;
			sani[count].startTime.h = read.startTime.h;
			sani[count].startTime.m = read.startTime.m;
			sani[count].endTime.h = read.endTime.h;
			sani[count].endTime.m = read.endTime.m;
			strcpy(sani[count].venue, read.venue);
			strcpy(sani[count].company, read.company);
			strcpy(sani[count].contact, read.contact);
			strcpy(sani[count].name, read.name);

			count++;
		}
		fclose(fsanitizationRecord);

		printf("\tType the name you want to delete : ");
		rewind(stdin);
		scanf("%[^\n]", &name);

		for (int a = 0; a < count; a++)
		{
			if (strcmp(name, sani[a].name) == 0)
			{
				count--;
				for (int b = a; b < count; b++)
				{

					sani[b].date.day = sani[b + 1].date.day;
					sani[b].date.month = sani[b + 1].date.month;
					sani[b].date.year = sani[b + 1].date.year;
					sani[b].startTime.h = sani[b + 1].startTime.h;
					sani[b].startTime.m = sani[b + 1].startTime.m;
					sani[b].endTime.h = sani[b + 1].endTime.h;
					sani[b].endTime.m = sani[b + 1].endTime.m;
					strcpy(sani[b].venue, sani[b + 1].venue);
					strcpy(sani[b].company, sani[b + 1].company);
					strcpy(sani[b].contact, sani[b + 1].contact);
					strcpy(sani[b].name, sani[b + 1].name);
				}
			}
		}

		fsanitizationRecord = fopen("fsanitizationRecord.bin", "wb");
		if (fsanitizationRecord == NULL)
		{
			printf("File error cannot open\n");
			system("pause");
			exit(-1);
		}

		for (int a = 0; a < count; a++)
		{
			fwrite(&sani[a], sizeof(Sanitization), 1, fsanitizationRecord);
		}
		fclose(fsanitizationRecord);

	}

	else {
		red();
		printf("You are not allowed to delete!");
		reset();
	}

}

void sanitizationReport()
{
	Sanitization read, sani[MAXIMUM];
	int count = 0;
	int saniLibrary = 0, saniToilet = 0, saniCanteen = 0;


	FILE* fsanitizationRecord;
	fsanitizationRecord = fopen("fsanitizationRecord.bin", "rb");
	if (fsanitizationRecord == NULL)
	{
		printf("\tFile error cannot open\n");
		system("pause");
		exit(-1);
	}


	while (fread(&read, sizeof(Sanitization), 1, fsanitizationRecord) != 0)
	{
		sani[count].date.day = read.date.day;
		sani[count].date.month = read.date.month;
		sani[count].date.year = read.date.year;
		sani[count].startTime.h = read.startTime.h;
		sani[count].startTime.m = read.startTime.m;
		sani[count].endTime.h = read.endTime.h;
		sani[count].endTime.m = read.endTime.m;
		strcpy(sani[count].venue, read.venue);
		strcpy(sani[count].company, read.company);
		strcpy(sani[count].contact, read.contact);
		strcpy(sani[count].name, read.name);

		count++;
	}
	fclose(fsanitizationRecord);

	for (int a = 0; a < count; a++)
	{
		if (strcmp(sani[a].venue, "library") == 0)
		{
			saniLibrary++;
		}
		if (strcmp(sani[a].venue, "lec.hall") == 0)
		{
			saniToilet;
		}
		if (strcmp(sani[a].venue, "canteen") == 0)
		{
			saniCanteen++;
		}
	} 
	printf("\n");
	printf("\tTotal sanitization library : %d \n",saniLibrary);
	printf("\tTotal sanitization toilet : %d \n", saniToilet);
	printf("\tTotal sanitization canteen : %d \n", saniCanteen);
}
