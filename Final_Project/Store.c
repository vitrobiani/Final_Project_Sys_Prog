#include "Store.h"

int createStore(Store* store, int id) {
	store->location = getStrExactName("Enter the location of the store: ");

	if(initStore(store, id)){
		return 0;
	}
	
	printf("Enter the store yearly rent: ");
	int rent;
	do{
		scanf("%d", &rent);
		if (rent <= 0)
		{
			printf("rent must be a positive number");
		}
	} while (rent <= 0);
	store->rent = rent;
	calculateStoreProfit(store);

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

	if(L_init(&store->invoiceList)) {
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
	if (store->noOfEmployees > 0){
		printf("All the employees who work in the store are:\n");
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
	if (emp == NULL) {
		return;
	}
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
	calculateStoreProfit(store);
}

Department* getDepartment(Store* store, int departmentID) {
	if (store == NULL) {
		return NULL;
	}
	for (int i = 0; i < store->noOfDepartments; i++) {
		if (store->departments[i].type == departmentID) {
			return &store->departments[i];
		}
	}
	return NULL;
}

Department* getDepartmentTUI(Store* store) {
	if (store == NULL) {
		return NULL;
	}
	printAllDepartments(store);
	int departmentID;
	printf("Enter the department ID: ");
	Department* department;
	do {
		scanf("%d", &departmentID);
		if (departmentID < 0 || departmentID >= noOfDepartmentTypes)
			printf("no such department, try again.\n");
	} while (departmentID < 0 || departmentID >= noOfDepartmentTypes);
	department = getDepartment(store, departmentID);
	return department;
}

void addProductToDepartment(Store* store) {
	if (store == NULL) {
		return;
	}
	Department* department = getDepartmentTUI(store);
	if(department->noOfProducts == 0) {
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
			if(store->departments[i].products[j].quantity > 0)
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
		if(((Invoice*)pN->key)->invoiceID == pInvoice->invoiceID)
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
	if(!insertNewInvoiceToList(&store->invoiceList, invoice))
		freeInvoice(invoice);
	calculateStoreProfit(store);
}

int generateInvoiceID(Store* store) {
	if (store == NULL) {
		return 0;
	}
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

int calculateStoreProfit(Store* store) {
	if (store == NULL) {
		return 0;
	}
	int sum = 0;
	NODE* tmp = store->invoiceList.head.next;
	while (tmp) {
		sum += calculateProfit((Invoice*)tmp->key);
		tmp = tmp->next;
	}
	for (int i = 0; i < store->noOfEmployees; i++)
	{
		sum -= store->employees[i].salary;
	}
	sum = sum - store->rent;
	store->profit = sum;
	return sum;
}

int calculateStoreSpendings(Store* store) {
	if (store == NULL) {
		return 0;
	}
	int sum = 0;
	for (int i = 0; i < store->noOfDepartments; i++){
		sum += calculateDepartmentSpendings(&store->departments[i]);
	}

	for (int i = 0; i < store->noOfEmployees; i++)
	{
		sum += store->employees[i].salary;
	}
	sum += store->rent;
	return sum;
}

void printAllInvoices(const Store* store) {
	if (store->noOfInvoices == 0){
		printf("There are no invoices.\n");
		return;
	}
	L_print(&store->invoiceList, printInvoice);
}

int compareStoreByID(const void* store1, const void* store2) {
	if (store1 == NULL || store2 == NULL) {
		return 0;
	}
	const Store* store1_ = *(const Store**)store1;
	const Store* store2_ = *(const Store**)store2;
	return (store1_)->storeID - (store2_)->storeID;
}

int compareStoreByProfit(const void* store1, const void* store2) {
	if (store1 == NULL || store2 == NULL) {
		return 0;
	}
	const Store* store1_ = *(const Store**)store1;
	const Store* store2_ = *(const Store**)store2;
	return store2_->profit - store1_->profit;
}

int compareStoreByRent(const void* store1, const void* store2) {
	if (store1 == NULL || store2 == NULL) {
		return 0;
	}
	const Store* store1_ = *(const Store**)store1;
	const Store* store2_ = *(const Store**)store2;
	return (store1_)->rent - (store2_)->rent;
}

int compareStoreByLocation(const void* store1, const void* store2) {
	if (store1 == NULL || store2 == NULL) {
		return 0;
	}
	const Store* store1_ = *(const Store**)store1;
	const Store* store2_ = *(const Store**)store2;
	return strcmp(store1_->location,store2_->location);
}

void printStoreProfit(const Store* store) {
	if (store == NULL) {
		return;
	}
	printf("Store profit for the year %d: %d\n", YEAR, store->profit);
}

void printStoreSpendings(const Store* store) {
	if (store == NULL) {
		return;
	}
	printf("Store spendings for the year %d: %d\n", YEAR, store->profit);
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
	if (store == NULL) {
		return;
	}
	for (int i = 0; i < noOfDepartmentTypes; i++) {
		printDepartmentFull(&store->departments[i]);
	}
	printf("\n");
}

void printAllProductsInStore(const Store* store) {
	if (store == NULL) {
		return;
	}
	for (int i = 0; i < store->noOfDepartments; i++) {
		printAllProducts(&store->departments[i]);
	}
}

void printStoreReduced(const Store* store) {
	if (store == NULL) {
		return;
	}
	printf("\n# Store ID: %d\t", store->storeID);
	printf("Location: %s\n", store->location);
}

void printStore(const Store* store) {
	if (store == NULL) {
		return;
	}
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
	fscanf(file, "%d", &store->storeID);
	fgetc(file);

	char tmp[MAX_STR_LEN];
	myGetsFile(tmp, MAX_STR_LEN, file);
	store->location = getDynStr(tmp);

	fscanf(file, "%d", &store->rent);
	fgetc(file);
	fscanf(file, "%d", &store->profit);
	fgetc(file);
	fscanf(file, "%d", &store->noOfEmployees);
	fgetc(file);
	store->employees = (Employee*)malloc(store->noOfEmployees * sizeof(Employee));
	if (!store->employees) {
		printf("error in allocating memory for Employees\n");
		return;
	}
	for (int i = 0; i < store->noOfEmployees; i++) {
		loadEmployeeFromTextFile(&store->employees[i], file);
	}

	fscanf(file, "%d", &store->noOfDepartments);
	fgetc(file);
	if (!store->departments) {
		return;
	}
	for (int i = 0; i < store->noOfDepartments; i++) {
		loadDepartmentFromTextFile(&store->departments[i], file);
	}
	int noOfInvoices;
	fscanf(file, "%d", &noOfInvoices);
	fgetc(file);
	store->noOfInvoices = noOfInvoices;
	for (int i = 0; i < noOfInvoices; i++) {
		Invoice* invoice = (Invoice*)malloc(sizeof(Invoice));
		if (!invoice) {
			return;
		}
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
	if(!writeIntToFile(store->profit, file, "Error writing store profit to file\n"))
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
	if (!readIntFromFile(&store->noOfEmployees, file, "Error reading number of employees from file\n"))
		return 0;
	if (!createEmployeeArr(store))
		return 0;
	for (int i = 0; i < store->noOfEmployees; i++) {
		if (!loadEmployeeFromBinaryFile(&store->employees[i], file))
			return 0;
	}
	if (!readIntFromFile(&store->noOfDepartments, file, "Error reading number of departments from file\n"))
		return 0;
	for (int i = 0; i < store->noOfDepartments; i++) {
		if (!loadDepartmentFromBinaryFile(&store->departments[i], file))
			return 0;
	}
	if (!readIntFromFile(&store->noOfInvoices, file, "Error reading number of invoices from file\n"))
		return 0;
	for (int i = 0; i < store->noOfInvoices; i++) {
		Invoice* invoice = (Invoice*)malloc(sizeof(Invoice));
		if (!invoice) {
			puts("Error allocating memory for invoice");
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
