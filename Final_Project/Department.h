#pragma once
#ifndef DEPARTMENT
#define DEPARTMENT
#include "Product.h"
#include "GeneralFunctions.h"
#include "FileHelper.h"
#include "Macros.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	eELECTRONICS, eHOME_DESIGN, eCLOTHING, eTOYS, eBAD_BATH, noOfDepartmentTypes
}eDepartmentType;

static char* departmentTypeStr[noOfDepartmentTypes] = { "Electronics", "Home Design", "Clothing", "Toys", "Bad and Bath"};

typedef struct Department {
	eDepartmentType type;
	Product* products;
	int noOfProducts;
} Department;

void initDepartment(Department* department, eDepartmentType type);

eDepartmentType getDepartmentType();

void addToProduct(Department* dep);

Product* getProduct(const Department* department, const char* productCode);

int checkDepartmentStock(const Department* dep);

void printDepartmentTypes();

void printAllProducts(const Department* department);

void printDepartment(const Department* department);

void printDepartmentFull(const Department* department);

void freeDepartment(Department* department);

int saveDepartmentToTextFile(const Department* department, FILE* file);

int loadDepartmentFromTextFile(Department* department, FILE* file);

int createProductArray(Department* department);

int saveDepartmentToBinaryFile(const Department* department, FILE* file);

int loadDepartmentFromBinaryFile(Department* department, FILE* file);

#endif // !DEPARTMENT
