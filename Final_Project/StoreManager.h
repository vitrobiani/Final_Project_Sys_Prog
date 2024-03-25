#pragma once

#ifndef STOREMANAGER
#define STOREMANAGER
#include "Store.h"
#include "Product.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct StoreManager {
	Store** stores;
	int noOfStores;
	departmentType* departments;
} StoreManager;

void addStore(StoreManager* storeManager);

void removeStore(StoreManager* storeManager, int storeID);

Store* getStore(StoreManager* storeManager, int storeID);

void addDepartmentType(StoreManager* storeManager);

void addProductToDepartment(StoreManager* storeManager);

#endif // !1