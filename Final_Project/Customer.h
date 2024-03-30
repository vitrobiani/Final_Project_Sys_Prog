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

//hi
void initCustomer(Customer* customer);

void initCustomer(Customer* customer, int CustomerID, const char* CustomerName, int contactNumber);

void setCustomerID(Customer* customer);

void setCustomerName(Customer* customer);

void setContactNumber(Customer* customer);

void printCustomer(const Customer* customer);


#endif // !1