#include "StoreManager.h"

void initStoreManager(StoreManager* storeManager) {
	storeManager->stores = NULL;
	storeManager->noOfStores = 0;
}

void loadSystem(StoreManager* storeManager) {
	printf("Load options:\n");
	for (int i = 0; i < eNoOfLoadOptions; i++){
		printf("%d. %s\n", i + 1, loadOptionsStr[i]);
	}
	int opt;
	do {
		scanf("%d", &opt);
		if (opt < 1 || opt > eNoOfLoadOptions)
			printf("Invalid option, please try again\n");
	} while (opt < 1 || opt > eNoOfLoadOptions);
	opt--;
	switch (opt)
	{
	case eLoadFromTextFile: {
		loadStoreManagerFromTextFile(storeManager, "storeManager.txt");
		break;
	}
	case eLoadFromBinaryFile: {
		//loadStoreManagerFromBinaryFile(storeManager, "storeManager.bin");
		break;
	}
	case eLoadNewSystem: {
		generateHQ(storeManager);
		break;
	}
	}
}

void generateHQ(StoreManager* storeManager) {
	printf("We will now generate the HQ store\n");
	storeManager->stores = (Store**)malloc(sizeof(Store*));
	addStore(storeManager);
}

int generateStoreID(const StoreManager* storeManager) {
	if (storeManager->noOfStores == 0) {
		return 0;
	}
	int id = 0;
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (storeManager->stores[i]->storeID > id) {
			id = storeManager->stores[i]->storeID;
		}
	}
	return id + 1;
}

void addStore(StoreManager* storeManager) {
	if(storeManager->stores == NULL) {
		printf("system not initialized\n");
		return;
	}
	int id = generateStoreID(storeManager);
	Store* store = (Store*)malloc(sizeof(Store));
	if (storeManager == NULL || store == NULL) {
		return;
	}
	if(!createStore(store, id)){
		free(store);
		return;
	}
	Store** tmp = (Store**)realloc(storeManager->stores, (storeManager->noOfStores + 1) * sizeof(Store*));
	if (!tmp) {
		free(store);
		return;
	}
	storeManager->stores = tmp;
	storeManager->stores[storeManager->noOfStores] = store;
	storeManager->noOfStores++;
	updateAllStoreDepartments(storeManager);
}

void addProductToMainStore(StoreManager storeManager, int departmentID ,Product* product) {
	Department* department = &storeManager.stores[0]->departments[departmentID];
	Product* tmp = (Product*)realloc(department->products, sizeof(Product) * (department->noOfProducts + 1));
	if (!tmp) {
		printf("error in reallocating memory\n");
		return;
	}
	department->products = tmp;
	department->products[department->noOfProducts++] = *product;
}

void addProductToDepartmentType(StoreManager* storeManager) {
	if (storeManager->stores == NULL) {
		printf("system not initialized\n");
		return;
	}
	printDepartmentTypes();
	int departmentTypeID;
	printf("Enter the department type ID: ");
	do {
		scanf("%d", &departmentTypeID);
		if(departmentTypeID < 0 || departmentTypeID >= noOfDepartmentTypes)
			printf("Invalid ID, please try again\n");
	} while (departmentTypeID < 0 || departmentTypeID >= noOfDepartmentTypes);

	Product* product = (Product*) malloc(sizeof(Product));
	if (product == NULL) {
		return;
	}
	do {
		getProductCode(product->code);
		if(checkIfProductCodeExists(storeManager, product->code))
			printf("Product code already exists, please try again: ");
	}while(checkIfProductCodeExists(storeManager, product->code));
	initProduct(product);
	printProduct(product);
	addProductToMainStore(*storeManager, departmentTypeID, product);
	updateAllStoreDepartments(storeManager);
}

int checkIfProductCodeExists(const StoreManager* storeManager, const char* productCode) {
	if (storeManager == NULL) {
		return 0;
	}
	for (int i = 0; i < storeManager->noOfStores; i++) {
		for (int j = 0; j < storeManager->stores[i]->noOfDepartments; j++) {
			for (int k = 0; k < storeManager->stores[i]->departments[j].noOfProducts; k++) {
				if (strcmp(storeManager->stores[i]->departments[j].products[k].code, productCode) == 0) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void updateAllStoreDepartments(StoreManager* storeManager) {
	if (storeManager->noOfStores <= 1) {
		return;
	}
	for (int i = 1; i < storeManager->noOfStores; i++) {
		for (int j = 0; j < storeManager->stores[i]->noOfDepartments; j++) {
			Department* department = &storeManager->stores[i]->departments[j];
			Department* MainDepartment = &storeManager->stores[0]->departments[j];
			if (department->noOfProducts != MainDepartment->noOfProducts) {
				
				Product* tmp = (Product*)realloc(department->products, sizeof(Product) * (MainDepartment->noOfProducts));
				if (!tmp) {
					printf("error in reallocating memory\n");
					return;
				}
				department->products = tmp;
				for (int k = 0; k < MainDepartment->noOfProducts; k++) {
					if(strcmp(department->products[k].code, MainDepartment->products[k].code) != 0)
						department->products[k] = MainDepartment->products[k];
				}
				department->noOfProducts = MainDepartment->noOfProducts;
			}
		
		}
	}
}

Store* getStore(StoreManager* storeManager, int storeID) {
	if (storeManager == NULL) {
		return NULL;
	}
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (storeManager->stores[i]->storeID == storeID) {
			return storeManager->stores[i];
		}
	}
	return NULL;
}

Store* enterStore(StoreManager* storeManager) {
	if (storeManager == NULL || storeManager->noOfStores == 0) {
		printf("No stores!\n");
		return NULL;
	}
	for (int i = 0; i < storeManager->noOfStores; i++)
	{
		printStoreReduced(storeManager->stores[i]);
	}
	int storeID;
	printf("Enter the store ID: ");
	scanf("%d", &storeID);
	Store* store = getStore(storeManager, storeID);
	if (!store) {
		printf("Store not found!\n");
	}
	return store;
}

void calculateTotalProfit(const StoreManager* storeManager) {
	if (storeManager == NULL) {
		return;
	}
	int totalProfit = 0;
	for (int i = 0; i < storeManager->noOfStores; i++) {
		totalProfit += calculateStoreProfit(storeManager->stores[i]);
	}
	printf("Total profit for the year %d: %d\n", YEAR, totalProfit);
}

void sortAllStoresBy(StoreManager* storeManager) {
	if(storeManager->stores == NULL) {
		printf("system not initialized\n");
		return;
	}
	storeManager->storeSortOpt = showSortMenu();
	int(*compare)(const void* store1, const void* store2) = NULL;
	switch (storeManager->storeSortOpt)
	{
	case eID: {
		compare = compareStoreByID;
		break;
	}
	case eProfit: {
		compare = compareStoreByProfit;
		break;
	}
	case eRent: {
		compare = compareStoreByRent;
		break;
	}
	case eLocation: {
		compare = compareStoreByLocation;
		break;
	}
	}
	if(compare != NULL)
		qsort(storeManager->stores, storeManager->noOfStores, sizeof(Store*), compare);
}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofSortOpt);

	return (eSortOption)opt;
}

void findStore(const StoreManager* storeManager)
{
	if (storeManager->stores == NULL) {
		printf("system not initialized\n");
		return;
	}
	int(*compare)(const void* store1, const void* store2) = NULL;
	Store store = { 0 };
	Store* pStore = &store;
	switch (storeManager->storeSortOpt)
	{
	case eID: {
		printf("Enter store's ID number:\n");
		scanf("%d", &store.storeID);
		compare = compareStoreByID;
		break;
	}
	case eProfit: {
		compare = compareStoreByProfit;
		break;
	}
	case eRent: {
		printf("Enter store's rent:\n");
		scanf("%d", &store.rent);
		compare = compareStoreByRent;
		break;
	}
	case eLocation: {
		pStore->location = getStrExactName("Enter the location of the store: ");
		compare = compareStoreByLocation;
		break;
	}
	}
	if (compare != NULL)
	{
		Store** foundStore = bsearch(&pStore, storeManager->stores, storeManager->noOfStores, sizeof(Store*), compare);
		if (foundStore == NULL)
			printf("Store was not found\n");
		else
			printStore(*foundStore);
		if (storeManager->storeSortOpt == eLocation)
				free(pStore->location);
	}
	else
		printf("The search cannot be performed, array not sorted\n");
}

void printAllStores(const StoreManager* storeManager) {
	if (storeManager->stores == NULL) {
		printf("no stores!\n");
		return;
	}
	for (int i = 0; i < storeManager->noOfStores; i++)
	{
		printStore(storeManager->stores[i]);
	}
}

void freeStoreManager(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return;
	}
	if (storeManager->stores != NULL) {
		for (int i = 0; i < storeManager->noOfStores; i++) {
			printf("freeing store %d\n", i); //debug
			freeStore(storeManager->stores[i]);
		}
		free(storeManager->stores);
	}
}

void saveStoreManagerToTextFile(const StoreManager* storeManager, const char* fileName) {
	if (storeManager == NULL) {
		return;
	}
	FILE* file = fopen(fileName, "w");
	if (!file) {
		printf("error in opening file\n");
		return;
	}
	printf("file opened"); //debug
	fprintf(file, "%d\n", storeManager->noOfStores);
	for (int i = 0; i < storeManager->noOfStores; i++) {
		saveStoreToTextFile(storeManager->stores[i], file);
	}
	fclose(file);
}

void loadStoreManagerFromTextFile(StoreManager* storeManager, const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (!file) {
		printf("error in opening file\n");
		return;
	}
	int noOfStores;
	fscanf(file, "%d", &noOfStores);
	fgetc(file);
	storeManager->noOfStores = noOfStores;
	printf("no of stores: %d\n", noOfStores); //debug
	Store** stores = (Store**)malloc(noOfStores * sizeof(Store*));
	if (!stores) {
		printf("error in allocating memory\n");
		return;
	}
	for (int i = 0; i < noOfStores; i++) {
		Store* store = (Store*)malloc(sizeof(Store));
		initStore(store, 0);
		if (!store) {
			printf("error in allocating memory\n");
			return;
		}
		loadStoreFromTextFile(store, file);
		stores[i] = store;
	}
	storeManager->stores = stores;
	fclose(file);
}

