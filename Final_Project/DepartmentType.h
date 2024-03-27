#pragma once
#ifndef DEPARTMENTTYPE
#define DEPARTMENTTYPE
#include "Product.h"
#include "GeneralFunctions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct DepartmentType {
	int id;
	char* name;
	Product* products;
	int noOfProducts;
} DepartmentType;

void initDepartmentType(DepartmentType* departmentType, int id);

void addProductToDepartmentType(DepartmentType* departmentType);

void printDepartmentType(const DepartmentType* departmentType);

void printDepartmentTypeFull(const DepartmentType* departmentType);

#endif // !DEPARTMENTTYPE