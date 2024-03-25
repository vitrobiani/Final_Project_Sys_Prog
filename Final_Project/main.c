#include "StoreManager.h"
#include "Store.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	eLOAD_FROM_FILE,
	eADD_STORE,
	eREMOVE_STORE,
	eVIEW_STORES,
	eENTER_STORE,
	eEXIT,
	eNumOfOptions
} Options;

const char* optionsStrings[] = {
	"Load from file",
	"Add a store",
	"Remove a store",
	"View all stores",
	"Enter a store",
	"Exit"
};

int lobby() {
	printf("Welcome to the store manager system!\n");
	
	for (int i = 0; i < eNumOfOptions; i++)
	{
		printf("%d. %s\n", i + 1, optionsStrings[i]);
	}

	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	return choice;
}

int main() {

	StoreManager storeManager;
	initStoreManager(&storeManager);

	int choice = lobby;

	switch (choice)
	{
	case ADD_STORE: {
		addStore(&storeManager);
		break;
	}

	default:
		break;
	}

	return 0;
}
