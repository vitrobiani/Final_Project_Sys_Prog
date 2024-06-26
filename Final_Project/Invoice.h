#pragma once
#ifndef INVOICE
#define INVOICE
#include "Product.h"
#include "Customer.h"
#include "Employee.h"
#include "Date.h"
#include "FileHelper.h"
#include "Macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct Invoice {
	int invoiceID;
	int storeID;
	Customer customer;
	Employee* employee;
	Product* products;
	int numOfProducts;
	int saleAmount;
	Date timeOfSale;
} Invoice;

void initInvoice(Invoice* invoice, int storeID, Employee* employee, Product* product, int numOfProducts, int id);

int calculateSaleAmount(const Invoice* invoice);

int calculateProfit(const Invoice* invoice);

void printInvoice(const Invoice* invoice);

void freeInvoice(Invoice* invoice);

int saveInvoiceToTextFile(const Invoice* invoice, FILE* file);

int loadInvoiceFromTextFile(Invoice* invoice, FILE* file);

int saveInvoiceToBinaryFile(const Invoice* invoice, FILE* file);

int createProductArr(Invoice* invoice);

int loadInvoiceFromBinaryFile(Invoice* invoice, FILE* file);

#endif // !1