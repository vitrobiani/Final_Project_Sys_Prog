#include "Invoice.h"

void initInvoice(Invoice* invoice, int storeID, Employee* employee, Product* product, int numOfProducts, int id) {
	if (invoice == NULL) {
		return;
	}
	invoice->invoiceID = id;
	invoice->storeID = storeID;
	invoice->employee = employee;
	invoice->products = product;
	invoice->numOfProducts = numOfProducts;
	invoice->saleAmount = calculateSaleAmount(invoice);
	getCorrectDate(&invoice->timeOfSale);
}

int calculateSaleAmount(const Invoice* invoice) {
	if (invoice == NULL) {
		return 0;
	}
	int sum = 0;
	
	for (int i = 0; i < invoice->numOfProducts; i++)
	{
		sum = sum + ((invoice->products[i].sellPrice)*(invoice->products[i].quantity));
	}

	return sum;
}

int calculateProfit(const Invoice* invoice) {
	if (invoice == NULL) {
		return 0;
	}
	int sum = 0;
	
	for (int i = 0; i < invoice->numOfProducts; i++)
	{
		sum = sum + ((invoice->products[i].sellPrice - invoice->products[i].buyPrice)*(invoice->products[i].quantity));
	}

	return sum;
}

void printInvoice(const Invoice* invoice) {
	if (invoice == NULL) {
		return;
	}
	printf("\nInvoice ID: %d\t", invoice->invoiceID);
	printf("Store ID: %d\n", invoice->storeID);
	printf("Employee that made the sale: %s\n", invoice->employee->name);
	printf("The Products:\n");
	generalArrayFunction(invoice->products, invoice->numOfProducts, sizeof(Product), printForInvoice);
	printf("Sale amount: %d\n", invoice->saleAmount);
	
	printf("Time of sale: ");
	printDate(&invoice->timeOfSale);
	printf("\n");
}

void freeInvoice(Invoice* invoice) {
	free(invoice->products);
	free(invoice);
}

void saveInvoiceToTextFile(const Invoice* invoice, FILE* file) {
	printf("Saving invoice to text file\n"); //debug
	fprintf(file, "%d\n", invoice->invoiceID);
	fprintf(file, "%d\n", invoice->storeID);
	fprintf(file,"%d\n", invoice->employee->id);
	fprintf(file, "%d\n", invoice->numOfProducts);
	for (int i = 0; i < invoice->numOfProducts; i++)
	{
		saveProductToTextFile(&invoice->products[i], file);
	}
	fprintf(file, "%d\n", invoice->saleAmount);

	fprintf(file, "%d\n", invoice->customer.id);
	fprintf(file, "%zu\n", strlen(invoice->customer.name));
	fprintf(file, "%d\n", invoice->customer.contactNumber);

	fprintf(file, "%d\n", invoice->timeOfSale.day);
	fprintf(file, "%d\n", invoice->timeOfSale.month);
	fprintf(file, "%d\n", invoice->timeOfSale.year);
}

void loadInvoiceFromTextFile(Invoice* invoice, FILE* file) {
	if (!invoice) {
		return;
	}

	fscanf(file, "%d", &invoice->invoiceID);
	fscanf(file, "%d", &invoice->storeID);
	//TODO: load employee
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	if (!emp) {
		return;
	}
	fscanf(file, "%d", &emp->id);
	fscanf(file, "%d", &invoice->numOfProducts);
	Product* products = (Product*)malloc(sizeof(Product) * invoice->numOfProducts);
	if (!products) {
		free(emp);
		return;
	}
	for (int i = 0; i < invoice->numOfProducts; i++)
	{
		loadProductFromTextFile(&products[i], file);
	}
	fscanf(file, "%d", &invoice->saleAmount);

	fscanf(file, "%d", &invoice->customer.id);
	int nameLength;
	fscanf(file, "%d", &nameLength);
	invoice->customer.name = (char*)malloc(nameLength + 1);
	if (!invoice->customer.name) {
		free(emp);
		free(products);
		return;
	}
	fscanf(file, "%s", invoice->customer.name);
	fscanf(file, "%d", &invoice->customer.contactNumber);

	fscanf(file, "%d", &invoice->timeOfSale.day);
	fscanf(file, "%d", &invoice->timeOfSale.month);
	fscanf(file, "%d", &invoice->timeOfSale.year);

}