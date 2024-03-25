#pragma once

#ifndef PRODUCT
#define PRODUCT
#include "GeneralFunctions.h"
#include "DepartmentType.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

typedef struct Product {
	departmentType* type;
	char code[SIZE+1];
	char* name;
	int price;
	int quantity;
} Product;

void initProduct(Product* product);

void getProductCode(const Product* product);

void getProductName(const Product* product);

int getPrice(const Product* product);

void printProduct(const Product* product);



#endif // !1