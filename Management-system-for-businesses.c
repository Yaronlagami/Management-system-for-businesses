// Yaron Lagami, ID - 301463279
//Shahar Hagbi. ID - 207071127

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>

typedef struct Item_List {
	int Id;
	char ItemType[10];
	char ItemColor[10];
	double ItemPrice;
	int ItemAmount;
	_Bool Gender;
	time_t time;
	struct Item_List* right;
	struct Item_List* left;
}node;
typedef struct employee 
{
	char UserName[15];
	char Password[15];
	char FullName[15];
	char Level[2];
}Employee;
typedef struct customers
{
	time_t DateOfJoined;
	char Name[15];
	int TotalItems;
	int Item_ID[3];
	time_t DateOfPurchase1;
	time_t DateOfPurchase2;
	time_t DateOfPurchase3;
	struct customers* next;
}Customers;

time_t Date_Of_Joining();
time_t Date_Of_Purchase();
Customers* Auto_Customer(time_t DateOfJoined, char Name[], int TotalItems, int Item_ID[], time_t DateOfPurchase1, time_t DateOfPurchase2, time_t DateOfPurchase3);
Customers* Create_List_Of_Customer_From_File();
Customers* Create_Customer();
Customers* Add_Customer(Customers* head_c, Customers* new_customer);
void Display_A_Customer_From_File();
void Free_List_Of_Customer(Customers* head_c);
void Write_To_File(Customers* head_c);
void Display_A_Customer(Customers* head_c);
void Display_All_Customer(Customers* head_c);
void Display_List_Of_Customer(Customers* head_c);
void Find_Customers_With_Name(Customers* head_c);
int Find_Customers(Customers* head_c, char* name);
void Sell_Item(Customers* head_c);
void Buy_Item(Customers* head_c);
void Remove_Customer_With_Name(Customers** head_c);
void UpdateCustomer(Customers* customer, int Id);
void UpdateCustomer3(Customers* customer, int Id);
void Find_Customers2(Customers* head_c, char* name, int Id);
void Find_Customers3(Customers* head_c, char* name, int Id);
int ReturnItem(Customers* customer, int Id);
int ReturnItemForCustomer(Customers* head_c, char* name, int Id);
void PrintToLogFile(char part1[60], char part2[60], int Num);
void PrintToLogFile_I(char part1[60], char part2[60]);
void PrintToLogFile_1(char part1[60], int Num, char part2[60], int Num2);
void PrintToLogFile_2(char part1[60], int Num, char part2[60], char part3[60]);
int UserIdentification(char* level);
void SetColor(int Color);//31 red, 32 green, 33 yellow, 34 blue, 35 purple
void ResetColor();
int CheckUser(char UserName[], char Password[]);
void Print_Item_To_Consul(node New_Item);
void SaveTree(node * root);
void save_node(node * Node, FILE * fp);
void Insert(node * *tree, int val);
void Print_Tree_From_Variable(node * tree);
void Print_Tree_From_File();
void DeleteZerosFromFile();
node* search(node * *tree, int val);
void Search_By_Type(node * *tree, char* ItemType, int* sum);
void Search_By_Color(node * *tree, char* ItemType, int* sum);
void Search_By_Color_And_Type(node * *tree, char* ItemType, char* ItemColor, int* sum);
void Search_By_Price_Less(node * *tree, double ItemPrice, int* sum);
void Search_By_Price_More(node * *tree, double ItemPrice, int* sum);
void Search_By_Gender_Man(node * *tree, int Gender, int* sum);
void Search_By_Gender_Woman(node * *tree, int Gender, int* sum);
void Search_By_Date_Less(node * *tree, int day, int month, int year, int* sum);
int DeleteNode(node * *tree, int Id);
void UpdateItemProperties(node * *tree, int val);
void SellItem(node * *tree, int val, int AmountToSell);
void GettItem(node * *tree, int val, int AmountToGet);
void AutoInsert(node * *tree, int val, char ItemType[], char ItemColor[], double ItemPrice, int ItemAmount, int Gender, time_t time);
void InsertNewEmployees(Employee * employees, int numEmployees);
void InsertNewEmployees(Employee * employees, int numEmployees, int numEmExist);
void PrintEployee(Employee * employees);
void WriteEmployeesToFile(Employee * employees, int TotEmp);

int main()
{
	node* NewRoot = NULL;
	Employee* employees = NULL;
	Customers* HeadOfCustomers = NULL;
	Customers* temp = NULL;
	node* tmp = NULL;
	int value, choice;
	char level[2];
	level[0] = '0';
	char level1[] = "1";
	char level2[] = "2";
	char level3[] = "3";
	FILE* fp1 = fopen("My_Items.bin", "rb");
	FILE* fp2 = fopen("My_Customers.bin", "rb");
	FILE* fp3 = fopen("My_Employees.bin", "rb");
	if (fp3 == NULL)
	{
		printf("making new employees file\n");
		FILE* fp3 = fopen("My_Employees.bin", "wb");
		Employee employee1;
		strncpy(employee1.UserName, "admin", sizeof(employee1.UserName));
		strncpy(employee1.Password, "admin", sizeof(employee1.Password));
		strncpy(employee1.FullName, "System_Manager", sizeof(employee1.FullName));
		strncpy(employee1.Level, "3", sizeof(employee1.Level));
		fwrite(&employee1.UserName, sizeof(employee1.UserName), 1, fp3);
		fwrite(&employee1.Password, sizeof(employee1.Password), 1, fp3);
		fwrite(&employee1.FullName, sizeof(employee1.FullName), 1, fp3);
		fwrite(&employee1.Level, sizeof(employee1.Level), 1, fp3);
		fclose(fp3);
	}
	else
	{
		FILE* fp3 = fopen("My_Employees.bin", "rb");
		fseek(fp3, 0, SEEK_END);
		int fileSize = ftell(fp3);
		int numEmployees = fileSize / sizeof(Employee);
		rewind(fp3);
		employees = (Employee*)malloc(numEmployees * sizeof(Employee));
		fread(employees, sizeof(Employee*), numEmployees, fp3);
		fclose(fp3);
	}
	if (fp1 == NULL)
	{
		printf("making new items file\n");
		FILE* fp1 = fopen("My_Items.bin", "wb");
		fclose(fp1);
	}
	else
	{
		node Node;
		int Id, ItemAmount, Gender;
		double ItemPrice;
		time_t time;
		char ItemType[10];
		char ItemColor[10];
		FILE* fp1 = fopen("My_Items.bin", "rb");
		while (fread(&Node, sizeof(node), 1, fp1)) 
		{
			Id = Node.Id;
			strncpy(ItemType, Node.ItemType, sizeof(ItemType));
			strncpy(ItemColor, Node.ItemColor, sizeof(ItemColor));
			ItemPrice = Node.ItemPrice;
			ItemAmount = Node.ItemAmount;
			Gender = Node.Gender;
			time = Node.time;
			if (Id != 0)
				AutoInsert(&NewRoot, Id, ItemType, ItemColor, ItemPrice,
							ItemAmount, Gender, time);
		}
		fclose(fp1);
	}
	if (fp2 == NULL)
	{
		FILE* fp2 = fopen("My_Customers.bin", "wb");
		fclose(fp2);
	}
	else
	{
		HeadOfCustomers = Create_List_Of_Customer_From_File();
	}
	int Tries = 0;
	while (Tries < 3)
	{
		if (UserIdentification(&level) == 0)
			break;
		else
		{
			SetColor(31);
			printf("\nUsername or password is incorrect\n");
			ResetColor();
			Tries++;
		}
	}
	if (Tries == 3)
	{
		SetColor(31);
		printf("Third incorrect entry - the program will close\n");
		ResetColor();
		char part1[40] = "3 failed attempts were made";
		char part2[40] = "to connect to the system";
		PrintToLogFile_I(part1, part2);
		exit(0);
	}
	do
	{
		if (strcmp(level, level1)==0)
		{
			SetColor(34);
			printf("\n============> MAIN MENU <============\n");
			printf("\n============>  LEVEL 1  <============\n");
			ResetColor();
			SetColor(35);
			printf("Choose your operation:\n\n");
			printf("1.ADD NEW ITEM\n");
			printf("2.DISPLAY ITEMS LIST \n");
			printf("3.SEARCH ITEM IN STORE \n");
			printf("4.ADD NEW CUSTOMER \n");
			printf("5.FIND CUSTOMER BY NAME \n");
			printf("6.DISPLAY CUSTOMERS LIST \n");
			SetColor(31); printf("7.EXIT \n"); ResetColor();
			printf("\nYOUR CHOISE IS: ");
			scanf("%d", &choice);
			printf("\n");
			switch (choice)
			{
			case 1:
			{
				printf("If its a new prodact press '1'\nIf it is an existing product press '2'\nYour choise:");
				scanf("%d", &choice);
				if (choice == 1)
				{
					printf("\n\n==>Enter the ID of the new product:");
					scanf("%d", &value);
					Insert(&NewRoot, value);
					SaveTree(NewRoot);
					fclose(fp1);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
					printf("The item was added to the store\n");
					fgetc(stdin);
					break;
				}
				else if (choice == 2)
				{
					int AmountToGet;
					printf("\n==>Enter the ID of the existing product:");
					scanf("%d", &value);
					tmp = search(&NewRoot, value);
					if (!tmp)
					{
						printf("Wrong Id\n");
						break;
					}
					printf("\n==>Enter the amount to get in store:");
					scanf("%d", &AmountToGet);
					GettItem(&NewRoot, tmp->Id, AmountToGet);
					SaveTree(NewRoot);
					fclose(fp1);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
					fgetc(stdin);
					break;
				}
				else
				{
					printf("wrong amount\n:");
					break;
				}
			}
			case 2:
			{
				Print_Tree_From_File();
				char part1[40] = "The store inventory";
				char part2[40] = "was shown to the user";
				PrintToLogFile_I(part1, part2);
				break;
			}
			case 3:
			{
				SetColor(34);
				printf("\n============> SEARCH MENU <============\n");
				ResetColor();
				SetColor(32);
				printf("1.SEARCH BY TYPE \n");
				printf("2.SEARCH BY COLOR \n");
				printf("3.SEARCH BY TYPE + COLOR \n");
				printf("4.SEARCH BY PRICE LESS THEN:## \n");
				printf("5.SEARCH BY PRICE OVER THEN:## \n");
				printf("6.SEARCH BY GENDER \n");
				printf("7.SEARCH BY DATE \n");
				printf("8.EXIT\n");
				printf("\nYOUR CHOISE IS: ");
				ResetColor();
				scanf("%d", &choice);
				printf("\n");
				switch (choice)
				{
				case 1:
				{
					fgetc(stdin);
					char ItemType[10];
					printf("Insert type for search:");
					int Sum = 0;
					gets(ItemType);
					Search_By_Type(&NewRoot, ItemType, &Sum);
					if (Sum == 0)
						printf("There is no item with this color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 2:
				{
					fgetc(stdin);
					char ItemColor[10];
					printf("Insert Color for search:");
					int Sum = 0;
					gets(ItemColor);
					Search_By_Color(&NewRoot, ItemColor, &Sum);
					if (Sum == 0)
						printf("There is no item with this color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 3:
				{
					fgetc(stdin);
					int Sum = 0;
					char ItemType[10];
					char ItemColor[10];
					printf("Insert Type for search:");
					gets(ItemType);
					printf("Insert Color for search:");
					gets(ItemColor);
					Search_By_Color_And_Type(&NewRoot, ItemType, ItemColor, &Sum);
					if (Sum == 0)
						printf("There is no item with this type and color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 4:
				{
					fgetc(stdin);
					int Sum = 0;
					double ItemPrice;
					printf("Insert max price:");
					scanf("%lf", &ItemPrice);
					Search_By_Price_Less(&NewRoot, ItemPrice, &Sum);
					if (Sum == 0)
						printf("There is no item with this type and color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 5:
				{
					fgetc(stdin);
					int Sum = 0;
					double ItemPrice;
					printf("Insert min price:");
					scanf("%lf", &ItemPrice);
					Search_By_Price_More(&NewRoot, ItemPrice, &Sum);
					if (Sum == 0)
						printf("There is no item with this type and color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 6:
				{
					fgetc(stdin);
					int Sum = 0;
					int Gender;
					printf("For products for man insert '1'\nFor products for woman insert '2'\nYour choise:");
					scanf("%d", &Gender);
					if (Gender == 1)
						Search_By_Gender_Man(&NewRoot, Gender, &Sum);
					if (Gender == 2)
						Search_By_Gender_Woman(&NewRoot, Gender, &Sum);
					if (Sum == 0)
						printf("There is no item with this type and color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 7:
				{
					int Sum = 0;
					int day = 10, month = 10, year = 10;
					Search_By_Date_Less(&NewRoot, day, month, year, &Sum);
					break;
				}
				case 8:
				{
					break;
				}
				}
				break;
				char part1[40] = "A search was made in";
				char part2[40] = "the store's inventory";
				PrintToLogFile_I(part1, part2);
			}
			case 4:
			{
				temp = Create_Customer();
				HeadOfCustomers = Add_Customer(HeadOfCustomers, temp);
				Write_To_File(HeadOfCustomers);
				break;
			}
			case 5:
			{
				Find_Customers_With_Name(HeadOfCustomers);
				char part1[40] = "A search was made in";
				char part2[40] = "the customers list";
				PrintToLogFile_I(part1, part2);
				break;
			}
			case 6:
			{
				Display_All_Customer(HeadOfCustomers);
				char part1[40] = "The customers list";
				char part2[40] = "was shown to the user";
				PrintToLogFile_I(part1, part2);
				break;
			}
			case 7:
			{
				exit(0);
			}
			}
		}
		else if (strcmp(level, level2) == 0)
		{
		SetColor(34);
		printf("\n============> MAIN MENU <============\n");
		printf("\n============>  LEVEL 2  <============\n");
		ResetColor();
		SetColor(35);
		printf("Choose your operation:\n\n");
		printf("1.ADD NEW ITEM\n");
		printf("2.DISPLAY ITEMS LIST \n");
		printf("3.UPDATE ITEM PROPERTIES \n");
		printf("4.SEARCH ITEM IN STORE \n");
		printf("5.SELL ITEM \n");
		printf("6.ADD NEW CUSTOMER \n");
		printf("7.DELETE CUSTOMER \n");
		printf("8.FIND CUSTOMER BY NAME \n");
		printf("9.DISPLAY CUSTOMERS LIST \n");
		printf("10.RETURN OF A PRODACT BY A CUSTOMER \n");
		SetColor(31); printf("11.EXIT \n"); ResetColor();
		printf("\nYOUR CHOISE IS: ");
		scanf("%d", &choice);
		printf("\n");
		switch (choice)
		{
			case 1:
			{
			printf("If its a new prodact press '1'\nIf it is an existing product press '2'\nYour choise:");
			scanf("%d", &choice);
			if (choice == 1)
			{
				printf("\n\n==>Enter the ID of the new product:");
				scanf("%d", &value);
				Insert(&NewRoot, value);
				SaveTree(NewRoot);
				fclose(fp1);
				DeleteZerosFromFile();
				int result = remove("My_Items.bin");
				if (result != 0)
					printf("Error deleting file: %s\n", strerror(errno));
				int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
				if (result2 != 0)
					printf("Error rename file: %s\n", strerror(errno));
				printf("The item was added to the store\n");
				fgetc(stdin);
				break;
			}
			else if (choice == 2)
			{
				int AmountToGet;
				printf("\n==>Enter the ID of the existing product:");
				scanf("%d", &value);
				tmp = search(&NewRoot, value);
				if (!tmp)
				{
					printf("Wrong Id\n");
					break;
				}
				printf("\n==>Enter the amount to get in store:");
				scanf("%d", &AmountToGet);
				GettItem(&NewRoot, tmp->Id, AmountToGet);
				SaveTree(NewRoot);
				fclose(fp1);
				DeleteZerosFromFile();
				int result = remove("My_Items.bin");
				if (result != 0)
					printf("Error deleting file: %s\n", strerror(errno));
				int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
				if (result2 != 0)
					printf("Error rename file: %s\n", strerror(errno));
				fgetc(stdin);
				break;
			}
			else
			{
				printf("wrong amount\n:");
				break;
			}
		}
			case 2:
			{
			Print_Tree_From_File();
			char part1[40] = "The store inventory";
			char part2[40] = "was shown to the user";
			PrintToLogFile_I(part1, part2);
			break;
		}
			case 3:
			{
			printf("\nInsert Id for Update:");
			scanf("%d", &choice);
			UpdateItemProperties(&NewRoot, choice);
			SaveTree(NewRoot);
			fclose(fp1);
			DeleteZerosFromFile();
			int result = remove("My_Items.bin");
			if (result != 0)
				printf("Error deleting file: %s\n", strerror(errno));
			int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
			if (result2 != 0)
				printf("Error rename file: %s\n", strerror(errno));
			fgetc(stdin);
			break;
		}
			case 4:
			{
			SetColor(34);
			printf("\n============> SEARCH MENU <============\n");
			ResetColor();
			SetColor(32);
			printf("1.SEARCH BY TYPE \n");
			printf("2.SEARCH BY COLOR \n");
			printf("3.SEARCH BY TYPE + COLOR \n");
			printf("4.SEARCH BY PRICE LESS THEN:## \n");
			printf("5.SEARCH BY PRICE OVER THEN:## \n");
			printf("6.SEARCH BY GENDER \n");
			printf("7.SEARCH BY DATE \n");
			printf("8.EXIT\n");
			printf("\nYOUR CHOISE IS: ");
			ResetColor();
			scanf("%d", &choice);
			printf("\n");
			switch (choice)
			{
			case 1:
			{
				fgetc(stdin);
				char ItemType[10];
				printf("Insert type for search:");
				int Sum = 0;
				gets(ItemType);
				Search_By_Type(&NewRoot, ItemType, &Sum);
				if (Sum == 0)
					printf("There is no item with this color in the store\n");
				else
				{
					printf("If you want to update any item press #1, else press #2:");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("Insert item ID to update:");
						scanf("%d", &choice);
						UpdateItemProperties(&NewRoot, choice);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
					}
				}
				fgetc(stdin);
				break;
			}
			case 2:
			{
				fgetc(stdin);
				char ItemColor[10];
				printf("Insert Color for search:");
				int Sum = 0;
				gets(ItemColor);
				Search_By_Color(&NewRoot, ItemColor, &Sum);
				if (Sum == 0)
					printf("There is no item with this color in the store\n");
				else
				{
					printf("If you want to update any item press #1, else press #2:");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("Insert item ID to update:");
						scanf("%d", &choice);
						UpdateItemProperties(&NewRoot, choice);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
					}
				}
				fgetc(stdin);
				break;
			}
			case 3:
			{
				fgetc(stdin);
				int Sum = 0;
				char ItemType[10];
				char ItemColor[10];
				printf("Insert Type for search:");
				gets(ItemType);
				printf("Insert Color for search:");
				gets(ItemColor);
				Search_By_Color_And_Type(&NewRoot, ItemType, ItemColor, &Sum);
				if (Sum == 0)
					printf("There is no item with this type and color in the store\n");
				else
				{
					printf("If you want to update any item press #1, else press #2:");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("Insert item ID to update:");
						scanf("%d", &choice);
						UpdateItemProperties(&NewRoot, choice);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
					}
				}
				fgetc(stdin);
				break;
			}
			case 4:
			{
				fgetc(stdin);
				int Sum = 0;
				double ItemPrice;
				printf("Insert max price:");
				scanf("%lf", &ItemPrice);
				Search_By_Price_Less(&NewRoot, ItemPrice, &Sum);
				if (Sum == 0)
					printf("There is no item with this type and color in the store\n");
				else
				{
					printf("If you want to update any item press #1, else press #2:");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("Insert item ID to update:");
						scanf("%d", &choice);
						UpdateItemProperties(&NewRoot, choice);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
					}
				}
				fgetc(stdin);
				break;
			}
			case 5:
			{
				fgetc(stdin);
				int Sum = 0;
				double ItemPrice;
				printf("Insert min price:");
				scanf("%lf", &ItemPrice);
				Search_By_Price_More(&NewRoot, ItemPrice, &Sum);
				if (Sum == 0)
					printf("There is no item with this type and color in the store\n");
				else
				{
					printf("If you want to update any item press #1, else press #2:");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("Insert item ID to update:");
						scanf("%d", &choice);
						UpdateItemProperties(&NewRoot, choice);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
					}
				}
				fgetc(stdin);
				break;
			}
			case 6:
			{
				fgetc(stdin);
				int Sum = 0;
				int Gender;
				printf("For products for man insert '1'\nFor products for woman insert '2'\nYour choise:");
				scanf("%d", &Gender);
				if (Gender == 1)
					Search_By_Gender_Man(&NewRoot, Gender, &Sum);
				if (Gender == 2)
					Search_By_Gender_Woman(&NewRoot, Gender, &Sum);
				if (Sum == 0)
					printf("There is no item with this type and color in the store\n");
				else
				{
					printf("If you want to update any item press #1, else press #2:");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("Insert item ID to update:");
						scanf("%d", &choice);
						UpdateItemProperties(&NewRoot, choice);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
					}
				}
				fgetc(stdin);
				break;
			}
			case 7:
			{
				int Sum = 0;
				int day = 10, month = 10, year = 10;
				Search_By_Date_Less(&NewRoot, day, month, year, &Sum);
				break;
			}
			case 8:
			{
				break;
			}
			}
			break;
			char part1[40] = "A search was made in";
			char part2[40] = "the store's inventory";
			PrintToLogFile_I(part1, part2);
		}
			case 5:
			{
			int AmountToSell = 1;
			printf("Insert Id for sell:");
			scanf("%d", &choice);
			tmp = search(&NewRoot, choice);
			if (!tmp)
			{
				printf("The item is out of stock\n");
				break;
			}
			//The item is out of stock
			char name[15];
			fgetc(stdin);
			printf("Enter name of the customer:");
			gets(name);
			int choice2 = Find_Customers(HeadOfCustomers, name);
			if (choice2 == 0)
			{
				printf("\n\nCustomer not exist\n");
				temp = Create_Customer();
				HeadOfCustomers = Add_Customer(HeadOfCustomers, temp);
				Write_To_File(HeadOfCustomers);
				tmp = search(&NewRoot, choice);
				if ((tmp->ItemAmount - AmountToSell) < 0)
				{
					printf("There are not enough items of this type\n:");
					break;
				}
				else if (tmp->ItemAmount > AmountToSell)
				{
					SellItem(&NewRoot, tmp->Id, AmountToSell);
					SaveTree(NewRoot);
					fclose(fp1);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
					fgetc(stdin);
					printf("Item sold\n");
					char part1[40] = "The following item Id:";
					char part2[40] = "has been sold to:";
					PrintToLogFile_2(part1, choice, part2, name);
					break;
				}
				else if ((tmp->ItemAmount - AmountToSell) == 0)
				{
					int result4 = DeleteNode(&NewRoot, choice);
					if (result4 == 1)
					{
						printf("The Item deleted\n");
						char part1[40] = "The following item Id";
						char part2[40] = "has been deleted from store:";
						PrintToLogFile(part1, part2, choice);
					}
					SaveTree(NewRoot);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
					fgetc(stdin);
					printf("Item sold\n");
					char part1[40] = "The following item Id:";
					char part2[40] = "has been sold to:";
					PrintToLogFile_2(part1, choice, part2, name);
					break;
				}
			}
			//àéï ì÷åç
			else if (choice2 == 1)
			{
				Find_Customers2(HeadOfCustomers, name, choice);
				Write_To_File(HeadOfCustomers);
				tmp = search(&NewRoot, choice);
				if ((tmp->ItemAmount - AmountToSell) < 0)
				{
					printf("There are not enough items of this type\n:");
					break;
				}
				else if (tmp->ItemAmount > AmountToSell)
				{
					SellItem(&NewRoot, tmp->Id, AmountToSell);
					SaveTree(NewRoot);
					fclose(fp1);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
					fgetc(stdin);
					printf("Item sold\n");
					char part1[40] = "The following item Id:";
					char part2[40] = "has been sold to:";
					PrintToLogFile_2(part1, choice, part2, name);
					break;
				}
				else if ((tmp->ItemAmount - AmountToSell) == 0)
				{
					int result4 = DeleteNode(&NewRoot, choice);
					if (result4 == 1)
					{
						printf("The Item deleted\n");
						char part1[40] = "The following item Id";
						char part2[40] = "has been deleted from store:";
						PrintToLogFile(part1, part2, choice);
					}
					SaveTree(NewRoot);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
					fgetc(stdin);
					printf("Item sold\n");
					char part1[40] = "The following item Id:";
					char part2[40] = "has been sold to:";
					PrintToLogFile_2(part1, choice, part2, name);
					break;
				}
				break;
			}
			//éù ì÷åç
		}
			case 6:
			{
			temp = Create_Customer();
			HeadOfCustomers = Add_Customer(HeadOfCustomers, temp);
			Write_To_File(HeadOfCustomers);
			break;
		}
			case 7:
			{
			Remove_Customer_With_Name(&HeadOfCustomers);
			Write_To_File(HeadOfCustomers);
			break;
		}
			case 8:
			{
			Find_Customers_With_Name(HeadOfCustomers);
			char part1[40] = "A search was made in";
			char part2[40] = "the customers list";
			PrintToLogFile_I(part1, part2);
			break;
		}
			case 9:
			{
			Display_All_Customer(HeadOfCustomers);
			char part1[40] = "The customers list";
			char part2[40] = "was shown to the user";
			PrintToLogFile_I(part1, part2);
			break;
		}
			case 10:
			{
			char name[15];
			fgetc(stdin);
			printf("Enter name of the customer:");
			gets(name);
			int choice2 = Find_Customers(HeadOfCustomers, name);
			if (choice2 == 0)
			{
				printf("\n\Customer not exist\n");
				break;
			}
			else if (choice2 == 1)
			{
				printf("Insert Id for return:");
				scanf("%d", &choice);
				int result10 = ReturnItemForCustomer(HeadOfCustomers, name, choice);
				if (result10 == 1)
				{
					Write_To_File(HeadOfCustomers);
					tmp = search(&NewRoot, choice);
					GettItem(&NewRoot, tmp->Id, 1);
					SaveTree(NewRoot);
					fclose(fp1);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
				}
				break;
			}
		}
			case 11:
			{
			exit(0);
		}
			}
		}
		else if (strcmp(level, level3)==0)
		{
			SetColor(34);
			printf("\n============> MAIN MENU <============\n");
			printf("\n============>  LEVEL 3  <============\n");
			ResetColor();
			SetColor(35);
			printf("Choose your operation:\n\n");
			printf("1.ADD NEW ITEM\n");
			printf("2.DISPLAY ITEMS LIST \n");
			printf("3.UPDATE ITEM PROPERTIES \n");
			printf("4.SEARCH ITEM IN STORE \n");
			printf("5.SELL ITEM \n");
			printf("6.DISPLAY EMPLOYEES \n");
			printf("7.ADD NEW EMPLOYEES \n");
			printf("8.ADD NEW CUSTOMER \n");
			printf("9.DELETE CUSTOMER \n");
			printf("10.FIND CUSTOMER BY NAME \n");
			printf("11.DISPLAY CUSTOMERS LIST \n");
			printf("12.RETURN OF A PRODACT BY A CUSTOMER \n");
			SetColor(31); printf("13.EXIT \n"); ResetColor();
			printf("\nYOUR CHOISE IS: ");
			scanf("%d", &choice);
			printf("\n");
			switch (choice)
			{
			case 1:
			{
				printf("If its a new prodact press '1'\nIf it is an existing product press '2'\nYour choise:");
				scanf("%d", &choice);
				if (choice == 1)
				{
					printf("\n\n==>Enter the ID of the new product:");
					scanf("%d", &value);
					Insert(&NewRoot, value);
					SaveTree(NewRoot);
					fclose(fp1);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
					printf("The item was added to the store\n");
					fgetc(stdin);
					break;
				}
				else if (choice == 2)
				{
					int AmountToGet;
					printf("\n==>Enter the ID of the existing product:");
					scanf("%d", &value);
					tmp = search(&NewRoot, value);
					if (!tmp)
					{
						printf("Wrong Id\n");
						break;
					}
					printf("\n==>Enter the amount to get in store:");
					scanf("%d", &AmountToGet);
					GettItem(&NewRoot, tmp->Id, AmountToGet);
					SaveTree(NewRoot);
					fclose(fp1);
					DeleteZerosFromFile();
					int result = remove("My_Items.bin");
					if (result != 0)
						printf("Error deleting file: %s\n", strerror(errno));
					int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
					if (result2 != 0)
						printf("Error rename file: %s\n", strerror(errno));
					fgetc(stdin);
					break;
				}
				else
				{
					printf("wrong amount\n:");
					break;
				}
			}
			case 2:
			{
				Print_Tree_From_File();
				char part1[40] = "The store inventory";
				char part2[40] = "was shown to the user";
				PrintToLogFile_I(part1, part2);
				break;
			}
			case 3:
			{
				printf("\nInsert Id for Update:");
				scanf("%d", &choice);
				UpdateItemProperties(&NewRoot, choice);
				SaveTree(NewRoot);
				fclose(fp1);
				DeleteZerosFromFile();
				int result = remove("My_Items.bin");
				if (result != 0)
					printf("Error deleting file: %s\n", strerror(errno));
				int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
				if (result2 != 0)
					printf("Error rename file: %s\n", strerror(errno));
				fgetc(stdin);
				break;
			}
			case 4:
			{
				SetColor(34);
				printf("\n============> SEARCH MENU <============\n");
				ResetColor();
				SetColor(32);
				printf("1.SEARCH BY TYPE \n");
				printf("2.SEARCH BY COLOR \n");
				printf("3.SEARCH BY TYPE + COLOR \n");
				printf("4.SEARCH BY PRICE LESS THEN:## \n");
				printf("5.SEARCH BY PRICE OVER THEN:## \n");
				printf("6.SEARCH BY GENDER \n");
				printf("7.SEARCH BY DATE \n");
				printf("8.EXIT\n");
				printf("\nYOUR CHOISE IS: ");
				ResetColor();
				scanf("%d", &choice);
				printf("\n");
				switch (choice)
				{
				case 1:
				{
					fgetc(stdin);
					char ItemType[10];
					printf("Insert type for search:");
					int Sum = 0;
					gets(ItemType);
					Search_By_Type(&NewRoot, ItemType, &Sum);
					if (Sum == 0)
						printf("There is no item with this color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 2:
				{
					fgetc(stdin);
					char ItemColor[10];
					printf("Insert Color for search:");
					int Sum = 0;
					gets(ItemColor);
					Search_By_Color(&NewRoot, ItemColor, &Sum);
					if (Sum == 0)
						printf("There is no item with this color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 3:
				{
					fgetc(stdin);
					int Sum = 0;
					char ItemType[10];
					char ItemColor[10];
					printf("Insert Type for search:");
					gets(ItemType);
					printf("Insert Color for search:");
					gets(ItemColor);
					Search_By_Color_And_Type(&NewRoot, ItemType, ItemColor, &Sum);
					if (Sum == 0)
						printf("There is no item with this type and color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 4:
				{
					fgetc(stdin);
					int Sum = 0;
					double ItemPrice;
					printf("Insert max price:");
					scanf("%lf", &ItemPrice);
					Search_By_Price_Less(&NewRoot, ItemPrice, &Sum);
					if (Sum == 0)
						printf("There is no item with this type and color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 5:
				{
					fgetc(stdin);
					int Sum = 0;
					double ItemPrice;
					printf("Insert min price:");
					scanf("%lf", &ItemPrice);
					Search_By_Price_More(&NewRoot, ItemPrice, &Sum);
					if (Sum == 0)
						printf("There is no item with this type and color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}	
				case 6:
				{
					fgetc(stdin);
					int Sum = 0;
					int Gender;
					printf("For products for man insert '1'\nFor products for woman insert '2'\nYour choise:");
					scanf("%d", &Gender);
					if (Gender == 1)
						Search_By_Gender_Man(&NewRoot, Gender, &Sum);
					if (Gender == 2)
						Search_By_Gender_Woman(&NewRoot, Gender, &Sum);
					if (Sum == 0)
						printf("There is no item with this type and color in the store\n");
					else
					{
						printf("If you want to update any item press #1, else press #2:");
						scanf("%d", &choice);
						if (choice == 1)
						{
							printf("Insert item ID to update:");
							scanf("%d", &choice);
							UpdateItemProperties(&NewRoot, choice);
							SaveTree(NewRoot);
							fclose(fp1);
							DeleteZerosFromFile();
							int result = remove("My_Items.bin");
							if (result != 0)
								printf("Error deleting file: %s\n", strerror(errno));
							int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
							if (result2 != 0)
								printf("Error rename file: %s\n", strerror(errno));
						}
					}
					fgetc(stdin);
					break;
				}
				case 7:
				{
					int Sum = 0;
					int day =10, month =10, year =10;
					Search_By_Date_Less(&NewRoot,day, month, year, &Sum);
					break;
				}
				case 8:
				{
					break;
				}
				}
				break;
				char part1[40] = "A search was made in";
				char part2[40] = "the store's inventory";
				PrintToLogFile_I(part1, part2);
			}
			case 5:
			{
				int AmountToSell = 1;
				printf("Insert Id for sell:");
				scanf("%d", &choice);
				tmp = search(&NewRoot, choice);
				if (!tmp)
				{
					printf("The item is out of stock\n");
					break;
				}
				//The item is out of stock
				char name[15];
				fgetc(stdin);
				printf("Enter name of the customer:");
				gets(name);
				int choice2 = Find_Customers(HeadOfCustomers, name);
				if (choice2 == 0)
				{
					printf("\n\nCustomer not exist\n");
					temp = Create_Customer();
					HeadOfCustomers = Add_Customer(HeadOfCustomers, temp);
					Write_To_File(HeadOfCustomers);
					tmp = search(&NewRoot, choice);
					if ((tmp->ItemAmount - AmountToSell) < 0)
					{
						printf("There are not enough items of this type\n:");
						break;
					}
					else if (tmp->ItemAmount > AmountToSell)
					{
						SellItem(&NewRoot, tmp->Id, AmountToSell);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
						fgetc(stdin);
						printf("Item sold\n");
						char part1[40] = "The following item Id:";
						char part2[40] = "has been sold to:";
						PrintToLogFile_2(part1, choice, part2, name);
						break;
					}
					else if ((tmp->ItemAmount - AmountToSell) == 0)
					{
						int result4 = DeleteNode(&NewRoot, choice);
						if (result4 == 1)
						{
							printf("The Item deleted\n");
							char part1[40] = "The following item Id";
							char part2[40] = "has been deleted from store:";
							PrintToLogFile(part1, part2, choice);
						}
						SaveTree(NewRoot);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
						fgetc(stdin);
						printf("Item sold\n");
						char part1[40] = "The following item Id:";
						char part2[40] = "has been sold to:";
						PrintToLogFile_2(part1, choice, part2, name);
						break;
					}
				}
				//àéï ì÷åç
				else if (choice2 == 1)
				{
					Find_Customers2(HeadOfCustomers, name, choice);
					Write_To_File(HeadOfCustomers);
					tmp = search(&NewRoot, choice);
					if ((tmp->ItemAmount - AmountToSell) < 0)
					{
						printf("There are not enough items of this type\n:");
						break;
					}
					else if (tmp->ItemAmount > AmountToSell)
					{
						SellItem(&NewRoot, tmp->Id, AmountToSell);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
						fgetc(stdin);
						printf("Item sold\n");
						char part1[40] = "The following item Id:";
						char part2[40] = "has been sold to:";
						PrintToLogFile_2(part1, choice, part2, name);
						break;
					}
					else if ((tmp->ItemAmount - AmountToSell) == 0)
					{
						int result4 = DeleteNode(&NewRoot, choice);
						if (result4 == 1)
						{
							printf("The Item deleted\n");
							char part1[40] = "The following item Id";
							char part2[40] = "has been deleted from store:";
							PrintToLogFile(part1, part2, choice);
						}
						SaveTree(NewRoot);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
						fgetc(stdin);
						printf("Item sold\n");
						char part1[40] = "The following item Id:";
						char part2[40] = "has been sold to:";
						PrintToLogFile_2(part1, choice, part2, name);
						break;
					}
					break;
				}
				//éù ì÷åç
			}
			case 6:
			{
				PrintEployee(employees);
				printf("\n\n");
				char part1[40] = "The employees list";
				char part2[40] = "was shown to the user";
				PrintToLogFile_I(part1, part2);
				break;
			}
			case 7:
			{
				FILE* fp3 = fopen("My_Employees.bin", "rb");
				fseek(fp3, 0, SEEK_END);
				int fileSize = ftell(fp3);
				int numEmExist = fileSize / sizeof(Employee);
				int numEmployees;
				printf("Enter number of employees: ");
				scanf("%d", &numEmployees);
				Employee* employees = (Employee*)malloc((numEmployees+ numEmExist) * sizeof(Employee));
				InsertNewEmployees(employees, numEmployees, numEmExist);
				WriteEmployeesToFile(employees, numEmployees + numEmExist);
				break;
			}
			case 8:
			{
				temp = Create_Customer();
				HeadOfCustomers = Add_Customer(HeadOfCustomers, temp);
				Write_To_File(HeadOfCustomers);
				break;
			}
			case 9:
			{
				Remove_Customer_With_Name(&HeadOfCustomers);
				Write_To_File(HeadOfCustomers);
				break;
			}
			case 10:
			{
				Find_Customers_With_Name(HeadOfCustomers);
				char part1[40] = "A search was made in";
				char part2[40] = "the customers list";
				PrintToLogFile_I(part1, part2);
				break;
			}
			case 11:
			{
				Display_All_Customer(HeadOfCustomers);
				char part1[40] = "The customers list";
				char part2[40] = "was shown to the user";
				PrintToLogFile_I(part1, part2);
				break;
			}
			case 12:
			{
				char name[15];
				fgetc(stdin);
				printf("Enter name of the customer:");
				gets(name);
				int choice2 = Find_Customers(HeadOfCustomers, name);
				if (choice2 == 0)
				{
					printf("\n\Customer not exist\n");
					break;
				}
				else if (choice2 == 1)
				{
					printf("Insert Id for return:");
					scanf("%d", &choice);
					int result10 = ReturnItemForCustomer(HeadOfCustomers, name, choice);
					if (result10 == 1)
					{
						Write_To_File(HeadOfCustomers);
						tmp = search(&NewRoot, choice);
						GettItem(&NewRoot, tmp->Id, 1);
						SaveTree(NewRoot);
						fclose(fp1);
						DeleteZerosFromFile();
						int result = remove("My_Items.bin");
						if (result != 0)
							printf("Error deleting file: %s\n", strerror(errno));
						int result2 = rename("Temp_My_Items.bin", "My_Items.bin");
						if (result2 != 0)
							printf("Error rename file: %s\n", strerror(errno));
					}
					break;
				}
			}
		
			case 13:
			{
				exit(0);
			}
			}
		}
		fgetc(stdin);
		SetColor(32);
		printf("PRESS ANY KEY TO MAIN MENU\n");
		ResetColor();
		SetColor(31);
		printf("PRINT 'X' TO EXIT");
		ResetColor();
	} while (getch() != 'x');
}

time_t Date_Of_Joining()
{
	struct tm time_info;
	char date_string[20];
	printf("\nEnter the date of joining (DD-MM-YYYY): ");
	scanf("%s", date_string);
	sscanf(date_string, "%d-%d-%d", &time_info.tm_mday, &time_info.tm_mon, &time_info.tm_year);
	time_info.tm_year -= 1900;
	time_info.tm_mon--;
	time_info.tm_hour = 0;
	time_info.tm_min = 0;
	time_info.tm_sec = 0;

	time_t date_of_joining = mktime(&time_info);

	return date_of_joining;
}
time_t Date_Of_Purchase()
{
	struct tm time_info;
	char date_string[20];
	printf("\nEnter the date of purchase (DD-MM-YYYY): ");
	scanf("%s", date_string);
	sscanf(date_string, "%d-%d-%d", &time_info.tm_mday, &time_info.tm_mon, &time_info.tm_year);
	time_info.tm_year -= 1900;
	time_info.tm_mon--;
	time_info.tm_hour = 0;
	time_info.tm_min = 0;
	time_info.tm_sec = 0;

	time_t date_of_joining = mktime(&time_info);

	return date_of_joining;
}
Customers* Auto_Customer(time_t DateOfJoined, char Name[], int TotalItems, int Item_ID[], time_t DateOfPurchase1, time_t DateOfPurchase2, time_t DateOfPurchase3)
{
	Customers* new_customer = (Customers*)malloc(sizeof(Customers));

	int i = 0;
	strncpy(new_customer->Name, Name, sizeof(new_customer->Name));
	new_customer->TotalItems = TotalItems;
	new_customer->DateOfPurchase1 = DateOfPurchase1;
	new_customer->DateOfPurchase2 = DateOfPurchase2;
	new_customer->DateOfPurchase3 = DateOfPurchase3;
	new_customer->Item_ID[0] = Item_ID[0];
	new_customer->Item_ID[1] = Item_ID[1];
	new_customer->Item_ID[2] = Item_ID[2];
	new_customer->DateOfJoined = DateOfJoined;

	new_customer->next = NULL;

	return new_customer;

}
Customers* Create_List_Of_Customer_From_File()
{
	Customers c;
	Customers* head = NULL;
	Customers* current = NULL;
	FILE* fp2 = fopen("My_Customers.bin", "rb+");

	while (fread(&c, sizeof(Customers), 1, fp2))
	{
		if (head == NULL)
		{
			head = Auto_Customer(c.DateOfJoined, c.Name, c.TotalItems, c.Item_ID, c.DateOfPurchase1, c.DateOfPurchase2, c.DateOfPurchase3);
			current = head;
		}
		else {
			current->next = Auto_Customer(c.DateOfJoined, c.Name, c.TotalItems, c.Item_ID, c.DateOfPurchase1, c.DateOfPurchase2, c.DateOfPurchase3);
			current = current->next;
		}
	}

	fclose(fp2);
	return head;
}
Customers* Create_Customer()
{
	Customers* new_customer = (Customers*)malloc(sizeof(Customers));
	FILE* fp2 = fopen("My_Customers.bin", "rb");
	int i = 0;
	fgetc(stdin);
	if (fp2 == NULL)
	{
		printf("\nEnter the name of the first customer:");
		gets(new_customer->Name);
		char part2[40] = "has been added to the customer list";
		PrintToLogFile_I(new_customer->Name, part2);
	}
	else
	{
		printf("\nEnter the name of the customer:");
		gets(new_customer->Name);
		char part2[40] = "has been added to the customer list";
		PrintToLogFile_I(new_customer->Name, part2);
	}
	printf("\nHow many item he would like to buy?");
	scanf("%d", &new_customer->TotalItems);
	if (new_customer->TotalItems == 1)
	{
		printf("\nEnter the id of item ?");
		scanf("%d", &new_customer->Item_ID[0]);
		time(&new_customer->DateOfPurchase1);
		new_customer->DateOfPurchase2 = NULL;
		new_customer->DateOfPurchase3 = NULL;
	}
	else
	{
		while (i != new_customer->TotalItems)
		{
			printf("\nWhat is the id of the #%d items ? :", i + 1);
			scanf("%d", &new_customer->Item_ID[i]);
			switch (i)
			{
			case 0:
				time(&new_customer->DateOfPurchase1);
				break;
			case 1:
				time(&new_customer->DateOfPurchase2);
				break;
			case 2:
				time(&new_customer->DateOfPurchase3);
				break;
			default:
				break;
			}
			i++;
		}
	}
	time(&new_customer->DateOfJoined);
	new_customer->next = NULL;
	return new_customer;

}
Customers* Add_Customer(Customers* head_c, Customers* new_customer)
{
	if (head_c == NULL)
	{
		return new_customer;
	}
	if (new_customer->DateOfJoined < head_c->DateOfJoined)
	{
		new_customer->next = head_c;
		return new_customer;
	}

	Customers* current = head_c;
	while (current->next != NULL)
	{
		if (new_customer->DateOfJoined < current->next->DateOfJoined)
		{
			new_customer->next = current->next;
			current->next = new_customer;
			return head_c;
		}
		current = current->next;
	}
	current->next = new_customer;
	return head_c;
}
void Display_A_Customer_From_File()
{
	Customers c;
	int x, i = 0;
	FILE* fp2 = fopen("My_Customers.bin", "rb");

	while (fread(&c, sizeof(Customers), 1, fp2))
	{
		printf("\nName of the customer is: %s", c.Name);

		if (c.TotalItems == 1)
		{
			printf("\nThe customer bought 1 item ");
			printf("\nThe id of the item is : %d\n", c.Item_ID[0]);
			printf("The Date Of Purchase is : %s", ctime(&c.DateOfPurchase1));
		}
		else
		{
			printf("\nThe customer bought %d items\n", c.TotalItems);

			while (i != c.TotalItems)
			{
				switch (i)
				{
				case 0:
					printf("The id of the #%d items is : %d\n", i + 1, c.Item_ID[i]);
					printf("The Date Of Purchase is : %s", ctime(&c.DateOfPurchase1));
					break;
				case 1:
					printf("The id of the #%d items is : %d\n", i + 1, c.Item_ID[i]);
					printf("The Date Of Purchase is : %s", ctime(&c.DateOfPurchase2));
					break;
				case 2:
					printf("The id of the #%d items is : %d\n", i + 1, c.Item_ID[i]);
					printf("The Date Of Purchase is : %s", ctime(&c.DateOfPurchase3));
					break;
				default:
					break;
				}

				i++;
			}
		}

		printf("The Date Of Joining : %s", ctime(&c.DateOfJoined));
	}

}
void Free_List_Of_Customer(Customers* head_c)
{
	Customers* head_customer = NULL;
	head_customer = head_c;
	while (head_customer != NULL)
	{
		head_c = head_c->next;
		free(head_customer);
		head_customer = head_c;
	}
}
void Write_To_File(Customers* head_c)
{
	Customers* temp = head_c;
	FILE* fp2 = fopen("My_Customers.bin", "wb");
	while (temp != NULL)
	{
		fwrite(temp, sizeof(Customers), 1, fp2);
		temp = temp->next;
	}
	fclose(fp2);
}
void Display_A_Customer(Customers* head_c)
{
	int i = 0;
	printf("\nName of the customer is: %s", head_c->Name);

	if (head_c->TotalItems == 1)
	{
		printf("\nThe customer bought 1 item ");
		printf("\nThe id of the item is : %d\n", head_c->Item_ID[0]);
		printf("The Date Of Purchase is : %s", ctime(&head_c->DateOfPurchase1));
	}
	else
	{
		printf("\nThe customer bought %d items\n", head_c->TotalItems);

		while (i != head_c->TotalItems)
		{
			switch (i)
			{
			case 0:
				printf("The id of the #%d items is : %d\n", i + 1, head_c->Item_ID[i]);
				printf("The Date Of Purchase is : %s", ctime(&head_c->DateOfPurchase1));
				break;
			case 1:
				printf("The id of the #%d items is : %d\n", i + 1, head_c->Item_ID[i]);
				printf("The Date Of Purchase is : %s", ctime(&head_c->DateOfPurchase2));
				break;
			case 2:
				printf("The id of the #%d items is : %d\n", i + 1, head_c->Item_ID[i]);
				printf("The Date Of Purchase is : %s", ctime(&head_c->DateOfPurchase3));
				break;
			default:
				break;
			}

			i++;
		}
	}
	printf("The Date Of Joining : %s", ctime(&head_c->DateOfJoined));
}
void Display_All_Customer(Customers* head_c)
{
	Customers* phc = head_c;
	if (phc == NULL)
		printf("There are no customers\n");
	else
	{
		while (phc != NULL)
		{
			Display_A_Customer(phc);
			phc = phc->next;
		}
	}
}
void Find_Customers_With_Name(Customers* head_c)
{
	char name[15];
	int x = 0;
	fgetc(stdin);
	printf("\n\nWhat is the name of the customer? :");
	gets(name);
	Customers* current_customer = head_c;

	while (current_customer != NULL)
	{
		if (strcmp(name, current_customer->Name) == 0)
		{
			printf("\nThe customer what you're looking for do exists\n");
			printf("\nWould you like to see his deatils ? : \n");
			printf("\nEnter '1' for Yes :");
			scanf("%d", &x);
			if (x == 1)
			{
				Display_A_Customer(current_customer);
				return;
			}
			else
				return;
		}
		current_customer = current_customer->next;
	}
	printf("\nThe customer what you're looking for do not exists\n");
}
int Find_Customers(Customers* head_c, char* name)
{
	Customers* current_customer = head_c;

	while (current_customer != NULL)
	{
		if (strcmp(name, current_customer->Name) == 0)
			return 1;
		current_customer = current_customer->next;
	}
	return 0;
}
void UpdateCustomer(Customers* customer, int Id) 
{
	if (customer->TotalItems == 3) {
		printf("The customer has reached the maximum number of items");
	}
	else {
		customer->TotalItems++;
		customer->Item_ID[customer->TotalItems - 1] = Id;
		switch (customer->TotalItems)
		{
		case 1:
			time(&customer->DateOfPurchase1);
			break;
		case 2:
			time(&customer->DateOfPurchase2);
			break;
		case 3:
			time(&customer->DateOfPurchase3);
			break;
		}
	}
}
void UpdateCustomer3(Customers* customer, int Id)
{
	time_t current_time;
	time(&current_time);
	int i;
	for (i = 0; i < customer->TotalItems; i++) {
		if (customer->Item_ID[i] == Id) {
			time_t date_of_purchase;
			if (i == 0)
				date_of_purchase = customer->DateOfPurchase1;
			else if (i == 1)
				date_of_purchase = customer->DateOfPurchase2;
			else if (i == 2)
				date_of_purchase = customer->DateOfPurchase3;
			if ((current_time - date_of_purchase) <= 14 * 24 * 60 * 60)
			{
				customer->TotalItems--;
				customer->Item_ID[i] = 0;
				if (i == 0)
					customer->DateOfPurchase1 = 0;
				else if (i == 1)
					customer->DateOfPurchase2 = 0;
				else if (i == 2)
					customer->DateOfPurchase3 = 0;
				printf("Item returned successfully\n");
			}
			else {
				printf("Item return not allowed, it's passed 14 days from the date of purchase.");
			}
			break;
		}
	}
}
void Find_Customers2(Customers* head_c, char* name, int Id) {
	Customers* current_customer = head_c;
	while (current_customer != NULL) {
		if (strcmp(name, current_customer->Name) == 0)
		{
			UpdateCustomer(current_customer, Id);
			break;
		}
		current_customer = current_customer->next;
	}
}
void Find_Customers3(Customers* head_c, char* name, int Id) {
	Customers* current_customer = head_c;
	while (current_customer != NULL) {
		if (strcmp(name, current_customer->Name) == 0)
		{
			UpdateCustomer3(current_customer, Id);
			break;
		}
		current_customer = current_customer->next;
	}
}
Customers* Find_Customers4(Customers* head_c, char* name)
{
	Customers* current_customer = head_c;
	while (current_customer != NULL) {
		if (strcmp(name, current_customer->Name) == 0)
		{
			return current_customer;
		}
		current_customer = current_customer->next;
	}
	return NULL;
}
void Sell_Item(Customers* head_c)
{
	char name[15];
	int x = 0, item = 0, i = 0;
	fgetc(stdin);
	printf("\n\nWhat is the name of the customer what you're looking for ? :");
	gets(name);
	printf("\n\nWhat is the id of the product ? :");
	scanf("%d", &item);
	Customers* current_customer = head_c;
	while (current_customer != NULL)
	{
		if (strcmp(name, current_customer->Name) == 0)
		{
			for (; i < current_customer->TotalItems; i++)
			{
				if (item == current_customer->Item_ID[i])
				{
					current_customer->TotalItems--;

				}
				else
					printf("\nThe customer didn't buy this item \n");
			}
		}
		current_customer = current_customer->next;
	}
	printf("\nThe customer what you're looking for do not exists\n");
}
void Buy_Item(Customers* head_c)
{
	char name[15];
	int x = 0, item = 0, i = 0;
	fgetc(stdin);
	printf("\n\nWhat is the name of the customer what you're looking for ? :");
	gets(name);
	printf("\n\nWhat is the id of the product ? :");
	scanf("%d", &item);
	Customers* current_customer = head_c;

	while (current_customer != NULL)
	{
		if (strcmp(name, current_customer->Name) == 0)
		{
			for (; i < current_customer->TotalItems; i++)
			{
				if (item == current_customer->Item_ID[i])
				{
					current_customer->TotalItems++;

				}
				else
					printf("\nThe customer didn't buy this item \n");
			}
		}
		current_customer = current_customer->next;
	}
	printf("\nThe customer what you're looking for do not exists\n");
}
void Remove_Customer_With_Name(Customers** head_c)
{
	char name[15];
	fgetc(stdin);
	printf("\n\nWhat is the name of the customer what you would like to remove ? :");
	gets(name);
	Customers* current_customer = *head_c;
	Customers* prev_customer = NULL;


	if (current_customer != NULL && strcmp(current_customer->Name, name) == 0)
	{
		*head_c = current_customer->next;
		free(current_customer);
		printf("\nCustomer was found and deleted !");
		return;
	}

	while (current_customer != NULL && strcmp(current_customer->Name, name) != 0)
	{
		prev_customer = current_customer;
		current_customer = current_customer->next;
	}

	if (current_customer == NULL)
	{
		printf("\nCustomer wasn't found\n");
		return;
	}
	prev_customer->next = current_customer->next;
	printf("\nCustomer was found and deleted !");
	free(current_customer);
}
int ReturnItem(Customers* customer, int Id) {
	time_t current_time;
	time(&current_time);
	int i;
	for (i = 0; i < customer->TotalItems; i++) {
		if (customer->Item_ID[i] == Id) {
			time_t date_of_purchase;
			if (i == 0)
				date_of_purchase = customer->DateOfPurchase1;
			else if (i == 1)
				date_of_purchase = customer->DateOfPurchase2;
			else if (i == 2)
				date_of_purchase = customer->DateOfPurchase3;
			if ((current_time - date_of_purchase) <= 14 * 24 * 60 * 60) {
				customer->TotalItems--;
				int j;
				for (j = i; j < customer->TotalItems; j++) {
					customer->Item_ID[j] = customer->Item_ID[j + 1];
					if (j == 0)
						customer->DateOfPurchase1 = customer->DateOfPurchase2;
					else if (j == 1)
						customer->DateOfPurchase2 = customer->DateOfPurchase3;
					else if (j == 2)
						customer->DateOfPurchase3 = 0;
				}
				printf("Item returned successfully\n");
				return 1;
			}
			else
			{
				printf("Item return not allowed, it's passed 14 days from the date of purchase\n");
				return 0;
			}
		}
	}
}
int ReturnItemForCustomer(Customers* head_c, char* name, int Id) {
	Customers* customer = Find_Customers4(head_c, name);
	if (customer != NULL) {
		return ReturnItem(customer, Id);
	}
	else {
		printf("Customer not found");
		return 0;
	}
}
int UserIdentification(char* level)
{
	char UserName[15];
	char Password[15];
	SetColor(34);
	printf("\n============> USER LOGIN <============\n");
	ResetColor();
	printf("Insert user name:");
	gets(UserName);
	printf("Insert password:");
	gets(Password);
	FILE* fp3 = fopen("My_Employees.bin", "rb+");
	Employee epm;
	if (fp3 != NULL)
	{
		while (!feof(fp3))
		{
			fread(epm.UserName, sizeof(epm.UserName), 1, fp3);
			fread(epm.Password, sizeof(epm.Password), 1, fp3);
			fread(epm.FullName, sizeof(epm.FullName), 1, fp3);
			fread(epm.Level, sizeof(epm.Level), 1, fp3);
			if (((strcmp(epm.UserName, UserName)) == 0) && (strcmp(epm.Password, Password)) == 0)
			{
				char part1[40];
				strncpy(part1, epm.UserName, sizeof(part1));
				char part2[40] = "has logged into the system";
				PrintToLogFile_I(part1, part2);
				strncpy(level, epm.Level, sizeof(char[2]));
				return 0;
			}
		}
		return 1;
	}
}
int CheckUser(char UserName[], char Password[])
{
	FILE* fp3 = fopen("My_Employees.bin", "rb+");
	Employee epm;
	if (fp3 != NULL)
	{

		while (!feof(fp3))
		{
			fread(&epm, sizeof(Employee), 1, fp3);
			if (epm.UserName == UserName && epm.Password == Password)
			{
				return 1;
			}

		}
	}
}
void Print_Item_To_Consul(node New_Item)
{
	printf("\n\nThe new product properties is:\n\n");
	printf("ID: %d\n", New_Item.Id);
}
void SaveTree(node* root)
{
	int count = 0;
	FILE* fp1 = fopen("My_Items.bin", "rb");
	node Node;
	while (fread(&Node, sizeof(node), 1, fp1))
	{
		if (Node.Id != 0)
		{
			count++;
		}
	}
	fclose(fp1);
	fp1 = fopen("My_Items.bin", "wb");
	fseek(fp1, count * sizeof(node), SEEK_SET);
	save_node(root, fp1);
	fclose(fp1);
}
void save_node(node* Node, FILE* fp)
{
	if (Node == NULL) {
		return;
	}
	save_node(Node->left, fp);
	fwrite(Node, sizeof(node), 1, fp);
	save_node(Node->right, fp);
}
void Insert(node** tree, int val)
{
	node* temp = NULL;
	if (!(*tree))
	{
		temp = (node*)malloc(sizeof(node));
		temp->left = temp->right = NULL;
		temp->Id = val;
		char ItemType[10];
		char ItemColor[10];
		double ItemPrice;
		int ItemAmount;
		int Gender;
		fgetc(stdin);
		printf("Insert item type:");
		gets(ItemType);
		strncpy(temp->ItemType, ItemType, sizeof(temp->ItemType));
		printf("Insert item color:");
		gets(ItemColor);
		strncpy(temp->ItemColor, ItemColor, sizeof(temp->ItemColor));
		printf("Insert item price:");
		scanf("%lf", &ItemPrice);
		temp->ItemPrice = ItemPrice;
		printf("Insert item amount:");
		scanf("%d", &ItemAmount);
		temp->ItemAmount = ItemAmount;
		printf("If the product for man insert '1',for woman insert '2' :");
		scanf("%d", &Gender);
		if (Gender == 1)
			temp->Gender = true;
		else if (Gender == 2)
			temp->Gender = false;
		time(&temp->time);
		char part1[40] ="The following item Id has";
		char part2[40] = "been added to the store:";
		PrintToLogFile(part1, part2, temp->Id);
		*tree = temp;
		return;
//		int x = 42;
//		char str[100];
//		sprintf(sentence, "%d", temp->Id);
	}
	if (val < (*tree)->Id)
		Insert(&(*tree)->left, val);
	else if (val > (*tree)->Id)
		Insert(&(*tree)->right, val);
}
void Print_Tree_From_File()
{
	FILE* fp1 = fopen("My_Items.bin", "rb");
	if (fp1 == NULL)
	{
		printf("Error opening file!\n");
		return;
	}
	node Node;
	while (fread(&Node, sizeof(node), 1, fp1))
	{
		SetColor(32);
		printf("ID: %d\n", Node.Id);
		printf("____________________________________________________________________________\n");
		printf("Item type: %s || ", Node.ItemType);
		printf("ItemColor: %s || ", Node.ItemColor);
		printf("item price: %.2lf || ", Node.ItemPrice);
		printf("item amount: %d || \n", Node.ItemAmount);
		(Node.Gender) ? printf("Gender: man || ") : printf("Gender: woman || ");
		printf("date of update: %s\n", ctime(&Node.time));
		ResetColor();
	}
	fclose(fp1);
}
void Print_Tree_From_Variable(node* tree)
{
	if (tree)
	{
		Print_Tree_From_Variable(tree->left);

		printf("ID: %d\n", tree->Id);
		printf("____________________________________________________________________________\n");
		printf("Item type: %s || ", tree->ItemType);
		//puts(tree->ItemType);
		printf("ItemColor: %s || ", tree->ItemColor);
		//puts(tree->ItemColor);
		printf("item price: %.2lf || ", tree->ItemPrice);
		printf("item amount: %d || \n", tree->ItemAmount);
		(tree->Gender) ? printf("Gender: man || ") : printf("Gender: woman || ");
		printf("date of update: %s\n", ctime(&tree->time));
		Print_Tree_From_Variable(tree->right);
	}
}
void DeleteZerosFromFile()
{
	FILE* fp1 = fopen("My_Items.bin", "rb");
	node Node;
	FILE* fp4 = fopen("Temp_My_Items.bin", "wb");
	while (fread(&Node, sizeof(node), 1, fp1))
	{
		if (Node.Id != 0)
		{
			fwrite(&Node, sizeof(node), 1, fp4);
		}
	}
	fclose(fp1);
	fclose(fp4);
	FILE* fp5 = fopen("Temp_My_Items.bin", "rb");
	if (fp5 == NULL)
	{
		printf("Error opening file!\n");
		return;
	}
	fclose(fp5);
	return;
}
node* search(node** tree, int val)
{
	if (!(*tree))
		return NULL;

	if (val < (*tree)->Id)
	{
		search(&((*tree)->left), val);
	}
	else if (val > (*tree)->Id)
	{
		search(&((*tree)->right), val);
	}
	else if (val == (*tree)->Id)
	{
		return *tree;
	}
}
void Search_By_Type(node** tree, char* ItemType, int* sum)
{
	if (*tree == NULL) {
		return;
	}

	Search_By_Type(&((*tree)->left), ItemType, sum);
	if (strcmp(ItemType, (*tree)->ItemType) == 0)
	{
		printf("The Id: %d is %s \n", (*tree)->Id, ItemType);
		(*sum)++;
	}
	Search_By_Type(&((*tree)->right), ItemType, sum);
}
void Search_By_Color(node** tree, char* ItemColor, int* sum)
{
	if (*tree == NULL) {
		return;
	}

	Search_By_Color(&((*tree)->left), ItemColor, sum);
	if (strcmp(ItemColor, (*tree)->ItemColor) == 0)
	{
		printf("The Id: %d is %s \n", (*tree)->Id, ItemColor);
		(*sum)++;
	}
	Search_By_Color(&((*tree)->right), ItemColor, sum);
}
void Search_By_Color_And_Type(node** tree, char* ItemType, char* ItemColor, int* sum)
{
	if (*tree == NULL) {
		return;
	}

	Search_By_Color_And_Type(&((*tree)->left), ItemType, ItemColor, sum);
	if ((strcmp(ItemColor, (*tree)->ItemColor) == 0) && (strcmp(ItemColor, (*tree)->ItemColor) == 0))
	{
		printf("The Id: %d is %s and %s \n", (*tree)->Id, ItemType, ItemColor);
		(*sum)++;
	}
	Search_By_Color_And_Type(&((*tree)->right), ItemType, ItemColor, sum);
}
void Search_By_Price_Less(node** tree, double ItemPrice, int* sum)
{
	if (*tree == NULL) {
		return;
	}

	Search_By_Price_Less(&((*tree)->left), ItemPrice, sum);
	if (ItemPrice > (*tree)->ItemPrice)
	{
		printf("The Id: %d is cheap then %.2lf \n", (*tree)->Id, ItemPrice);
		(*sum)++;
	}
	Search_By_Price_Less(&((*tree)->right), ItemPrice, sum);
}
void Search_By_Price_More(node** tree, double ItemPrice, int* sum)
{
	if (*tree == NULL) {
		return;
	}

	Search_By_Price_More(&((*tree)->left), ItemPrice, sum);
	if (ItemPrice < (*tree)->ItemPrice)
	{
		printf("The Id: %d is more expensive then %.2lf \n", (*tree)->Id, ItemPrice);
		(*sum)++;
	}
	Search_By_Price_More(&((*tree)->right), ItemPrice, sum);
}
void Search_By_Gender_Man(node** tree, int Gender, int* sum)
{
	if (*tree == NULL) {
		return;
	}

	Search_By_Gender_Man(&((*tree)->left), Gender, sum);
	if ((Gender = 1) && (*tree)->Gender)
	{
		printf("The Id: %d is protact for man \n", (*tree)->Id);
		(*sum)++;
	}
	Search_By_Gender_Man(&((*tree)->right), Gender, sum);
}
void Search_By_Gender_Woman(node** tree, int Gender, int* sum)
{
	if (*tree == NULL) {
		return;
	}

	Search_By_Gender_Woman(&((*tree)->left), Gender, sum);
	if ((Gender = 2) && !(*tree)->Gender)
	{
		printf("The Id: %d is protact for woman \n", (*tree)->Id);
		(*sum)++;
	}
	Search_By_Gender_Woman(&((*tree)->right), Gender, sum);
}
void Search_By_Date_Less(node** tree, int day,int month,int year, int* sum)
{
	time_t current_time = time(NULL);
	if (*tree == NULL) {
		return;
	}

	Search_By_Date_Less(&((*tree)->left), day, month, year, sum);
	current_time = (*tree)->time;
	if (year < (*tree)->time)
	{
		printf("The Id: %d is more expensive then %.2lf \n", (*tree)->Id, year);
		(*sum)++;
	}
	Search_By_Date_Less(&((*tree)->right), day, month, year, sum);
}
int DeleteNode(node** tree, int Id){
	if (*tree == NULL)
		return 0; 
	if (Id < (*tree)->Id)
		return DeleteNode(&((*tree)->left), Id);
	if (Id > (*tree)->Id)
		return DeleteNode(&((*tree)->right), Id);
 	if ((*tree)->left == NULL)
	{
		node* temp = (*tree)->right;
		*tree = temp;
	}
	else if ((*tree)->right == NULL)
	{
		node* temp = (*tree)->left;
		*tree = temp;
	}
	else
	{
		node* temp = (*tree)->right;
		while (temp->left != NULL)
			temp = temp->left;
		(*tree)->Id = temp->Id;
		return DeleteNode(&((*tree)->right), temp->Id);
	}
	return 1;
}
void UpdateItemProperties(node** tree, int val)
{
	int Id;
	node* temp = NULL;
	temp = (node*)malloc(sizeof(node));
	temp = search(&(*tree), val);
	if (temp)
	{
		char ItemType[10];
		char ItemColor[10];
		double ItemPrice;
		int ItemAmount;
		int Gender;
		fgetc(stdin);
		printf("Insert new item type:");
		gets(ItemType);
		strncpy(temp->ItemType, ItemType, sizeof(temp->ItemType));
		printf("Insert new item color:");
		gets(ItemColor);
		strncpy(temp->ItemColor, ItemColor, sizeof(temp->ItemColor));
		printf("Insert new item price:");
		scanf("%lf", &ItemPrice);
		temp->ItemPrice = ItemPrice;
		printf("Insert new item amount:");
		scanf("%d", &ItemAmount);
		temp->ItemAmount = ItemAmount;
		printf("If the product for man insert '1',for woman insert '2' :");
		scanf("%d", &Gender);
		if (Gender == 1)
			temp->Gender = true;
		else if (Gender == 2)
			temp->Gender = false;
		time(&temp->time);
		char part1[40] = "The following item Id";
		char part2[40] = "has been updated:";
		PrintToLogFile(part1, part2, temp->Id);
		printf("Changes saved to the item list \n");
	}
	else
		printf("The Item is NOT in the store\n");
}
void SellItem(node** tree, int val, int AmountToSell)
{
	int Id;
	node* temp = NULL;
	temp = (node*)malloc(sizeof(node));
	temp = search(&(*tree), val);
	if (temp)
	{
		temp->ItemAmount = temp->ItemAmount - AmountToSell;
		time(&temp->time);
		char part1[40] = "The inventory of item with Id";
		char part2[40] = "was updated following a sale to:";
		PrintToLogFile_1(part1, temp->Id, part2, temp->ItemAmount);
		printf("Changes saved to the item list \n");
	}
	else
		printf("The Item is NOT in the store\n");
}
void GettItem(node** tree, int val, int AmountToGet)
{
	int Id;
	node* temp = NULL;
	temp = (node*)malloc(sizeof(node));
	temp = search(&(*tree), val);
	if (temp)
	{
		temp->ItemAmount = temp->ItemAmount + AmountToGet;
		time(&temp->time);
		char part1[40] = "The inventory of item with Id";
		char part2[40] = "was updated upon receipt of stock to:";
		PrintToLogFile_1(part1, temp->Id, part2, temp->ItemAmount);
		printf("Changes saved to the item list \n");

	}
	else
		printf("The Item is NOT in the store\n");
}
void AutoInsert(node** tree, int val, char ItemType[], char ItemColor[], double ItemPrice, int ItemAmount, int Gender, time_t time)
{
	node* temp = NULL;
	if (!(*tree))
	{
		temp = (node*)malloc(sizeof(node));
		temp->left = temp->right = NULL;
		temp->Id = val;
		strncpy(temp->ItemType, ItemType, sizeof(temp->ItemType));
		strncpy(temp->ItemColor, ItemColor, sizeof(temp->ItemColor));
		temp->ItemPrice = ItemPrice;
		temp->ItemAmount = ItemAmount;
		if (Gender == 1)
			temp->Gender = true;
		else if (Gender == 0)
			temp->Gender = false;
		temp->time = time;
		*tree = temp;
		return;
	}
	if (val < (*tree)->Id)
		AutoInsert(&(*tree)->left, val, ItemType, ItemColor, ItemPrice,
			ItemAmount, Gender, time);
	else if (val > (*tree)->Id)
		AutoInsert(&(*tree)->right, val, ItemType, ItemColor, ItemPrice,
			ItemAmount, Gender, time);
}
void SetColor(int Color)
{
	printf("\033[1;%dm", Color);
}
void ResetColor()
{
	printf("\033[0m");
}
void PrintToLogFile(char part1[60], char part2[60], int Num)
{
	char* CurTime;
	time_t tm = time(NULL);
	CurTime = strtok(ctime(&tm), "\n");
	FILE* log = fopen("My_Log.txt", "a");
	fprintf(log, "[ %s ] : %s %s %d\n", CurTime, part1, part2, Num);
	fclose(log);
}
void PrintToLogFile_1(char part1[60], int Num, char part2[60], int Num2)
{
	char* CurTime;
	time_t tm = time(NULL);
	CurTime = strtok(ctime(&tm), "\n");
	FILE* log = fopen("My_Log.txt", "a");
	fprintf(log, "[ %s ] : %s %d %s %d\n", CurTime, part1, Num, part2, Num2);
	fclose(log);
}
void PrintToLogFile_2(char part1[60], int Num, char part2[60], char part3[60])
{
	char* CurTime;
	time_t tm = time(NULL);
	CurTime = strtok(ctime(&tm), "\n");
	FILE* log = fopen("My_Log.txt", "a");
	fprintf(log, "[ %s ] : %s %d %s %s\n", CurTime, part1, Num, part2, part3);
	fclose(log);
}
void PrintToLogFile_I(char part1[60], char part2[60])
{
	char* CurTime;
	time_t tm = time(NULL);
	CurTime = strtok(ctime(&tm), "\n");
	FILE* log = fopen("My_Log.txt", "a");
	fprintf(log, "[ %s ] : %s %s\n", CurTime, part1, part2);
	fclose(log);
}
void InsertNewEmployees(Employee* employees, int numEmployees,int numEmExist)
{
	FILE* fp3 = fopen("My_Employees.bin", "rb");
	fread(employees, sizeof(Employee), numEmExist, fp3);
	fclose(fp3);
	for (int i = numEmExist; i < numEmployees+ numEmExist; i++)
	{
		printf("Enter UserName for Employee %d: ", i + 1);
		scanf("%s", employees[i].UserName);
		printf("Enter Password for Employee %d: ", i + 1);
		scanf("%s", employees[i].Password);
		printf("Enter FullName for Employee %d: ", i + 1);
		scanf("%s", employees[i].FullName);
		printf("Enter Level for Employee %d: ", i + 1);
		scanf("%s", employees[i].Level);
		char part1[60] = "The following employee has been added to the list:";
		//char part2[60] = employees[i].FullName;
		PrintToLogFile_I(part1, employees[i].FullName);
	}
}
void WriteEmployeesToFile(Employee* employees, int TotEmp)
{
	FILE* fp = fopen("My_Employees.bin", "wb");
	if (fp == NULL) {
		printf("Error opening file\n");
		return;
	}
	fwrite(employees, sizeof(Employee), TotEmp, fp);
	fclose(fp);
}
void PrintEployee(Employee* employees)
{
	FILE* fp3 = fopen("My_Employees.bin", "rb");
	fseek(fp3, 0, SEEK_END);
	int fileSize = ftell(fp3);
	int numEmployees = fileSize / sizeof(Employee);
	fseek(fp3, 0, SEEK_SET);
	fread(employees, sizeof(Employee), numEmployees, fp3);
	fclose(fp3);
	SetColor(32);
	for (int i = 0; i < numEmployees; i++)
	{
		printf("UserName: %s\n", employees[i].UserName);
		printf("Password: %s\n", employees[i].Password);
		printf("FullName: %s\n", employees[i].FullName);
		printf("Level: %s\n", employees[i].Level);
		printf("____________________\n");
	}
	ResetColor();
}
