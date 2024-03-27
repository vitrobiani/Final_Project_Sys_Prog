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

void addProduct(Department* department) {
	Product* product = (Product*)malloc(sizeof(Product));
	if (department == NULL || product == NULL) {
		return;
	}

	initProduct(product);
	Product* tmp = (Product*)realloc(department->products, (department->noOfProducts + 1) * sizeof(Product));
	if (!tmp)
	{
		free(product);
		return;
	}
	department->products = tmp;
	department->products[department->noOfProducts] = *product;
	
	department->noOfProducts++;
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

void printDepartment(const Department* department) {
	if (department == NULL) {
		return;
	}
	printf("Department Name: %s\n", department->type->name);
	for (int i = 0; i < department->noOfProducts; i++) {
		printProduct(&department->products[i]);
	}
}

void printDepartmentFull(const Department* department) {
	if (department == NULL) {
		return;
	}
	printf("\nDepartment Name: %s\n", department->type->name);
	for (int i = 0; i < department->noOfProducts; i++) {
		printProductFull(&department->products[i]);
	}
}