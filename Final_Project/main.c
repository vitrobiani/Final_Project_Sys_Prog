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
	eSORT_BY,
	eFIND_STORE,
	eCALCULATE_TOTAL_PROFIT,
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
	"View all department types",
	"Sort by",
	"Find a store",
	"Calculate total profit",
	"Exit"
};

typedef enum {
	eADD_EMPLOYEE,
	eADD_DEPARTMENT,
	ePRINT_DEPARTMENTS,
	eADD_PRODUCT,
	eMAKE_SALE,
	eCALCULATE_PROFIT,
	ePRINT_INVOICES,
	eGO_BACK,
	eNumOfStoreMenuOptions
}storeMenu;

const char* storeMenuStrings[] = {
	"Add an employee",
	"Add a department",
	"Print all departments and their products",
	"Add a product",
	"Make a sale",
	"Calculate profit",
	"Print all invoices",
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

	int choice = 0;
	do
	{
	printf("\nWelcome to the store lobby! - location: %s\n", store->location);
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
		case eADD_PRODUCT: {
			addProductToDepartment(store);
			break;
		}
		case eMAKE_SALE: {
			makeSale(store);
			break;
		}
		case ePRINT_INVOICES: {
			printAllInvoices(store);
			break;
		}
		case eCALCULATE_PROFIT: {
			printf("\nThe store profit is: %d\n\n", calculateStoreProfit(store));
			break;
		}
		default:
			break;
		}
	} while (choice != eGO_BACK);
}

void ExitProgram(StoreManager* storeManager) {
	//saveStoreManagerToTextFile(storeManager, "storeManager.txt");
	freeStoreManager(storeManager);
	printf("Goodbye!\n");
}

int main(int argc, char* argv[], char* env[]) {

	StoreManager storeManager;
	initStoreManager(&storeManager);

	//loadStoreManagerFromTextFile(&storeManager, "storeManager.txt");

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
			addProductToDepartmentType(&storeManager);
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
		case eCALCULATE_TOTAL_PROFIT: {
			calculateTotalProfit(&storeManager);
			break;
		}
		case eSORT_BY: {
			sortAllStoresBy(&storeManager);
			break;
		}
		case eFIND_STORE: {
			findStore(&storeManager);
			break;
		}
		default:
			break;
		}
	} while (choice != eEXIT);

	ExitProgram(&storeManager);
	return 0;
}
