#include "DepartmentType.h"

void initDepartmentType(DepartmentType* departmentType, int id) {
	departmentType->name = getStrExactName("Enter the Department type: ");
	departmentType->products = NULL;
	departmentType->id = id;
	departmentType->noOfProducts = 0;
}

void addProductToDepartmentType(DepartmentType* departmentType) {
	Product* product = (Product*)malloc(sizeof(Product));
	if (departmentType == NULL || product == NULL) {
		return;
	}
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