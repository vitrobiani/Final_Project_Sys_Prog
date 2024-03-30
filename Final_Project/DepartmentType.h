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

int checkIfProductExist(const DepartmentType* departmentType, const char* code);

void createProductToDepartmentType(DepartmentType* departmentType);

void printDepartmentType(const DepartmentType* departmentType);

void printDepartmentTypeFull(const DepartmentType* departmentType);

void freeDepartementType(DepartmentType* departmentType);

void saveDepartmentTypeToTextFile(const DepartmentType* departmentType, FILE* file);\

void loadDepartmentTypeFromTextFile(DepartmentType* departmentType, FILE* file);

#endif // !DEPARTMENTTYPE