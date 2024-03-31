#pragma once
#ifndef DEPARTMENT
#define DEPARTMENT
#include "Product.h"
#include "GeneralFunctions.h"
#include "DepartmentType.h"
#include "GeneralFunctions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Department {
	DepartmentType* type;
	Product* products;
	int noOfProducts;
} Department;

void initDepartment(Department* department, DepartmentType* type);

int setProductArray(Department* department, DepartmentType* type);

Product* getProduct(const Department* department, char* productCode);

void addProduct(Department* department);

void removeProduct(Department* department, const char* productCode);

void printAllProducts(const Department* department);

void printDepartment(const Department* department);

void printDepartmentFull(const Department* department);

void freeDepartment(Department* department);

void saveDepartmentToTextFile(const Department* department, FILE* file);

void loadDepartmentFromTextFile(Department* department, FILE* file);

#endif // !DEPARTMENT
