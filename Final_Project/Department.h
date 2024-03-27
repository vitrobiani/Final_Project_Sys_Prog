#pragma once
#ifndef DEPARTMENT
#define DEPARTMENT
#include "Product.h"
#include "GeneralFunctions.h"
#include "DepartmentType.h"
#include <stdio.h>
#include <stdlib.h>
#include "GeneralFunctions.h"

typedef struct Department {
	DepartmentType* type;
	Product* products;
	int noOfProducts;
} Department;

void initDepartment(Department* department, DepartmentType* type);

int setProductArray(Department* department, DepartmentType* type);

void addProduct(Department* department);

void removeProduct(Department* department, const char* productCode);

void printDepartment(const Department* department);

void printDepartmentFull(const Department* department);

#endif // !DEPARTMENT
