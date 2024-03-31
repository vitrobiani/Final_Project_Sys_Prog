#include "Department.h"

void initDepartment(Department* department, DepartmentType* type) {
	department->type = type;
	setProductArray(department, type);
	department->noOfProducts = type->noOfProducts;
}

int setProductArray(Department* department, DepartmentType* type) {
	if(!department || !department->type->products)
	{
		return 0;
	}
	Product* products = (Product*)malloc(sizeof(Product) * department->type->noOfProducts);
	if (!products) {
		return 0;
	}
	for(int i = 0; i < department->type->noOfProducts; i++) {
		products[i].buyPrice = type->products[i].buyPrice;
		products[i].sellPrice = type->products[i].sellPrice;
		products[i].quantity = type->products[i].quantity;
		strcpy(products[i].code, type->products[i].code);
		products[i].name = (char*)malloc(strlen(type->products[i].name) + 1);
		if(!products[i].name)
		{
			free(products);
			return 0;
		}
		strcpy(products[i].name, type->products[i].name);
	}
	department->products = products;
	return 1;
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

void addProduct(Department* department) {
	if(department->noOfProducts == 0)
	{
		printf("No products in this department\n");
		return;
	}
	printAllProducts(department);
	printf("Enter the product code: ");
	char code[MAX_STR_LEN];
	Product* product = NULL;
	do{
		myGets(code, MAX_STR_LEN);
		product = getProduct(department, code);
		if(!product)
			printf("no such product\n");
	}while(product == NULL);
	updateQuantity(product);
}

void removeProduct(Department* department, const char* productCode) {
	int i;
	for (i = 0; i < department->noOfProducts; i++) {
		if (strcmp(department->products[i].code, productCode) == 0) {
			break;
		}
	}
	if (i < department->noOfProducts) {
		for (int j = i; j < department->noOfProducts - 1; j++) {
			department->products[j] = department->products[j + 1];
		}
		department->noOfProducts--;
	}
}

void printAllProducts(const Department* department) {
	if (department == NULL) {
		return;
	}
	for (int i = 0; i < department->noOfProducts; i++) {
		printProductFull(&department->products[i]);
	}
}

void printDepartment(const Department* department) {
	if (department == NULL) {
		return;
	}
	printf("\nDepartment Name: %s \t Department ID: %d\n", department->type->name, department->type->id);
	for (int i = 0; i < department->noOfProducts; i++) {
		printProduct(&department->products[i]);
	}
}

void printDepartmentFull(const Department* department) {
	if (department == NULL) {
		return;
	}
	printf("\nDepartment Name: %s \t Department ID: %d\n", department->type->name, department->type->id);
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
	fprintf(file, "%d\n", department->type->id);
	fprintf(file, "%d\n", department->noOfProducts);
	for (int i = 0; i < department->noOfProducts; i++) {
		saveProductToTextFile(&department->products[i], file);
	}
}

void loadDepartmentFromTextFile(Department* department, FILE* file) {
	int departmentTypeID;
	fscanf(file, "%d", &departmentTypeID);
	fgetc(file);
	DepartmentType* type = (DepartmentType*)malloc(sizeof(DepartmentType));
	if (!type) {
		return;
	}
	//TODO: check if the department type exists
	type->id = departmentTypeID;
	department->type = type;
	fscanf(file, "%d", &department->noOfProducts);
	fgetc(file);
	Product* products = (Product*)malloc(sizeof(Product) * department->noOfProducts);
	if(!products) {
		free(type);
		return;
	}
	for (int i = 0; i < department->noOfProducts; i++) {
		loadProductFromTextFile(&products[i], file);
	}
	department->products = products;
}