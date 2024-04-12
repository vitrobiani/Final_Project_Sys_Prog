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
		if (strlen(temp) != SIZE) {
			printf("code should be %d letters\n", SIZE);
			ok = 0;
		}
		else {
			for (int i = 0; i < SIZE; i++) {
				if (isupper(temp[i]) == 0) {
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
			printf("Price must be greater than 0, try again.\n");
		}
	} while (buyPrice <= 0);
	product->buyPrice = buyPrice;
	printf("\nEnter the sell price of product: ");
	int sellPrice;
	do {
		scanf("%d", &sellPrice);
		if (sellPrice <= buyPrice) {
			printf("Sell price must be greater than buy price, try again.\n");
		}
	} while (sellPrice <= buyPrice);
	product->sellPrice = sellPrice;
}

void updateQuantity(Product* product) {
	printf("Enter the quantity of the product: ");
	int quantity;
	do {
		scanf("%d", &quantity);
		if (quantity <= product->quantity) {
			printf("The quantity must be greater than the current quantity, try again.\n");
		}
	} while (quantity <= product->quantity);
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

int saveProductToTextFile(const Product* product, FILE* file) {
	if (!writeStringToTextFile(product->code, file, "Error saving Product code")) return 0;
	if (!writeStringToTextFile(product->name, file, "Error saving Product name")) return 0;
	if (!writeIntToTextFile(product->buyPrice, file, "Error saving Product buy price")) return 0;
	if (!writeIntToTextFile(product->sellPrice, file, "Error saving Product sell price")) return 0;
	if (!writeIntToTextFile(product->quantity, file, "Error saving Product quantity")) return 0;
	return 1;
}

int loadProductFromTextFile(Product* product, FILE* file) {
	fscanf(file, "%s", product->code);
	fgetc(file);

	char tmp[MAX_STR_LEN];
	myGetsFile(tmp, MAX_STR_LEN, file);
	product->name = getDynStr(tmp);

	if(!readIntFromTextFile(&product->buyPrice, file, "Error loading Product buy price")) return 0;
	if(!readIntFromTextFile(&product->sellPrice, file, "Error loading Product sell price")) return 0;
	if(!readIntFromTextFile(&product->quantity, file, "Error loading Product quantity")) return 0;
	return 1;
}

int saveProductToBinaryFile(const Product* product, FILE* file)
{
	if (!writeCharsToFile(product->code, 4, file, "Error writing product code to file\n"))
		return 0;
	if (!writeStringToFile(product->name, file, "Error writing product name to file\n"))
		return 0;
	if (!writeIntToFile(product->sellPrice, file, "Error writing product buy price to file\n"))
		return 0;
	if (!writeIntToFile(product->buyPrice, file, "Error writing product sell price to file\n"))
		return 0;
	if (!writeIntToFile(product->quantity, file, "Error writing product quantity to file\n"))
		return 0;
	return 1;
}

int loadProductFromBinaryFile(Product* product, FILE* file)
{
	if (!readCharsFromFile(product->code, 4, file, "Error reading product code from file\n"))
		return 0;
	product->name = readStringFromFile(file, "Error reading product name from file\n");
	if (!product->name)
		return 0;
	if (!readIntFromFile(&product->sellPrice, file, "Error reading product sell price from file\n"))
		return 0;
	if (!readIntFromFile(&product->buyPrice, file, "Error reading product buy price from file\n"))
		return 0;
	if (!readIntFromFile(&product->quantity, file, "Error reading product quantity from file\n"))
		return 0;
	return 1;
}