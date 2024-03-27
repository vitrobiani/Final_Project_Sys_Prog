#include "StoreManager.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	eLOAD_FROM_FILE,
	eADD_STORE,
	eREMOVE_STORE,
	eADD_DEPARTMENT_TYPE,
	eADD_PRODUCT_TO_DEPARTMENT,
	eENTER_STORE,
	eVIEW_STORES,
	eVIEW_DEPARTMENTS,
	eEXIT,
	eNumOfOptions
} Options;

const char* optionsStrings[] = {
	"Load from file",
	"Add a store",
	"Remove a store",
	"Add a department type",
	"Add a product to a department type",
	"Enter a store",
	"View all stores",
	"View all departments",
	"Exit"
};

typedef enum {
	eADD_EMPLOYEE,
	eADD_DEPARTMENT,
	ePRINT_DEPARTMENTS,
	eGO_BACK,
	eNumOfStoreMenuOptions
}storeMenu;

const char* storeMenuStrings[] = {
	"Add an employee",
	"Add a department",
	"Print all departments and their products",
	"Go back to the main menu"
};

int managerOptions() {
	printf("\nWelcome to the store manager system!\n");
	
	for (int i = 0; i < eNumOfOptions; i++)
	{
		printf("%d. %s\n", i + 1, optionsStrings[i]);
	}

	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	return choice-1;
}

int storeMenuOptions() {
	for (int i = 0; i < eNumOfStoreMenuOptions; i++)
	{
		printf("%d. %s\n", i + 1, storeMenuStrings[i]);
	}

	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	return choice-1;
}

void storeLobby(Store* store, StoreManager* storeManager) {
	if (store == NULL) return;

	printf("\nWelcome to the store lobby! - loc: %s\n", store->location);
	int choice = 0;
	do
	{
		choice = storeMenuOptions();
		switch (choice)
		{
		case eADD_EMPLOYEE: {
			addEmployee(store);
			break;
		}
		case eADD_DEPARTMENT: {
			addDepartment(store, getDepartmentTypeByID(storeManager));
			break;
		}
		case ePRINT_DEPARTMENTS: {
			printAllDepartments(store);
			break;
		}
		default:
			break;
		}
	} while (choice != eGO_BACK);
}

int main(int argc, char* argv[], char* env[]) {

	StoreManager storeManager;
	initStoreManager(&storeManager);

	int choice = 0;
	do
	{
		choice = managerOptions();
		switch (choice)
		{
		case eADD_STORE: {
			addStore(&storeManager);
			break;
		}
		case eVIEW_STORES: {
			printAllStores(&storeManager);
			break;
		}
		case eADD_DEPARTMENT_TYPE: {
			addDepartmentType(&storeManager);
			break;
		}
		case eADD_PRODUCT_TO_DEPARTMENT: {
			addProductToDepartment(&storeManager);
			break;
		}
		case eENTER_STORE: {
			storeLobby(enterStore(&storeManager), &storeManager);
			break;
		}
		case eVIEW_DEPARTMENTS: {
			printAllDepartmentTypesFull(&storeManager);
			break;
		}

		default:
			break;
		}
	} while (choice != eEXIT);

	return 0;
}
