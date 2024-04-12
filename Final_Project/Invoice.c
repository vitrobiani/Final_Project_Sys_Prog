#include "Invoice.h"

void initInvoice(Invoice* invoice, int storeID, Employee* employee, Product* product, int numOfProducts, int id) {
	invoice->invoiceID = id;
	invoice->storeID = storeID;
	invoice->employee = employee;
	invoice->products = product;
	invoice->numOfProducts = numOfProducts;
	invoice->saleAmount = calculateSaleAmount(invoice);
	getCorrectDate(&invoice->timeOfSale);
}

int calculateSaleAmount(const Invoice* invoice) {
	int sum = 0;

	for (int i = 0; i < invoice->numOfProducts; i++)
	{
		sum = sum + ((invoice->products[i].sellPrice) * (invoice->products[i].quantity));
	}

	return sum;
}

int calculateProfit(const Invoice* invoice) {
	int sum = 0;

	for (int i = 0; i < invoice->numOfProducts; i++)
	{
		sum = sum + ((invoice->products[i].sellPrice - invoice->products[i].buyPrice) * (invoice->products[i].quantity));
	}

	return sum;
}

void printInvoice(const Invoice* invoice) {
	printf("\nInvoice ID: %d\t", invoice->invoiceID);
	printf("Store ID: %d\n", invoice->storeID);
	printf("Customer details:\t");
	printCustomer(&invoice->customer);
	printf("Employee that made the sale: %s\n", invoice->employee->name);
	printf("The Products:\n");
	generalArrayFunction(invoice->products, invoice->numOfProducts, sizeof(Product), printForInvoice);
	printf("Sale amount: %d\n", invoice->saleAmount);

	printf("Time of sale: ");
	printDate(&invoice->timeOfSale);
	printf("\n");
}

void freeInvoice(Invoice* invoice) {
	if (invoice == NULL) {
		return;
	}
	generalArrayFunction(invoice->products, invoice->numOfProducts, sizeof(Product), freeProduct);
	free(invoice->products);
	free(invoice->customer.name);
	free(invoice);
}

int saveInvoiceToTextFile(const Invoice* invoice, FILE* file) {
	if (!writeIntToTextFile(invoice->invoiceID, file, "Error writing invoice ID to file\n")) return 0;
	if (!writeIntToTextFile(invoice->storeID, file, "Error writing store ID to file\n")) return 0;
	if (!writeIntToTextFile(invoice->employee->id, file, "Error writing employee ID to file\n")) return 0;
	if (!writeIntToTextFile(invoice->numOfProducts, file, "Error writing number of products to file\n")) return 0;
	for (int i = 0; i < invoice->numOfProducts; i++){
		if (!saveProductToTextFile(&invoice->products[i], file)) return 0;
	}
	if (!writeIntToTextFile(invoice->saleAmount, file, "Error writing sale amount to file\n")) return 0;
	if (!writeIntToTextFile(invoice->customer.id, file, "Error writing customer ID to file\n")) return 0;
	if (!writeStringToTextFile(invoice->customer.name, file, "Error writing customer name to file\n")) return 0;
	if (!writeIntToTextFile(invoice->customer.contactNumber, file, "Error writing customer contact number to file\n")) return 0;
	if (!writeIntToTextFile(invoice->timeOfSale.day, file, "Error writing day to file\n")) return 0;
	if (!writeIntToTextFile(invoice->timeOfSale.month, file, "Error writing month to file\n")) return 0;
	if (!writeIntToTextFile(invoice->timeOfSale.year, file, "Error writing year to file\n")) return 0;
	return 1;
}

int loadInvoiceFromTextFile(Invoice* invoice, FILE* file) {
	if (!readIntFromTextFile(&invoice->invoiceID, file, "Error reading invoice ID from file\n")) return 0;
	if (!readIntFromTextFile(&invoice->storeID, file, "Error reading store ID from file\n")) return 0;
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	PRINT_RETURN_INT(emp, 0, "Memory allocation failed");
	if (!readIntFromTextFile(&emp->id, file, "Error reading employee ID from file\n")) return 0;
	if (!readIntFromTextFile(&invoice->numOfProducts, file, "Error reading number of products from file\n")) return 0;
	Product* products = (Product*)malloc(sizeof(Product) * invoice->numOfProducts);
	if (!products) {
		free(emp);
		return 0;
	}
	for (int i = 0; i < invoice->numOfProducts; i++) {
		if(!loadProductFromTextFile(&products[i], file)) return 0;
	}

	if (!readIntFromTextFile(&invoice->saleAmount, file, "Error reading sale amount from file\n")) return 0;
	if (!readIntFromTextFile(&invoice->customer.id, file, "Error reading customer ID from file\n")) return 0;
	char tmp[MAX_STR_LEN];
	myGetsFile(tmp, MAX_STR_LEN, file);
	invoice->customer.name = getDynStr(tmp);
	
	if (!readIntFromTextFile(&invoice->customer.contactNumber, file, "Error reading customer contact number from file\n")) return 0;
	if (!readIntFromTextFile(&invoice->timeOfSale.day, file, "Error reading day from file\n")) return 0;
	if (!readIntFromTextFile(&invoice->timeOfSale.month, file, "Error reading month from file\n")) return 0;
	if (!readIntFromTextFile(&invoice->timeOfSale.year, file, "Error reading year from file\n")) return 0;
	invoice->products = products;
	invoice->employee = emp;
	return 1;
}

int saveInvoiceToBinaryFile(const Invoice* invoice, FILE* file) {
	if (!writeIntToFile(invoice->invoiceID, file, "Error writing invoice ID to file\n"))
		return 0;
	if (!writeIntToFile(invoice->storeID, file, "Error writing store ID to file\n"))
		return 0;
	if (!saveCustomerToBinaryFile(&invoice->customer, file))
		return 0;
	if (!writeIntToFile(invoice->employee->id, file, "Error writing employee ID to file\n"))
		return 0;
	if (!writeIntToFile(invoice->numOfProducts, file, "Error writing number of products to file\n"))
		return 0;
	for (int i = 0; i < invoice->numOfProducts; i++) {
		if (!saveProductToBinaryFile(&invoice->products[i], file))
			return 0;
	}
	if (!writeIntToFile(invoice->saleAmount, file, "Error writing sale amount to file\n"))
		return 0;
	if (!saveDateToBinaryFileCompressed(&invoice->timeOfSale, file))
		return 0;
	return 1;
}

int createProductArr(Invoice* invoice)
{
	invoice->products = (Product*)malloc(sizeof(Product) * invoice->numOfProducts);
	if (!invoice->products)
	{
		puts("Error allocating memory for products");
		return 0;
	}
	return 1;
}

int loadInvoiceFromBinaryFile(Invoice* invoice, FILE* file) {
	if (!readIntFromFile(&invoice->invoiceID, file, "Error reading invoice ID from file\n"))
		return 0;
	if (!readIntFromFile(&invoice->storeID, file, "Error reading store ID from file\n"))
		return 0;
	if (!loadCustomerFromBinaryFile(&invoice->customer, file))
		return 0;
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	if (!emp) {
		puts("Error allocating memory for employee");
		return 0;
	}
	if (!readIntFromFile(&emp->id, file, "Error reading employee ID from file\n")) {
		free(emp);
		return 0;
	}
	invoice->employee = emp;
	if (!readIntFromFile(&invoice->numOfProducts, file, "Error reading number of products from file\n"))
		return 0;
	if (!createProductArr(invoice))
		return 0;
	for (int i = 0; i < invoice->numOfProducts; i++) {
		if (!loadProductFromBinaryFile(&invoice->products[i], file))
			return 0;
	}
	if (!readIntFromFile(&invoice->saleAmount, file, "Error reading sale amount from file\n"))
		return 0;
	if (!loadDateFromBinaryFileCompressed(&invoice->timeOfSale, file))
		return 0;
	return 1;
}


