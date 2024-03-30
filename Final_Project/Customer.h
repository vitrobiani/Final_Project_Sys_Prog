#pragma once

#ifndef CUSTOMER
#define CUSTOMER
#include "GeneralFunctions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
	int id;
	char* name;
	int contactNumber;
} Customer;

void initCustomer(Customer* customer, int CustomerID, const char* CustomerName, int contactNumber);
//hi

int getCustomerID(const Customer* customer);

const char* getCustomerName(const Customer* customer);

int getContactNumber(const Customer* customer);

void printCustomer(const Customer* customer);


#endif // !1