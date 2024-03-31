#include "StoreManager.h"

void initStoreManager(StoreManager* storeManager) {
	storeManager->stores = NULL;
	storeManager->noOfStores = 0;
	storeManager->departments = NULL;
	storeManager->noOfDepartmentTypes = 0;
}

int generateStoreID(const StoreManager* storeManager) {
	int id = 0;
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (storeManager->stores[i]->storeID > id) {
			id = storeManager->stores[i]->storeID;
		}
	}
	return id + 1;
}

void addStore(StoreManager* storeManager) {
	Store* store = (Store*)malloc(sizeof(Store));
	if (storeManager == NULL || store == NULL) {
		return;
	}
	createStore(store, generateStoreID(storeManager));
	Store** tmp = (Store**)realloc(storeManager->stores, (storeManager->noOfStores + 1) * sizeof(Store*));
	if (!tmp) {
		free(store);
		return;
	}
	storeManager->stores = tmp;
	storeManager->stores[storeManager->noOfStores++] = store;
}

void removeStore(StoreManager* storeManager, int storeID) {
}

void addDepartmentType(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return;
	}
	DepartmentType* departmentType = (DepartmentType*)malloc(sizeof(DepartmentType));
	if (!departmentType) {
		printf("error in allocating memory\n");
		return;
	}
	initDepartmentType(departmentType, generateDepartmentTypeID(storeManager));
	DepartmentType* tmp = (DepartmentType*)realloc(storeManager->departments, (storeManager->noOfDepartmentTypes + 1) * sizeof(DepartmentType));
	if (!tmp) {
		printf("error in allocating memory\n");
		free(departmentType);
		return;
	}
	storeManager->departments = tmp;
	storeManager->departments[storeManager->noOfDepartmentTypes] = *departmentType;
	storeManager->noOfDepartmentTypes++;
}

int generateDepartmentTypeID(const StoreManager* storeManager) {
	int id = 0;
	for (int i = 0; i < storeManager->noOfDepartmentTypes; i++) {
		if (storeManager->departments[i].id > id) {
			id = storeManager->departments[i].id;
		}
	}
	return id + 1;
}

DepartmentType* getDepartmentTypeByID(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return NULL;
	}
	printAllDepartmentTypes(storeManager);
	int departmentTypeID;
	printf("Enter the department type ID: ");
	DepartmentType* tmp = NULL;
	do
	{
		scanf("%d", &departmentTypeID);
		tmp = getDepartmentType(storeManager, departmentTypeID);
	} while (!tmp);
	return tmp;
}

DepartmentType* getDepartmentType(StoreManager* storeManager, int departmentTypeID) {
	if (storeManager == NULL) {
		return NULL;
	}
	for (int i = 0; i < storeManager->noOfDepartmentTypes; i++) {
		if (storeManager->departments[i].id == departmentTypeID) {
			return &storeManager->departments[i];
		}
	}
	return NULL;
}

void addProductToDepartmentType(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return;
	}
	printAllDepartmentTypes(storeManager);
	int departmentTypeID;
	printf("Enter the department type ID: ");
	scanf("%d", &departmentTypeID);
	DepartmentType* departmentType = getDepartmentType(storeManager, departmentTypeID);
	if (!departmentType) {
		printf("Department type not found!\n");
		return;
	}
	createProductToDepartmentType(departmentType);
	updateAllStoreDepartments(storeManager, departmentType);
}

void updateAllStoreDepartments(StoreManager* storeManager, DepartmentType* type) {
	if (storeManager == NULL) {
		return;
	}
	for (int i = 0; i < storeManager->noOfStores; i++) {
		for (int j = 0; j < storeManager->stores[i]->noOfDepartments; j++) {
			if (storeManager->stores[i]->departments[j].type->id == type->id) {
				Product* tmp = (Product*)realloc(storeManager->stores[i]->departments[j].products, sizeof(Product) * type->noOfProducts);
				if (!tmp) {
					return;
				}
				storeManager->stores[i]->departments[j].products = tmp;
				storeManager->stores[i]->departments[j].products[type->noOfProducts - 1] = type->products[type->noOfProducts - 1];
				storeManager->stores[i]->departments[j].noOfProducts = type->noOfProducts;
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
	double totalProfit = 0;
	for (int i = 0; i < storeManager->noOfStores; i++) {
		totalProfit += calculateStoreProfit(storeManager->stores[i]);
	}
	printf("Total profit: %.2lf\n", totalProfit);
}

void sortAllStoresBy(StoreManager* storeManager) {
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

void printAllDepartmentTypes(const StoreManager* storeManager) {
	if (storeManager->departments == NULL) {
		printf("no department types!\n");
		return;
	}
	generalArrayFunction(storeManager->departments, storeManager->noOfDepartmentTypes, sizeof(DepartmentType), printDepartmentType);
}

void printAllDepartmentTypesFull(const StoreManager* storeManager) {
	if (storeManager->departments == NULL) {
		printf("no department types!\n");
		return;
	}
	generalArrayFunction(storeManager->departments, storeManager->noOfDepartmentTypes, sizeof(DepartmentType), printDepartmentTypeFull);
}

void freeStoreManager(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return;
	}
	if (storeManager->stores != NULL) {
		for (int i = 0; i < storeManager->noOfStores; i++) {
			freeStore(storeManager->stores[i]);
		}
		free(storeManager->stores);
	}
	if (storeManager->departments != NULL) {
		generalArrayFunction(storeManager->departments, storeManager->noOfDepartmentTypes, sizeof(DepartmentType), freeDepartementType);
		free(storeManager->departments);
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
	fprintf(file, "%d\n", storeManager->noOfDepartmentTypes);
	for (int i = 0; i < storeManager->noOfDepartmentTypes; i++) {
		saveDepartmentTypeToTextFile(&storeManager->departments[i], file);
	}
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
	int noOfDepartmentTypes;
	fscanf(file, "%d", &noOfDepartmentTypes);
	fgetc(file);
	storeManager->noOfDepartmentTypes = noOfDepartmentTypes;
	DepartmentType* types = (DepartmentType*)malloc(noOfDepartmentTypes * sizeof(DepartmentType));
	if (!types) {
		printf("error in allocating memory\n");
		return;
	}
	for (int i = 0; i < noOfDepartmentTypes; i++) {
		loadDepartmentTypeFromTextFile(&types[i], file);
	}
	storeManager->departments = types;
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
	fixLoadedStoreManager(storeManager);
}

void fixLoadedStoreManager(StoreManager* storeManager) {
	for (int i = 0; i < storeManager->noOfStores; i++) {
		for (int j = 0; j < storeManager->stores[i]->noOfDepartments; j++) {
			DepartmentType* type = getDepartmentType(storeManager, storeManager->stores[i]->departments[j].type->id);
			printDepartmentType(type); //debug
			if (!type) {
				printf("Department type not found!\n");
				return;
			}
			free(storeManager->stores[i]->departments[j].type);
			storeManager->stores[i]->departments[j].type = type;
		}
		NODE* invoice = &storeManager->stores[i]->invoiceList.head;
		for (int j = 0; j < storeManager->stores[i]->noOfInvoices; j++)
		{
			invoice = invoice->next;
			Invoice* inv = (Invoice*)invoice;
			Employee* emp = getEmployee(storeManager->stores[i], inv->employee->id);
			if (!emp) {
				printf("Employee not found!\n");
				return;
			}
			free(inv->employee);
			inv->employee = emp;
		}
	}
}