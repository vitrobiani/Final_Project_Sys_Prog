#include "Product.h"

void initProduct(Product* product) {
	getProductCode(product->code);
	getProductName(product);
	getPrice(product);
	product->quantity = 0;
}

void getProductCode(char* code) {
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

	strcpy(code, temp);
}

void getProductName(Product* product) {
	product->name = getStrExactName("Enter product name:");
}

void getPrice(Product* product) {
	printf("\nEnter the buy price of product: ");
	int buyPrice;
	do {
		scanf("%d", &buyPrice);
		if (buyPrice <= 0) {
			printf("Price must be a positive number\n");
		}
	} while (buyPrice <= 0);
	product->buyPrice = buyPrice;
	printf("\nEnter the sell price of product: ");
	int sellPrice;
	do {
		scanf("%d", &sellPrice);
		if (sellPrice <= 0) {
			printf("Price must be a positive number\n");
		}
	} while (sellPrice <= 0);
	product->sellPrice = sellPrice;
}

void printProduct(const Product* product) {
	if (product == NULL) {
		return;
	}
	printf("\t# Product Name: %s", product->name);
	printf("\tProduct Code: %s\n", product->code);
	printf("\t  Buy Price: %d", product->buyPrice);
	printf("\tSell Price: %d\n", product->sellPrice);
}

void printProductFull(const Product* product) {
	if (product == NULL) {
		return;
	}
	printf("\t# Product Name: %s", product->name);
	printf("\tProduct Code: %s\n", product->code);
	printf("\t  Buy Price: %d", product->buyPrice);
	printf("\tSell Price: %d\n", product->sellPrice);
	printf("\t - Quantity: %d\n", product->quantity);
}