#pragma once
#ifndef DEPARTMENT
#define DEPARTMENT
#include "Product.h"
#include <stdio.h>
#include <stdlib.h>
#include "GeneralFunctions.h"

typedef struct Department {
	departmentType* type;
	char* DepartmentName;
	Product* products;
	int noOfProducts;
} Department;

void initDepartment(Department* department);

int setDepartmentType(Department* department);

int setDepartmentName(Department* department);

void addProduct(Department* department);

void removeProduct(Department* department, const char* productCode);

#endif // !DEPARTMENT
