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
		printf("Saving product %d to text file\n", i); //debug
		saveProductToTextFile(&invoice->products[i], file);
	}
	fprintf(file, "%d\n", invoice->saleAmount);

	fprintf(file, "%d\n", invoice->customer.id);
	fprintf(file, "%zu\n", strlen(invoice->customer.name));
	fprintf(file, "%s\n", invoice->customer.name);
	fprintf(file, "%d\n", invoice->customer.contactNumber);

	fprintf(file, "%d\n", invoice->timeOfSale.day);
	fprintf(file, "%d\n", invoice->timeOfSale.month);
	fprintf(file, "%d\n", invoice->timeOfSale.year);
}

void loadInvoiceFromTextFile(Invoice* invoice, FILE* file) {
	printf("Loading invoice from text file\n"); //debug
	fscanf(file, "%d", &invoice->invoiceID);
	fgetc(file);
	fscanf(file, "%d", &invoice->storeID);
	fgetc(file);
	printf("invoice id: %d, store id: %d\n", invoice->invoiceID, invoice->storeID); //debug

	Employee* emp = (Employee*)malloc(sizeof(Employee));
	if (!emp) {
		printf("Memory allocation failed\n");
		return;
	}
	fscanf(file, "%d", &emp->id);
	fgetc(file);

	fscanf(file, "%d", &invoice->numOfProducts);
	fgetc(file);
	Product* products = (Product*)malloc(sizeof(Product) * invoice->numOfProducts);
	if (!products) {
		free(emp);
		return;
	}
	for (int i = 0; i < invoice->numOfProducts; i++)
	{
		loadProductFromTextFile(&products[i], file);
	}
	invoice->products = products;
	fscanf(file, "%d", &invoice->saleAmount);
	fgetc(file);
	fscanf(file, "%d", &invoice->customer.id);
	fgetc(file);
	int nameLength;
	fscanf(file, "%d", &nameLength);
	fgetc(file);
	invoice->customer.name = (char*)malloc(nameLength + 1);
	if (!invoice->customer.name) {
		free(emp);
		free(products);
		return;
	}
	fscanf(file, "%[^\n]", invoice->customer.name);
	fgetc(file);
	fscanf(file, "%d", &invoice->customer.contactNumber);
	fgetc(file);
	invoice->employee = emp;
	printf("id: %d, name: %s, contact number: %d\n", invoice->customer.id, invoice->customer.name, invoice->customer.contactNumber); //debug

	fscanf(file, "%d", &invoice->timeOfSale.day);
	fgetc(file);
	fscanf(file, "%d", &invoice->timeOfSale.month);
	fgetc(file);
	fscanf(file, "%d", &invoice->timeOfSale.year);
	fgetc(file);
	printf("day: %d, month: %d, year: %d\n", invoice->timeOfSale.day, invoice->timeOfSale.month, invoice->timeOfSale.year); //debug
}

int saveInvoiceToBinaryFile(const Invoice* invoice, FILE* file)
{
	if (!writeIntToFile(invoice->invoiceID, file, "Error writing invoice ID to file\n"))
		return 0;
	if (!writeIntToFile(invoice->storeID, file, "Error writing store ID to file\n"))
		return 0;
	if(!saveCustomerToBinaryFile(&invoice->customer, file))
		return 0;
	if (!writeIntToFile(invoice->employee->id, file, "Error writing employee ID to file\n"))
		return 0;
	if (!writeIntToFile(invoice->numOfProducts, file, "Error writing number of products to file\n"))
		return 0;
	for (int i = 0; i < invoice->numOfProducts; i++)
	{
		if (!saveProductToBinaryFile(&invoice->products[i], file))
			return 0;
	}
	if (!writeIntToFile(invoice->saleAmount, file, "Error writing sale amount to file\n"))
		return 0;

	return 0;
}
