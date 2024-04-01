#pragma once

#ifndef PRODUCT
#define PRODUCT
#include "GeneralFunctions.h"
#include "FileHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 3

typedef struct Product {
	char code[SIZE+1];
	char* name;
	int sellPrice;
	int buyPrice;
	int quantity;
} Product;

void initProduct(Product* product);

void getProductCode(char* code);

void getProductName(Product* product);

void getPrice(Product* product);

void updateQuantity(Product* product);

void printForInvoice(const Product* product);

void printProduct(const Product* product);

void printProductFull(const Product* product);

void freeProduct(Product* product);

void saveProductToTextFile(const Product* product, FILE* file);

void loadProductFromTextFile(Product* product, FILE* file);

int saveProductToBinaryFile(const Product* product, FILE* file);

#endif // !1