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


void initCustomer(Customer* customer);

void setCustomerID(Customer* customer);

void setCustomerName(Customer* customer);

void setContactNumber(Customer* customer);

void printCustomer(const Customer* customer);


#endif // !1