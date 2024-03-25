#include "Department.h"

void initDepartment(Department* department) {
	department->products = NULL;
	department->noOfProducts = 0;
	setDepartmentType(department);
	setDepartmentName(department);
}

int setDepartmentType(Department* department) {
}

int setDepartmentName(Department* department) {
	department->DepartmentName = getStrExactName("Enter department name:");
	return 1;
}

void addProduct(Department* department) {
	Product* product = (Product*)malloc(sizeof(Product));
	if (department == NULL || product == NULL) {
		return;
	}

	initProduct(product);
	department->products = (Product*)realloc(department->products, (department->noOfProducts + 1) * sizeof(Product));
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