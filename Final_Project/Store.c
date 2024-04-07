#include "Store.h"

int createStore(Store* store, int id) {
	store->location = getStrExactName("Enter the location of the store: ");
	capitalizeFirstLetter(store->location);

	if (!initStore(store, id))
		return 0;
	printf("Enter the store rent: ");
	int rent;
	do {
		scanf("%d", &rent);
		if (rent <= 0)
			printf("rent must be a positive number, try again.\n");
	} while (rent <= 0);
	store->rent = rent;
	return 1;
}

int initStore(Store* store, int id) {
	store->storeID = id;
	store->employees = NULL;
	store->noOfEmployees = 0;
	store->noOfInvoices = 0;
	store->profit = 0;
	store->noOfDepartments = noOfDepartmentTypes;

	initDepartmentArray(store);

	if (!L_init(&store->invoiceList)) {
		return 0;
	}
	return 1;
}

void initDepartmentArray(Store* store) {
	for (int i = 0; i < noOfDepartmentTypes; i++)
	{
		initDepartment(&store->departments[i], i);
	}
}

void initEmployee(Store* store, Employee* employee) {
	if (store->noOfEmployees > 0) {
		printf("All the employees that work in the store are:\n");
		printAllEmployees(store);
	}
	employee->id = getEmployeeID(store);
	employee->name = getStrExactName("Enter the employee name: ");
	employee->position = getPosition();
	employee->salary = getSalary();
}

int getEmployeeID(Store* store) {
	int id;
	printf("Enter the employee ID:(the ID must be unique)\n");
	do {
		scanf("%d", &id);
		if (id <= 0) {
			printf("Invalid ID, please enter a positive number:\n");
		}
	} while (id <= 0 || !isEmployeeIDUnique(store, id));
	return id;
}

int isEmployeeIDUnique(Store* store, int id)
{
	for (int i = 0; i < store->noOfEmployees; i++) {
		if (store->employees[i].id == id) {
			printf("There is already an employee in the store with the ID you entered, try again.\n");
			return 0;
		}
	}
	return 1;
}

void addEmployee(Store* store) {
	if (store == NULL) {
		return;
	}
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	PRINT_RETURN(emp, "error in allocating memory for employee");

	initEmployee(store, emp);
	Employee* tmp = (Employee*)realloc(store->employees, (store->noOfEmployees + 1) * sizeof(Employee));
	if (!tmp) {
		free(emp);
		return;
	}
	store->employees = tmp;
	store->employees[store->noOfEmployees].id = emp->id;
	store->employees[store->noOfEmployees].name = (char*)malloc(strlen(emp->name) + 1);
	if (!store->employees[store->noOfEmployees].name) {
		free(emp);
		return;
	}
	strcpy(store->employees[store->noOfEmployees].name, emp->name);
	store->employees[store->noOfEmployees].salary = emp->salary;
	store->employees[store->noOfEmployees].position = emp->position;
	store->noOfEmployees++;
	free(emp->name);
	free(emp);
}

Department* getDepartment(Store* store, int departmentID) {
	for (int i = 0; i < store->noOfDepartments; i++) {
		if (store->departments[i].type == departmentID) {
			return &store->departments[i];
		}
	}
	return NULL;
}

Department* getDepartmentTUI(Store* store) {
	printAllDepartments(store);
	int departmentID;
	printf("Enter the department ID: ");
	Department* department;
	INT_FROM_USER(departmentID, -1, noOfDepartmentTypes, "no such department, try again.");
	department = getDepartment(store, departmentID);
	return department;
}

void addProductToDepartment(Store* store) {
	Department* department = getDepartmentTUI(store);
	if (department->noOfProducts == 0) {
		printf("No products in this department\n");
		return;
	}
	addToProduct(department);
}

Employee* getEmployee(Store* store, int employeeID) {
	for (int i = 0; i < store->noOfEmployees; i++) {
		if (store->employees[i].id == employeeID) {
			return &store->employees[i];
		}
	}
	return NULL;
}

Employee* getEmployeeTUI(Store* store) {
	printAllEmployees(store);
	int employeeID;
	printf("Enter the employee ID: ");
	Employee* employee;
	do {
		scanf("%d", &employeeID);
		employee = getEmployee(store, employeeID);
		if (!employee)
			printf("no such employee, try again.\n");
	} while (!employee);
	return employee;
}

int checkIfThereAreProductsInStore(Store* store) {
	if (store == NULL) {
		return 0;
	}
	for (int i = 0; i < store->noOfDepartments; i++) {
		if (store->departments[i].noOfProducts > 0 && checkDepartmentStock(&store->departments[i])) {
			return 1;
		}
	}
	return 0;
}

int countAvailableProductsInStore(Store* store)
{
	int sum = 0;
	for (int i = 0; i < store->noOfDepartments; i++) {
		for (int j = 0; j < store->departments[i].noOfProducts; j++) {
			if (store->departments[i].products[j].quantity > 0)
				sum++;
		}
	}
	return sum;
}

int getNumOfProducts(int availableProducts)
{
	int numOfProducts;
	printf("There are %d available products in the store how many do you want to buy? ", availableProducts);
	do {
		scanf("%d", &numOfProducts);
		if (numOfProducts <= 0 || numOfProducts > availableProducts) {
			printf("number of products must be between 1 - %d, try again.\n", availableProducts);
		}
	} while (numOfProducts <= 0 || numOfProducts > availableProducts);

	return numOfProducts;
}

int insertNewInvoiceToList(LIST* pList, Invoice* pInvoice)
{
	NODE* pN = pList->head.next;
	NODE* pPrev = &pList->head;
	while (pN)
	{
		if (((Invoice*)pN->key)->invoiceID == pInvoice->invoiceID)
		{
			printf("Invoice with the same ID already exists\n");
			return 0;
		}
		if (((Invoice*)pN->key)->invoiceID > pInvoice->invoiceID)
		{
			if (!L_insert(pPrev, pInvoice)) {
				printf("error in inserting the invoice to the list\n");
				return 0;
			}
			return 1;
		}
		pPrev = pN;
		pN = pN->next;
	}
	if (!L_insert(pPrev, pInvoice)) {
		printf("error in inserting the invoice to the list\n");
		return 0;
	}
	return 1;
}

Department* chooseDepartment(Store* store)
{
	Department* department;
	do {
		department = getDepartmentTUI(store);
		if (!checkDepartmentStock(department)) {
			printf("no products in this department\n");
		}
	} while (!checkDepartmentStock(department));
	return department;
}

Product* chooseProduct(Department* department)
{
	printAllProducts(department);
	Product* product;
	char code[MAX_STR_LEN];
	printf("Enter the product code: ");
	do {
		myGets(code, MAX_STR_LEN);
		product = getProduct(department, code);
		if (!product || product->quantity == 0)
			printf("no such product or quantity is 0, try again.\n");
	} while (!product || product->quantity == 0);
	return product;
}

int chooseQuantity(Product* product)
{
	int quantity;
	printf("Enter the quantity: ");
	do {
		scanf("%d", &quantity);
		if (quantity <= 0 || product->quantity < quantity)
			printf("quantity must be between 1 - %d, try again.\n", product->quantity);
	} while (quantity <= 0 || product->quantity < quantity);
	return quantity;
}



void makeSale(Store* store) {
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
	initCustomer(&invoice->customer);
	store->noOfInvoices++;
	initInvoice(invoice, store->storeID, employee, products, numOfProducts, generateInvoiceID(store));
	if (!insertNewInvoiceToList(&store->invoiceList, invoice))
		freeInvoice(invoice);
}

int generateInvoiceID(Store* store) {
	int maxID = 0;
	NODE* tmp = store->invoiceList.head.next;
	while (tmp) {
		if (((Invoice*)tmp->key)->invoiceID > maxID) {
			maxID = ((Invoice*)tmp->key)->invoiceID;
		}
		tmp = tmp->next;
	}
	return maxID + 1;
}

void printAllInvoices(const Store* store) {
	if (store->noOfInvoices == 0) {
		printf("There are no invoices.\n");
		return;
	}
	L_print(&store->invoiceList, printInvoice);
}

int compareStoreByID(const void* store1, const void* store2) {
	
	const Store* store1_ = *(const Store**)store1;
	const Store* store2_ = *(const Store**)store2;
	return (store1_)->storeID - (store2_)->storeID;
}

int compareStoreByProfit(const void* store1, const void* store2) {

	const Store* store1_ = *(const Store**)store1;
	const Store* store2_ = *(const Store**)store2;
	return store2_->profit - store1_->profit;
}

int compareStoreByRent(const void* store1, const void* store2) {
	
	const Store* store1_ = *(const Store**)store1;
	const Store* store2_ = *(const Store**)store2;
	return (store1_)->rent - (store2_)->rent;
}

int compareStoreByLocation(const void* store1, const void* store2) {
	
	const Store* store1_ = *(const Store**)store1;
	const Store* store2_ = *(const Store**)store2;
	return strcmp(store1_->location, store2_->location);
}

void printAllEmployees(const Store* store) {
	if (store->noOfEmployees == 0) {
		printf("There are no employees in the store.\n");
		return;
	}
	for (int i = 0; i < store->noOfEmployees; i++) {
		printEmployee(&store->employees[i]);
	}
	printf("\n");
}

void printAllDepartments(const Store* store) {
	for (int i = 0; i < noOfDepartmentTypes; i++) {
		printDepartmentFull(&store->departments[i]);
	}
	printf("\n");
}

void printAllProductsInStore(const Store* store) {
	for (int i = 0; i < store->noOfDepartments; i++) {
		printAllProducts(&store->departments[i]);
	}
}

void printStoreReduced(const Store* store) {
	printf("\n# Store ID: %d\t", store->storeID);
	printf("Location: %s\n", store->location);
}

void printStore(const Store* store) {
	printf("\n# Store ID: %d\t", store->storeID);
	printf("Location: %s\n", store->location);
	printf("\tRent: %d\t Profit: %d\n", store->rent, store->profit);
	printf("\tNumber of employees: %d\n", store->noOfEmployees);
}

void freeStore(Store* store) {
	generalArrayFunction(store->employees, store->noOfEmployees, sizeof(Employee), freeEmployee);
	free(store->employees);
	generalArrayFunction(store->departments, store->noOfDepartments, sizeof(Department), freeDepartment);
	L_free(&store->invoiceList, freeInvoice);
	free(store->location);
}

Employee* getBestSalesMan(const Store* store, int* saleAmount, int* bestProfit, int year, int month) {
	int max = 0;
	int maxProfit = 0;
	Employee* bestSalesMan = NULL;
	for (int i = 0; i < store->noOfEmployees; i++) {
		NODE* tmp = store->invoiceList.head.next;
		int sum = 0;
		int profit = 0;
		while (tmp) {
			Invoice* invoice = (Invoice*)tmp->key;
			if (invoice->employee->id == store->employees[i].id && invoice->timeOfSale.year == year && invoice->timeOfSale.month == month) {
				sum += invoice->saleAmount;
				profit += calculateProfit(invoice);
			}
			tmp = tmp->next;
		}
		if (sum >= max && sum > 0) {
			if (bestSalesMan && sum == max && profit <= maxProfit)
				continue;
			max = sum;
			maxProfit = profit;
			bestSalesMan = &store->employees[i];
		}
	}
	*saleAmount = max;
	*bestProfit = maxProfit;
	return bestSalesMan;
}

//If there are multiple salesmen with the same sales amount, the salesman with the highest profit will be chosen.
//If there are multiple salesmen with the same sales amount and profit(really unlikely), the first one will be chosen.
void findBestSalesMan(const Store* store) {
	int year = getYear();
	int month = getMonth();
	int saleAmount;
	int profit;
	Employee* bestSalesMan = getBestSalesMan(store, &saleAmount, &profit, year, month);
	if (!bestSalesMan) {
		printf("The store had no sales in %d/%d\n", month, year);
		return;
	}
	printf("The best salesman in the store for %d/%d is: %s\n", month, year, bestSalesMan->name);
	printf("His total sales amount is: %d\n", saleAmount);
	printf("His total profit is: %d\n", profit);
}

Product* getBestSellerProduct(const Store* store, int* quantity, int year, int mouth) {
	int max = 0;
	Product* bestSeller = NULL;
	for (int i = 0; i < store->noOfDepartments; i++) {
		for (int j = 0; j < store->departments[i].noOfProducts; j++) {
			NODE* tmp = store->invoiceList.head.next;
			int sum = 0;
			while (tmp) {
				Invoice* invoice = (Invoice*)tmp->key;
				if (invoice->timeOfSale.year == year && invoice->timeOfSale.month == mouth) {
					for (int k = 0; k < invoice->numOfProducts; k++) {
						if (strcmp(invoice->products[k].code, store->departments[i].products[j].code) == 0) {
							sum += invoice->products[k].quantity;
						}
					}
				}
				tmp = tmp->next;
			}
			int profit = store->departments[i].products[j].sellPrice - store->departments[i].products[j].buyPrice;
			if (sum >= max && sum > 0) {
				if (bestSeller && sum == max && profit <= bestSeller->sellPrice - bestSeller->buyPrice)
					continue;
				max = sum;
				bestSeller = &store->departments[i].products[j];
			}
		}
	}
	*quantity = max;
	return bestSeller;
}

//If there are multiple products with the same quantity sold, the product with the highest profit will be chosen.
//If there are multiple products with the same quantity sold and profit(really unlikely), the first one will be chosen.
void findBestSellerProduct(const Store* store) {
	int year = getYear();
	int month = getMonth();
	int quantity;
	Product* bestSeller = getBestSellerProduct(store, &quantity, year, month);
	if (!bestSeller) {
		printf("The store had no sales in %d/%d.\n", month, year);
		return;
	}
	int profit = (bestSeller->sellPrice - bestSeller->buyPrice) * quantity;
	printf("The best-selling product in the store for %d/%d is: %s\n", month, year, bestSeller->name);
	printf("The total quantity sold is %d units, generating a total revenue of %d and %d profit\n", quantity, bestSeller->sellPrice * quantity, profit);
}

int getYear()
{
	int year;
	printf("Enter the year: ");
	INT_FROM_USER(year, MIN_YEAR -1, MAX_YEAR +1, "\nYear must be between 2024 - 9999, try again.");
	return year;
}

int getMonth()
{
	int month;
	printf("Enter the month: ");
	INT_FROM_USER(month, 0, 13, "\nMonth must be between 1 - 12, try again.");
	return month;
}

void saveStoreToTextFile(const Store* store, FILE* file) {
	fprintf(file, "%d\n", store->storeID);
	fprintf(file, "%s\n", store->location);
	fprintf(file, "%d\n", store->rent);
	fprintf(file, "%d\n", store->profit);

	fprintf(file, "%d\n", store->noOfEmployees);
	for (int i = 0; i < store->noOfEmployees; i++) {
		saveEmployeeToTextFile(&store->employees[i], file);
	}

	fprintf(file, "%d\n", store->noOfDepartments);
	for (int i = 0; i < store->noOfDepartments; i++) {
		saveDepartmentToTextFile(&store->departments[i], file);
	}
	fprintf(file, "%d\n", store->noOfInvoices);
	NODE* tmp = store->invoiceList.head.next;
	while (tmp)
	{
		saveInvoiceToTextFile((Invoice*)tmp->key, file);
		tmp = tmp->next;
	}
}

void loadStoreFromTextFile(Store* store, FILE* file) {
	readIntFromTextFile(&store->storeID, file, "Error reading store ID from text file.");
	char tmp[MAX_STR_LEN];
	myGetsFile(tmp, MAX_STR_LEN, file);
	store->location = getDynStr(tmp);
	readIntFromTextFile(&store->rent, file, "Error reading store rent from text file.");
	readIntFromTextFile(&store->profit, file, "Error reading store profit from text file.");
	readIntFromTextFile(&store->noOfEmployees, file, "Error reading number of employees from text file.");
	store->employees = (Employee*)malloc(store->noOfEmployees * sizeof(Employee));
	PRINT_RETURN(store->employees, "error in allocating memory for employees");
	for (int i = 0; i < store->noOfEmployees; i++) {
		loadEmployeeFromTextFile(&store->employees[i], file);
	}
	readIntFromTextFile(&store->noOfDepartments, file, "Error reading number of departments from text file.");
	if (!store->departments)
		return;
	for (int i = 0; i < store->noOfDepartments; i++) {
		loadDepartmentFromTextFile(&store->departments[i], file);
	}
	int noOfInvoices;
	readIntFromTextFile(&noOfInvoices, file, "Error reading number of invoices from text file.");
	store->noOfInvoices = noOfInvoices;
	for (int i = 0; i < noOfInvoices; i++) {
		Invoice* invoice = (Invoice*)malloc(sizeof(Invoice));
		PRINT_RETURN(invoice, "error in allocating memory for invoice");
		loadInvoiceFromTextFile(invoice, file);
		Employee* employee = getEmployee(store, invoice->employee->id);
		free(invoice->employee);
		invoice->employee = employee;
		insertNewInvoiceToList(&store->invoiceList, invoice);
	}
}

int saveStoreToBinaryFile(const Store* store, FILE* file) {
	if (!writeIntToFile(store->storeID, file, "Error writing store ID to file\n"))
		return 0;
	if (!writeStringToFile(store->location, file, "Error writing store location to file\n"))
		return 0;
	if (!writeIntToFile(store->rent, file, "Error writing store rent to file\n"))
		return 0;
	if (!writeIntToFile(store->profit, file, "Error writing store profit to file\n"))
		return 0;
	if (!writeIntToFile(store->noOfEmployees, file, "Error writing number of employees to file\n"))
		return 0;
	for (int i = 0; i < store->noOfEmployees; i++) {
		if (!saveEmployeeToBinaryFile(&store->employees[i], file))
			return 0;
	}
	if (!writeIntToFile(store->noOfDepartments, file, "Error writing number of departments to file\n"))
		return 0;
	for (int i = 0; i < store->noOfDepartments; i++) {
		if (!saveDepartmentToBinaryFile(&store->departments[i], file))
			return 0;
	}
	if (!writeIntToFile(store->noOfInvoices, file, "Error writing number of invoices to file\n"))
		return 0;
	NODE* tmp = store->invoiceList.head.next;
	while (tmp)
	{
		if (!saveInvoiceToBinaryFile((Invoice*)tmp->key, file))
			return 0;
		tmp = tmp->next;
	}
	return 1;
}

int createEmployeeArr(Store* store) {
	store->employees = (Employee*)malloc(sizeof(Employee) * store->noOfEmployees);
	if (!store->employees) {
		puts("Error allocating memory for employees");
		return 0;
	}
	return 1;
}

int loadEmployeeArrFromBinaryFile(Store* store, FILE* file)
{
	if (!readIntFromFile(&store->noOfEmployees, file, "Error reading number of employees from file\n"))
		return 0;
	if (!createEmployeeArr(store))
		return 0;
	for (int i = 0; i < store->noOfEmployees; i++) {
		if (!loadEmployeeFromBinaryFile(&store->employees[i], file))
			return 0;
	}
	return 1;
}

int loadDepartmentArrFromBinaryFile(Store* store, FILE* file)
{
	if (!readIntFromFile(&store->noOfDepartments, file, "Error reading number of departments from file\n"))
		return 0;
	for (int i = 0; i < store->noOfDepartments; i++) {
		if (!loadDepartmentFromBinaryFile(&store->departments[i], file))
			return 0;
	}
	return 1;
}

int loadInvoiceListFromBinaryFile(Store* store, FILE* file)
{
	if (!readIntFromFile(&store->noOfInvoices, file, "Error reading number of invoices from file\n"))
		return 0;
	for (int i = 0; i < store->noOfInvoices; i++) {
		Invoice* invoice = (Invoice*)malloc(sizeof(Invoice));
		if (!invoice) {
			printf("Error allocating memory for invoice\n");
			return 0;
		}
		if (!loadInvoiceFromBinaryFile(invoice, file)) {
			free(invoice);
			return 0;
		}
		Employee* employee = getEmployee(store, invoice->employee->id);
		free(invoice->employee);
		invoice->employee = employee;
		insertNewInvoiceToList(&store->invoiceList, invoice);
	}
	return 1;
}

int loadStoreFromBinaryFile(Store* store, FILE* file) {
	if (!readIntFromFile(&store->storeID, file, "Error reading store ID from file\n"))
		return 0;
	store->location = readStringFromFile(file, "Error reading store location from file\n");
	if (!store->location)
		return 0;
	if (!readIntFromFile(&store->rent, file, "Error reading store rent from file\n"))
		return 0;
	if (!readIntFromFile(&store->profit, file, "Error reading store profit from file\n"))
		return 0;
	if(!loadEmployeeArrFromBinaryFile(store, file))
		return 0;
	if(!loadDepartmentArrFromBinaryFile(store, file))
		return 0;
	if(!loadInvoiceListFromBinaryFile(store, file))
		return 0;
	return 1;
}
