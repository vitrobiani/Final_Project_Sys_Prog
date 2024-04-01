#include "Product.h"

void initProduct(Product* product) {
	getProductName(product);
	getPrice(product);
	product->quantity = 0;
}

void getProductCode(char* code) {
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter Product code  - %d UPPER CASE letters\t", SIZE);
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

void updateQuantity(Product* product) {
	printf("Enter the quantity of the product: ");
	int quantity;
	do {
		scanf("%d", &quantity);
		if (quantity < 0) {
			printf("Quantity must be a positive number\n");
		}
	} while (quantity < 0);
	product->quantity = quantity;
}

void printForInvoice(const Product* product) {
	if (product == NULL) {
		return;
	}
	printf("\t# Product Name: %s", product->name);
	printf("\tProduct Code: %s\n", product->code);
	printf("\tSell Price: %d", product->sellPrice);
	printf("\t - Quantity: %d\n", product->quantity);
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

void freeProduct(Product* product) {
	free(product->name);
	product->name = NULL;
}

void saveProductToTextFile(const Product* product, FILE* file) {
	printf("Saving product to file\n"); //debug
	fprintf(file, "%s\n", product->code);
	fprintf(file, "%zu\n", strlen(product->name));
	fprintf(file, "%s\n", product->name);
	fprintf(file, "%d\n", product->buyPrice);
	fprintf(file, "%d\n", product->sellPrice);
	fprintf(file, "%d\n", product->quantity);
}

void loadProductFromTextFile(Product* product, FILE* file) {
	printf("Loading product from file\n"); //debug
	fscanf(file, "%s", product->code);
	fgetc(file);
	printf("code: %s\n", product->code); //debug
	int length;
	fscanf(file, "%d", &length);
	fgetc(file);
	printf("length: %d\n", length); //debug
	product->name = (char*)malloc(length + 1);
	if (product->name == NULL) {
		return;
	}
	fscanf(file, "%[^\n]", product->name);
	fgetc(file);
	printf("name: %s\n", product->name); //debug
	fscanf(file, "%d", &product->buyPrice);
	fgetc(file);
	printf("buy price: %d\n", product->buyPrice); //debug
	fscanf(file, "%d", &product->sellPrice);
	fgetc(file);
	printf("sell price: %d\n", product->sellPrice); //debug
	fscanf(file, "%d", &product->quantity);
	fgetc(file);
	printf("quantity: %d\n", product->quantity); //debug
};