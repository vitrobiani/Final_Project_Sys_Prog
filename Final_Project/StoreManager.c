#include "StoreManager.h"

void initStoreManager(StoreManager* storeManager) {
	storeManager->stores = NULL;
	storeManager->noOfStores = 0;
}

void loadSystem(StoreManager* storeManager) {
	printf("Welcome to the system for managing the all-in-one store chain!\n");
	printf("From which file you wish to upload the system?\n");
	for (int i = 0; i < eNoOfLoadOptions; i++) {
		printf("%d. %s\n", i + 1, loadOptionsStr[i]);
	}
	int opt;
	INT_FROM_USER(opt, 0, eNoOfLoadOptions + 1, "Invalid option, please try again.");
	opt--;
	switch (opt)
	{
	case eLoadFromTextFile: {
		initStoreManagerFromTextFile(storeManager, "storeManager.txt");
		break;
	}
	case eLoadFromBinaryFile: {
		initStoreManagerFromBinaryFile(storeManager, "storeManager.bin");
		break;
	}
	}
}

void generateHQ(StoreManager* storeManager) {
	printf("We will now generate the HQ store\n");
	storeManager->stores = (Store**)malloc(sizeof(Store*));
	PRINT_RETURN(storeManager->stores, "error in allocating memory");
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
	int id = generateStoreID(storeManager);
	Store* store = (Store*)malloc(sizeof(Store));
	PRINT_RETURN(store, "error in allocating memory");
	if (!createStore(store, id)) {
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
	storeManager->storeSortOpt = eNone;
	updateAllStoreDepartments(storeManager);
}

void addProductToMainStore(StoreManager* storeManager, int departmentID, Product* product) {
	Department* department = &storeManager->stores[0]->departments[departmentID];
	Product* tmp = (Product*)realloc(department->products, sizeof(Product) * (department->noOfProducts + 1));
	PRINT_RETURN(tmp, "error in reallocating memory");
	department->products = tmp;
	department->products[department->noOfProducts].buyPrice = product->buyPrice;
	department->products[department->noOfProducts].sellPrice = product->sellPrice;
	department->products[department->noOfProducts].name = (char*)malloc(strlen(product->name) + 1);
	PRINT_RETURN(department->products[department->noOfProducts].name, "error in allocating memory");
	strcpy(department->products[department->noOfProducts].name, product->name);
	strcpy(department->products[department->noOfProducts].code, product->code);
	department->products[department->noOfProducts].quantity = 0;
	department->noOfProducts++;
}

void addProductToDepartmentType(StoreManager* storeManager) {
	printDepartmentTypes();
	int departmentTypeID;
	printf("Enter the department type ID: ");
	INT_FROM_USER(departmentTypeID, -1, noOfDepartmentTypes, "Invalid ID, please try again.");
	Product* product = (Product*)malloc(sizeof(Product));
	PRINT_RETURN(product, "error in allocating memory");
	int check;
	do {
		getProductCode(product->code);
		check = checkIfProductCodeExists(storeManager, product->code);
		if (check)
			printf("Product code already exists, please try again.\n");
	} while (check);
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

void printAllChainEmployees(const StoreManager* storeManager) {
	printf("All the employees that work in the chain are:\n");
	for (int i = 0; i < storeManager->noOfStores; i++) {
		printStoreReduced(storeManager->stores[i]);
		printAllEmployees(storeManager->stores[i]);
	}
}

void addEmployeeToStore(StoreManager* storeManager, Store* store)
{
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	PRINT_RETURN(emp, "error in allocating memory for employee");
	printAllChainEmployees(storeManager);
	initEmployee(storeManager, emp);
	addEmployee(store, emp);

}

void initEmployee(const StoreManager* storeManager, Employee* employee) {
	
	employee->id = getEmployeeID(storeManager);
	employee->name = getStrExactName("Enter the employee name: ");
	employee->position = getPosition();
	employee->salary = getSalary();
}

int getEmployeeID(const StoreManager* storeManager) {
	int id;
	printf("Enter the employee ID:(the ID must be unique)\n");
	do {
		scanf("%d", &id);
		if (id <= 0) {
			printf("Invalid ID, please enter a positive number:\n");
		}
	} while (id <= 0 || !isEmployeeIDUnique(storeManager, id));
	return id;
}

int isEmployeeIDUnique(const StoreManager* storeManager, int id)
{
	for (int i = 0; i < storeManager->noOfStores; i++) {
		for (int j = 0; j < storeManager->stores[i]->noOfEmployees; j++) {
			if (storeManager->stores[i]->employees[j].id == id) {
				printf("There is already an employee in the chain with the ID you entered, try again.\n");
				return 0;
			}
		}
	}
	return 1;
}

void makeSale(StoreManager* storeManager, Store* store) {
	PRINT_RETURN(store->noOfEmployees, "no employees in the store");
	PRINT_RETURN(checkIfThereAreProductsInStore(store), "no products in the store");
	int availableProducts = countAvailableProductsInStore(store);
	int numOfProducts = getNumOfProducts(availableProducts);
	Product* products = (Product*)malloc(numOfProducts * sizeof(Product));
	PRINT_RETURN(products, "error in allocating memory for products");
	for (int i = 0; i < numOfProducts; i++) {
		Department* department;
		department = chooseDepartment(store);
		Product* product;
		product = chooseProduct(department);
		int quantity;
		quantity = chooseQuantity(product);
		product->quantity -= quantity;
		products[i].buyPrice = product->buyPrice;
		products[i].sellPrice = product->sellPrice;
		products[i].quantity = quantity;
		strcpy(products[i].code, product->code);
		products[i].name = (char*)malloc(strlen(product->name) + 1);
		PRINT_FREE_RETURN(products[i].name, products, "error in allocating memory for product name.");
		strcpy(products[i].name, product->name);
	}
	Employee* employee = getEmployeeTUI(store);
	Invoice* invoice = (Invoice*)malloc(sizeof(Invoice));
	PRINT_FREE_RETURN(invoice, products, "error in allocating memory for invoice");
	initCustomer(storeManager, &invoice->customer);
	store->noOfInvoices++;
	initInvoice(invoice, store->storeID, employee, products, numOfProducts, generateInvoiceID(store));
	if (!insertNewInvoiceToList(&store->invoiceList, invoice))
		freeInvoice(invoice);
}

void initCustomer(const StoreManager* storeManager, Customer* customer) {
	int check;
	do
	{
		check = 0;
		setCustomerID(customer);
		Customer* tmp = isCustomerIDUnique(storeManager, customer->id);
		if (tmp && getUserChoice()) {
			customer->name = (char*)malloc(strlen(tmp->name) + 1);
			PRINT_RETURN(customer->name, "error in allocating memory");
			strcpy(customer->name, tmp->name);
			customer->contactNumber = tmp->contactNumber;
			return;
		}
		else if (!tmp) {
			check = 1;
		}
	} while (!check);
	setCustomerName(customer);
	setContactNumber(customer);
}

Customer* isCustomerIDUnique(const StoreManager* storeManager, int id)
{
	for (int i = 0; i < storeManager->noOfStores; i++) {
		NODE* tmp = storeManager->stores[i]->invoiceList.head.next;
		while (tmp) {
			Invoice* invoice = (Invoice*)tmp->key;
			if (invoice->customer.id == id) {
				printf("There is already a customer in the chain with the ID you entered.\n");
				return &invoice->customer;
			}
			tmp = tmp->next;
		}
	}
	return NULL;
}

int getUserChoice()
{
	int opt;
	printf("what would you like to do?\n");
	printf("Enter 1 to create a new customer.\n");
	printf("Enter 2 to associate the sale with the existing customer.\n");
	INT_FROM_USER(opt, 0, 3, "Invalid option, please try again.");
	return opt -1;
}


void updateAllStoreDepartments(StoreManager* storeManager) {
	if (storeManager->noOfStores <= 1)
		return;
	for (int i = 1; i < storeManager->noOfStores; i++) {
		for (int j = 0; j < storeManager->stores[i]->noOfDepartments; j++) {
			Department* department = &storeManager->stores[i]->departments[j];
			Department* MainDepartment = &storeManager->stores[0]->departments[j];
			if (department->noOfProducts != MainDepartment->noOfProducts) {
				Product* tmp = (Product*)realloc(department->products, sizeof(Product) * (MainDepartment->noOfProducts));
				PRINT_RETURN(tmp, "error in reallocating memory");
				department->products = tmp;
				for (int k = 0; k < MainDepartment->noOfProducts; k++) {
					if (strcmp(department->products[k].code, MainDepartment->products[k].code) != 0) {
						department->products[k].buyPrice = MainDepartment->products[k].buyPrice;
						department->products[k].sellPrice = MainDepartment->products[k].sellPrice;
						department->products[k].name = (char*)malloc(strlen(MainDepartment->products[k].name) + 1);
						PRINT_RETURN(department->products[k].name, "error in allocating memory");
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
	for (int i = 0; i < storeManager->noOfStores; i++)
	{
		printStoreReduced(storeManager->stores[i]);
	}
	int storeID;
	printf("Enter the store ID: ");
	scanf("%d", &storeID);
	Store* store = getStore(storeManager, storeID);
	if (!store) {
		printf("Store not found, try again.\n");
	}
	return store;
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
	case eRent: {
		compare = compareStoreByRent;
		break;
	}
	case eLocation: {
		compare = compareStoreByLocation;
		break;
	}
	}
	if (compare != NULL)
		qsort(storeManager->stores, storeManager->noOfStores, sizeof(Store*), compare);
}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	for (int i = 1; i < eNofSortOpt; i++)
		printf("Enter %d for %s\n", i, sortOptStr[i]);
	INT_FROM_USER(opt, 0, eNofSortOpt, "Invalid option, please try again.");

	return (eSortOption)opt;
}

void findStore(const StoreManager* storeManager) {
	PRINT_RETURN(storeManager->stores, "system not initialized");
	int(*compare)(const void* store1, const void* store2) = NULL;
	Store store = { 0 };
	Store* pStore = &store;
	switch (storeManager->storeSortOpt) {
	case eID: {
		printf("Enter store's ID number:\n");
		scanf("%d", &store.storeID);
		compare = compareStoreByID;
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
	if (compare) {
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

	for (int i = 0; i < storeManager->noOfStores; i++)
	{
		printStore(storeManager->stores[i]);
	}
}

void printSystemDetails(const StoreManager* storeManager) {
	printf("The system has %d stores.\n", storeManager->noOfStores);
	for (int i = 0; i < storeManager->noOfStores; i++) {
		printStoreFull(storeManager->stores[i]);
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

//If there are multiple salesmen with the same sales amount, the salesman with the highest profit will be chosen.
//If there are multiple salesmen with the same sales amount and profit(really unlikely), the first one will be chosen.
void findChainBestSalesMan(const StoreManager* storeManager) {
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
				if (bestSeller && saleAmount == maxSales && bestProfit <= maxProfit)
					continue;
				maxSales = saleAmount;
				maxProfit = bestProfit;
				bestSeller = tmp;
				storeIndex = i;
			}
		}
	}
	if (!bestSeller) {
		printf("The chain had no sales in %d/%d\n", month, year);
		return;
	}
	printf("The best salesman in the chain for the year %d/%d is: %s.\n", month, year, bestSeller->name);
	printf("The store he works in is in: %s.\n", storeManager->stores[storeIndex]->location);
	printf("His total sales amount is: %d\n", maxSales);
	printf("His total profit is: %d\n", maxProfit);
}

Product* getChainBestSellerProduct(const StoreManager* storeManager, int* quantity, int year, int mouth) {
	Product* bestSeller = NULL;
	int maxQuantity = 0;
	for (int i = 0; i < noOfDepartmentTypes; i++) {
		for (int j = 0; j < storeManager->stores[0]->departments[i].noOfProducts; j++) {
			int totalQuantity = 0;
			for (int k = 0; k < storeManager->noOfStores; k++) {
				NODE* tmp = storeManager->stores[k]->invoiceList.head.next;
				while (tmp) {
					Invoice* invoice = (Invoice*)tmp->key;
					if (invoice->timeOfSale.year == year && invoice->timeOfSale.month == mouth) {
						for (int l = 0; l < invoice->numOfProducts; l++) {
							if (strcmp(invoice->products[l].code, storeManager->stores[0]->departments[i].products[j].code) == 0) {
								totalQuantity += invoice->products[l].quantity;
							}
						}
					}
					tmp = tmp->next;
				}
			}
			int profit = (storeManager->stores[0]->departments[i].products[j].sellPrice - storeManager->stores[0]->departments[i].products[j].buyPrice) * totalQuantity;
			if (totalQuantity >= maxQuantity && totalQuantity > 0) {
				if (bestSeller && totalQuantity == maxQuantity && profit <= (bestSeller->sellPrice - bestSeller->buyPrice) * maxQuantity)
					continue;
				maxQuantity = totalQuantity;
				bestSeller = &storeManager->stores[0]->departments[i].products[j];
			}
		}
	}
	*quantity = maxQuantity;
	return bestSeller;
}

//If there are multiple products with the same quantity sold, the product with the highest profit will be chosen.
//If there are multiple products with the same quantity sold and profit(really unlikely), the first one will be chosen.
void findChainBestSellerProduct(const StoreManager* storeManager) {
	int year = getYear();
	int month = getMonth();
	int quantity = 0;
	Product* bestSeller = getChainBestSellerProduct(storeManager, &quantity, year, month);
	if (!bestSeller) {
		printf("The chain had no sales in %d/%d\n", month, year);
		return;
	}
	int profit = (bestSeller->sellPrice - bestSeller->buyPrice) * quantity;
	printf("The best-selling product in the chain for %d/%d is: %s\n", month, year, bestSeller->name);
	printf("The total quantity sold is %d units, generating a total revenue of %d and %d profit\n", quantity, bestSeller->sellPrice * quantity, profit);
}



int saveStoreManagerToTextFile(const StoreManager* storeManager, const char* fileName) {
	FILE* file = fopen(fileName, "w");
	PRINT_RETURN_INT(file, 0 ,"error in opening file");

	if (!writeIntToTextFile(storeManager->noOfStores, file, "error in writing number of stores to file1\n")) return 0;
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if(!saveStoreToTextFile(storeManager->stores[i], file)) return 0;
	}
	fclose(file);
	return 1;
}

int loadStoreManagerFromTextFile(StoreManager* storeManager, const char* fileName) {
	FILE* file = fopen(fileName, "r");
	PRINT_RETURN_INT(file, 0,"error in opening file");

	if (!readIntFromTextFile(&storeManager->noOfStores, file, "error in reading number of stores from file\n")) return 0;
	Store** stores = (Store**)malloc(storeManager->noOfStores * sizeof(Store*));
	PRINT_RETURN_INT(stores, 0,"error in allocating memory1");

	for (int i = 0; i < storeManager->noOfStores; i++) {
		Store* store = (Store*)malloc(sizeof(Store));
		PRINT_RETURN_INT(store, 0, "error in allocating memory");
		int id = 0;
		if (!readIntFromTextFile(&id, file, "Error reading store ID from text file.")) return 0;
		initStore(store, id);
		if(!loadStoreFromTextFile(store, file)) return 0;
		stores[i] = store;
	}
	storeManager->stores = stores;
	fclose(file);
	return 1;
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
		storeManager->stores = (Store**)malloc(storeManager->noOfStores * sizeof(Store*));
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

void initStoreManagerFromTextFile(StoreManager* storeManager, const char* fileName) {
	if (!loadStoreManagerFromTextFile(storeManager, fileName)) {
		initStoreManager(storeManager);
		generateHQ(storeManager);
	}
}

void initStoreManagerFromBinaryFile(StoreManager* storeManager, const char* fileName)
{
	if (!loadStoreManagerFromBinaryFile(storeManager, fileName)) {
		initStoreManager(storeManager);
		generateHQ(storeManager);
	}
}

