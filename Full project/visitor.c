#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<math.h>

#pragma warning(disable:4996)

typedef struct
{
	char icNo[15];
	char telNum[13];
	char name[20];
	char venue[100];
	int day, month, year, hour, min;
	float temperature;
	char tempCheck[10];
	char firststLine;
	char orderNum;
	char position[20];
}Visitor;

void shiZiJia();
const char* readFile123(int j);
void writeFile(int num, int count, Visitor data[20]);
int readFile(Visitor data[20]);
int checkName(char name[20]);
void visitorSystem(int power);
int Add();
void sreach();
void addChoice(int power);
int modifyMenu();
int sreachMenu();
int sreachName(Visitor data[20], int count, char name[20]);
void sreachVenue(Visitor data[20], int count, char venue[20], int choice);
void sreachTime(Visitor data[20], int choice, int count);
void display();
void visitorModify(int power);
void modifyName(Visitor modifyData[20], int count, char input[20]);
void report();
void openFile();
int readFile(Visitor data[20]);
int deleteMenu();
void delData(int num, int position[20], int count, Visitor data[20]);
void writeFile(int num, int count, Visitor data[20]);
void printData(int num, Visitor data[20]);

int checkName(char name[20])
{
	Visitor data[20];
	readFile(data);
	int nameCount = 0;
	for (int i = 0; i < 20; i++)
	{

		if (strcmp(data[i].name, name) == 0)
			nameCount++;
	}
	return nameCount;
}

int readFile(Visitor data[20])
{
	FILE* fptr1;
	char name;
	int count = 0;

	fptr1 = fopen("visitorData.txt", "r");

	fscanf(fptr1, "%[^\n]\n", &data->firststLine);

	while (!feof(fptr1))
	{
		fscanf(fptr1, "%[^\t]\t", &data[count].orderNum);
		fscanf(fptr1, "%20[^\t]", &data[count].name);
		fscanf(fptr1, "\t%30[^\t]", &data[count].position);
		fscanf(fptr1, "\t%30[^\t]", &data[count].icNo);
		fscanf(fptr1, "\t%30[^\t]", &data[count].telNum);
		fscanf(fptr1, "\t%50[^\t]", &data[count].venue);
		fscanf(fptr1, "\t%5f", &data[count].temperature);
		fscanf(fptr1, "\t%d/%d/%d", &data[count].day, &data[count].month, &data[count].year);
		fscanf(fptr1, "%d:", &data[count].hour);
		fscanf(fptr1, "%d", &data[count].min);
		fscanf(fptr1, "%20s\n", &data[count].tempCheck);
		count++;
	}

	fclose(fptr1);
	return count;
}

void writeFile(int num, int count, Visitor data[20])
{
	FILE* fptr2;
	fptr2 = fopen("visitorData.txt", "w");

	fprintf(fptr2, "	               name:		            	   position                 IC No.							   Tel.No						  venue			temp	date		time			temp check\n");
	for (int i = 0; i <= count - num - 1; i++)
	{
		fprintf(fptr2, "%d)\t", i + 1);
		fprintf(fptr2, "%20s\t", data[i].name);
		fprintf(fptr2, "%30s\t", data[i].position);
		fprintf(fptr2, "%30s\t", data[i].icNo);
		fprintf(fptr2, "%30s\t", data[i].telNum);
		fprintf(fptr2, "%30s\t", data[i].venue);
		fprintf(fptr2, "%5.2f\t", data[i].temperature);
		fprintf(fptr2, "%d/", data[i].day);
		fprintf(fptr2, "%d/", data[i].month);
		fprintf(fptr2, "%d\t", data[i].year);
		fprintf(fptr2, "%d:", data[i].hour);
		fprintf(fptr2, "%d", data[i].min);
		fprintf(fptr2, "%20s\n", data[i].tempCheck);
	}
	fclose(fptr2);
}

void visitorSystem(int power)
{
	int choice;

	do
	{
		space(30);
		cornerTopLeft();
		line2(41);
		cornerTopRight();
		printf("\n");

		space(30);
		line();
		printf("             Visitor Menu                ");
		line();
		printf("\n");

		space(30);
		connectionLeft();
		line2(41);
		connectionRight();
		printf("\n");

		space(30);
		line();
		printf("            1. Adding data               ");
		line();
		printf("\n");

		space(30);
		line();
		printf("            2. sreach(delete) data       ");
		line();
		printf("\n");

		space(30);
		line();
		printf("            3. Display data              ");
		line();
		printf("\n");

		space(30);
		line();
		printf("            4. Modify data               ");
		line();
		printf("\n");

		space(30);
		line();
		printf("            5. overall report            ");
		line();
		printf("\n");


		space(30);
		line();
		printf("            6. Exit                      ");
		line();
		printf("\n");

		space(30);
		cornerBotomLeft();
		line2(41);
		cornerBotomRight();
		printf("\n");
		printf("your choice >");
		scanf("%d", &choice);
		rewind(stdin);

		while (choice < 1 || choice > 6)
		{
			printf("error, please enter choice between 1~6");
			scanf("%d", &choice);
			rewind(stdin);
		}

		system("cls");

		switch (choice)
		{
		case 1:
			addChoice(power);
			system("cls");
			break;
		case 2:
			sreach();
			system("pause");
			system("cls");
			break;
		case 3:
			display();
			system("pause");
			system("cls");
			break;
		case 4:
			visitorModify(power);
			system("pause");
			system("cls");
			break;
		case 5:
			report();
			system("pause");
			system("cls");
			break;
		case 6:
			printf("thanks for using\n");
			system("pause");
			break;
		}
	} while (choice !=6);

}

void addChoice(int power)
{
	if (power == 1) {

		char choice;

		printf("start enter user data\n");


		do
		{
			Add();
			printf("continue input?(n=>exit to main menu,y>coninue)");
			scanf("%c", &choice);
			rewind(stdin);

			while (choice != 'y' && choice != 'n')
			{
				printf("error,please enter the choice according to the order (n=>exit to main menu,y>coninue)");
				scanf("%c", &choice);
				rewind(stdin);
			}


		} while (choice != 'n');

	}
	else {
		red();
		printf("You are not allowed to add file!");
		system("pause");
	}

		
}

int Add()
{
	FILE* fptr1;
	FILE* fptr2;
	FILE* fptr3;
	Visitor input;
	char choice;
	int visitorNum = 0;
	int namecount = 0;
	char check;
	int nameCheck = 0;
	int count;
	char venueName[19][50] = { 0 };
	SYSTEMTIME t;
	GetLocalTime(&t);
	Visitor data[20];

	fptr2 = fopen("visitorData.txt", "r");

	if (fptr2 == NULL)
	{
		printf("error,unable to locate file,do you want to create a files and add some data first?(y=yes,n=return to main menu)");
		scanf("%c", &choice);
		rewind(stdin);

		while (choice != 'y' && choice != 'n')
		{
			printf("error,please enter chocie (y=yes,n=return to main menu)>");
			scanf("%c", &choice);
			rewind(stdin);
		}
		if (choice == 'y')
		{
			openFile();
		}

		else
			exit(-1);
	}

	count=readFile(data);

	fptr1 = fopen("visitorData.txt", "a");

	do
	{

		do
		{
			namecount = 0;
			printf("enter name>");
			scanf("%[^\n]", &input.name);
			rewind(stdin);
			for (int i = 0; i < 20; i++)
			{
				if (strcmp(data[i].name, input.name) == 0)
					namecount++;
			}
			if (namecount > 0)
			{
				printf("there is more than one of data having a same name, are you sure this is a correct data?(1=>yes,2=>no,reenter the data)>\n");
				scanf("%d", &nameCheck);
				rewind(stdin);

				while (nameCheck != 1 && nameCheck != 2)
				{
					printf("error, enter the choice between  1~2(1=>yes,2=>2=>no,reenter the data)>");
					scanf("%d", &nameCheck);
					rewind(stdin);
				}

			}
			if (namecount == 0)
			{
				nameCheck = 1;
			}
		} while (nameCheck==2);


		if (nameCheck != 2)
		{
			int whoareyou;
			printf("\nenter your position(1=>student 2=>teacher 3=>staffs 4=>visitors)>");
			scanf("%d", &whoareyou);
			rewind(stdin);

			while (whoareyou < 1 || whoareyou > 4)
			{
				printf("error, please enter the position(1=>student 2=>tutor 3=>staffs 4=>visitors)>");
				scanf("%d", &whoareyou);
				rewind(stdin);
			}

			if (whoareyou == 1)
				strcpy(input.position, "student");
			if (whoareyou == 2)
				strcpy(input.position, "teacher");
			if (whoareyou == 3)
				strcpy(input.position, "staffs");
			if (whoareyou == 4)
				strcpy(input.position, "visitors");

			printf("\nenter ic number (eg.123456-12-1234)>");
			scanf("%[^\n]", &input.icNo);
			rewind(stdin);

			while (input.icNo[6] != '-' || input.icNo[9] != '-' || strlen(input.icNo) != 14)
			{
				printf("error, please enter the ic number according to the provided format=>(123456-12-1234)>");
				scanf("%[^\n]", &input.icNo);
				rewind(stdin);
			}

			printf("\nenter your telephone number(eg.012-3456789)>");
			scanf("%[^\n]", &input.telNum);
			rewind(stdin);

			for (int i = 0; i < 12; i++)
			{
				while (input.telNum[3] != '-' || strlen(input.telNum) != 11 || (input.telNum[i] >= 'a' && input.telNum[i] <= 'z') || (input.telNum[i] >= 'A' && input.telNum[i] <= 'Z'))
				{
					printf("error,enter your telephone number in the folllowing format(eg.012-3456789)>");
					scanf("%[^\n]", &input.telNum);
					rewind(stdin);
				}
			}

			FILE* readRow;
			char c;
			int countOfRow = 0;

			readRow = fopen("venue.txt", "r");

			while (fscanf(readRow, "%c", &c) != EOF) {
				if (c == '\n')
					countOfRow++;
			}
			fclose(readRow);
			int totalRowOfData = countOfRow / 2;

			for (int i = 0; i < totalRowOfData; i++) {
				strcpy(venueName[i],readFile123(i));
			}

			int whrtogo;
			for (int i = 0; i < totalRowOfData; i++)
			{
				printf("%d)%s\n", i+1,venueName[i]);
			}
			printf("\n");
			printf("\nenter the place visited>");
			scanf("%d", &whrtogo);
			rewind(stdin);

			while (whrtogo < 1 || whrtogo > 19)
			{
				printf("\nenter the place you visited in range of 1~19>");
				scanf("%d", &whrtogo);
				rewind(stdin);
			}

			strcpy(input.venue, venueName[whrtogo-1]);
			//if (whrtogo == 1)
			//	strcpy(input.venue, "computer lab");
			//if (whrtogo == 2)
			//	strcpy(input.venue, "swimming pool");
			//if (whrtogo == 3)
			//	strcpy(input.venue, "library");

			printf("\nnow, enter your body temperature>");
			scanf("%f", &input.temperature);
			rewind(stdin);
			if (input.temperature <= 35 || input.temperature >= 40)
			{
				printf("Unnatural body temperature, you are not allowed to go in.");
				strcpy(input.tempCheck, "abnormal");
			}


			printf("\n\nbelow is the data you have entered>\n");
			printf("----------------------------------------\n");
			printf("|name:%33s|\n|icNo:%33s|\n|telephone number:%21s|\n|venue:%32s|\n|body temperature:%21.2f|\n|date:%26d/%d/%d|\n|time:%30d:%d|\n", input.name, input.icNo, input.telNum, input.venue, input.temperature, t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
			printf("----------------------------------------\n");
			printf("is the data correct? (y=yes,n=reenter)");
			scanf("%c", &choice);
			rewind(stdin);
			while (choice != 'y' && choice != 'n')
			{
				printf("error,please enter the choice according to the order (y=yes,n=reenter)");
				scanf("%c", &choice);
				rewind(stdin);
			}
		}

	} while (choice != 'y');

	char c;

	fptr3 = fopen("visitorData.txt", "r");
	while (!feof(fptr3))
	{
		fscanf(fptr3, "%c", &c);

		if (c == '\n')
			visitorNum++;

	}

	if (input.temperature >= 36.3 && input.temperature <= 37.5)
	{
		printf("you are visiter num>%d, welcome to taruc ^.^\n", visitorNum - 1);
		strcpy(input.tempCheck, "normal");
	}
	else
	{
		printf("abnormal body temperature, you are not allowed to go in");
		strcpy(input.tempCheck, "abnormal");
	}


	fclose(fptr3);

	fprintf(fptr1, "%d)\t", count + 1);
	fprintf(fptr1, "%20s\t", input.name);
	fprintf(fptr1, "%30s\t", input.position);
	fprintf(fptr1, "%30s\t", input.icNo);
	fprintf(fptr1, "%30s\t", input.telNum);
	fprintf(fptr1, "%30s\t", input.venue);
	fprintf(fptr1, "%5.2f\t", input.temperature);
	fprintf(fptr1, "%d/", t.wDay);
	fprintf(fptr1, "%d/", t.wMonth);
	fprintf(fptr1, "%d\t", t.wYear);
	fprintf(fptr1, "%d:", t.wHour);
	fprintf(fptr1, "%d", t.wMinute);
	fprintf(fptr1, "%20s\n", input.tempCheck);

	printf("the data has successfully inputed\n");

	fclose(fptr1);
}

void sreach()
{

	FILE* fptr1;
	FILE* fptr2;
	Visitor sreachData[20];
	int count = 0;
	int choice;
	int pick;
	char name[20];
	char venue1[20];
	char position[20];
	fptr1 = fopen("visitorData.txt", "r");

	if (fptr1 == NULL)
	{
		printf("error,unable to locate file,do you want to create a files and add some data first?(y=yes,n=return to main menu)");
		scanf("%c", &choice);
		rewind(stdin);

		while (choice != 'y' && choice != 'n')
		{
			printf("error,please enter chocie (y=yes,n=return to main menu)>");
			scanf("%c", &choice);
			rewind(stdin);
		}
		if (choice == 'y')
		{
			openFile();
			exit(-1);
		}

		else
			exit(-1);
	}
	do
	{

		count = readFile(sreachData);


		printf("welcome to sreach menu,which action do you love to take after sreaching these datas?\n");
		printf("1.display data\n2.delete data>,0=>return to main menu");
		scanf("%d", &pick);
		rewind(stdin);

		while (pick < 0 || pick > 2)
		{
			printf("error,please enter choice between (1=>display data,2=>delete data,0>return to main menu)>");
			scanf("%d", &pick);
			rewind(stdin);
		}

		if (pick == 1)
			choice = sreachMenu();
		if (pick == 2)
			choice = deleteMenu();
		if (pick == 0)
			break;

		switch (choice)
		{
		case 1:
			printf("enter the name you hope to sreach for:");
			gets(name);
			rewind(stdin);
			sreachName(sreachData, count, name);
			fclose(fptr1);
			break;
		case 2:
			printf("enter the venue you hope to sreach for:");
			gets(venue1);
			rewind(stdin);
			sreachVenue(sreachData, count, venue1, choice);
			fclose(fptr1);
			break;
		case 3:
			printf("enter the following data to sreach the data you hope to display>\n");
			sreachTime(sreachData, choice, count);
			fclose(fptr1);
			break;
		case 4:
			printf("enter the following data to sreach the data you hope to display	>\n");
			gets(position);
			rewind(stdin);
			sreachVenue(sreachData, count, position, choice);
			fclose(fptr1);
			break;
		case 5:
			printf("enter the following data to sreach the data you hope to delete>\n");
			sreachTime(sreachData, choice, count);
			fclose(fptr1);
			break;
		case 6:
			printf("enter the venue you hope to delete for:");
			gets(venue1);
			rewind(stdin);
			sreachVenue(sreachData, count, venue1, choice);
			fclose(fptr1);
			break;
		case 7:
			printf("enter the position to sreach the data you hope to delete	>\n");
			gets(position);
			rewind(stdin);
			sreachVenue(sreachData, count, position, choice);
			fclose(fptr1);
			break;
		}
	} while (choice != 0);



}

int sreachMenu()
{
	int choice;
	printf("which category of data you hope to sreach for?\n");
	printf("1=>name\n");
	printf("2=>venue visited\n");
	printf("3=>time\n");
	printf("4=>position\n");
	printf("0=>exit to main menu\n");

	scanf("%d", &choice);
	rewind(stdin);
	while (choice < 0 || choice > 4)
	{
		printf("error,please enter the choice between the range(0~3)");
		scanf("%d", &choice);
		rewind(stdin);
	}

	return choice;
}

int deleteMenu()
{
	int choice;
	printf("which category of data you hope to delete for?\n");
	printf("1=>time\n");
	printf("2=>venue visited\n");
	printf("0=>exit to main menu\n");
	scanf("%d", &choice);
	rewind(stdin);

	while (choice != 1 && choice != 2 && choice != 3)
	{
		printf("error,please enter the choice between the range(1~2)");
		scanf("%d", &choice);
		rewind(stdin);
	}

	return choice + 4;
}

int sreachName(Visitor data[20], int count, char name[20])
{


	int result;
	int ava = 0;
	int delChoice;
	int position[20];
	int delPosition;


	for (int i = 0; i < count; i++)
	{
		result = strcmp(name, data[i].name);
		if (result == 0)
		{
			position[ava] = i;
			ava++;
		}
	}
	if (ava != 0)
	{
		printf("candidate available, below is the data inputed\n");
		for (int i = 0; i < ava; i++)
		{

			printf("%d", position[i] + 1);
			printf("------------------------------\n");
			printf("|name:%25s|\n|icNo:%25s|\n|telephone number:%13s|\n|venue:%24s|\n|body temperature:%13.2f|\n|date:%18d/%d/%d|\n|time:%22d:%d|\ntemperature check:%13s|\n", data[position[i]].name, data[position[i]].icNo, data[position[i]].telNum, data[position[i]].venue, data[position[i]].temperature, data[position[i]].day, data[position[i]].month, data[position[i]].year, data[position[i]].hour, data[position[i]].min, data[position[i]].tempCheck);
			printf("------------------------------\n\n");
		}
	}

	if (ava == 0)
	{
		printf("error, no candidate named %s is available.\n", name);
	}

	if (ava > 1)
	{
		printf("there is more than one candidate are having same name, are you wish to delete any one of them?(1=>yes,2=>no,return to sreach menu)");
		scanf("%d", &delChoice);
		rewind(stdin);

		while (delChoice != 1 && delChoice != 2)
		{
			printf("error, please enter the choice between (1=>yes,2=>no,return to sreach menu)");
			scanf("%d", &delChoice);
			rewind(stdin);
		}
		if (delChoice == 1)
		{
			printf("which one do you hope to delete?>");
			scanf("%d", &delPosition);
			position[0] = delPosition - 1;
			delData(1, position, count, data);
		}
	}
	system("pause");
	system("cls");
}

void sreachVenue(Visitor data[20], int count, char venue[20], int choice)
{

	Visitor temp[20];
	int result;
	int num = 0;
	int j;
	int k = 0;
	int position[20];
	int delposition[20];
	char delOption;
	int del1;
	int del2;


	if (choice == 6 || choice == 2)
		for (int i = 0; i < 20; i++)
		{
			result = strcmp(venue, data[i].venue);
			if (result == 0)
			{
				position[num] = i;
				num++;
			}
		}
	if (choice == 4 || choice == 7)
		for (int i = 0; i < 20; i++)
		{
			result = strcmp(venue, data[i].position);
			if (result == 0)
			{
				position[num] = i;
				num++;
			}
		}
	if (num > 0)
	{
		printf("candidate available, below are the data of candidate visited the venue(%s) recently\n\n", venue);
		printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("|NO|          name         |position|       icNo       |   tel number   |      venue                        | body temp |    date     |time    |temp check |\n");
		for (int i = 0; i < num; i++)
		{
			j = position[i];

			printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("|%2d|%20s   |%8s|%15s   |%13s   |%13s   |   %5.2f   |%2d/%2d/%2d   |%2d:%2d   |%8s   |\n", j + 1, data[j].name, data[j].position, data[j].icNo, data[j].telNum, data[j].venue, data[j].temperature, data[j].day, data[j].month, data[j].year, data[j].hour, data[j].min, data[j].tempCheck);
		}

		printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		if (choice == 6 || choice == 5)
		{
			printf("are you sure to delete these data?(y=yes,n=return to main menu)\n");
			scanf("%c", &delOption);
			rewind(stdin);
			while (delOption != 'y' && delOption != 'n')
			{
				printf("error, please enter (y=>yes,n=>return to main menu");
				scanf("%c", &delOption);
				rewind(stdin);
			}

			if (delOption == 'y')
			{
				printf("which range of data you hope to delete for(from)?");
				scanf("%d", &del1);
				printf("which range of data you hope to delete for(from)?");
				scanf("%d", &del2);
				del1 -= 1;
				del2 -= 1;
				for (int i = 0; i < 20; i++)
				{
					if (position[i] >= del1 && position[i] <= del2)
					{
						delposition[k] = position[i];
						k++;
					}
				}
				delData(k, delposition, count, data);
			}

		}

	}
	else
		printf("no data about(%c) available ", venue);

}

void sreachTime(Visitor data[20], int choice, int count)
{
	Visitor temp[20];
	int result;
	int num = 0;
	int position[20];
	int positionCount = 0;
	char delOption;
	int delposition[20];
	int del1;
	int del2;
	int k = 0;

	int date, month, hour, min;
	int date2, month2, hour2, min2;
	int tempMin, tempHour, tempDay;

	printf("from:\n");
	printf("month>");
	scanf("%d", &month);
	printf("date>");
	scanf("%d", &date);
	printf("hour>");
	scanf("%d", &hour);
	printf("min>");
	scanf("%d", &min);


	printf("to:\n");
	printf("month>");
	scanf("%d", &month2);
	printf("date>");
	scanf("%d", &date2);
	printf("hour>");
	scanf("%d", &hour2);
	printf("min>");
	scanf("%d", &min2);
	rewind(stdin);
	while (month > month2 || month > 12 || month < 1 || month2 > 12 || month2 < 1)
	{
		printf("error, please enter the time zone of month(from)>");
		scanf("%d", &month);
		printf("                                            (to)>");
		scanf("%d", &month2);
	}
	while (date > date2 || date > 31 || date < 1 || date2 > 31 || date2 < 1)
	{
		if (month2 > month)
			printf("error, please enter the time zone of date   (from)>");
		scanf("%d", &date);
		printf("                                            (to)>");
		scanf("%d", &date2);
	}

	while (hour > hour2 || hour > 24 || hour <= 0 || hour2 > 24 || hour2 <= 0)
	{
		printf("error, please enter the time zone of hour (from)>");
		scanf("%d", &hour);
		printf("                                            (to)>");
		scanf("%d", &hour2);
	}
	while (min >= 60 || min <= 0 || min2 >= 60 || min2 <= 0 && hour2 != hour)
	{
		printf("error, please enter the time zone of month(from)>");
		scanf("%d", &min);
		printf("                                            (to)>");
		scanf("%d", &min2);
	}

	if (month2 > month)
		tempDay = 31;
	else tempDay = date2;

	if (tempDay > date)
		tempHour = 24;
	else tempHour = hour2;

	if (tempHour > hour)
		tempMin = 60;
	else
		tempMin = min2;




	for (int i = 0; i < 20; i++)
	{
		if (data[i].month >= month && data[i].month <= month2 &&
			data[i].day >= date && data[i].day <= tempDay &&
			data[i].hour >= hour && data[i].hour <= tempHour &&
			data[i].min >= min && data[i].min <= tempMin)
		{
			position[num] = positionCount;
			num++;
		}
		positionCount++;
	}

	if (num > 0)
	{
		printf("candidate available, below are the data of candidate visited TARUC between %d/%d,%d:%d and %d/%d,%d:%d>\n\n", date, month, hour, min, date2, month2, hour2, min2);
		for (int i = 0; i < num; i++)
		{
			int j = position[i];
			printf("data number%d>\n", j + 1);
			printf("------------------------------\n");
			printf("|name:%25s|\n|icNo:%25s|\n|telephone number:%13s|\n|venue:%24s|\n|body temperature:%13.2f|\n|date:%18d/%d/%d|\n|time:%22d:%d|\n", data[j].name, data[j].icNo, data[j].telNum, data[j].venue, data[j].temperature, data[j].day, data[j].month, data[j].year, data[j].hour, data[j].min);
			printf("------------------------------\n\n");

		}
		system("pause");


		if (choice == 5)
		{
			printf("are you sure to delete all of these data?(y=yes,n=return to main menu)\n");
			scanf("%c", &delOption);
			rewind(stdin);
			while (delOption != 'y' && delOption != 'n')
			{
				printf("error, please enter (y=>yes,n=>return to main menu");
				scanf("%c", &delOption);
				rewind(stdin);
			}

			if (delOption == 'y')
			{
				printf("which range of data you hope to delete for(from)?");
				scanf("%d", &del1);
				printf("which range of data you hope to delete for(from)?");
				scanf("%d", &del2);
				del1 -= 1;
				del2 -= 1;
				for (int i = 0; i < 20; i++)
				{
					if (position[i] >= del1 && position[i] <= del2)
					{
						delposition[k] = position[i];
						k++;
					}
				}
				delData(k, delposition, count, data);
			}

		}
	}
	else
	{
		printf("no candidate has visited in this time zone\n");
		system("pause");
	}



}

void display()
{
	FILE* fptr1;
	Visitor displayData[20] = { 0 };
	int count = 0;
	char choice;

	fptr1 = fopen("visitorData.txt", "r");

	if (fptr1 == NULL)
	{
		printf("error,unable to locate file,do you want to create a files and add some data first?(y=yes,n=return to main menu)");
		scanf("%c", &choice);
		rewind(stdin);

		while (choice != 'y' && choice != 'n')
		{
			printf("error,please enter chocie (y=yes,n=return to main menu)>");
			scanf("%c", &choice);
			rewind(stdin);
		}
		if (choice == 'y')
		{
			openFile();
		}

		else
			exit(-1);

	}


	else
	{
		count = readFile(displayData);
		if (count > 0)
		{
			printf("data available, below are data inputed>\n\n");
			printData(count, displayData);
			fclose(fptr1);


		}
		else
		{
			printf("no data available\n");

		}

	}
}

void visitorModify(int power)
{
	if (power == 1) {

		FILE* fptr3;
		Visitor modifyData[20];
		char inputName[20];
		char inputTel[13];
		int count = 0;
		int choice;
		char pick;
		fptr3 = fopen("visitorData.txt", "r");

		if (fptr3 == NULL)
		{
			printf("error,unable to locate file,do you want to create a files and add some data first?(y=yes,n=return to main menu)");
			scanf("%c", &pick);
			rewind(stdin);

			while (pick == 'y' || pick == 'n')
			{
				printf("error,please enter chocie (y=yes,n=return to main menu)>");
				scanf("%c", &pick);
				rewind(stdin);
			}
			if (pick == 'y')
			{
				openFile();
			}

			else
				exit(-1);
		}

		count = readFile(modifyData);

		choice = modifyMenu();

		switch (choice)
		{
		case 1:
			printf("enter the name of the visitor that you hope to modify>");
			gets(inputName);
			rewind(stdin);
			modifyName(modifyData, count, inputName);
			break;
		case 2:
			printf("enter the telephone number of the visitor that you hope to modify>");
			gets(inputTel);
			rewind(stdin);
			modifyName(modifyData, count, inputTel);
			break;
		}
	}
	else{
		red();
		printf("You are not allowed to modify file!");
	}

}

int modifyMenu()
{
	int choice;
	printf("which category of data you hope to modify by?\n");
	printf("1=>name\n");
	printf("2=>Telephone number\n");
	printf("3=>cancel\n");

	scanf("%d", &choice);
	rewind(stdin);
	while (choice <= 1 && choice >= 3)
	{
		printf("error,please enter the choice between the range(1~4)");
		scanf("%d", &choice);
		rewind(stdin);
	}
	return choice;
}

void modifyName(Visitor modifyData[20], int count, char input[20])
{
	int sucessCount = 0;
	int position = 0;
	char choice;
	int aviability = 0;
	int whoareyou;
	char venueName[19][50];

	for (int i = 0; i < count; i++)
	{
		if (strcmp(input, modifyData[i].name) == 0 || strcmp(input, modifyData[i].telNum) == 0)
		{
			aviability = 1;
			position = i;
			
			int pick;
			printf("candidate available>\n");
			printf("------------------------------\n");
			printf("|name:%25s|\n|icNo:%25s|\n|telephone number:%13s|\n|venue:%24s|\n|body temperature:%13.2f|\n|date:%18d/%d/%d|\n|time:%22d:%d|\n", modifyData[position].name, modifyData[position].icNo, modifyData[position].telNum, modifyData[position].venue, modifyData[position].temperature, modifyData[position].day, modifyData[position].month, modifyData[position].year, modifyData[position].hour, modifyData[position].min, modifyData[position].tempCheck);
			printf("------------------------------\n\n");
			printf("enter the data you hope to modify below >\n");
			printf("name>");
			strcpy(modifyData[i].name, gets(input));
			rewind(stdin);

			printf("enter your position(1=>student 2=>tutor 3=>staffs 4=>visitors)>");
			scanf("%d", &whoareyou);
			rewind(stdin);

			while (whoareyou < 1 || whoareyou > 4)
			{
				printf("error, please enter the position(1=>student 2=>teacher 3=>staffs 4=>visitors)>");
				scanf("%d", &whoareyou);
				rewind(stdin);
			}

			if (whoareyou == 1)
				strcpy(modifyData[i].position, "student");
			if (whoareyou == 2)
				strcpy(modifyData[i].position, "teacher");
			if (whoareyou == 3)
				strcpy(modifyData[i].position, "staffs");
			if (whoareyou == 4)
				strcpy(modifyData[i].position, "visitors");

			printf("telephone number>");
			scanf("%s", modifyData[i].telNum);
			rewind(stdin);
			while (modifyData[i].telNum[3] != '-' && strlen(modifyData[i].telNum) != 9)
			{
				printf("error, please enter the ic number according to the provided format=>(012-3456789)>");
				scanf("%s", &modifyData[i].telNum);
				rewind(stdin);
			}
			printf("IC number");
			scanf("%s", modifyData[i].icNo);
			rewind(stdin);
			while (modifyData[i].icNo[6] != '-' || modifyData[i].icNo[9] != '-' || strlen(modifyData[i].icNo) != 14)
			{
				printf("error, please enter the ic number according to the provided format=>(123456-12-1234)>");
				scanf("%s", &modifyData[i].icNo);
				rewind(stdin);
			}

			for (int i = 0; i < 19; i++) {
				strcpy(venueName[i], readFile123(i));
			}

			int whrtogo;
			for (int i = 0; i < 19; i++)
			{
				printf("%d)%s\n", i + 1, venueName[i]);
			}
			printf("\n");
			printf("\nenter the place visited>");
			scanf("%d", &whrtogo);
			rewind(stdin);

			while (whrtogo < 1 || whrtogo > 19)
			{
				printf("\nenter the place you visited in range of 1~19>");
				scanf("%d", &whrtogo);
				rewind(stdin);
			}		
			strcpy(modifyData[i].venue, venueName[whrtogo - 1]);
		}
	}

	if (aviability == 1)
	{
		printf("below is the data after modified>\n\n");

		printf("------------------------------\n");
		printf("|name:%25s|\n|icNo:%25s|\n|telephone number:%13s|\n|venue:%24s|\n|body temperature:%13.2f|\n|date:%18d/%d/%d|\n|time:%22d:%d|\n", modifyData[position].name, modifyData[position].icNo, modifyData[position].telNum, modifyData[position].venue, modifyData[position].temperature, modifyData[position].day, modifyData[position].month, modifyData[position].year, modifyData[position].hour, modifyData[position].min, modifyData[position].tempCheck);
		printf("------------------------------\n\n");


		printf("are you sure to modify?(y=yes,n=no)");
		scanf("%c", &choice);
		rewind(stdin);

		while (choice != 'y' && choice != 'n')
		{
			printf("error,please enter (y=yes,n=no)");
			scanf("%c", &choice);
			rewind(stdin);
		}

		if (choice == 'y')
		{
			writeFile(0, count, modifyData);
		}

	}

	if (aviability == 0)
	{
		printf("no candidate available.");
	}



}

void report()
{
	FILE* fptr1;
	Visitor reportData[20];
	int count;
	int abnormalCount[12] = { 0 };
	char position[4][10] = { "teacher","student","staffs","visitors" };

	int totalAbnormalCount = 0, totalV1 = 0, totalV2 = 0, totalV3 = 0, totalAC1 = 0, totalAC2 = 0, totalAC3 = 0;
	int totalV[19] = { 0 };
	int totalAC[19] = { 0 };
	int month;
	int choice;
	char disMonth[10];
	int sreachVenue;
	char venueName[30][50];

	FILE* readRow;
	char c;
	int countOfRow = 0;

	readRow = fopen("venue.txt", "r");

	while (fscanf(readRow, "%c", &c) != EOF) {
		if (c == '\n')
			countOfRow++;
	}
	fclose(readRow);
	int totalRowOfData = countOfRow / 2;

	for (int i = 0; i < totalRowOfData; i++) {
		strcpy(venueName[i], readFile123(i));
	}

	typedef struct
	{
		int venue1[19][12], venue2[19][12], venue3[19][12];
		int abvenue1[19][12], abvenue2[19][12], abvenue3[19][12];

	}checkData;

	checkData whoAreYou[4] = { 0 };

	fptr1 = fopen("visitorData.txt", "r");

	if (fptr1 == NULL)
	{
		printf("error,unable to locate file,do you want to create a files and add some data first?(y=yes,n=return to main menu)");
		scanf("%c", &choice);
		rewind(stdin);

		while (choice != 'y' && choice != 'n')
		{
			printf("error,please enter chocie (y=yes,n=return to main menu)>");
			scanf("%c", &choice);
			rewind(stdin);
		}
		if (choice == 'y')
		{
			openFile();
			exit(-1);
		}

		else
			exit(-1);
	}


	count = readFile(reportData);

	for (int k = 0; k < 4; k++)
	{
		for (int l = 0; l < 19; l++)
		{
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < count; j++)
				{
					if (strcmp(reportData[j].venue, venueName[l]) == 0 && reportData[j].month == i && strcmp(reportData[j].position, position[k]) == 0)
					{
						if (strcmp(reportData[j].tempCheck, "abnormal") == 0)
						{
							whoAreYou[k].abvenue1[l][i]++;
							totalAC[l]++;
							totalAbnormalCount++;
						}
						else
						{
							whoAreYou[k].venue1[l][i]++;
							totalV[l]++;
						}

					}
				}
			}
		}
	}

	printf("                                total number of visitor>%d\n", count);
	printf("total visitor rejected due to abnormal body temperature>%d\n", totalAbnormalCount);

	do
	{
		printf("Report menu:\n");
		printf("1.Monthly Report\n");
		printf("2.Overall Report\n");
		printf("3.Exit\n");
		scanf("%d", &choice);
		rewind(stdin);

		while (choice < 1 || choice > 3)
		{
			printf("error,please enter choice between 1~3>\n");
			scanf("%d", &choice);
			rewind(stdin);
		}

		switch (choice)
		{
		case 1:
			printf("please enter your choice of report that you hope to view in term of month>");
			scanf("%d", &month);
			while (month < 1 && month > 12)
			{
				printf("error, please enter choice between 1~12");
				scanf("%d", &choice);
			}

			switch (month)
			{
			case 1:
				strcpy(disMonth, "January");
				break;
			case 2:
				strcpy(disMonth, "February");
				break;
			case 3:
				strcpy(disMonth, "March");
				break;
			case 4:
				strcpy(disMonth, "April");
				break;
			case 5:
				strcpy(disMonth, "May");
				break;
			case 6:
				strcpy(disMonth, "June");
				break;
			case 7:
				strcpy(disMonth, "July");
				break;
			case 8:
				strcpy(disMonth, "August");
				break;
			case 9:
				strcpy(disMonth, "September");
				break;
			case 10:
				strcpy(disMonth, "October");
				break;
			case 11:
				strcpy(disMonth, "November");
				break;
			default:
				strcpy(disMonth, "December");
				break;
			}


			printf("number of visitor visited by venues in %s>\n", disMonth);
			printf("T=>teacher,SU=>student,SA=>staff,V=>visitor\n");
			cornerTopLeft();
			line2(141);
			cornerTopRight();
			printf("\n");
			line();
			printf("               Venue                      ");
			line();
			printf("     visitor with normal body temperature    ");
			line();
			printf("      visitors with abnormal body temperature       ");
			line();
			printf("\n");

			for (int i = 0; i < totalRowOfData; i++)
			{
				connectionLeft();
				line2(42);
				shiZiJia();
				line2(45);
				shiZiJia();
				line2(52);
				connectionRight();
				printf("\n");

				line();
				printf(" %40s ", venueName[i]);
				line();
				for (int j = 0; j < 4; j++)
				{
					if (whoAreYou[j].venue1[i][month] != 0)
					{
						green();
					}
				}


				printf("        T>%-5d SU>%-5d SA>%-5d V>%-5d    ", whoAreYou[0].venue1[i][month], whoAreYou[1].venue1[i][month], whoAreYou[2].venue1[i][month], whoAreYou[3].venue1[i][month]);
				line();

				for (int j = 0; j < 4; j++)
				{
					if (whoAreYou[j].abvenue1[i][month] != 0)
					{
						red();
					}
				}
				printf("           T>%-5d SU>%-5d SA>%-5d V>%-5d        ", whoAreYou[0].abvenue1[i][month], whoAreYou[1].abvenue1[i][month], whoAreYou[2].abvenue1[i][month], whoAreYou[3].abvenue1[i][month]);
				line();

				printf("\n");
			}
			line2(142);
			system("pause");
			system("cls");
			break;

		case 2:
			cornerTopLeft();
			line2(141);
			cornerTopRight();
			printf("\n");
			line();
			printf("               Venue                      ");
			line();
			printf("     visitor with normal body temperature    ");
			line();
			printf("      visitors with abnormal body temperature       ");
			line();
			printf("\n");


			for (int i = 0; i < totalRowOfData; i++)
			{
				connectionLeft();
				line2(42);
				shiZiJia();
				line2(45);
				shiZiJia();
				line2(52);
				connectionRight();
				printf("\n");

				line();
				printf(" %40s ", venueName[i]);
				line();
				if (totalV[i] != 0)
				{
					green();
				}
				else
				{
					reset();
				}
				printf("                   %-5d                     ", totalV[i]);
				line();
				if (totalAC[i] != 0)
				{
					red();
				}
				else
				{
					reset();
				}
				printf("                       %-5d                        ", totalAC[i]);
				line();

				printf("\n");
			}
			line2(142);
			system("pause");
			system("cls");
			break;

		}
	} while (choice != 3);
	fclose(fptr1);
}

void openFile()
{
	FILE* fptr1;

	fptr1 = fopen("visitorData.txt", "w");
	fprintf(fptr1, "	name:						IC No.							   Tel.No						  venue			temp	date		time		\n");
	fclose(fptr1);
	printf("sucessfully created the text file ^.^\n");
}

void delData(int num, int position[20], int count, Visitor data[20])
{


	int pick;
	int k = 0;
	for (int i = 0; i < num; i++)
	{
		for (int j = position[i] - k; j < count; j++)
		{
			strcpy(data[j].name, data[j + 1].name);
			strcpy(data[j].position, data[j + 1].position);
			strcpy(data[j].icNo, data[j + 1].icNo);
			strcpy(data[j].telNum, data[j + 1].telNum);
			strcpy(data[j].tempCheck, data[j + 1].tempCheck);
			strcpy(data[j].venue, data[j + 1].venue);
			data[j].day = data[j + 1].day;
			data[j].month = data[j + 1].month;
			data[j].year = data[j + 1].year;
			data[j].hour = data[j + 1].hour;
			data[j].min = data[j + 1].min;
			data[j].temperature = data[j + 1].temperature;

		}
		k++;
	}

	printf("below will be the data after deleted, are you sure to do so（1=>yes,2=>no,back to menu)?\n");
	printData(count - num, data);


	scanf("%d", &pick);
	rewind(stdin);
	while (pick != 1 && pick != 2)
	{
		printf("error,please enter you choice in term of（1=>yes,2=>no,back to menu)?");
		scanf("%d", &pick);
		rewind(stdin);
	}

	if (pick == 1)
	{
		writeFile(num, count, data);
	}



}

void printData(int num, Visitor data[20])
{
	cornerTopLeft();
	line2(155);
	cornerTopRight();
	printf("\n");
	line();
	printf("NO ");
	line();
	printf("          name         ");
	line();
	printf("position");
	line();
	printf("icNo              ");
	line();
	printf("   tel number   ");
	line();
	printf("               venue               ");
	line();
	printf(" body temp ");
	line();
	printf("    date     ");
	line();
	printf("time    ");
	line();
	printf("temp check ");
	line();
	printf("\n");
	
	connectionLeft();

	line2(3);
	shiZiJia();
	line2(23);//133-23
	shiZiJia();
	line2(8);
	shiZiJia();
	line2(18);
	shiZiJia();
	line2(16);
	shiZiJia();
	line2(35);
	shiZiJia();
	line2(11);
	shiZiJia();
	line2(13);
	shiZiJia();
	line2(8);
	shiZiJia();
	line2(11);
	connectionRight();
	

	for (int i = 0; i < num;i++)

	{	
		printf("\n");
		line();
		printf("%2d ", i + 1);
		line();
		printf("%20s   ", data[i].name);
		line();
		printf("%8s", data[i].position);
		line();
		printf("%15s   ", data[i].icNo);
		line();
		printf("%13s   ", data[i].telNum);
		line();
		printf("%32s   ", data[i].venue);
		line();
		printf("   %5.2f   ", data[i].temperature);
		line();
		printf("%2d/%2d/%2d   ", data[i].day, data[i].month, data[i].year);
		line();
		printf("%2d:%2d   ", data[i].hour, data[i].min);
		line();
		printf("%8s   ", data[i].tempCheck);
		line();
		printf("\n");
		connectionLeft();
		line2(3);
		shiZiJia();
		line2(23);
		shiZiJia();
		line2(8);
		shiZiJia();
		line2(18);
		shiZiJia();
		line2(16);
		shiZiJia();
		line2(35);
		shiZiJia();
		line2(11);
		shiZiJia();
		line2(13);
		shiZiJia();
		line2(8);
		shiZiJia();
		line2(11);
		connectionRight();

	}
	printf("\n");
	cornerBotomLeft();

	line2(155);


	cornerBotomRight();
	
	


}

const char* readFile123(int j)
{
	FILE* fptr1,*fptr2;
	char line1;
	char line2;
	char venue[30][50];
	char c;
	int count = 0;

	fptr2 = fopen("venue.txt", "r");

	while (fscanf(fptr2, "%c", &c) != EOF) {
		if (c == '\n')
			count++;
	}
	fclose(fptr2);
	int totalRowOfData = count / 2;

	fptr1 = fopen("venue.txt", "r");

	for (int i = 0; i < totalRowOfData; i++)
	{
		fscanf(fptr1, "%[^\|]|", &venue[i]);

		fscanf(fptr1, "%*[^\n]\n");
		fscanf(fptr1, "%*[^\n]\n");
	}
	return venue[j];
	fclose(fptr1);
}

void shiZiJia()
{
	cyan();
	printf("%c", 216);
	reset();

}