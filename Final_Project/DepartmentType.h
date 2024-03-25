#pragma once
#ifndef DEPARTMENTTYPE
#define DEPARTMENTTYPE

typedef struct departmentType {
	char* name;
	char** names;
	char** productCodes;
	int* productPrices;
	int noOfProducts;
} departmentType;


#endif // !DEPARTMENTTYPE