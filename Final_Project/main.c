#include "StoreManager.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	eLOAD_SYSTEM,
	eADD_STORE,
	eADD_PRODUCT_TO_DEPARTMENT,
	eENTER_STORE,
	eVIEW_STORES,
	eSORT_BY,
	eFIND_STORE,
	eCALCULATE_TOTAL_PROFIT,
	eCHAIN_BEST_SALESMAN,
	eCHAIN_BEST_SELLER,
	eEXIT,
	eNumOfOptions
} Options;

const char* optionsStrings[] = {
	"Load system",
	"Add a store",
	"Add a product to a department type",
	"Enter a store",
	"View all stores",
	"Sort by",
	"Find a store",
	"Calculate total profit",
	"Find the best salesman in the chain",
	"Find the best seller product in the chain",
	"Exit"
};

typedef enum {
	eADD_EMPLOYEE,
	eADD_PRODUCT,
	eMAKE_SALE,
	eCALCULATE_PROFIT,
	eCALCULATE_SPENDINGS,
	ePRINT_EMPLOYEES,
	ePRINT_DEPARTMENTS,
	ePRINT_INVOICES,
	eBEST_SALESMAN,
	eBEST_SELLER,
	eGO_BACK,
	eNumOfStoreMenuOptions
}storeMenu;

const char* storeMenuStrings[] = {
	"Add an employee",
	"Add a product",
	"Make a sale",
	"Calculate profit",
	"Calculate spendings",
	"Print all employees",
	"Print all departments and their products",
	"Print all invoices",
	"Find the best salesman in the store",
	"Find the best seller product in the store",
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
		case eADD_PRODUCT: {
			addProductToDepartment(store);
			break;
		}
		case eMAKE_SALE: {
			makeSale(store);
			break;
		}
		case eCALCULATE_PROFIT: {
			printStoreProfit(store);
			break;
		}
		case eCALCULATE_SPENDINGS: {
			printStoreSpendings(store);
			break;
		}
		case ePRINT_EMPLOYEES: {
			printAllEmployees(store);
			break;
		}
		case ePRINT_DEPARTMENTS: {
			printAllDepartments(store);
			break;
		}
		case ePRINT_INVOICES: {
			printAllInvoices(store);
			break;
		}
		case eBEST_SALESMAN: {
			findBestSalesMan(store);
			break;
		}
		case eBEST_SELLER: {
			findBestSellerProduct(store);
			break;
		}
		default:
			break;
		}
	} while (choice != eGO_BACK);
}

void ExitProgram(StoreManager* storeManager) {
	saveStoreManagerToTextFile(storeManager, "storeManager.txt");
	saveStoreManagerToBinaryFile(storeManager, "storeManager.bin");
	freeStoreManager(storeManager);
	printf("before dump\n");
	int check =_CrtDumpMemoryLeaks();
	printf("%s\n", (check) ? "there are memory leaks" : "no memory leaks");
	printf("Goodbye!\n");
}

int main() {

	StoreManager storeManager;
	initStoreManager(&storeManager);

	int choice = 0;
	do
	{
		choice = managerOptions();
		switch (choice)
		{
		case eLOAD_SYSTEM: {
			loadSystem(&storeManager);
			break;
		}
		case eADD_STORE: {
			addStore(&storeManager);
			break;
		}
		case eVIEW_STORES: {
			printAllStores(&storeManager);
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
		case eSORT_BY: {
			sortAllStoresBy(&storeManager);
			break;
		}
		case eFIND_STORE: {
			findStore(&storeManager);
			break;
		}
		case eCALCULATE_TOTAL_PROFIT: {
			calculateTotalProfit(&storeManager);
			break;
		}
		case eCHAIN_BEST_SALESMAN: {
			findChainBestSalesMan(&storeManager);
			break;
		}
		case eCHAIN_BEST_SELLER: {
			findChainBestSellerProduct(&storeManager);
			break;
		}
		default:
			break;
		}
	} while (choice != eEXIT);

	ExitProgram(&storeManager);
	return 0;
}
