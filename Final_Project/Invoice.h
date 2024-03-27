#pragma once
#ifndef INVOICE
#define INVOICE
#include <stdio.h>
#include <stdlib.h>
#include "Product.h"
#include "Customer.h"
#include "Employee.h"
#include "DateTime.h"

typedef struct Invoice {
	int invoiceID;
	int storeID;
	Customer customer;
	Employee* employee;
	Product** products;
	int saleAmount;
	Date timeOfSale;
} Invoice;

int initInvoice(Invoice* invoice);

int getInvoiceID(const Invoice* invoice);

int getStoreID(const Invoice* invoice);

const Customer* getCustomer(const Invoice* invoice);

int getSaleAmount(const Invoice* invoice);

void printInvoice(const Invoice* invoice);

#endif // !1