#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)

void readVenueFile(struct VenueInformation venue[30],int saveRecord,int power);
void venueSystem(int power);
void venueMainMenu(int saveRecord,int power);
void venueAdd(int saveRecord,int power);
void venueSearch(struct VenueInformation venue[30],int saveRecord);
void venueMenuForSearch(int criteria[10], int saveRecord, int* totalCriteria);
void venueModify(struct VenueInformation venue[30],int saveRecord,int power);
void venueInformationMenu(struct VenueInformation venue[30], int modifyFile, int saveRecord);
void allignmentOfVenueDetails(struct VenueInformation venue[30], int modifyFile, int saveRecord);
void allignmentOfVenueEquipment(struct VenueInformation venue[30], int modifyFile, int saveRecord);
void allignmentOfVenueDescriptionAndVisitors(struct VenueInformation venue[30], int modifyFile,int saveRecord);
void activity(int saveRecord);
void addActivityOfUser(char addSentenceInFile[200]);
int saveRecordOfUser();
void fileValidation(FILE**fileName,char fileName2[30],int saveRecord,int power);
void validationForNum(int* num);
void printLocalTime();
void printLocalTimeInFile(FILE** addLocalTime);
void deleteData(struct VenueInformation venue[30], int saveRecord,int power);

void gotoXY(int x, int y); // Adjust position of X,Y . Used in table format

int totalRowOfData;

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
	int deleteRow;

}VenueInformation;

void venueSystem(int power)
{
	purple();
	gotoXY(50, 3);
	printf("\t\tWelcome to TarucSejahtera [Venue System]\n\n\n");
	_sleep(300);

	int saveRecord;

	red();

	for (int i = 2; i > 0; i--) {
		printf("%-62sVenue Main Menu will be shown in %d seconds...", "", i);
		for (int i = 0; i < 112; i++)
			printf("\b");
		_sleep(1000);
	}
	system("CLS");
	printf("\n\n\n\n\n");
	saveRecord = saveRecordOfUser();
	venueMainMenu(saveRecord,power);
}

void venueMainMenu(int saveRecord,int power) // MAIN MENU OF WHOLE VENUE PROJECT
{	
	int modifyFile = 0;

	int option;
	char ans;
	char exitChoice;

	//transfer data from text file
	VenueInformation venue[30] = { 0 };
	char c;
	int count = 0;

	FILE* Venue;
	Venue = fopen("venue.txt", "r");
	fileValidation(&Venue, "venue.txt",saveRecord,power);

	// check rows of txt file
	while (fscanf(Venue, "%c", &c) != EOF) {
		if (c == '\n')
			count++;
	}

	fclose(Venue);

	//one venue consist of 2 rows in txt file
	totalRowOfData = count / 2;

	readVenueFile(venue,saveRecord,power);

	do {
		system("CLS");
		gotoXY(75, 1);
		underlineBlue();
		printf(" VENUE MAIN MENU ");
		printf("\n\n");

		blue();
		printf("%-75s1.\t ADD\n\n\n", "");
		printf("%-75s2.\t SEARCH\n\n\n", "");
		printf("%-75s3.\t MODIFY\n\n\n", "");
		printf("%-75s4.\t DISPLAY\n\n\n", "");
		printf("%-75s5.\t DELETE\n\n\n", "");
		printf("%-75s6.\t ACTIVITY\n\n\n", "");
		printf("%-75s7.\t EXIT\n\n\n", "");

		printf("%-75sYour option ->[ ]\b\b", "");
		scanf("%d", &option);

		switch (option) {
		case 1:
			system("CLS");
			venueAdd(saveRecord,power);
			break;

		case 2:
			system("CLS");
			venueSearch(venue,saveRecord);
			break;

		case 3:
			system("CLS");
			venueModify(venue,saveRecord,power);
			break;

		case 4:
			system("CLS");
			venueInformationMenu(venue,modifyFile,saveRecord);
			break;

		case 5:
			system("CLS");
			deleteData(venue,saveRecord,power);
			break;

		case 6:
			system("CLS");
			activity(saveRecord);
			break;

		case 7:
			if (saveRecord == 1) {
				char addSentenceInFile[200];
				strcpy(addSentenceInFile, "User has quit the venue program.");
				addActivityOfUser(addSentenceInFile);
			}

			system("CLS");
			break;

		default:
			red();
			printf("Invalid options have been chosen.");

		}

		if (option != 7) {
			purple();
			printf("\n\n%-60sDo you want to continue to Venue Main Menu again?(Y/N) [ ]\b\b", "");
			rewind(stdin);
			scanf("%c", &ans);
			system("CLS");
		}
		else
			ans = 'N';

	} while (ans == 'Y' || ans == 'y');
}

void readVenueFile(VenueInformation venue[30],int saveRecord,int power)
{
	FILE* Venue;

	Venue = fopen("venue.txt", "r");
	fileValidation(&venue, "venue.txt",saveRecord,power);

	// transfer data to structure array
	for (int i = 0; i <= totalRowOfData * 2; i++) {
		fscanf(Venue, "%[^\|]|", &venue[i].venueName);
		fscanf(Venue, "%[^\|]|", &venue[i].venueID);
		fscanf(Venue, "%c|", &venue[i].venueCategory);
		fscanf(Venue, "%[^\|]|", &venue[i].venueLastSanitizationDate);
		fscanf(Venue, "%d,", &venue[i].venueCloseForSanitization);
		fscanf(Venue, "%d,", &venue[i].numberOfCurrentVisitors);
		fscanf(Venue, "%d,", &venue[i].numberOfStaff);
		fscanf(Venue, "%d,", &venue[i].maxNumberOfVisitors);
		fscanf(Venue, "%d,", &venue[i].venueHistoryOfinfectedPeople);
		fscanf(Venue, "%f,", &venue[i].venueAreaInMetres);
		fscanf(Venue, "%c,", &venue[i].venueMeasurementCovidZone);
		fscanf(Venue, "%[^\,],", &venue[i].venueOpeningTime);
		fscanf(Venue, "%[^\,],", &venue[i].venueClosingTime);
		fscanf(Venue, "%d,", &venue[i].availabilityOfEquipment.numOfAvailableNoseSwabTest);
		fscanf(Venue, "%d,", &venue[i].availabilityOfEquipment.availabilityOfTemperatureSensor);
		fscanf(Venue, "%d,", &venue[i].availabilityOfEquipment.numberOfMask);
		fscanf(Venue, "%d,", &venue[i].availabilityOfEquipment.numOfSanizationBottle);
		fscanf(Venue, "%f,", &venue[i].availabilityOfEquipment.volumeOfSanizationBottleInLitres);

		for (int j = 0; j < 10; j++) {
			if (j == 9) {
				fscanf(Venue, "%[^\n]\n", &venue[i].venueHistoryOfLastTenVistorsName[j]);
				break;
			}
			fscanf(Venue, "%[^\.].", &venue[i].venueHistoryOfLastTenVistorsName[j]);
		}
		fscanf(Venue, "%[^\*]*\n", &venue[i].venueDescriptions);
	}
	fclose(Venue);
}

void venueAdd(int saveRecord,int power)
{
	if (power == 1) {

		FILE* addedVenue;

		addedVenue = fopen("venue.txt", "a");
		fileValidation(&addedVenue, "venue.txt",saveRecord,power);

		VenueInformation addedByUser = { 0 };

		char ans;
		int retype;
		char addSentenceInFile[200];

		printf("\nYou have chosen add option.\n\n");
		red();
		printf("Please type Y to proceed >_\b"); //confirmation
		rewind(stdin);
		scanf("%c", &ans);

		if (ans == 'Y' || ans == 'y') {
			for (int i = 0; i < 10; i++) {

				underlineGreen();
				gotoXY(77, 15);
				printf(" New Venue Details (%d)", i + 1);
				green();
				printf("%-43s", "");
				printLocalTime();

				gotoXY(14, 20);
				printf("No.");

				gotoXY(28, 19);
				printf("Name of");
				gotoXY(27, 20);
				printf("the Venue");

				gotoXY(47, 19);
				printf("Venue");
				gotoXY(48, 20);
				printf("ID");

				gotoXY(56, 18);
				printf("Venue");
				gotoXY(55, 19);
				printf("Category");
				gotoXY(55, 20);
				printf("(S/M/B)");

				gotoXY(69, 18);
				printf("Last");
				gotoXY(65, 19);
				printf("Sanitization");
				gotoXY(69, 20);
				printf("Date");

				gotoXY(82, 18);
				printf("Close");
				gotoXY(83, 19);
				printf("For");
				gotoXY(79, 20);
				printf("Sanitization");

				gotoXY(94, 19);
				printf("Current");
				gotoXY(94, 20);
				printf("Visitors");

				gotoXY(105, 19);
				printf("Num.Of");
				gotoXY(105, 20);
				printf("Staff");

				gotoXY(114, 19);
				printf("Maximum");
				gotoXY(114, 20);
				printf("Visitors");

				gotoXY(125, 18);
				printf("Infected");
				gotoXY(126, 19);
				printf("Cases");
				gotoXY(125, 20);
				printf("At Past");

				gotoXY(136, 18);
				printf("Covid");
				gotoXY(136, 19);
				printf("Zone");
				gotoXY(135, 20);
				printf("(G/Y/R)");

				gotoXY(143, 18);
				printf("Area of");
				gotoXY(144, 19);
				printf("Venue");
				gotoXY(144, 20);
				printf("(km)");

				gotoXY(153, 19);
				printf("Opening");
				gotoXY(154, 20);
				printf("Time");

				gotoXY(163, 19);
				printf("Closing");
				gotoXY(164, 20);
				printf("Time");

				for (int j = 18; j < 24; j++) {
					gotoXY(13, j);
					printf("|");
					gotoXY(18, j);
					printf("|");
					gotoXY(45, j);
					printf("|");
					gotoXY(53, j);
					printf("|");
					gotoXY(64, j);
					printf("|");
					gotoXY(77, j);
					printf("|");
					gotoXY(92, j);
					printf("|");
					gotoXY(103, j);
					printf("|");
					gotoXY(112, j);
					printf("|");
					gotoXY(123, j);
					printf("|");
					gotoXY(134, j);
					printf("|");
					gotoXY(142, j);
					printf("|");
					gotoXY(151, j);
					printf("|");
					gotoXY(161, j);
					printf("|");
					gotoXY(171, j);
					printf("|");

				}

				for (int k = 13; k < 172; k++) {
					gotoXY(k, 17);
					printf("-");
					gotoXY(k, 21);
					printf("-");
					gotoXY(k, 24);
					printf("-");
				}

				red();
				gotoXY(48, 4);
				printf("vvv Please type in the below following blank according to the pointer vvv");

				blue();
				gotoXY(56, 6);
				printf("Format for last sanitization date -> (DD-MM-YYYY)");

				gotoXY(56, 8);
				printf("Format for Close for sanitizaiton AND avaiability of temperature sensor ( 1 = YES / 0 = NO )");

				gotoXY(56, 10);
				printf("Format for Opening Time / Closing Time ( HH:MM ) 24H Format");

				gotoXY(56, 12);
				printf("Format for volume of each bottles (liter format)");

				gotoXY(14, 22);
				yellow();
				printf("%d)", i + 1);

				gotoXY(19, 22);
				rewind(stdin);
				scanf("%[^\n]", &addedByUser.venueName);

				if (saveRecord == 1) {
					strcpy(addSentenceInFile, "User has added a new venue called ");
					strcat(addSentenceInFile, addedByUser.venueName);
					addActivityOfUser(addSentenceInFile);
				}

				gotoXY(47, 22);
				rewind(stdin);
				scanf("%s", &addedByUser.venueID);

				while (strlen(addedByUser.venueID) != 5) {
					red();
					gotoXY(15, 26);
					printf("Something is wrong with your venue ID.Please retype again.Make sure the venue ID contains ONLY 5 characters.\n");

					gotoXY(47, 22);
					rewind(stdin);
					printf("     \b\b\b\b\b");
					yellow();
					scanf("%s", &addedByUser.venueID);

					//clear screen
					gotoXY(15, 26);
					for (int l = 0; l < 120; l++)
						printf("  ");
				}

				gotoXY(58, 22);
				rewind(stdin);
				scanf("%c", &addedByUser.venueCategory);
				toupper(addedByUser.venueCategory);

				while (addedByUser.venueCategory != 'S' && addedByUser.venueCategory != 'M' && addedByUser.venueCategory != 'B') {
					red();
					gotoXY(15, 26);
					printf("Something is wrong with your venue category code.Please retype again.\n");

					gotoXY(58, 22);
					rewind(stdin);
					printf("  \b\b");
					yellow();
					scanf("%c", &addedByUser.venueCategory);
					toupper(addedByUser.venueCategory);

					//clear screen
					gotoXY(15, 26);
					for (int l = 0; l < 120; l++)
						printf("  ");
				}

				gotoXY(66, 22);
				rewind(stdin);
				scanf("%s", &addedByUser.venueLastSanitizationDate);

				while (addedByUser.venueLastSanitizationDate[2] != '-' || addedByUser.venueLastSanitizationDate[5] != '-' || strlen(addedByUser.venueLastSanitizationDate) > 10) {
					red();
					gotoXY(15, 26);
					printf("Something is wrong with your date.Please retype.Make sure the date follows the format.\n");

					yellow();
					gotoXY(66, 22);
					printf("          \b\b\b\b\b\b\b\b\b\b");
					rewind(stdin);
					scanf("%s", &addedByUser.venueLastSanitizationDate);

					//clear screen
					gotoXY(15, 26);
					for (int l = 0; l < 120; l++)
						printf("  ");
				}

				gotoXY(84, 22);
				scanf("%d", &addedByUser.venueCloseForSanitization);
				rewind(stdin);

				while (addedByUser.venueCloseForSanitization != 1 && addedByUser.venueCloseForSanitization != 0) {
					red();
					gotoXY(15, 26);
					printf("Something is wrong with your answer.Please retype.Make sure it's ONLY 1 (YES) OR 0 (NO).\n");

					yellow();
					gotoXY(84, 22);
					printf("     \b\b\b\b\b");
					rewind(stdin);
					scanf("%d", &addedByUser.venueCloseForSanitization);
					printf("\n%d", addedByUser.venueCloseForSanitization);

					//clear screen
					gotoXY(15, 26);
					for (int m = 0; m < 120; m++)
						printf("  ");
				}

				if (addedByUser.venueCloseForSanitization == 1) {
					gotoXY(97, 22);
					red();
					printf("0");
					yellow();
					addedByUser.numberOfCurrentVisitors = 0;
				}

				else {
					gotoXY(97, 22);
					scanf("%d", &addedByUser.numberOfCurrentVisitors);
				}

				gotoXY(107, 22);
				scanf("%d", &addedByUser.numberOfStaff);

				gotoXY(116, 22);
				scanf("%d", &addedByUser.maxNumberOfVisitors);

				// visitors numbers error
				while (addedByUser.maxNumberOfVisitors < addedByUser.numberOfCurrentVisitors) {
					red();
					gotoXY(15, 26);
					printf("Something is wrong with your maximum number of visitors or number of current visiotrs.Which one you would like to retype?\n");
					printf("%-15s (1=Number of current visitors 2=Max Number of visitors) -> [ ]\b\b\a", " ");

					scanf("%d", &retype);

					//clear screen
					gotoXY(15, 26);
					for (int l = 0; l < 120; l++)
						printf("  ");
					gotoXY(15, 27);
					for (int l = 0; l < 100; l++)
						printf("  ");

					if (retype == 1) {
						gotoXY(97, 22);
						printf("  \b\b");
						yellow();
						scanf("%d", &addedByUser.numberOfCurrentVisitors);
					}
					else if (retype == 2) {
						gotoXY(116, 22);
						printf("  \b\b");
						yellow();
						scanf("%d", &addedByUser.maxNumberOfVisitors);
					}
					else
						continue;
				}

				gotoXY(128, 22);
				scanf("%d", &addedByUser.venueHistoryOfinfectedPeople);

				gotoXY(138, 22);
				rewind(stdin);
				scanf("%c", &addedByUser.venueMeasurementCovidZone);

				gotoXY(145, 22);
				scanf("%f", &addedByUser.venueAreaInMetres);

				gotoXY(154, 22);
				rewind(stdin);
				scanf("%s", &addedByUser.venueOpeningTime);

				while ((int)(addedByUser.venueOpeningTime[0]) > 50 || (int)(addedByUser.venueOpeningTime[3] > 53) || addedByUser.venueOpeningTime[2] != ':' || strlen(addedByUser.venueOpeningTime) > 5) {

					red();
					gotoXY(15, 26);
					printf("Something is wrong with your opening time.Please retype.Make sure the time is in 24 hours format.\n");

					yellow();
					gotoXY(154, 22);
					printf("     \b\b\b\b\b");
					rewind(stdin);
					scanf("%s", &addedByUser.venueOpeningTime);

					//clear screen
					gotoXY(15, 26);
					for (int l = 0; l < 120; i++)
						printf("  ");

				}

				gotoXY(164, 22);
				rewind(stdin);
				scanf("%s", &addedByUser.venueClosingTime);
				green();

				// check time validaiton
				while ((int)(addedByUser.venueClosingTime[0]) > 50 || (int)(addedByUser.venueClosingTime[3] > 53) || addedByUser.venueClosingTime[2] != ':' || strlen(addedByUser.venueClosingTime) > 5) {

					red();
					gotoXY(15, 26);
					printf("Something is wrong with your closing time.Please retype.Make sure the time is in 24 hours format.\n");

					yellow();
					gotoXY(164, 22);
					printf("     \b\b\b\b\b");
					rewind(stdin);
					scanf("%s", &addedByUser.venueClosingTime);

					//clear screen
					gotoXY(15, 26);
					for (int l = 0; l < 120; l++)
						printf("  ");

				}

				green();

				for (int k = 40; k < 145; k++) {
					gotoXY(k, 27);
					printf("-");
					gotoXY(k, 31);
					printf("-");
					gotoXY(k, 34);
					printf("-");
				}

				for (int k = 28; k < 34; k++) {
					gotoXY(40, k);
					printf("|");
					gotoXY(60, k);
					printf("|");
					gotoXY(85, k);
					printf("|");
					gotoXY(107, k);
					printf("|");
					gotoXY(127, k);
					printf("|");
					gotoXY(144, k);
					printf("|");
				}

				gotoXY(46, 28);
				printf("Number of");
				gotoXY(46, 29);
				printf("Available");
				gotoXY(43, 30);
				printf("Nose Swap Test");

				gotoXY(67, 28);
				printf("Avilability");
				gotoXY(71, 29);
				printf("of");
				gotoXY(64, 30);
				printf("Temperature sensor");

				gotoXY(93, 28);
				printf("Number");
				gotoXY(95, 29);
				printf("of");
				gotoXY(93, 30);
				printf("Masks");

				gotoXY(113, 28);
				printf("Number of");
				gotoXY(112, 29);
				printf("Sanitization");
				gotoXY(114, 30);
				printf("Bottles");

				gotoXY(130, 28);
				printf("Volume");
				gotoXY(130, 29);
				printf("of Each");
				gotoXY(130, 30);
				printf("Bottles");

				yellow();
				gotoXY(49, 32);
				scanf("%d", &addedByUser.availabilityOfEquipment.numOfAvailableNoseSwabTest);

				gotoXY(70, 32);
				scanf("%d", &addedByUser.availabilityOfEquipment.availabilityOfTemperatureSensor);

				gotoXY(93, 32);
				scanf("%d", &addedByUser.availabilityOfEquipment.numberOfMask);

				gotoXY(116, 32);
				scanf("%d", &addedByUser.availabilityOfEquipment.numOfSanizationBottle);

				gotoXY(131, 32);
				scanf("%f", &addedByUser.availabilityOfEquipment.volumeOfSanizationBottleInLitres);

				gotoXY(40, 37);
				purple();
				printf("Please write a simple description for this venue : ");
				yellow();
				rewind(stdin);
				scanf("%[^\n]", addedByUser.venueDescriptions);

				for (int n = 9; n >= 0; n--) {
					gotoXY(40, 40);
					purple();
					printf("The name of last number %2d visitor (enter one by one) >", n + 1);
					rewind(stdin);
					yellow();
					scanf("%[^\n]", addedByUser.venueHistoryOfLastTenVistorsName[n]);

					gotoXY(95, 40);
					for (int m = 0; m < 40; m++) {
						printf(" ");
					}
				}

				gotoXY(40, 40);
				for (int m = 0; m < 70; m++) {
					printf(" ");
				}

				//transfer added value to file
				fprintf(addedVenue, "%s|%s|%c|%s|%d,%d,%d,%d,%d,%.2f,%c,%s,%s,%d,%d,%d,%d,%.2f,", addedByUser.venueName, addedByUser.venueID, addedByUser.venueCategory,
					addedByUser.venueLastSanitizationDate, addedByUser.venueCloseForSanitization, addedByUser.numberOfCurrentVisitors, addedByUser.numberOfStaff,
					addedByUser.maxNumberOfVisitors, addedByUser.venueHistoryOfinfectedPeople, addedByUser.venueAreaInMetres, addedByUser.venueMeasurementCovidZone,
					addedByUser.venueOpeningTime, addedByUser.venueClosingTime, addedByUser.availabilityOfEquipment.numOfAvailableNoseSwabTest,
					addedByUser.availabilityOfEquipment.availabilityOfTemperatureSensor, addedByUser.availabilityOfEquipment.numberOfMask,
					addedByUser.availabilityOfEquipment.numOfSanizationBottle, addedByUser.availabilityOfEquipment.volumeOfSanizationBottleInLitres);

				for (int m = 0; m < 10; m++) {
					// adjust name before adding to text file
					if (m == 9)
						fprintf(addedVenue, "%s", addedByUser.venueHistoryOfLastTenVistorsName[m]);
					else
						fprintf(addedVenue, "%s.", addedByUser.venueHistoryOfLastTenVistorsName[m]);
				}

				fprintf(addedVenue, "\n%s*\n", addedByUser.venueDescriptions);

				if (ans == 'N' || ans == 'n') {
					break;
				}

				gotoXY(65, 41);
				red();
				printf("Thank you! Continue to add new venue? (Y/N) -> [ ]\b\b");
				rewind(stdin);
				scanf("%c", &ans);
				system("CLS");
			}
		}
	}
	else {
		red();
		printf("You are not allowed to add");
		reset();
	}
}

void venueSearch(VenueInformation venue[30], int saveRecord)
{
	int criteria[13] = { 0 }, totalCriteria;
	venueMenuForSearch(criteria, saveRecord, &totalCriteria);
	char option;
	int  optionInNum, option2InNum;
	float optionInFloat, option2InFloat;
	char continueToSearch;
	system("CLS");

	for (int i = 0; i < totalCriteria; i++) {
		printf("%d)", i + 1);
		for (int j = 0; j < 13; j++) {
			yellow();
			if (criteria[j] == 1) {

				printf("\nWhich category? (S/M/B) [ ]\b\b");
				rewind(stdin);
				scanf("%c", &option);
				option = toupper(option);
				printf("\n");

				while (option != 'S' && option != 'M' && option != 'B') {
					red();
					printf("\nPlease retype.Your option is not valid.\n");
					printf("Which category? (S/M/B) [ ]\b\b");
					rewind(stdin);
					scanf("%c", &option);
					green();
				}
				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].venueCategory == option) {
						green();
						printf("\n%s\n", venue[i].venueName);
					}
				}
			}
			else if (criteria[j] == 2) {
				yellow();
				printf("\nIs it check for which venue close for sanitization? ( 1 = YES / 0 =NO) > [ ]\b\b");
				scanf("%d", &optionInNum);

				while (optionInNum != 1 && optionInNum != 0) {
					red();
					printf("\nPlease retype.Your option is not valid.\n");
					printf("Check for which venue close for sanitization? ( 1 = YES / 0 =NO)");
					scanf("%d", &optionInNum);
					green();
				}

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].venueCloseForSanitization == optionInNum) {
						green();
						printf("\n%s\n", venue[i].venueName);
					}
				}
			}

			else if (criteria[j] == 3) {
				printf("\nNumber of visitors from [   ]\b\b\b\b");
				scanf("%d", &optionInNum);
				validationForNum(&optionInNum);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%d", &option2InNum);
				validationForNum(&option2InNum);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].numberOfCurrentVisitors >= optionInNum && venue[i].numberOfCurrentVisitors <= option2InNum) {
						green();
						printf("\n%s -> %d\n", venue[i].venueName, venue[i].numberOfCurrentVisitors);
					}
				}
			}

			else if (criteria[j] == 4) {
				printf("\nNumber of staff from [   ]\b\b\b\b");
				scanf("%d", &optionInNum);
				validationForNum(&optionInNum);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%d", &option2InNum);
				validationForNum(&option2InNum);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].numberOfStaff >= optionInNum && venue[i].numberOfStaff <= option2InNum) {
						green();
						printf("\n%s -> %d\n", venue[i].venueName, venue[i].numberOfStaff);
					}
				}
			}

			else if (criteria[j] == 5) {
				printf("\nMaximum visitor from [   ]\b\b\b\b");
				scanf("%d", &optionInNum);
				validationForNum(&optionInNum);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%d", &option2InNum);
				validationForNum(&option2InNum);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].maxNumberOfVisitors >= optionInNum && venue[i].maxNumberOfVisitors <= option2InNum) {
						green();
						printf("\n%s -> %d\n", venue[i].venueName, venue[i].maxNumberOfVisitors);
					}
				}
			}

			else if (criteria[j] == 6) {
				printf("\nInfected cases at past from [   ]\b\b\b\b");
				scanf("%d", &optionInNum);
				validationForNum(&optionInNum);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%d", &option2InNum);
				validationForNum(&option2InNum);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].venueHistoryOfinfectedPeople >= optionInNum && venue[i].venueHistoryOfinfectedPeople <= option2InNum) {
						green();
						printf("\n%s -> %d\n", venue[i].venueName, venue[i].venueHistoryOfinfectedPeople);
					}
				}
			}

			else if (criteria[j] == 7) {
				printf("\nWhich zone? (G/Y/R) >[ ]\b\b");
				rewind(stdin);
				scanf("%c", &option);
				option = toupper(option);

				while (option != 'G' && option != 'Y' && option != 'R') {
					red();
					printf("Invalid option.Please retype.\n");
					printf("Which zone? (G/Y/R) >[ ]\b\b");
					rewind(stdin);
					scanf("%c", &option);
					option = toupper(option);
				}
				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].venueMeasurementCovidZone == option) {
						green();
						printf("\n%s\n", venue[i].venueName);
					}
				}
			}

			else if (criteria[j] == 8) {
				printf("\nArea of venue from [   ]\b\b\b\b");
				scanf("%f", &optionInFloat);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%f", &option2InFloat);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].venueAreaInMetres >= optionInFloat && venue[i].venueAreaInMetres <= option2InFloat) {
						green();
						printf("\n%s ->%.2f\n", venue[i].venueName, venue[i].venueAreaInMetres);
					}
				}
			}

			else if (criteria[j] == 9) {
				printf("\nNumber of available nose swap from [   ]\b\b\b\b");
				scanf("%d", &optionInNum);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%d", &option2InNum);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].availabilityOfEquipment.numOfAvailableNoseSwabTest >= optionInNum && venue[i].availabilityOfEquipment.numOfAvailableNoseSwabTest <= option2InNum) {
						green();
						printf("\n%s -> %d\n", venue[i].venueName, venue[i].availabilityOfEquipment.numOfAvailableNoseSwabTest);
					}
				}
			}

			else if (criteria[j] == 10) {
				printf("\nIs it check for temperature sensor is available? ( 1 = YES / 0 =NO) >[ ]\b\b");
				scanf("%d", &optionInNum);

				while (optionInNum != 1 && optionInNum != 0) {
					red();
					printf("\nPlease retype.Your option is not valid.\n");
					printf("Is it check for temperature sensor is available? ( 1 = YES / 0 =NO)");
					scanf("%d", &optionInNum);
					green();
				}

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].availabilityOfEquipment.availabilityOfTemperatureSensor == optionInNum) {
						green();
						printf("\n%s\n", venue[i].venueName);
					}
				}
			}

			else if (criteria[j] == 11) {
				printf("\nNumber of mask from [   ]\b\b\b\b");
				scanf("%d", &optionInNum);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%d", &option2InNum);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].availabilityOfEquipment.numberOfMask >= optionInNum && venue[i].availabilityOfEquipment.numberOfMask <= option2InNum) {
						green();
						printf("\n%s -> %d\n", venue[i].venueName, venue[i].availabilityOfEquipment.numberOfMask);
					}
				}
			}

			else if (criteria[j] == 12) {
				printf("\nNumber of sanitization bottle from [   ]\b\b\b\b");
				scanf("%d", &optionInNum);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%d", &option2InNum);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].availabilityOfEquipment.numOfSanizationBottle >= optionInNum && venue[i].availabilityOfEquipment.numOfSanizationBottle <= option2InNum) {
						green();
						printf("\n%s -> %d\n", venue[i].venueName, venue[i].availabilityOfEquipment.numOfSanizationBottle);
					}
				}
			}

			else if (criteria[j] == 13) {
				printf("\nVolume of sanitization bottle from [   ]\b\b\b\b");
				scanf("%f", &optionInFloat);

				printf("\n%-20sto [   ]\b\b\b\b", "");
				scanf("%f", &option2InFloat);

				for (int i = 0; i < totalRowOfData; i++) {
					if (venue[i].availabilityOfEquipment.volumeOfSanizationBottleInLitres >= optionInFloat && venue[i].availabilityOfEquipment.volumeOfSanizationBottleInLitres <= option2InFloat) {
						green();
						printf("\n%s -> %.2f\n", venue[i].venueName, venue[i].availabilityOfEquipment.volumeOfSanizationBottleInLitres);
					}
				}
			}
		}
		char continueToSearch;

		yellow();
		printf("\n\n\n%-50sContinue to search with other criterias? (Y/N) [ ]\b\b", "");
		rewind(stdin);
		scanf("%c", &continueToSearch);

		if (continueToSearch == 'Y' || continueToSearch == 'y') {
			system("CLS");
			venueMenuForSearch(criteria, saveRecord, &totalCriteria);
			system("CLS");
		}

		else
			break;
	}
}

void venueMenuForSearch(int criteria[10], int saveRecord, int* totalCriteria) {
	char criteriaContent[13][60] = { "Venue Category","Close for sanitization","Numbers of Current visitors","Number of staff","Maximum Visitors" ,
	"Infected cases at past","Measurement of Covid Zone","Area of venue","Number of the available nose swab test","Availability of temperature sensor",
	"Number of masks","Number of sanitization bottles","Volume of each sanitization bottles" };

	printf("\n%-73s", "");
	underlineGreen();
	printf("Criteria");

	green();
	printf("\n\n\n");

	for (int i = 0; i < 13; i++) {
		printf("%-50s%d. %s\n\n", "", i + 1, criteriaContent[i]);
	}

	for (int i = 48; i < 111; i++) {
		gotoXY(i, 2);
		printf("-");
		gotoXY(i, 30);
		printf("-");
	}

	for (int i = 3; i < 30; i++) {
		gotoXY(48, i);
		printf("|");
		gotoXY(110, i);
		printf("|");
	}

	yellow();
	printf("\n\n\n\n%-50sTotal of criterias you would like to search >[ ]\b\b", "");
	scanf("%d", &*totalCriteria);

	for (int i = 0; i < *totalCriteria; i++) {
		printf("\n\n%-50sCriteria %d you would like to search > [  ]\b\b\b", "",i+1);
		scanf("%d", &criteria[i]);

		while (criteria[i] > 13 || criteria[i] < 0) {
			red();
			printf("Please enter a valid selection.\n");
			yellow();
			printf("\n\n%-50sCriteria %d you would like to search? [  ]\b\b\b",i+1, "");
			scanf("%d", &criteria[i]);
		}

		if (saveRecord == 1) {
			char addSentenceInFile[200];

			strcpy(addSentenceInFile, "User has searched a criteria based on ");
			strcat(addSentenceInFile, criteriaContent[criteria[i] - 1]);
			addActivityOfUser(addSentenceInFile);
		}
	}
}

void validationForNum(int *num) {

	while (*num < 0) {
		red();
		printf("\nError!\n");
		purple();
		printf("Please retype with a valid numbers. [   ]\b\b\b\b");
		scanf("%d", &*num);
	}

}

void venueModify(VenueInformation venue[30],int saveRecord,int power)
{
	if (power == 1) {

		int modifyFile = 1;

		allignmentOfVenueDetails(venue, modifyFile, saveRecord);

		system("CLS");
		blue();
		printf("\n\n\n\n%-60sDone modify,Thank you.", "");

		FILE* modify;
		modify = fopen("venue.txt", "w");

		for (int i = 0; i < totalRowOfData; i++) {
			fprintf(modify, "%s|%s|%c|%s|%d,%d,%d,%d,%d,%.2f,%c,%s,%s,%d,%d,%d,%d,%.2f,", venue[i].venueName, venue[i].venueID, venue[i].venueCategory,
				venue[i].venueLastSanitizationDate, venue[i].venueCloseForSanitization, venue[i].numberOfCurrentVisitors, venue[i].numberOfStaff,
				venue[i].maxNumberOfVisitors, venue[i].venueHistoryOfinfectedPeople, venue[i].venueAreaInMetres, venue[i].venueMeasurementCovidZone,
				venue[i].venueOpeningTime, venue[i].venueClosingTime, venue[i].availabilityOfEquipment.numOfAvailableNoseSwabTest,
				venue[i].availabilityOfEquipment.availabilityOfTemperatureSensor, venue[i].availabilityOfEquipment.numberOfMask,
				venue[i].availabilityOfEquipment.numOfSanizationBottle, venue[i].availabilityOfEquipment.volumeOfSanizationBottleInLitres);

			for (int m = 0; m < 10; m++) {
				// adjust name before adding to text file
				if (m == 9)
					fprintf(modify, "%s", venue[i].venueHistoryOfLastTenVistorsName[m]);
				else
					fprintf(modify, "%s.", venue[i].venueHistoryOfLastTenVistorsName[m]);
			}

			fprintf(modify, "\n%s*\n", venue[i].venueDescriptions);
		}

		green();
	}
	else {
		red();
		printf("You are not allowed to modify file.");
		reset();
	}

}

void venueInformationMenu(VenueInformation venue[30],int modifyFile,int saveRecord) //USER CHOICE TO CHECK DIFFERENT DETAILS OF VENUE IN TABLE FORM
{
	int userChoice;
	char backToVenueInfoMenu;

	do {
		gotoXY(55, 3);
		underlineGreen();
		printf(" VENUE INFORMATION MENU ");

		green();
		gotoXY(55, 5);
		printf("1. VENUE GENERAL DETAILS");
		gotoXY(55, 8);
		printf("2. VENUE EQUIPMENT");
		gotoXY(55, 11);
		printf("3. VENUE DESCRIPTION AND VISITORS");
		gotoXY(55, 14);
		printf("4. EXIT");

		gotoXY(55, 20);
		printf("Your choices  >_\b");
		scanf("%d", &userChoice);

		system("CLS");

		switch (userChoice) {
		case 1:
			allignmentOfVenueDetails(venue,modifyFile,saveRecord);
			break;

		case 2:
			allignmentOfVenueEquipment(venue, modifyFile,saveRecord);
			break;

		case 3:
			allignmentOfVenueDescriptionAndVisitors(venue, modifyFile,saveRecord);
			break;

		default:
			gotoXY(60, 10);
			red();
			printf("You have chosen exit or invalid option!\n\n");
		}
		red();
		printf("\n\n%-63sBack to Venue Display Menu?(Y/N) [ ]\b\b","");
		rewind(stdin);
		scanf("%c", &backToVenueInfoMenu);
		printf("\n\n");

		if (backToVenueInfoMenu == 'N' || backToVenueInfoMenu == 'n') {
			for (int i = 2; i > 0; i--) {
				red();
				printf("%-56sVenue Display Information System will be closed in %d seconds..", "", i);

				for (int i = 0; i < 130; i++)
				{
					printf("\b");
				}
				_sleep(1000);
			}
			system("CLS");
			reset();
		}
		system("CLS");

	} while (backToVenueInfoMenu == 'Y' || backToVenueInfoMenu == 'y');

}

void allignmentOfVenueDetails(VenueInformation venue[30], int modifyFile,int saveRecord) // to restrcuture table format
{
	if (saveRecord == 1) {
		char addSentenceInFile[200];

		strcpy(addSentenceInFile, "User has checked venue details table.");
		addActivityOfUser(addSentenceInFile);
	}

	char ans;
	int extraRowCount = 0;
	underlineGreen();
	gotoXY(85, 3);
	printf(" VENUE DETAILS ");
	green();

	// table allignment
	for (int i = 20; i < 170; i++) {
		gotoXY(i, 5);
		printf("-");
		gotoXY(i, 9);
		printf("-");
		gotoXY(i, 29);
		printf("-");
	}

	// display array of structure in table form
	for (int i = 0; i < totalRowOfData; i++) {

		gotoXY(21, 8);
		printf("No.");
		gotoXY(21, 2 * i + extraRowCount + 10);
		printf("%d.", i + 1);

		gotoXY(32, 7);
		printf("Name of");
		gotoXY(31, 8);
		printf("the Venue");
		gotoXY(26, 2 * i + extraRowCount + 10);

		// display name in 2 rows
		if (strlen(venue[i].venueName) > 19) {
			for (int j = 30; j > 0; j--) {
				if (venue[i].venueName[j] == ' ') {
					for (int k = 0; k < j; k++) {
						printf("%c", venue[i].venueName[k]);
					}
					// seperate 2 rows to print. First row until last 'space', second row start from last 'space'
					printf("\n%-25s", "");
					for (int k = j; k < strlen(venue[i].venueName); k++) {
						printf("%c", venue[i].venueName[k]);
					}
					break;
				}
			}
			extraRowCount++;
		}
		else
			printf("%s", venue[i].venueName);

		gotoXY(47, 7);
		printf("Venue");
		gotoXY(48, 8);
		printf("ID");
		gotoXY(47, 2 * i + extraRowCount + 10);
		printf("%s", venue[i].venueID);

		gotoXY(56, 6);
		printf("Venue");
		gotoXY(55, 7);
		printf("Category");
		gotoXY(55, 8);
		printf("(S/M/B)");
		gotoXY(58, 2 * i + extraRowCount + 10);
		printf("%c", venue[i].venueCategory);

		gotoXY(69, 6);
		printf("Last");
		gotoXY(65, 7);
		printf("Sanitization");
		gotoXY(69, 8);
		printf("Date");
		gotoXY(66, 2 * i + extraRowCount + 10);
		printf("%s", venue[i].venueLastSanitizationDate);

		gotoXY(82, 6);
		printf("Close");
		gotoXY(83, 7);
		printf("For");
		gotoXY(79, 8);
		printf("Sanitization");
		gotoXY(83, 2 * i + extraRowCount + 10);

		// print red color if venue are under sanitization
		if (venue[i].venueCloseForSanitization == TRUE) {
			red();
			printf("%s", "YES");
			green();
		}
		else
			printf("%s", "NO");

		gotoXY(94, 7);
		printf("Current");
		gotoXY(94, 8);
		printf("Visitors");
		gotoXY(97, 2 * i + extraRowCount + 10);
		printf("%d", venue[i].numberOfCurrentVisitors);

		gotoXY(105, 7);
		printf("Num.Of");
		gotoXY(105, 8);
		printf("Staff");
		gotoXY(107, 2 * i + extraRowCount + 10);
		printf("%d", venue[i].numberOfStaff);

		gotoXY(114, 7);
		printf("Maximum");
		gotoXY(114, 8);
		printf("Visitors");
		gotoXY(116, 2 * i + extraRowCount + 10);
		printf("%d", venue[i].maxNumberOfVisitors);

		gotoXY(125, 6);
		printf("Infected");
		gotoXY(126, 7);
		printf("Cases");
		gotoXY(125, 8);
		printf("At Past");
		gotoXY(128, 2 * i + extraRowCount + 10);

		// print red color if infected cases had happened at the venue
		if (venue[i].venueHistoryOfinfectedPeople == 0)
			printf("%d", venue[i].venueHistoryOfinfectedPeople);
		else {
			red();
			printf("%d", venue[i].venueHistoryOfinfectedPeople);
			green();
		}

		gotoXY(135, 7);
		printf("Covid");
		gotoXY(135, 8);
		printf("Zone");
		gotoXY(137, 2 * i + extraRowCount + 10);

		if (venue[i].venueMeasurementCovidZone == 'Y')
			yellow();
		else if (venue[i].venueMeasurementCovidZone == 'R')
			red();

		printf("%c", venue[i].venueMeasurementCovidZone);

		green();
		gotoXY(141, 6);
		printf("Area of");
		gotoXY(142, 7);
		printf("Venue");
		gotoXY(142, 8);
		printf("(km)");
		gotoXY(142, 2 * i + extraRowCount + 10);
		printf("%.2f", venue[i].venueAreaInMetres);

		gotoXY(151, 7);
		printf("Opening");
		gotoXY(152, 8);
		printf("Time");
		gotoXY(152, 2 * i + extraRowCount + 10);

		// Closing time is N/A when venue close for sanitizaiton
		if (venue[i].venueCloseForSanitization == TRUE) {
			strcpy(venue[i].venueOpeningTime, "N/A");
		}

		// print N/A in red color
		if (strcmp(venue[i].venueOpeningTime, "N/A") == 0) {
			red();
			printf("%s", venue[i].venueOpeningTime);
			green();
		}
		else
			printf("%s", venue[i].venueOpeningTime);

		gotoXY(161, 7);
		printf("Closing");
		gotoXY(162, 8);
		printf("Time");
		gotoXY(162, 2 * i + extraRowCount + 10);

		if (venue[i].venueCloseForSanitization == TRUE) {
			strcpy(venue[i].venueClosingTime, "N/A");
		}

		// print N/A in red color
		if (strcmp(venue[i].venueClosingTime, "N/A") == 0) {
			red();
			printf("%s", venue[i].venueClosingTime);
			green();
		}
		else
			printf("%s", venue[i].venueClosingTime);

		// ALLIGNMENT
		for (int j = 20; j < 170; j++) {
			gotoXY(j, 2 * i + extraRowCount + 11);
			printf("-");
		}
	}

	// table allignmnet
	for (int i = 6; i < totalRowOfData * 2 + extraRowCount + 9; i++)
	{
		gotoXY(20, i);
		printf("|");
		gotoXY(25, i);
		printf("|");
		gotoXY(45, i);
		printf("|");
		gotoXY(53, i);
		printf("|");
		gotoXY(64, i);
		printf("|");
		gotoXY(77, i);
		printf("|");
		gotoXY(92, i);
		printf("|");
		gotoXY(103, i);
		printf("|");
		gotoXY(112, i);
		printf("|");
		gotoXY(123, i);
		printf("|");
		gotoXY(134, i);
		printf("|");
		gotoXY(140, i);
		printf("|");
		gotoXY(149, i);
		printf("|");
		gotoXY(159, i);
		printf("|");
		gotoXY(169, i);
		printf("|");
	}

	if (modifyFile == 0) {

		// User choice to see next table
		gotoXY(40, totalRowOfData * 2 + extraRowCount + 12);
		blue();
		printf("Proceed to check venue equipment?(Y/N) [ ]\b\b");

		rewind(stdin);
		scanf("%c", &ans);
		printf("\n\n");
		red();

		//proceed to venue equipment table
		if (ans == 'Y' || ans == 'y') {
			for (int i = 3; i > 0; i--) {
				printf("%-50sClose Table in %d seconds..", "", i);
				for (int i = 0; i < 77; i++)
				{
					printf("\b");
				}
				_sleep(1000);
			}
			system("CLS");

			allignmentOfVenueEquipment(venue, modifyFile,saveRecord);
		}

		else {
			gotoXY(40, totalRowOfData * 2 + extraRowCount + 15);
			blue();
			printf("Proceed to check venue descriptions and last ten visitors name?(Y/N) [ ]\b\b");
			rewind(stdin);
			scanf("%c", &ans);

			if (ans == 'Y' || ans == 'y') {
				printf("\n");
				for (int i = 3; i > 0; i--) {
					red();
					printf("%-50sClose Table in %d seconds..", "", i);
					for (int i = 0; i < 77; i++)
					{
						printf("\b");
					}
					_sleep(1000);
				}
				//proceed to venue description and visitors menu
				system("CLS");
				green();
				allignmentOfVenueDescriptionAndVisitors(venue, modifyFile,saveRecord);
			}
		}
		reset();
	}

	else {
		int modifyOption;
		int modifyNumOfVenue;
		char newVenueIdentity[40];
		char newVenueInCharacter;
		int newVenueIdentityInNum;
		float newVenueIdentityInFloat;
		char option;
		char addSentenceInFile[200];

		gotoXY(40, totalRowOfData * 2 + extraRowCount + 12);
		blue();
		printf("Which data you would like to modify?\n\n");

		char modifyTable[13][30] = { "Name of the venue","Venue ID","Last Sanitization Date" ,"Close for Sanitization","Current visitors",
		"Number of staff","Maximum Visitors","Infected cases at past","Covid zone","Area of venue","Opening Time","Closing Time","None of the above"};

		purple();
		printf("%-25s", "");

		for (int i = 0; i < 13; i++) {
			if (i == 5 || i==10) {
				printf("\n\n%-25s","");
			}

			printf("%d =  %s%-10s", i + 1, modifyTable[i],"");
		}

		do {
			yellow();
			printf("\n\n%-40sYour option:[  ]\b\b\b", "");
			scanf("%d", &modifyOption);

			if (modifyOption > 0 && modifyOption < 13) {
				printf("\n%-39s What is the number of the venue you would like to modify? [  ]\b\b\b", "");
				scanf("%d", &modifyNumOfVenue);
				purple();
				printf("\n%-40s%s -> ", "",venue[modifyNumOfVenue-1].venueName);

				if (saveRecord == 1) {
					strcpy(addSentenceInFile, "User has modify ");
					strcat(addSentenceInFile, modifyTable[modifyOption - 1]);
					strcat(addSentenceInFile, " on a venue which is called ");
					strcat(addSentenceInFile, venue[modifyNumOfVenue - 1].venueName);
					strcat(addSentenceInFile, ".");
					strcat(addSentenceInFile, modifyTable[modifyOption-1]);
					strcat(addSentenceInFile, " ");
				}

				if (modifyOption == 1) {

					printf("\n%-40sWhat venue name you would like to change to >", "");
					yellow();
					rewind(stdin);
					scanf("%[^\n]", &newVenueIdentity);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %s->%s", addSentenceInFile, venue[modifyNumOfVenue - 1].venueName, newVenueIdentity);
					}
					strcpy(venue[modifyNumOfVenue - 1].venueName, newVenueIdentity);
				}

				else if (modifyOption == 2) {

					printf("%s", venue[modifyNumOfVenue - 1].venueID);
					yellow();
					printf("\n\n%-40sWhat venue ID you would like to change to >", "");
					rewind(stdin);
					scanf("%s", &newVenueIdentity);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %s->%s", addSentenceInFile, venue[modifyNumOfVenue - 1].venueID, newVenueIdentity);
					}
					strcpy(venue[modifyNumOfVenue - 1].venueID, newVenueIdentity);
				}
				else if (modifyOption == 3) {
					printf("%s", venue[modifyNumOfVenue - 1].venueLastSanitizationDate);
					yellow();
					printf("\n\n%-40sWhat Sanitizaiton date you would like to change to (DD-MM-YYYY) >", "");
					rewind(stdin);
					scanf("%s", &newVenueIdentity);
					if (saveRecord == 1) {
						strcat(addSentenceInFile, venue[modifyNumOfVenue - 1].venueLastSanitizationDate);
						strcat(addSentenceInFile, "->");
						strcat(addSentenceInFile, newVenueIdentity);
					}
					strcpy(venue[modifyNumOfVenue - 1].venueLastSanitizationDate, newVenueIdentity);
				}

				else if (modifyOption == 4) {
					printf("%d", venue[modifyNumOfVenue - 1].venueCloseForSanitization);
					yellow();
					printf("\n\n%-40sWhat value you would like to change to ( 1 = Close / 0 = Open) >", "");
					scanf("%d", &newVenueIdentityInNum);
					validationForNum(&newVenueIdentityInNum);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %d->%d", addSentenceInFile, venue[modifyNumOfVenue - 1].venueCloseForSanitization, newVenueIdentityInNum);
					}
					venue[modifyNumOfVenue - 1].venueCloseForSanitization = newVenueIdentityInNum;
				}

				else if (modifyOption == 5) {
					printf("%d", venue[modifyNumOfVenue - 1].numberOfCurrentVisitors);
					yellow();
					printf("\n\n%-40sHow many number of current visitors you would like to change to>", "");
					scanf("%d", &newVenueIdentityInNum);
					validationForNum(&newVenueIdentityInNum);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %d->%d", addSentenceInFile, venue[modifyNumOfVenue - 1].numberOfCurrentVisitors, newVenueIdentityInNum);
					}
					venue[modifyNumOfVenue - 1].numberOfCurrentVisitors = newVenueIdentityInNum;
				}

				else if (modifyOption == 6) {
					printf("%d", venue[modifyNumOfVenue - 1].numberOfStaff);
					yellow();
					printf("\n\n%-40sHow many number of staff you would like to change to>", "");
					scanf("%d", &newVenueIdentityInNum);
					validationForNum(&newVenueIdentityInNum);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %d->%d", addSentenceInFile, venue[modifyNumOfVenue - 1].numberOfStaff, newVenueIdentityInNum);
					}
					venue[modifyNumOfVenue - 1].numberOfStaff = newVenueIdentityInNum;
				}

				else if (modifyOption == 7) {
					printf("%d", venue[modifyNumOfVenue - 1].maxNumberOfVisitors);
					yellow();
					printf("\n\n%-40sHow many number of maximum visitors you would like to change to>", "");
					scanf("%d", &newVenueIdentityInNum);
					validationForNum(&newVenueIdentityInNum);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %d->%d", addSentenceInFile, venue[modifyNumOfVenue - 1].maxNumberOfVisitors, newVenueIdentityInNum);
					}
					venue[modifyNumOfVenue - 1].maxNumberOfVisitors = newVenueIdentityInNum;
				}

				else if (modifyOption == 8) {
					printf("%d", venue[modifyNumOfVenue - 1].venueHistoryOfinfectedPeople);
					yellow();
					printf("\n\n%-40sHow many number of infected cases at past you would like to change to>", "");
					scanf("%d", &newVenueIdentityInNum);
					validationForNum(&newVenueIdentityInNum);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %d->%d", addSentenceInFile, venue[modifyNumOfVenue - 1].venueHistoryOfinfectedPeople, newVenueIdentityInNum);
					}
					venue[modifyNumOfVenue - 1].venueHistoryOfinfectedPeople = newVenueIdentityInNum;
				}

				else if (modifyOption == 9) {
					printf("%c", venue[modifyNumOfVenue - 1].venueMeasurementCovidZone);
					yellow();
					printf("\n\n%-40sWhich covid zone you would like to change to >", "");
					rewind(stdin);
					scanf("%c", &newVenueInCharacter);
					newVenueInCharacter = toupper(newVenueInCharacter);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %c->%c", addSentenceInFile, venue[modifyNumOfVenue - 1].venueMeasurementCovidZone, newVenueInCharacter);
					}
					venue[modifyNumOfVenue - 1].venueMeasurementCovidZone = newVenueInCharacter;
				}

				else if (modifyOption == 10) {
				printf("%.2f", venue[modifyNumOfVenue - 1].venueAreaInMetres);
				yellow();
				printf("\n\n%-40sWhat's the new area for the venue >", "");
				scanf("%d", &newVenueIdentityInFloat);

				if (saveRecord == 1) {
					sprintf(addSentenceInFile, "%s %.2f->%.2f", addSentenceInFile, venue[modifyNumOfVenue - 1].venueAreaInMetres, newVenueIdentityInFloat);
				}
				venue[modifyNumOfVenue - 1].venueAreaInMetres = newVenueIdentityInFloat;
				}

				else if (modifyOption == 11) {
					printf("%s", venue[modifyNumOfVenue - 1].venueOpeningTime);
					yellow();
					printf("\n\n%-40sWhat opening time you would like to change to (HH:MM) >", "");
					rewind(stdin);
					scanf("%s", &newVenueIdentity);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %s->%s", addSentenceInFile, venue[modifyNumOfVenue - 1].venueOpeningTime, newVenueIdentity);
					}
					strcpy(venue[modifyNumOfVenue - 1].venueOpeningTime, newVenueIdentity);
				}

				else if (modifyOption == 12) {
					printf("%s", venue[modifyNumOfVenue - 1].venueClosingTime);
					yellow();
					printf("\n\n%-40sWhat closing time you would like to change to (HH:MM) >", "");
					rewind(stdin);
					scanf("%s", &newVenueIdentity);
					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %s->%s", addSentenceInFile, venue[modifyNumOfVenue - 1].venueClosingTime, newVenueIdentity);
					}
					strcpy(venue[modifyNumOfVenue - 1].venueClosingTime, newVenueIdentity);
				}
				if (saveRecord == 1) {
					addActivityOfUser(addSentenceInFile);
				}
			}
			else if (modifyOption > 12 || modifyOption < 0) {
				red();
				printf("\n%-40sYou have selected none of the above or invalid option.\n","");
				yellow();
			}

			printf("\n%-40sModify other data? (Y/N) [ ]\b\b", "");
			rewind(stdin);
			scanf("%c", &option);

		} while (option == 'Y' || option == 'y');

		printf("\n%-40sProceed to another venue equipment table to modify? (Y/N) [ ]\b\b", "");
		rewind(stdin);
		scanf("%c", &option);

		if (option == 'Y' || option == 'y') {
			system("CLS");
			allignmentOfVenueEquipment(venue, modifyFile,saveRecord);
		}

		else {
			printf("\n%-40sProceed to another venue description table and last ten visitors to modify? (Y/N) [ ]\b\b", "");
			rewind(stdin);
			scanf("%c", &option);

			if (option == 'Y' || option == 'y') {
				system("CLS");
				allignmentOfVenueDescriptionAndVisitors(venue, modifyFile,saveRecord);
			}
		}
	}
}

void allignmentOfVenueEquipment(VenueInformation venue[30], int modifyFile,int saveRecord)
{
	char ans;
	char addSentenceInFile[200];

	if (saveRecord == 1) {
		strcpy(addSentenceInFile, "User has checked venue equipment table");
		addActivityOfUser(addSentenceInFile);
	}

	gotoXY(60, 3);
	underlineGreen();
	printf("Venue Equipment");
	green();

	gotoXY(20, 11);
	printf("No.");
	gotoXY(35, 10);

	printf("Name of");
	gotoXY(34, 11);
	printf("the Venue");

	gotoXY(75, 7);
	printf("Venue Equipment");
	gotoXY(58, 9);

	printf("Number of");
	gotoXY(58, 10);
	printf("Available");
	gotoXY(56, 11);
	printf("Nose Swab Test");

	gotoXY(76, 9);
	printf("Availability");
	gotoXY(81, 10);
	printf("of");
	gotoXY(73, 11);
	printf("Temperature sensor");

	gotoXY(94, 9);
	printf("Number");
	gotoXY(96, 10);
	printf("of");
	gotoXY(94, 11);
	printf("Masks");

	gotoXY(104, 9);
	printf("Number of");
	gotoXY(103, 10);
	printf("Sanitization");
	gotoXY(105, 11);
	printf("Bottles");

	gotoXY(118, 9);
	printf("Volume");
	gotoXY(118, 10);
	printf("of Each");
	gotoXY(118, 11);
	printf("Bottles");

	// print table
	for (int i = 0; i < totalRowOfData; i++) {

		gotoXY(20, 2 * i + 13);
		printf("%d.", i + 1);

		gotoXY(25, 2 * i + 13);
		printf("%s", venue[i].venueName);

		gotoXY(61, 2 * i + 13);
		printf("%d", venue[i].availabilityOfEquipment.numOfAvailableNoseSwabTest);

		gotoXY(80, 2 * i + 13);
		if (venue[i].availabilityOfEquipment.availabilityOfTemperatureSensor == TRUE) {
			printf("TRUE");
		}
		else{
			red();
			printf("FALSE");
			green();
		}

		gotoXY(95, 2 * i + 13);
		printf("%d", venue[i].availabilityOfEquipment.numberOfMask);

		gotoXY(107, 2 * i + 13);
		printf("%d", venue[i].availabilityOfEquipment.numOfSanizationBottle);

		gotoXY(119, 2 * i + 13);
		printf("%.2f L", venue[i].availabilityOfEquipment.volumeOfSanizationBottleInLitres);

		green();
		//ALLIGNMENT
		for (int j = 18; j < 127; j++) {
			gotoXY(j, 6);
			printf("-");
			gotoXY(j, 8);
			printf("-");
			gotoXY(j, 12);
			printf("-");
			gotoXY(j, 2 * i + 14);
			printf("-");
		}

		// ALLIGNMNET
		for (int j = 7; j < totalRowOfData*2+12; j++) {
			gotoXY(18, j);
			printf("|");
			gotoXY(24, j);
			printf("|");
			gotoXY(54, j);
			printf("|");
			gotoXY(126, j);
			printf("|");
			if (j == 7 || j == 8)
				continue;
			gotoXY(71, j);
			printf("|");
			gotoXY(92, j);
			printf("|");
			gotoXY(101, j);
			printf("|");
			gotoXY(116, j);
			printf("|");
		}
	}
	
	if (modifyFile == 0) {
		gotoXY(40, totalRowOfData * 2 + 15);
		blue();
		printf("Proceed to check venue description and last ten visitors?(Y/N) [ ]\b\b");
		rewind(stdin);
		scanf("%c", &ans);

		//proceed to venue description and visitors table
		if (ans == 'Y' || ans == 'y') {
			printf("\n\n");
			red();
			for (int i = 3; i > 0; i--) {
				printf("%-50sTable will be closed in %d seconds...", "", i);
				for (int i = 0; i < 86; i++)
					printf("\b");
				_sleep(1000);
			}
			system("CLS");
			allignmentOfVenueDescriptionAndVisitors(venue, modifyFile,saveRecord);
		}
	}

	else {
		int option;
		int numOfVenue;
		char modifyOption;
		int modifyInNum;
		float modifyInFloat;
		char modifyEquipmentTable[6][60] = {"Number of available nose swab test","Availability of temperature sensor" ,"Number of masks",
		"Number of sanitization bottles","Volume of each sanitization bottles","None of the above"
		};

		printf("\n\n\n%-60sWhich data you would like to modify?", "");
		purple();
		printf("\n\n%-30s", "");

		for (int i=0;i<6;i++){
			if (i == 3)
				printf("\n%-30s","");

			printf("%d. %s%-10s", i + 1, modifyEquipmentTable[i],"");
		}

		do {
			yellow();
			printf("\n\n%-30sYour option >[ ]\b\b", "");
			scanf("%d", &option);

			if (option > 0 && option < 6) {
				printf("\n%-30sWhat is the number of the venue you would like to modify? [  ]\b\b\b","");
				scanf("%d", &numOfVenue);

				if (saveRecord == 1) {
					strcpy(addSentenceInFile, "User has modify ");
					strcat(addSentenceInFile, modifyEquipmentTable[option - 1]);
					strcat(addSentenceInFile, " on a venue which is called ");
					strcat(addSentenceInFile, venue[numOfVenue - 1].venueName);
					strcat(addSentenceInFile, ".");
					strcat(addSentenceInFile, modifyEquipmentTable[option - 1]);
					strcat(addSentenceInFile, " ");
				}

				purple();
				printf("\n%-30s%s > ", "",venue[numOfVenue - 1].venueName);
				yellow();

				if (option == 1) {
					printf("%d", venue[numOfVenue - 1].availabilityOfEquipment.numOfAvailableNoseSwabTest);
					printf("\n\n%-30sWhat is the number of available nose swab test you would like to change to >","");
					scanf("%d", &modifyInNum);
					validationForNum(&modifyInNum);

					if (saveRecord == 1) {
						sprintf(addSentenceInFile,"%s %d ->%d",addSentenceInFile,venue[numOfVenue - 1].availabilityOfEquipment.numOfAvailableNoseSwabTest, modifyInNum);
					}
					venue[numOfVenue - 1].availabilityOfEquipment.numOfAvailableNoseSwabTest = modifyInNum;
				}

				else if (option == 2) {
					printf("%d", venue[numOfVenue - 1].availabilityOfEquipment.availabilityOfTemperatureSensor);

					printf("\n\n%-30sWhat is the value of availability of temperature sensor you would like to change to ( 1 = TRUE / 0 = FALSE) >","");
					scanf("%d", &modifyInNum);
					validationForNum(&modifyInNum);

					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %d ->%d", addSentenceInFile,venue[numOfVenue - 1].availabilityOfEquipment.availabilityOfTemperatureSensor, modifyInNum);
					}

					venue[numOfVenue - 1].availabilityOfEquipment.availabilityOfTemperatureSensor = modifyInNum;
				}

				else if (option == 3) {
					printf("%d", venue[numOfVenue - 1].availabilityOfEquipment.numberOfMask);

					printf("\n\n%-30sWhat is the number of masks you would like to change to >","");
					scanf("%d", &modifyInNum);
					validationForNum(&modifyInNum);

					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %d ->%d", addSentenceInFile,venue[numOfVenue - 1].availabilityOfEquipment.numberOfMask, modifyInNum);
					}

					venue[numOfVenue - 1].availabilityOfEquipment.numberOfMask = modifyInNum;
				}

				else if (option == 4) {
					printf("%d", venue[numOfVenue - 1].availabilityOfEquipment.numOfSanizationBottle);

					printf("\n\n%-30sWhat is the number of sanitization bottles you would like to change to >","");
					scanf("%d", &modifyInNum);
					validationForNum(&modifyInNum);

					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %d ->%d", addSentenceInFile,venue[numOfVenue - 1].availabilityOfEquipment.numOfSanizationBottle, modifyInNum);
					}

					venue[numOfVenue - 1].availabilityOfEquipment.numOfSanizationBottle = modifyInNum;
				}

				else if (option == 5) {
					printf("%.2f", venue[numOfVenue - 1].availabilityOfEquipment.volumeOfSanizationBottleInLitres);

					printf("\n\n%-30sWhat is the volume of sanitization bottles you would like to change to >","");
					scanf("%f", &modifyInFloat);

					while (modifyInFloat < 0) {
						red();
						printf("Error! Please retype with a valid number");
						scanf("%f", &modifyInFloat);
					}
					int correctToIntVolume;
					correctToIntVolume = modifyInFloat * 1000;

					if (saveRecord == 1) {
						sprintf(addSentenceInFile, "%s %f ->%f", addSentenceInFile,venue[numOfVenue - 1].availabilityOfEquipment.volumeOfSanizationBottleInLitres, modifyInFloat);
					}

					venue[numOfVenue - 1].availabilityOfEquipment.volumeOfSanizationBottleInLitres = modifyInFloat;
				}
				if (saveRecord == 1) {
					addActivityOfUser(addSentenceInFile);
				}
			}
			else {
				red();
				printf("\nYou have chosen none of the above or invalid option.");
				yellow();
			}

			printf("\n\n%-30sContinue to modify? (Y/N) [ ]\b\b","");
			rewind(stdin);
			scanf("%c", &modifyOption);

		} while (modifyOption == 'Y' || modifyOption == 'y');

		printf("\n%-30sProceed to another venue description table and last ten visitors to modify? (Y/N) [ ]\b\b", "");
		rewind(stdin);
		scanf("%c", &modifyOption);

		if (modifyOption == 'Y' || modifyOption == 'y') {
			system("CLS");
			allignmentOfVenueDescriptionAndVisitors(venue, modifyFile,saveRecord);
		}
	}
}

void allignmentOfVenueDescriptionAndVisitors(VenueInformation venue[30], int modifyFile,int saveRecord)
{
	if (saveRecord == 1) {
		char addSentenceInFile[200];

		strcpy(addSentenceInFile, "User has checked venue descriptions and visitors table");
		addActivityOfUser(addSentenceInFile);
	}

	gotoXY(60, 1);
	underlineGreen();
	printf(" VENUE DESCRIPTION AND LAST TEN VISIOTRS ");
	green();

	printf("\n\n\n    ");
	for (int i = 0; i < 150; i++)
		printf("-");

	gotoXY(5, 5);
	printf("No.");

	gotoXY(10, 5);
	printf("Name of the venue");

	gotoXY(40, 5);
	printf("Venue Descriptions");

	gotoXY(120, 5);
	printf("Last Ten Visitors Name");

	printf("\n    ");
	for (int i = 0; i < 150; i++)
		printf("-");

	//table allignment
	for (int i = 5; i < totalRowOfData*11+7; i++) {
		
		gotoXY(4, i);
		printf("|");

		gotoXY(9, i);
		printf("|");

		gotoXY(39, i);
		printf("|");

		gotoXY(109, i);
		printf("|");

		gotoXY(153, i);
		printf("|");
	}

	//display table
	for (int i = 0; i < totalRowOfData; i++)
	{
		gotoXY(5, 11 * i + 7);
		printf("%d.", i+1);

		gotoXY(10, 11 * i + 7);
		printf("%s", venue[i].venueName);

		gotoXY(40, 11 * i + 7);
		printf("%s", venue[i].venueDescriptions);

		for (int j = 0; j < 10; j+=2) {

			gotoXY(113, 11 * i + 7+j);
			printf("%d.%s", j+1,venue[i].venueHistoryOfLastTenVistorsName[j]);

			gotoXY(112, 11 * i + 7 + j);
			printf("|");

			gotoXY(130,11 * i + 7 + j);
			printf("|");

			gotoXY(149, 11 * i + 7 + j);
			printf("|");

			for (int k = 112; k < 150; k++) {
				gotoXY(k, 11 * i + 8 + j);
				printf("*");
			}

			// more space for 2 visitor name in same row
			gotoXY(131, 11 * i + 7 + j);
			printf("%d.%s", j + 2, venue[i].venueHistoryOfLastTenVistorsName[j+1]);

		}
		printf("\n\n    ");
		for (int i=0;i<150;i++)
		printf("-");
	}
	
	if (modifyFile == 1) {
		int option;
		int numOfVenue;
		char newDescriptions[100];
		int numOfVisitors;
		char newVisitorsName[40];
		char modifyOption;
		char addSentenceInFile[200];

		printf("\n\n\n%-40sWhich data you would like to modify?","");

		purple();
		char selection[3][40] = {"Venue Descriptions","Visitors name","None of the above"};
		printf("\n\n");

		for (int i = 0; i < 3; i++) {
			printf("%-30s%d. %s%-10s","", i + 1, selection[i],"");
		}

		do {
			yellow();
			printf("\n\n%-40sYour option > [ ]\b\b", "");
			scanf("%d", &option);

			if (option == 1 || option == 2) {
				printf("\n%-40sWhat is the number of venue you would like to change >", "");
				scanf("%d", &numOfVenue);

				if (saveRecord == 1) {
					strcpy(addSentenceInFile, "User has modify ");
					strcat(addSentenceInFile, selection[option - 1]);
					strcat(addSentenceInFile, " on a venue which is called ");
					strcat(addSentenceInFile, venue[numOfVenue - 1].venueName);
					strcat(addSentenceInFile, ".");
					strcat(addSentenceInFile, selection[option - 1]);
					strcat(addSentenceInFile, " ");
				}

				if (option == 1) {
					printf("\n%-40s%s->%s","", venue[numOfVenue - 1].venueName, venue[numOfVenue - 1].venueDescriptions);

					printf("\n\n%-40sWhat's the new description for this venue >", "");
					rewind(stdin);
					scanf("%[^\n]", &newDescriptions);

					if (saveRecord == 1) {
						strcat(addSentenceInFile, venue[numOfVenue - 1].venueDescriptions);
						strcat(addSentenceInFile, "->");
						strcat(addSentenceInFile, newDescriptions);
					}

					strcpy(venue[numOfVenue - 1].venueDescriptions, newDescriptions);
				}

				else if (option == 2) {
					printf("\n%-40sWhich number of visitors you would like to change >", "");
					scanf("%d", &numOfVisitors);

					purple();
					printf("\n%-40s%s - %s\n", "", venue[numOfVenue - 1].venueName, venue[numOfVenue - 1].venueHistoryOfLastTenVistorsName[numOfVisitors - 1]);

					yellow();
					printf("\n%-40sPlease enter the modifed name >", "");
					rewind(stdin);
					scanf("%[^\n]", &newVisitorsName);

					if (saveRecord == 1) {
						strcat(addSentenceInFile, venue[numOfVenue - 1].venueHistoryOfLastTenVistorsName[numOfVisitors - 1]);
						strcat(addSentenceInFile, "->");
						strcat(addSentenceInFile, newVisitorsName);
					}

					strcpy(venue[numOfVenue - 1].venueHistoryOfLastTenVistorsName[numOfVisitors - 1], newVisitorsName);
				}

				if (saveRecord == 1) {
					addActivityOfUser(addSentenceInFile);
				}
			}
			else {
				red();
				printf("\n%-40sYou have selected none of the above or invalid option.","");
				yellow();
			}
			printf("\n\n%-40sContinue to modify? (Y/N) [ ]\b\b", "");
			rewind(stdin);
			scanf("%c", &modifyOption);
		
		} while (modifyOption == 'Y' || modifyOption == 'y');
	}
}

void fileValidation(FILE **fileName,char fileName2[30],int saveRecord,int power) //TO CHECK FILE EXISTENCE, IF NOT WILL ASK USER WHETHER TO CREATE A NEW FILE
{
	char ans;

	if (*fileName == NULL) {
		printf("%s is not exist.\n", fileName2);

		printf("Do you want to add the file manually (Y/N) >");
		rewind(stdin);
		scanf("%c", &ans);

		if (ans == 'Y' || ans == 'y') {
			venueAdd(saveRecord,power);
		}

		else {
			system("pause");
			exit(-1);
		}
	}
}

void deleteData(VenueInformation venue[30],int saveRecord,int power)
{
	if (power == 1) {

		int deleteData, deleteCount;

		printf("\n\n");
		green();

		for (int i = 0; i < totalRowOfData; i++) {
			printf("%-50s%d.  %s\n\n", "", i + 1, venue[i].venueName);
		}

		printf("%-50s%d.  None of the above\n\n", "", totalRowOfData + 1);

		yellow();
		printf("\n%-50sWhat number of venue you would like to delete > [  ]\b\b\b", "");
		scanf("%d", &deleteData);

		while (deleteData > totalRowOfData + 1 || deleteData < 0) {
			red();
			printf("It's not valid option.Please retype");
			scanf("%d", &deleteData);
		}
		deleteData--;

		if (deleteData != totalRowOfData) {

			FILE* deleteDataInFile;
			deleteDataInFile = fopen("venue.txt", "w");
			fileValidation(&deleteDataInFile, "Venue.txt", saveRecord, power);

			if (saveRecord == 1) {
				char addSentenceInFile[200];

				strcpy(addSentenceInFile, "User has deleted ");
				strcpy(addSentenceInFile, venue[deleteData].venueName);
				addActivityOfUser(addSentenceInFile);
			}

			venue[deleteData].deleteRow = 1;

			for (int i = 0; i < totalRowOfData; i++) {
				if (venue[i].deleteRow != 1) {
					fprintf(deleteDataInFile, "%s|%s|%c|%s|%d,%d,%d,%d,%d,%.2f,%c,%s,%s,%d,%d,%d,%d,%.2f,", venue[i].venueName, venue[i].venueID, venue[i].venueCategory,
						venue[i].venueLastSanitizationDate, venue[i].venueCloseForSanitization, venue[i].numberOfCurrentVisitors, venue[i].numberOfStaff,
						venue[i].maxNumberOfVisitors, venue[i].venueHistoryOfinfectedPeople, venue[i].venueAreaInMetres, venue[i].venueMeasurementCovidZone,
						venue[i].venueOpeningTime, venue[i].venueClosingTime, venue[i].availabilityOfEquipment.numOfAvailableNoseSwabTest,
						venue[i].availabilityOfEquipment.availabilityOfTemperatureSensor, venue[i].availabilityOfEquipment.numberOfMask,
						venue[i].availabilityOfEquipment.numOfSanizationBottle, venue[i].availabilityOfEquipment.volumeOfSanizationBottleInLitres);

					for (int m = 0; m < 10; m++) {
						// adjust name before adding to text file
						if (m == 9)
							fprintf(deleteDataInFile, "%s", venue[i].venueHistoryOfLastTenVistorsName[m]);
						else
							fprintf(deleteDataInFile, "%s.", venue[i].venueHistoryOfLastTenVistorsName[m]);
					}

					fprintf(deleteDataInFile, "\n%s*\n", venue[i].venueDescriptions);
				}
			}

			fclose(deleteDataInFile);
			deleteDataInFile = fopen("venue.txt", "r");
			char c;
			int count = 0;

			red();
			printf("\n%-50sDone deleted.", "");

			while (fscanf(deleteDataInFile, "%c", &c) != EOF) {
				if (c == '\n')
					count++;
			}
			fclose(deleteDataInFile);

			totalRowOfData = count / 2;
		}
		else {
			red();
			printf("\n\n%-50sYou have selected not to delete any venue!\n","");
		}
	}

	else {
		red();
		printf("You are not allowed to delete file.");
		reset();
	}
}

void activity(int saveRecord) {
	green();

	if (saveRecord == 1) 
		printf("You may view your activity in venueActivity.txt after closing this program.");

	else
		printf("You are not able to view your activity in venueActivity.txt. ");

}

int saveRecordOfUser() //TO SAVE ALL THE RECORD DONE BY USER IN ADD, MODIFY,SEARCH AND DISPLAY
{
	int saveRecord;
	FILE* activity;
	activity = fopen("venueActivity.txt", "w");

	printf("%-48sDo you want to save your venue activity in the program into a text file?\n\n%-52sYou may view it after closing this program. ( 1 = YES / 0 = NO)\n\n","","");
	yellow();
	printf("\n%-75sYour option [ ]\b\b","");
	scanf("%d", &saveRecord);
	
	while (saveRecord != 1 && saveRecord != 0) {
		red();
		printf("\n%-50sPlease enter a valid option for this program.\n","");
		printf("%-50sDo you want to save your activity in the program into a text file?\n%-52sYou may view it after closing this program. ( 1 = YES / 0 = NO)\n\n", "", "");
		yellow();
		printf("%-75sYour option [ ]\b\b", "");
		scanf("%d", &saveRecord);
	}

	if (saveRecord == 1) {
		printLocalTimeInFile(&activity);
		fprintf(activity, "User has selected to save file.\n");
	}

	else
		fprintf(activity, " ");

	fclose(activity);

	return saveRecord;
}

void addActivityOfUser(char addSentenceInFile[200]) {
	FILE* addActivity;

	addActivity = fopen("venueActivity.txt", "a");
	printLocalTimeInFile(&addActivity);

	fprintf(addActivity,"%s\n",addSentenceInFile);
}

void gotoXY(int x, int y) //ALLIGNMENT PURPOSE
{
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printLocalTime() {
	SYSTEMTIME t;
	GetLocalTime(&t);
	printf("%d/%d/%d %d:%d:%d ", t.wMonth, t.wDay, t.wYear, t.wHour, t.wMinute, t.wSecond);

	if (t.wHour > 12) {
		printf("PM");
	}
	else
		printf("AM");
}

void printLocalTimeInFile(FILE **addLocalTime) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	fprintf(*addLocalTime,"%02d/%02d/%d %02d:%02d:%02d ", t.wMonth, t.wDay, t.wYear, t.wHour, t.wMinute, t.wSecond);

	if (t.wHour > 12) {
		fprintf(*addLocalTime,"PM :");
	}

	else
		fprintf(*addLocalTime,"AM :");
}