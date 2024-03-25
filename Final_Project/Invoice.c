#include "Invoice.h"

int initInvoice(Invoice* invoice, int invoiceID, int storeID, Product* products, Customer customer, Employee** employee, int saleAmount, Date timeOfSale) {
	if (invoice == NULL || products == NULL || employee == NULL) {
		return 0;
	}

	invoice->invoiceID = invoiceID;
	invoice->storeID = storeID;
	invoice->customer = customer;
	invoice->employee = *employee;
	invoice->products = &products;
	invoice->saleAmount = saleAmount;
	invoice->timeOfSale = timeOfSale;
	return 1;
}

int getInvoiceID(const Invoice* invoice) {
	if (invoice == NULL) {
		return 0;
	}
	return invoice->invoiceID;
}

void printInvoice(const Invoice* invoice) {
	if (invoice == NULL) {
		return;
	}
	printf("Invoice ID: %d\n", invoice->invoiceID);
	printf("Store ID: %d\n", invoice->storeID);
	printf("Customer: %s\n", invoice->customer.name);
	printf("Employee: %s\n", invoice->employee->name);
	printf("Sale Amount: %d\n", invoice->saleAmount);
	printf("Time of Sale: %d/%d/%d\n", invoice->timeOfSale.day, invoice->timeOfSale.month, invoice->timeOfSale.year);
}