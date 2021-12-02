#include<stdio.h>
#include<stdlib.h>
#include <Windows.h>
#include<ctype.h>
#include<stdbool.h>
#pragma warning(disable:4996)

//xc struct
typedef struct {
	int day, month, year;
}Date;

typedef struct {
	char icNo[15];
	Date date;
	int enterHour;
	int enterMinute;
	char venueID[20];
	float temperature;
	int hour;
	int minute;
	char gender[7];
}Information;
    
//ys struct
struct Equipment {
	int numOfAvailableNoseSwabTest;
	bool availabilityOfTemperatureSensor;
	int numberOfMask;
	int numOfSanizationBottle;
	float volumeOfSanizationBottleInLitres;
};

typedef struct VenueInformation {
	char venueName[30];
	char venueID[6];
	char venueCategory;
	char venueLastSanitizationDate[11];
	bool venueCloseForSanitization;
	int numberOfCurrentVisitors;
	int numberOfStaff;
	int maxNumberOfVisitors;
	int venueHistoryOfinfectedPeople;
	float venueAreaInMetres;
	char venueMeasurementCovidZone; //red,yellow,green zone
	char venueOpeningTime[6];
	char venueClosingTime[6];

	struct Equipment availabilityOfEquipment;

	char venueHistoryOfLastTenVistorsName[10][40];
	char venueDescriptions[150];

}VenueInformation;

void visitAndExitSystem(int power);
void addCustomer(int power);
void visitAndExitDisplay();
void visitAndExitSearch();
void visitAndExitModify(int power);
int visitAndExitCheckDate(int day, int month, int year);
int visitAndExitCheckTime(int enterHour, int enterMinute);
int visitAndExitCheckEnterExitTime(int enterHour, int enterMinute, int hour, int minute);
int visitAndExitCheckID(char icNo[15]);
float visitAndExitCheckTemperature(float temperature);
void morningRecord();
void afternoonRecord();
void eveningRecord();
void allRecord();
void visitAndExitReport();

//delete function(if a two visitor same id can delete one or all data / repeat the visitor data have two times can delete one data)
void visitAndExitSystem(int power)
{
	int code;
	char choice;
	
	do {
		printf("\t\t\t+===================================+\n");
		printf("\t\t\t|         Main Menu                 |\n");
		printf("\t\t\t+===================================+\n");
		printf("\t\t\t|   1.Display Visit Name List       |\n");
		printf("\t\t\t|   2.Add Visitor                   |\n");
		printf("\t\t\t|   3.Search Visitor                |\n");
		printf("\t\t\t|   4.   Modify                     |\n");
		printf("\t\t\t|   5.   Report                     |\n");
		printf("\t\t\t|   6.  Exit Program                |\n");
		printf("\t\t\t+===================================+\n");
		printf("\n");
		printf("Please enter your choice > ");
		scanf("%d", &code);

		system("CLS");

		if (code == 1)
			visitAndExitDisplay();
		else if (code == 2)
			addCustomer(power);
		else if (code == 3)
			visitAndExitSearch();
		else if (code == 4)
			visitAndExitModify(power);
		else if (code == 5)
			visitAndExitReport();
		else if (code == 6)
			printf("Thank you so much ^-^\n");
		else
			printf("Invalid code, pls enter again\n");

	} while (code != 6);
	
}

void addCustomer(int power)
{
	if (power == 1) {

		int door;
		Information inform = { 0 };
		int choice;
		char ans;




		SYSTEMTIME t;
		GetLocalTime(&t);
		printf("Date/time Entered --- %d-%d-%d , %02d:%02d \n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);

		printf("+================================================+\n");
		printf("|Sample of add visitor                           |\n");
		printf("+================================================+\n");
		printf("|Entered date                   > 13/03/2021     |\n");
		printf("|Entered time (24-hour clock)   > 13 05          |\n");
		printf("|Enter visitor IC NO            > 123456-89-4739 |\n");
		printf("|Enter Venue ID                 > lab123         |\n");
		printf("|Enter Visitor Temperature      > 36.5           |\n");
		printf("|Exit Time (24-hour clock)      > 15 34          |\n");
		printf("+================================================+\n");

		do
		{
			do
			{
				printf("Entered date > ");
				rewind(stdin);
				scanf("%d/%d/%d", &inform.date.day, &inform.date.month, &inform.date.year);
				door = visitAndExitCheckDate(inform.date.day, inform.date.month, inform.date.year);

				if (door == 1)
					printf("Invalid date ,please enter again !\n");
			} while (door == 1);// check validation(832929131)


			do
			{
				do
				{
					printf("Entered time >");
					rewind(stdin);
					scanf(" %d %d", &inform.enterHour, &inform.enterMinute);
					door = visitAndExitCheckTime(inform.enterHour, inform.enterMinute);

				} while (door == 1);//done validation

				do
				{
					printf("Exit time > ");
					rewind(stdin);
					scanf("%d %d", &inform.hour, &inform.minute);
					door = visitAndExitCheckTime(inform.hour, inform.minute);

				} while (door == 1);
				door = visitAndExitCheckEnterExitTime(inform.enterHour, inform.enterMinute, inform.hour, inform.minute);
			} while (door == 0);//redo

			do
			{
				printf("Enter visitor IC NO > ");
				rewind(stdin);
				scanf("%s", &inform.icNo);//do validation
				door = visitAndExitCheckID(inform.icNo);

			} while (door == 0);



			do
			{

				printf("+==========+\n");
				printf("|  Gender  |\n");
				printf("+==========+\n");
				printf("1.Male\n");
				printf("2.Female\n\n");

				printf("Please select the gender > ");
				scanf("%d", &choice);

				if (choice == 1)
					strcpy(inform.gender, "Male");
				else if (choice == 2)
					strcpy(inform.gender, "Female");
				else
					printf("Invalide code , pls enter again\n");
			} while (choice != 1 && choice != 2);


			printf("Select Venue ID > ");
			rewind(stdin);
			scanf("%[^\n]", &inform.venueID);

			do
			{
				printf("Enter visitor temperature > ");
				scanf("%f", &inform.temperature);
				door = visitAndExitCheckTemperature(inform.temperature);
			} while (door == 1);



			FILE* customer;
			customer = fopen("CustomerInformation.bin", "ab");
			if (customer == NULL)
			{
				printf("Can't open the file");
				exit(-999);
			}
			fwrite(&inform, sizeof(Information), 1, customer);

			fclose(customer);


			printf("You want to add more? press Y/y to continue >");
			rewind(stdin);
			scanf("%c", &ans);
		} while (ans == 'Y' || ans == 'y');
		system("CLS");

		printf("Thank you for your visit ^_^\n");
	}
	else {
		red();
		printf("You are not allowed to add!\n");
		reset();
	}
}

void visitAndExitDisplay()
{
	int visit = 1;
	Information inform;
	int code;

	FILE* customer;
	customer = fopen("CustomerInformation.bin", "rb");

	if (customer == NULL)
	{
		printf("Can't open the file");
		exit(-999);
	}

	do
	{
		printf("\t\t\t+========================================================+\n");
		printf("\t\t\t|                      Display Menu                      |\n");
		printf("\t\t\t+========================================================+\n");
		printf("\t\t\t|        1.Morning Visitor Record   (06:00-11:59 )       |\n");
		printf("\t\t\t|                                                        |\n");
		printf("\t\t\t|        2.Afternnon Visitor Record (12:00-16:59)        |\n");
		printf("\t\t\t|                                                        |\n");
		printf("\t\t\t|        3.Evening Visitor Record   (17:00-20:00 )       |\n");
		printf("\t\t\t|                                                        |\n");
		printf("\t\t\t|        4. Display All Record      (06:00- 20:00)       |\n");
		printf("\t\t\t|                                                        |\n");
		printf("\t\t\t|        5. Exit                                         |\n");
		printf("\t\t\t+========================================================+\n");

		printf("Please enter display time > ");
		rewind(stdin);
		scanf("%d", &code);

		system("CLS");

		if (code == 1)
			morningRecord();
		else if (code == 2)
			afternoonRecord();
		else if (code == 3)
			eveningRecord();
		else if (code == 4)
			allRecord();
		else if (code == 5)
			printf("Thank you so much ^-^\n");
		else
			printf("Invalid code , pls enter again ^-^\n");
		
	} while (code != 5 );
}

void visitAndExitSearch()
{

	Information read, save[50];
	int countVisitor = 0;
	char ic[15];
	int key;


	FILE* customer;
	customer = fopen("CustomerInformation.bin", "rb");

	if (customer == NULL)
	{
		printf("Can't open the file");
		exit(-999);
	}

	while (fread(&read, sizeof(Information), 1, customer) != 0)
	{
		save[countVisitor].date.day = read.date.day;
		save[countVisitor].date.month = read.date.month;
		save[countVisitor].date.year = read.date.year;
		strcpy(save[countVisitor].icNo, read.icNo);
		save[countVisitor].enterHour = read.enterHour;
		save[countVisitor].enterMinute = read.enterMinute;
		strcpy(save[countVisitor].venueID, read.venueID);
		save[countVisitor].temperature = read.temperature;
		save[countVisitor].hour = read.hour;
		save[countVisitor].minute = read.minute;

		countVisitor++;
	}
	fclose(customer);

	do
	{
		printf("Enter Visitor IC NO >");
		rewind(stdin);
		scanf("%s", &ic);
		printf("\t\t\t+===========================================+\n");
		printf("\t\t\t|           Visitor record                  |\n");
		printf("\t\t\t+===========================================+\n");
		printf("\n");
		for (int i = 0; i < countVisitor; i++)
		{
			if (strcmp(save[i].icNo, ic) == 0)
			{

				printf("\t\t\tVisitor %d\n", i + 1);
				printf("\t\t\t+===========================================+\n");
				printf("\t\t\t| Entered date         > %2d/%2d/%4d %8s|\n", save[i].date.day, save[i].date.month, save[i].date.year, " ");
				printf("\t\t\t|                                           |\n");
				printf("\t\t\t| Enter time           > %02d:%02d %13s|\n", save[i].enterHour, save[i].enterMinute, " ");
				printf("\t\t\t|                                           |\n");
				printf("\t\t\t| Visitor IC No        > %-15s    |\n", save[i].icNo);
				printf("\t\t\t|                                           |\n");
				printf("\t\t\t| Gender               > %-7s           |\n", save[i].gender);
				printf("\t\t\t|                                           |\n");
				printf("\t\t\t| Venue ID             > %-15s    |\n", save[i].venueID);
				printf("\t\t\t|                                           |\n");
				printf("\t\t\t| Visitor Temperature  > %2.2f %13s|\n", save[i].temperature, " ");
				printf("\t\t\t|                                           |\n");
				printf("\t\t\t| Exit Time            > %02d:%02d %13s|\n", save[i].hour, save[i].minute, " ");
				printf("\t\t\t+===========================================+\n");
				key = 0;
			}
			else if (i == countVisitor - 1)
			{
				printf("Error, please enter again\n");
				key = 0;

			}

		}
	} while (key == 0);
}

void visitAndExitModify(int power)
{
	if (power == 1) {

		Information read, save[50];
		int choice, visitor;
		int countVisitor = 0;
		char coc;

		FILE* customer;
		customer = fopen("CustomerInformation.bin", "rb");
		if (customer == NULL)
		{
			printf("Can't open the file");
			exit(-999);
		}

		while (fread(&read, sizeof(Information), 1, customer) != 0)
		{
			save[countVisitor].date.day = read.date.day;
			save[countVisitor].date.month = read.date.month;
			save[countVisitor].date.year = read.date.year;
			strcpy(save[countVisitor].icNo, read.icNo);
			save[countVisitor].enterHour = read.enterHour;
			save[countVisitor].enterMinute = read.enterMinute;
			strcpy(save[countVisitor].venueID, read.venueID);
			save[countVisitor].temperature = read.temperature;
			strcpy(save[countVisitor].gender, read.gender);
			save[countVisitor].hour = read.hour;
			save[countVisitor].minute = read.minute;

			countVisitor++;
		}
		fclose(customer);

		printf("+===========================================+\n");
		printf("|           Visitor record                  |\n");
		printf("+===========================================+\n");
		printf("\n");
		printf("+====================================================================================================================================================================================+\n");
		printf("|%2s Visitor No. %2s| %3s Entered date %2s    |  %2s Enter time %3s  | %2s Visitor IC No  %3s|%3s Gender %3s | %9s Venue ID %9s |   Visitor Temperature  | %3s Exit Time %3s  |\n", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ");
		printf("+====================================================================================================================================================================================+\n");

		for (int c = 0; c < countVisitor; c++)
		{
			printf("|%6s  %d %5s  | %3s %2d / %2d / %4d %2s  | %4s %02d:%02d %5s    |    %15s   |%3s %7s %3s|%10s%10s%10s|  %5s %2.2f %9s  |%5s %02d:%02d %6s |\n", " ", c + 1, " ", " ", save[c].date.day, save[c].date.month, save[c].date.year, " ", " ", save[c].enterHour, save[c].enterMinute, " ", save[c].icNo, " ", save[c].gender, " ", " ", save[c].venueID, " ", " ", save[c].temperature, " ", " ", save[c].hour, save[c].minute, " ");
			printf("+====================================================================================================================================================================================+\n");
		}

		printf("Please enter the which Visitor u want to modify (Visitor no.) > ");
		scanf("%d", &visitor);

		for (int q = 0; q < countVisitor; q++)
		{
			if (visitor == q + 1)
			{
				do
				{
					printf("+====================================================================================================================================================================================+\n");
					printf("|%2s Visitor No. %2s| %3s Entered date %2s    |  %2s Enter time %3s  | %2s Visitor IC No  %3s|%3s Gender %3s | %9s Venue ID %9s |   Visitor Temperature  | %3s Exit Time %3s  |\n", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ");
					printf("+====================================================================================================================================================================================+\n");
					printf("|%6s  %d %5s  | %3s %2d / %2d / %4d %2s  | %4s %02d:%02d %5s    |    %15s   |%3s %7s %3s|%10s%10s%10s|  %5s %2.2f %9s  |%5s %02d:%02d %6s |\n", " ", q + 1, " ", " ", save[q].date.day, save[q].date.month, save[q].date.year, " ", " ", save[q].enterHour, save[q].enterMinute, " ", save[q].icNo, " ", save[q].gender, " ", " ", save[q].venueID, " ", " ", save[q].temperature, " ", " ", save[q].hour, save[q].minute, " ");
					printf("+====================================================================================================================================================================================+\n");


					printf("+=================================================+\n");
					printf("|                    Modify                       |\n");
					printf("+=================================================+\n");
					printf("|              1. Visitor Ic No                   |\n");
					printf("|              2. Venue ID                        |\n");
					printf("|              3. Exit                            |\n");
					printf("+=================================================+\n");

					printf("Enter your choice > ");
					scanf("%d", &choice);

					if (choice == 1)
					{
						do
						{
							printf("Modify your Ic NO > ");
							scanf("%s", &read.icNo);

							printf("Confirm modify the result?\nIf yes press Y/y to continue > ");
							rewind(stdin);
							scanf("%c", &coc);
						} while (coc != 'Y' && coc != 'y');
						strcpy(save[q].icNo, read.icNo);
					}
					else if (choice == 2)
					{
						do
						{
							printf("Modify your venue ID > ");
							rewind(stdin);
							scanf("%[^\n]", &read.venueID);

							printf("Confirm, modify the result?\nIf yes press Y/y to continue > ");
							rewind(stdin);
							scanf("%c", &coc);

						} while (coc != 'Y' && coc != 'y');
						strcpy(save[q].venueID, read.venueID);
					}
					else if (choice == 3)
						printf("Sucessful to modify, thank you !\n");
					else
						printf("Invalid code, pls enter again\n");
				} while (choice != 3);

			}
			else if (q == countVisitor - 1)
			{
				printf("Error , cannot find the visitor.\n");
			}
		}

		customer = fopen("CustomerInformation.bin", "wb");
		if (customer == NULL)
		{
			printf("Can't open the file");
			exit(-999);
		}


		for (int a = 0; a < countVisitor; a++)
		{
			fwrite(&save[a], sizeof(Information), 1, customer);
		}
		fclose(customer);
	}

	else {
		red();
		printf("You are not allowed to modify!\n");
		reset();
	}

}


int visitAndExitCheckDate(int day, int month, int year)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{

		if (day >= 1 && day <= 31)
			return 0;
		else
		return 1;
		
	}

	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day >= 1 && day <= 30)
		{
			return 0;
		}
		else
			return 1;
	}

	else if (month == 2)
	{
		if (year / 4 != 0)
		{
			if (day >= 1 && day <= 29)
			{
				return 0;
			}
			else
				return 1;
			
		}
		else if (year % 4 == 0)
		{
			return 0;
		}
		else
			return 1;
	}
	else
		return 1;
}

int visitAndExitCheckTime(int enterHour, int enterMinute)
{
	if (enterHour >= 6 && enterHour <= 20 && enterMinute >= 0 && enterMinute <= 59)
		return 0;

	else
	{
		printf("Invalid time, pls enter again\n");
		return 1;
	}

}

int visitAndExitCheckEnterExitTime(int enterHour, int enterMinute, int hour, int minute)
{
	if (hour == enterHour)
	{
		if (minute > enterMinute)
			return 1;//true
		else
		{
			printf("Invalid time, pls enter again!\n");
			return 0;//false
		}
			
	}
	else if (hour > enterHour)
	{
		return 1;
	}
	else
	{
		printf("Invalid time, pls enter again!\n");
		return 0;
	}
		
		
}

int visitAndExitCheckID(char icNo[15])
{
	//020202-02-0202
	if (strlen(icNo) ==14 )
	{
		
		for (int a = 0; a < 15; a++)
		{
			if (a == 6 || a == 9 && icNo[a] == '-' )
			{
				
			}
			else if (isalpha(icNo[a]) != 0)
			{
				printf("Invalid Ic No, pls enter again\n");
				return 0;

			}
			else if (a == 15)
			{
				return 1;
			}
		}
	}
	
	else
	{
		printf("hihi");
		printf("Invalid Ic No, pls enter again\n");
		return 0;
	}

		
	
}

float visitAndExitCheckTemperature(float temperature)
{
	if (temperature >= 36.30 && temperature <= 37.49)
		return 0;
	else if (temperature <= 36.0)
	{
		printf("Opps Cannot  visit -_-\n");
		return 1;
	}
	else if (temperature >= 37.50)
	{
		printf("Opps Cannot  visit -_-\n");
		return 1;
	}
}

void morningRecord()
{
	Information inform,read, save[50];
	int countVisitor = 0;
	int num = 1;

	FILE* customer;
	customer = fopen("CustomerInformation.bin", "rb");

	if (customer == NULL)
	{
		printf("Can't open the file");
		exit(-999);
	}

	while (fread(&read, sizeof(Information), 1, customer) != 0)
	{
		save[countVisitor].date.day = read.date.day;
		save[countVisitor].date.month = read.date.month;
		save[countVisitor].date.year = read.date.year;
		strcpy(save[countVisitor].icNo, read.icNo);
		save[countVisitor].enterHour = read.enterHour;
		save[countVisitor].enterMinute = read.enterMinute;
		strcpy(save[countVisitor].venueID, read.venueID);
		save[countVisitor].temperature = read.temperature;
		save[countVisitor].hour = read.hour;
		save[countVisitor].minute = read.minute;
		strcpy(save[countVisitor].gender, read.gender);

		countVisitor++;
	}
	fclose(customer);

	printf("\t\t+===========================================+\n");
	printf("\t\t|           Visitor record                  |\n");
	printf("\t\t+===========================================+\n");
	printf("\n");

	printf("+====================================================================================================================================================================================+\n");
	printf("|%2s Visitor No. %2s| %3s Entered date %2s    |  %2s Enter time %3s  | %2s Visitor IC No  %3s|%3s Gender %3s | %9s Venue ID %9s |   Visitor Temperature  | %3s Exit Time %3s  |\n", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ");
	printf("+====================================================================================================================================================================================+\n");
	for (int i = 0; i < countVisitor; i++)
	{
		if (save[i].enterHour > 5 && save[i].enterHour < 12)
		{
			printf("|%6s  %d %5s  | %3s %2d / %2d / %4d %2s  | %4s %02d:%02d %5s    |    %15s   |%3s %7s %3s|%5s%20s%5s|  %5s %2.2f %9s  |%5s %02d:%02d %6s |\n", " ", num++, " ", " ", save[i].date.day, save[i].date.month, save[i].date.year, " ", " ", save[i].enterHour, save[i].enterMinute, " ", save[i].icNo , " ", save[i].gender," ", " ", save[i].venueID, " ", " ", save[i].temperature, " ", " ", save[i].hour, save[i].minute, " ");
			printf("+====================================================================================================================================================================================+\n");


		}
	}

}

void afternoonRecord()
{
	Information inform, read, save[50];
	int countVisitor = 0;
	int num = 1;

	FILE* customer;
	customer = fopen("CustomerInformation.bin", "rb");

	if (customer == NULL)
	{
		printf("Can't open the file");
		exit(-999);
	}

	while (fread(&read, sizeof(Information), 1, customer) != 0)
	{
		save[countVisitor].date.day = read.date.day;
		save[countVisitor].date.month = read.date.month;
		save[countVisitor].date.year = read.date.year;
		strcpy(save[countVisitor].icNo, read.icNo);
		save[countVisitor].enterHour = read.enterHour;
		save[countVisitor].enterMinute = read.enterMinute;
		strcpy(save[countVisitor].venueID, read.venueID);
		save[countVisitor].temperature = read.temperature;
		save[countVisitor].hour = read.hour;
		save[countVisitor].minute = read.minute;
		strcpy(save[countVisitor].gender, read.gender);

		countVisitor++;
	}
	fclose(customer);

	printf("+===========================================+\n");
	printf("|           Visitor record                  |\n");
	printf("+===========================================+\n");
	printf("\n");

	printf("+====================================================================================================================================================================================+\n");
	printf("|%2s Visitor No. %2s| %3s Entered date %2s    |  %2s Enter time %3s  | %2s Visitor IC No  %3s|%3s Gender %3s | %9s Venue ID %9s |   Visitor Temperature  | %3s Exit Time %3s  |\n", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ");
	printf("+====================================================================================================================================================================================+\n");
	for (int a = 0; a < countVisitor; a++)
	{
		if (save[a].enterHour >= 12 && save[a].enterHour <= 16)
		{
			printf("|%6s  %d %5s  | %3s %2d / %2d / %4d %2s  | %4s %02d:%02d %5s    |    %15s   |%3s %7s %3s|%5s%20s%5s|  %5s %2.2f %9s  |%5s %02d:%02d %6s |\n", " ", num++, " ", " ", save[a].date.day, save[a].date.month, save[a].date.year, " ", " ", save[a].enterHour, save[a].enterMinute, " ", save[a].icNo, " ", save[a].gender, " ", " ", save[a].venueID, " ", " ", save[a].temperature, " ", " ", save[a].hour, save[a].minute, " ");
			printf("+====================================================================================================================================================================================+\n");
		}
	}
}

void eveningRecord()
{
	Information inform, read, save[50];
	int countVisitor = 0;
	int num = 1;

	FILE* customer;
	customer = fopen("CustomerInformation.bin", "rb");

	if (customer == NULL)
	{
		printf("Can't open the file");
		exit(-999);
	}

	while (fread(&read, sizeof(Information), 1, customer) != 0)
	{
		save[countVisitor].date.day = read.date.day;
		save[countVisitor].date.month = read.date.month;
		save[countVisitor].date.year = read.date.year;
		strcpy(save[countVisitor].icNo, read.icNo);
		save[countVisitor].enterHour = read.enterHour;
		save[countVisitor].enterMinute = read.enterMinute;
		strcpy(save[countVisitor].venueID, read.venueID);
		save[countVisitor].temperature = read.temperature;
		save[countVisitor].hour = read.hour;
		save[countVisitor].minute = read.minute;
		strcpy(save[countVisitor].gender, read.gender);

		countVisitor++;
	}
	fclose(customer);

	printf("\t\t+===========================================+\n");
	printf("\t\t|           Visitor record                  |\n");
	printf("\t\t+===========================================+\n");
	printf("\n");
	printf("+====================================================================================================================================================================================+\n");
	printf("|%2s Visitor No. %2s| %3s Entered date %2s    |  %2s Enter time %3s  | %2s Visitor IC No  %3s|%3s Gender %3s | %9s Venue ID %9s |   Visitor Temperature  | %3s Exit Time %3s  |\n", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ");
	printf("+====================================================================================================================================================================================+\n");
	for(int b=0; b < countVisitor; b++)
	{
		if (save[b].enterHour > 16 && save[b].enterHour < 21)
		{
			
			
			printf("|%6s  %d %5s  | %3s %2d / %2d / %4d %2s  | %4s %02d:%02d %5s    |    %15s   |%3s %7s %3s|%5s%20s%5s|  %5s %2.2f %9s  |%5s %02d:%02d %6s |\n", " ", num++, " ", " ", save[b].date.day, save[b].date.month, save[b].date.year, " ", " ", save[b].enterHour, save[b].enterMinute, " ", save[b].icNo, " ", save[b].gender, " ", " ", save[b].venueID, " ", " ", save[b].temperature, " ", " ", save[b].hour, save[b].minute, " ");
			printf("+====================================================================================================================================================================================+\n");


		}
	}
}

void allRecord()
{
	Information inform, read, save[50];
	int countVisitor = 0;

	FILE* customer;
	customer = fopen("CustomerInformation.bin", "rb");

	if (customer == NULL)
	{
		printf("Can't open the file");
		exit(-999);
	}

	printf("\t\t\+===========================================+\n");
	printf("\t\t|           Visitor record                  |\n");
	printf("\t\t+===========================================+\n");
	printf("\n");

	printf("+====================================================================================================================================================================================+\n");
	printf("|%2s Visitor No. %2s| %3s Entered date %2s    |  %2s Enter time %3s  | %2s Visitor IC No  %3s|%3s Gender %3s | %9s Venue ID %9s |   Visitor Temperature  | %3s Exit Time %3s  |\n", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ");
	printf("+====================================================================================================================================================================================+\n");

	while (fread(&read, sizeof(Information), 1, customer) != 0)
	{

		
		printf("|%6s  %d %5s  | %3s %2d / %2d / %4d %2s  | %4s %02d:%02d %5s    |    %15s   |%3s %7s %3s|%5s%20s%5s|  %5s %2.2f %9s  |%5s %02d:%02d %6s |\n", " ", 1+ countVisitor, " ", " ", read.date.day, read.date.month, read.date.year, " ", " ", read.enterHour, read.enterMinute, " ", read.icNo, " ", read.gender, " ", " ", read.venueID, " ", " ", read.temperature, " ", " ", read.hour, read.minute, " ");
		printf("+====================================================================================================================================================================================+\n");

		countVisitor++;
	}
	fclose(customer);

}

void visitAndExitReport()
{
	Information inform, read, save[50];
	int countVisitor = 0;
	int num = 1;
	int totalVisitor = 0;
	int totalExit = 0;
	int nTemperature = 0, unTemperature = 0, computer = 0, gym = 0, library = 0;


	FILE* customer;
	customer = fopen("CustomerInformation.bin", "rb");

	if (customer == NULL)
	{
		printf("Can't open the file");
		exit(-999);
	}

	while (fread(&read, sizeof(Information), 1, customer) != 0)
	{
		save[countVisitor].date.day = read.date.day;
		save[countVisitor].date.month = read.date.month;
		save[countVisitor].date.year = read.date.year;
		strcpy(save[countVisitor].icNo, read.icNo);
		save[countVisitor].enterHour = read.enterHour;
		save[countVisitor].enterMinute = read.enterMinute;
		strcpy(save[countVisitor].venueID, read.venueID);
		save[countVisitor].temperature = read.temperature;
		save[countVisitor].hour = read.hour;
		save[countVisitor].minute = read.minute;
		strcpy(save[countVisitor].gender, read.gender);

		countVisitor++;
	}
	fclose(customer);

	
	for (int n = 0; n < countVisitor; n++)
	{
		if (strcmp(save[n].venueID, "computer lab") == 0)
		{
			if (save[n].temperature >= 37.5 || save[n].temperature <= 36.0)
			{
				unTemperature++;
			}
			else
				nTemperature++;
			computer++;
		}
		else if (strcmp(save[n].venueID, "gym room") == 0)
		{
			if (save[n].temperature >= 37.5 || save[n].temperature <= 36.0)
			{
				unTemperature++;
			}
			else
				nTemperature++;
			gym++;

		}
		else if (strcmp(save[n].venueID, "library") == 0)
		{
			if (save[n].temperature >= 37.5 || save[n].temperature <= 36.0)
			{
				unTemperature++;
			}
			else
				nTemperature++;
			library++;
		}
			
	}
	printf("+====================================================================================================================================================================================+\n");
	printf("|%2s Visitor No. %2s| %3s Entered date %2s    |  %2s Enter time %3s  | %2s Visitor IC No  %3s|%3s Gender %3s | %9s Venue ID %9s |   Visitor Temperature  | %3s Exit Time %3s  |\n", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ");
	printf("+====================================================================================================================================================================================+\n");
	
	customer = fopen("CustomerInformation.bin", "rb");

	if (customer == NULL)
	{
		printf("Can't open the file");
		exit(-999);
	}
	countVisitor = 0;

	while (fread(&read, sizeof(Information), 1, customer) != 0)
	{


		printf("|%6s  %d %5s  | %3s %2d / %2d / %4d %2s  | %4s %02d:%02d %5s    |    %15s   |%3s %7s %3s|%5s%20s%5s|  %5s %2.2f %9s  |%5s %02d:%02d %6s |\n", " ", 1 + countVisitor, " ", " ", read.date.day, read.date.month, read.date.year, " ", " ", read.enterHour, read.enterMinute, " ", read.icNo, " ", read.gender, " ", " ", read.venueID, " ", " ", read.temperature, " ", " ", read.hour, read.minute, " ");
		printf("+====================================================================================================================================================================================+\n");

		countVisitor++;
	}
	fclose(customer);

	printf("\t\t+=============================================+\n");
	printf("\t\t|Computer lab   Total Visitor     > %d         |\n", computer);
	printf("\t\t|Gym Room       Total Visitor     > %d         |\n", gym);
	printf("\t\t|Library        Total Visitor     > %d         |\n", library);
	printf("\t\t|                                             |\n");
	printf("\t\t|Total normal temperature         > %d         |\n", nTemperature);
	printf("\t\t|Total unusual temperature        > %d         |\n", unTemperature);
	printf("\t\t|Total Visitor                    >%2d         |\n", countVisitor);
	printf("\t\t+=============================================+\n");
	
}
