#pragma once
#ifndef MAIN
#define MAIN
#include "StoreManager.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	eADD_STORE,
	eADD_PRODUCT_TO_DEPARTMENT,
	eADD_EMPLOYEE,
	eENTER_STORE,
	eVIEW_STORES,
	eSORT_BY,
	eFIND_STORE,
	eCHAIN_BEST_SALESMAN,
	eCHAIN_BEST_SELLER,
	eEXIT,
	eNumOfOptions
} Options;

const char* optionsStrings[] = {
	"Add a store",
	"Add a product to a department type",
	"Add an employee to a store",
	"Enter a store",
	"View all stores",
	"Sort by",
	"Find a store",
	"Find the best salesman in the chain",
	"Find the best seller product in the chain",
	"Exit"
};

typedef enum {
	eADD_PRODUCT,
	eMAKE_SALE,
	ePRINT_EMPLOYEES,
	ePRINT_DEPARTMENTS,
	ePRINT_INVOICES,
	eBEST_SALESMAN,
	eBEST_SELLER,
	eGO_BACK,
	eNumOfStoreMenuOptions
}storeMenu;

const char* storeMenuStrings[] = {
	"Add a product",
	"Make a sale",
	"Print all employees",
	"Print all departments and their products",
	"Print all invoices",
	"Find the best salesman in the store",
	"Find the best seller product in the store",
	"Go back to the main menu"
};

int managerOptions();

int storeMenuOptions();

void storeLobby(Store* store, StoreManager* storeManager);

void ExitProgram(StoreManager* storeManager);


#endif // !MAIN