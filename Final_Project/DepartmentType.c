#include "DepartmentType.h"

void initDepartmentType(DepartmentType* departmentType, int id) {
	departmentType->name = getStrExactName("Enter the Department type: ");
	departmentType->products = NULL;
	departmentType->id = id;
	departmentType->noOfProducts = 0;
}

int checkIfProductExist(const DepartmentType* departmentType, const char* code) {
	if (departmentType == NULL) {
		return 0;
	}
	for (int i = 0; i < departmentType->noOfProducts; i++) {
		if (strcmp(departmentType->products[i].code, code) == 0) {
			return 1;
		}
	}
	return 0;
}

void createProductToDepartmentType(DepartmentType* departmentType) {
	Product* product = (Product*)malloc(sizeof(Product));
	if (departmentType == NULL || product == NULL) {
		return;
	}
	do {
		getProductCode(product->code);
	} while (checkIfProductExist(departmentType, product->code));
	initProduct(product);
	Product* tmp = (Product*)realloc(departmentType->products, (departmentType->noOfProducts + 1) * sizeof(Product));
	if (!tmp)
	{
		printf("error in allocating memory\n");
		free(product);
		return;
	}
	departmentType->products = tmp;
	departmentType->products[departmentType->noOfProducts] = *product;
	departmentType->noOfProducts++;
}

void printDepartmentType(const DepartmentType* departmentType) {
	if (departmentType == NULL) {
		return;
	}
	printf("\nDepartment Type ID: %d\n", departmentType->id);
	printf("Department Type Name: %s\n", departmentType->name);
}

void printDepartmentTypeFull(const DepartmentType* departmentType) {
	if (departmentType == NULL) {
		return;
	}
	printf("\nDepartment Type Name: %s\t", departmentType->name);
	printf("Department Type ID: %d \n", departmentType->id);
	printf("Products in this department: \n");
	for (int i = 0; i < departmentType->noOfProducts; i++) {
		printProduct(&departmentType->products[i]);
	}
}

void freeDepartementType(DepartmentType* departmentType) {
	if (departmentType == NULL) {
		return;
	}
	free(departmentType->name);
	for (int i = 0; i < departmentType->noOfProducts; i++) {
		freeProduct(&departmentType->products[i]);
	}
	free(departmentType->products);
}

void saveDepartmentTypeToTextFile(const DepartmentType* departmentType, FILE* file) {
	printf("Saving department type to file\n"); //debug
	fprintf(file, "%d\n", departmentType->id);
	fprintf(file, "%zu\n", strlen(departmentType->name));
	fprintf(file, "%s\n", departmentType->name);
	fprintf(file, "%d\n", departmentType->noOfProducts);
	for (int i = 0; i < departmentType->noOfProducts; i++) {
		saveProductToTextFile(&departmentType->products[i], file);
	}
}

void loadDepartmentTypeFromTextFile(DepartmentType* departmentType, FILE* file) {
	printf("Loading department type from file\n"); //debug
	fscanf(file, "%d", &departmentType->id);
	int length;
	fscanf(file, "%d", &length);
	departmentType->name = (char*)malloc(length * sizeof(char));
	if (departmentType->name == NULL) {
		return;
	}
	fscanf(file, "%s", departmentType->name);
	printf("name: %s\n", departmentType->name); //debug
	fscanf(file, "%d", &departmentType->noOfProducts);
	departmentType->products = (Product*)malloc(departmentType->noOfProducts * sizeof(Product));
	if (departmentType->products == NULL) {
		return;
	}
	for (int i = 0; i < departmentType->noOfProducts; i++) {
		loadProductFromTextFile(&departmentType->products[i], file);
	}
}