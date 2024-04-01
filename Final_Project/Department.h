#pragma once
#ifndef DEPARTMENT
#define DEPARTMENT
#include "Product.h"
#include "GeneralFunctions.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	eELECTRONICS, eHOME_DESIGN, eTOYS, noOfDepartmentTypes
}eDepartmentType;

static char* departmentTypeStr[noOfDepartmentTypes] = { "Electronics", "Home Design", "Toys" };

typedef struct Department {
	eDepartmentType type;
	Product* products;
	int noOfProducts;
} Department;

void initDepartment(Department* department, eDepartmentType type);

eDepartmentType getDepartmentType();

void addToProduct(Department* dep);

Product* getProduct(const Department* department, char* productCode);

int checkDepartmentStock(Department* dep);

int calculateDepartmentSpendings(Department* dep);

void printDepartmentTypes();

void printAllProducts(const Department* department);

void printDepartment(const Department* department);

void printDepartmentFull(const Department* department);

//void freeDepartment(Department* department);

void saveDepartmentToTextFile(const Department* department, FILE* file);

void loadDepartmentFromTextFile(Department* department, FILE* file);

#endif // !DEPARTMENT
