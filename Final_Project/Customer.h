#pragma once

#ifndef CUSTOMER
#define CUSTOMER
#include "GeneralFunctions.h"
#include "FileHelper.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
	int id;
	char* name;
	int contactNumber;
} Customer;

void setCustomerID(Customer* customer);

void setCustomerName(Customer* customer);

void setContactNumber(Customer* customer);

void printCustomer(const Customer* customer);

int saveCustomerToBinaryFile(const Customer* customer, FILE* file);

int loadCustomerFromBinaryFile(Customer* customer, FILE* file);


#endif // !1