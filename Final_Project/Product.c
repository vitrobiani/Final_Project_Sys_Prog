#include "Product.h"

int initProduct(Product* product) {
	getProductCode(product);
	getProductName(product);
	product->price = getPrice(product);
	product->quantity = 0;
	return 1;
}

void getProductCode(Product* product) {
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter airport code  - %d UPPER CASE letters\t", SIZE);
		myGets(temp, MAX_STR_LEN);
		if (strlen(temp) != SIZE)
		{
			printf("code should be %d letters\n", SIZE);
			ok = 0;
		}
		else {
			for (int i = 0; i < SIZE; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(product->name, temp);
}

void getProductName(Product* product) {
	product->name = getStrExactName("Enter product name:");
}

int getPrice(Product* product) {
	char temp[MAX_STR_LEN];
	int price;
	do {
		printf("Enter price of product: ");
		myGets(temp, MAX_STR_LEN);
		price = atoi(temp);
		if (price <= 0) {
			printf("Price must be a positive number\n");
		}
	} while (price <= 0);
	return price;
}

void printProduct(const Product* product) {
	if (product == NULL) {
		return;
	}
	printf("Product Code: %s\n", product->code);
	printf("Product Name: %s\n", product->name);
	printf("Price: %d\n", product->price);
	printf("Quantity: %d\n", product->quantity);
}