#pragma once

#ifndef CUSTOMER
#define CUSTOMER
#include "Store.h"

typedef struct Customer {
	int CustomerID;
	char* CustomerName;
	int contactNumber;
} Customer;

void initCustomer(Customer* customer, int CustomerID, const char* CustomerName, int contactNumber);

void getPurchaseHistory(const Customer* customer, Store store);

int getCustomerID(const Customer* customer);

const char* getCustomerName(const Customer* customer);

int getContactNumber(const Customer* customer);

void printCustomer(const Customer* customer);


#endif // !1