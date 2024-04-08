#include "Main.h"

int managerOptions() {
	printf("\nWelcome to the store manager system!\n");

	for (int i = 0; i < eNumOfOptions; i++) {
		printf("%d. %s\n", i + 1, optionsStrings[i]);
	}

	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	return choice - 1;
}

int storeMenuOptions() {
	for (int i = 0; i < eNumOfStoreMenuOptions; i++) {
		printf("%d. %s\n", i + 1, storeMenuStrings[i]);
	}

	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	return choice - 1;
}

void storeLobby(Store* store, StoreManager* storeManager) {
	if (store == NULL) return;
	int choice = 0;
	do {
		printf("\nWelcome to the store lobby! - location: %s\n", store->location);
		choice = storeMenuOptions();
		switch (choice)
		{
		case eADD_PRODUCT: {
			addProductToDepartment(store);
			break;
		}
		case eMAKE_SALE: {
			makeSale(store);
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
	int check = _CrtDumpMemoryLeaks();
	printf("%s\n", (check) ? "there are memory leaks" : "no memory leaks");
	printf("Goodbye!\n");
}

int main() {

	StoreManager storeManager;
	loadSystem(&storeManager);
	//initStoreManager(&storeManager);

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
		case eADD_PRODUCT_TO_DEPARTMENT: {
			addProductToDepartmentType(&storeManager);
			break;
		}
		case eADD_EMPLOYEE: {
			addEmployeeToStore(&storeManager);
			break;
		}
		case eENTER_STORE: {
			storeLobby(enterStore(&storeManager), &storeManager);
			break;
		}
		case eVIEW_STORES: {
			printAllStores(&storeManager);
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
