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
		int check = loadStoreManagerFromBinaryFile(storeManager, "storeManager.bin");
		printf("check: %d\n", check);
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

void addProductToMainStore(StoreManager* storeManager, int departmentID ,Product* product) {
	if (storeManager->stores == NULL) {
		printf("system not initialized\n");
		return;
	}
	Department* department = &storeManager->stores[0]->departments[departmentID];
	Product* tmp = (Product*)realloc(department->products, sizeof(Product) * (department->noOfProducts + 1));
	if (!tmp) {
		printf("error in reallocating memory\n");
		return;
	}
	department->products = tmp;
	department->products[department->noOfProducts].buyPrice = product->buyPrice;
	department->products[department->noOfProducts].sellPrice = product->sellPrice;
	department->products[department->noOfProducts].name = (char*)malloc(strlen(product->name) + 1);
	if (!department->products[department->noOfProducts].name) {
		printf("error in allocating memory\n");
		return;
	}
	strcpy(department->products[department->noOfProducts].name, product->name);
	strcpy(department->products[department->noOfProducts].code, product->code);
	department->products[department->noOfProducts].quantity = 0;
	department->noOfProducts++;
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
	int check;
	do {
		getProductCode(product->code);
		check = checkIfProductCodeExists(storeManager, product->code);
		if(check)
			printf("Product code already exists, please try again.\n");
	}while(check);
	initProduct(product);
	printProduct(product);
	addProductToMainStore(storeManager, departmentTypeID, product);
	updateAllStoreDepartments(storeManager);
	free(product->name);
	free(product);
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
				PRINT_RETURN(tmp, "error in reallocating memory");
				department->products = tmp;
				for (int k = 0; k < MainDepartment->noOfProducts; k++) {
					if (strcmp(department->products[k].code, MainDepartment->products[k].code) != 0){
						department->products[k].buyPrice = MainDepartment->products[k].buyPrice;
						department->products[k].sellPrice = MainDepartment->products[k].sellPrice;
						department->products[k].name = (char*)malloc(strlen(MainDepartment->products[k].name) + 1);
						if (!department->products[k].name) {
							printf("error in allocating memory\n");
							return;
						}
						strcpy(department->products[k].name, MainDepartment->products[k].name);
						strcpy(department->products[k].code, MainDepartment->products[k].code);
						department->products[k].quantity = 0;
					}
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
	PRINT_RETURN(storeManager->stores, "system not initialized");
	int totalProfit = 0;
	for (int i = 0; i < storeManager->noOfStores; i++) {
		totalProfit += calculateStoreProfit(storeManager->stores[i]);
	}
	printf("Total profit for the year %d: %d\n", MIN_YEAR, totalProfit);
}

void sortAllStoresBy(StoreManager* storeManager) {
	PRINT_RETURN(storeManager->stores, "system not initialized");
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
	PRINT_RETURN(storeManager->stores, "system not initialized");
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
		printf("Enter store's profit:\n");
		scanf("%d", &store.profit);
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
	PRINT_RETURN(storeManager->stores, "no stores!");

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
			freeStore(storeManager->stores[i]);
			free(storeManager->stores[i]);
		}
		free(storeManager->stores);
	}
}

void findChainBestSalesMan(const StoreManager* storeManager){
//If there are multiple salesmen with the same sales amount, the salesman with the highest profit will be chosen.
//If there are multiple salesmen with the same sales amount and profit(really unlikely), the first one will be chosen.
	PRINT_RETURN(storeManager->stores, "system not initialized");
	int year = getYear();
	int month = getMonth();
	int saleAmount = 0;
	int maxSales = 0;
	int bestProfit = 0;
	int maxProfit = 0;
	int storeIndex;
	Employee* bestSeller = NULL;
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (storeManager->stores[i]->noOfInvoices > 0) {
			Employee* tmp = getBestSalesMan(storeManager->stores[i], &saleAmount, &bestProfit, year, month);
			if (saleAmount >= maxSales && saleAmount > 0) {
				if(bestSeller && saleAmount == maxSales && bestProfit <= maxProfit)
					continue;
				maxSales = saleAmount;
				maxProfit = bestProfit;
				bestSeller = tmp;
				storeIndex = i;
			}
		}
	}
	if (!bestSeller) {
		printf("The chain had no sales in %d\n", year);
		return;
	}
		printf("The best salesman in the chain for the year %d/%d is: %s.\n", month, year, bestSeller->name);
		printf("The store he works in is in: %s.\n", storeManager->stores[storeIndex]->location);
		printf("His total sales amount is: %d\n", maxSales);
		printf("His total profit is: %d\n", maxProfit);
}

void findChainBestSellerProduct(const StoreManager* storeManager) {
	PRINT_RETURN(storeManager->stores, "system not initialized");
	int year = getYear();
	int month = getMonth();
	int quantity = 0;
	int maxQuantity = 0;
	int maxProfit = 0;
	int storeIndex;
	Product* bestSeller = NULL;
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (storeManager->stores[i]->noOfInvoices > 0) {
			Product* tmp = getBestSellerProduct(storeManager->stores[i], &quantity, year, month);
			int profit = (tmp->sellPrice - tmp->buyPrice) * quantity;
			if (quantity >= maxQuantity && quantity > 0) {
				if(bestSeller && quantity == maxQuantity && profit <= maxProfit)
					continue;
				maxQuantity = quantity;
				maxProfit = profit;
				bestSeller = tmp;
				storeIndex = i;
			}
		}
	}
	if (!bestSeller) {
		printf("The chain had no sales in %d/%d\n", month, year);
		return;
	}
	printf("The best-selling product in the chain for %d/%d is: %s\n", month, year, bestSeller->name);
	printf("The total quantity sold is %d units, generating a total revenue of %d and %d profit\n", quantity, bestSeller->sellPrice * maxQuantity, maxProfit);
	printf("The store it is in is in: %s.\n", storeManager->stores[storeIndex]->location);
}



void saveStoreManagerToTextFile(const StoreManager* storeManager, const char* fileName) {
	if (storeManager == NULL) {
		return;
	}
	FILE* file = fopen(fileName, "w");
	PRINT_RETURN(file, "error in opening file");

	fprintf(file, "%d\n", storeManager->noOfStores);
	for (int i = 0; i < storeManager->noOfStores; i++) {
		saveStoreToTextFile(storeManager->stores[i], file);
	}
	fclose(file);
}

void loadStoreManagerFromTextFile(StoreManager* storeManager, const char* fileName) {
	FILE* file = fopen(fileName, "r");
	PRINT_RETURN(file, "error in opening file");

	int noOfStores;
	fscanf(file, "%d", &noOfStores);
	fgetc(file);
	storeManager->noOfStores = noOfStores;
	Store** stores = (Store**)malloc(noOfStores * sizeof(Store*));
	PRINT_RETURN(stores, "error in allocating memory");

	for (int i = 0; i < noOfStores; i++) {
		Store* store = (Store*)malloc(sizeof(Store));
		initStore(store, 0);
		PRINT_RETURN(store, "error in allocating memory");
		loadStoreFromTextFile(store, file);
		stores[i] = store;
	}
	storeManager->stores = stores;
	fclose(file);
}

int saveStoreManagerToBinaryFile(const StoreManager* storeManager, const char* fileName) {
	FILE* file = fopen(fileName, "wb");
	if (!file) {
		printf("error in opening file\n");
		return 0;
	}
	if (!writeIntToFile(storeManager->noOfStores, file, "error in writing number of stores to file\n"))
		CLOSE_RETURN_INT(file, 0);
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (!saveStoreToBinaryFile(storeManager->stores[i], file))
			CLOSE_RETURN_INT(file, 0);
	}
	CLOSE_RETURN_INT(file, 1);
}

int createStoreArr(StoreManager* storeManager) {
	if (storeManager->noOfStores > 0) {
		storeManager->stores = (Store**)malloc(storeManager->noOfStores*sizeof(Store*));
		if (!storeManager->stores) {
			printf("error in allocating memory\n");
			return 0;
		}
	}
	else
		storeManager->stores = NULL;

	for (int i = 0; i < storeManager->noOfStores; i++)
	{
		storeManager->stores[i] = (Store*)calloc(1, sizeof(Store));
		if (!storeManager->stores[i]) {
			printf("error in allocating memory\n");
			return 0;
		}
	}
	return 1;
}

int loadStoreManagerFromBinaryFile(StoreManager* storeManager, const char* fileName) {
	FILE* file = fopen(fileName, "rb");
	if (!file) {
		printf("error in opening file\n");
		return 0;
	}
	if (!readIntFromFile(&storeManager->noOfStores, file, "error in reading number of stores from file\n"))
		CLOSE_RETURN_INT(file, 0);
	if (!createStoreArr(storeManager))
		CLOSE_RETURN_INT(file, 0);
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (!loadStoreFromBinaryFile(storeManager->stores[i], file)) {
			for (int j = 0; j < i; j++) {
				freeStore(storeManager->stores[j]);
				free(storeManager->stores[j]);
			}
			free(storeManager->stores);
			CLOSE_RETURN_INT(file, 0);
		}
	}
	CLOSE_RETURN_INT(file, 1);
}

