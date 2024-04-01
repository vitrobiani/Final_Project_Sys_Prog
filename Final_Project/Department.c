#include "Department.h"

void initDepartment(Department* department, eDepartmentType type) {
	department->type = type;
	department->noOfProducts = 0;
	department->products = NULL;
}

eDepartmentType getDepartmentType() {
	int type;
	do {
		printf("Enter the department type\n");
		printDepartmentTypes();
		scanf("%d", &type);
		if (type < 1 || type >= noOfDepartmentTypes) {
			printf("Invalid department type\n");
		}
	} while (type < 1 || type >= noOfDepartmentTypes);
	return type;
}

void addToProduct(Department* dep) {
	printAllProducts(dep);
	printf("Enter the product code: ");
	char code[MAX_STR_LEN];
	Product* product = NULL;
	do {
		myGets(code, MAX_STR_LEN);
		product = getProduct(dep, code);
		if (!product)
			printf("no such product\n");
	} while (product == NULL);
	updateQuantity(product);
}

int checkDepartmentStock(Department* dep) {
	for (int i = 0; i < dep->noOfProducts; i++) {
		if (dep->products[i].quantity > 0)
			return 1;
	}
	return 0;
}

Product* getProduct(const Department* department, char* productCode) {
	if (department == NULL) {
		return NULL;
	}
	for (int i = 0; i < department->noOfProducts; i++) {
		if (strcmp(department->products[i].code, productCode) == 0) {
			return &department->products[i];
		}
	}
	return NULL;
}

int calculateDepartmentSpendings(Department* dep) {
	int sum = 0;
	for (int i = 0; i < dep->noOfProducts; i++) {
		sum += dep->products[i].quantity * dep->products[i].buyPrice;
	}
	return sum;
}

void printAllProducts(const Department* department) {
	if (department == NULL) {
		return;
	}
	for (int i = 0; i < department->noOfProducts; i++) {
		printProductFull(&department->products[i]);
	}
}

void printDepartmentTypes() {
	for (int i = 0; i < noOfDepartmentTypes; i++)
	{
		printf("%d. %s\n", i, departmentTypeStr[i]);
	}
}

void printDepartment(const Department* department) {
	if (department == NULL) {
		return;
	}
	printf("\nDepartment Name: %s \t Department ID: %d\n", departmentTypeStr[department->type], department->type);
	for (int i = 0; i < department->noOfProducts; i++) {
		printProduct(&department->products[i]);
	}
}

void printDepartmentFull(const Department* department) {
	if (department == NULL) {
		return;
	}
	printf("\nDepartment Name: %s \t Department ID: %d\n", departmentTypeStr[department->type], department->type);
	printAllProducts(department);
}

void freeDepartment(Department* department) {
	if (department == NULL || department->products == NULL) {
		return;
	}
	for (int i = 0; i < department->noOfProducts; i++) {
		freeProduct(&department->products[i]);
	}
	free(department->products);
}

void saveDepartmentToTextFile(const Department* department, FILE* file) {
	printf("saving Department"); //debug
	fprintf(file, "%d\n", department->type);
	fprintf(file, "%d\n", department->noOfProducts);
	for (int i = 0; i < department->noOfProducts; i++) {
		saveProductToTextFile(&department->products[i], file);
	}
}

void loadDepartmentFromTextFile(Department* department, FILE* file) {
	int type = 0;
	fscanf(file, "%d", &type);
	department->type = type;
	fgetc(file);
	fscanf(file, "%d", &department->noOfProducts);
	fgetc(file);
	Product* products = (Product*)malloc(sizeof(Product) * department->noOfProducts);
	if(!products) {
		return;
	}
	for (int i = 0; i < department->noOfProducts; i++) {
		loadProductFromTextFile(&products[i], file);
	}
	department->products = products;
}

int createProductArr(Department* department)
{
	department->products = (Product*)malloc(sizeof(Product) * department->noOfProducts);
	if (!department->products)
	{
		puts("Error allocating memory for products");
		return 0;
	}

	return 1;
}

int saveDepartmentToBinaryFile(const Department* department, FILE* file)
{
	if(fwrite(&department->type, sizeof(eDepartmentType), 1, file) != 1)
	{
		puts("Error writing department type");
		return 0;
	}
	if (!writeIntToFile(department->noOfProducts, file, "Error writing number of products to file\n"))
		return 0;
	for (int i = 0; i < department->noOfProducts; i++)
	{
		if (!saveProductToBinaryFile(&department->products[i], file))
			return 0;
	}

	return 0;
}
