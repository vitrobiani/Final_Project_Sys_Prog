#include "StoreManager.h"

void initStoreManager(StoreManager* storeManager) {
	storeManager->stores = NULL;
	storeManager->noOfStores = 0;
	storeManager->departments = NULL;
	storeManager->noOfDepartmentTypes = 0;
}

void addStore(StoreManager* storeManager) {
	Store* store = (Store*)malloc(sizeof(Store));
	if (storeManager == NULL || store == NULL) {
		return;
	}
	createStore(store);
	Store** tmp = (Store**)realloc(storeManager->stores, (storeManager->noOfStores + 1) * sizeof(Store*));
	if (!tmp) {
		free(store);
		return;
	}
	storeManager->stores = tmp;
	storeManager->stores[storeManager->noOfStores++] = store;
}

void removeStore(StoreManager* storeManager, int storeID) {
}

void addDepartmentType(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return;
	}
	DepartmentType* departmentType = (DepartmentType*)malloc(sizeof(DepartmentType));
	if (!departmentType) {
		printf("error in allocating memory\n");
		return;
	}
	initDepartmentType(departmentType, generateDepartmentTypeID(storeManager));
	DepartmentType* tmp = (DepartmentType*)realloc(storeManager->departments, (storeManager->noOfDepartmentTypes + 1) * sizeof(DepartmentType));
	if (!tmp) {
		printf("error in allocating memory\n");
		free(departmentType);
		return;
	}
	storeManager->departments = tmp;
	storeManager->departments[storeManager->noOfDepartmentTypes] = *departmentType;
	storeManager->noOfDepartmentTypes++;
}

int generateDepartmentTypeID(const StoreManager* storeManager) {
	int id = 0;
	for (int i = 0; i < storeManager->noOfDepartmentTypes; i++) {
		if (storeManager->departments[i].id > id) {
			id = storeManager->departments[i].id;
		}
	}
	return id + 1;
}

DepartmentType* getDepartmentTypeByID(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return NULL;
	}
	printAllDepartmentTypes(storeManager);
	int departmentTypeID;
	printf("Enter the department type ID: ");
	DepartmentType* tmp = NULL;
	do
	{
		scanf("%d", &departmentTypeID);
		tmp = getDepartmentType(storeManager, departmentTypeID);
	} while (!tmp);
	return tmp;
}

DepartmentType* getDepartmentType(StoreManager* storeManager, int departmentTypeID) {
	if (storeManager == NULL) {
		return NULL;
	}
	for (int i = 0; i < storeManager->noOfDepartmentTypes; i++) {
		if (storeManager->departments[i].id == departmentTypeID) {
			return &storeManager->departments[i];
		}
	}
	return NULL;
}

void addProductToDepartment(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return;
	}
	printAllDepartmentTypes(storeManager);
	int departmentTypeID;
	printf("Enter the department type ID: ");
	scanf("%d", &departmentTypeID);
	DepartmentType* departmentType = getDepartmentType(storeManager, departmentTypeID);
	if (!departmentType) {
		printf("Department type not found!\n");
		return;
	}
	addProductToDepartmentType(departmentType);
	updateAllStoreDepartments(storeManager, departmentType);
}

void updateAllStoreDepartments(StoreManager* storeManager, DepartmentType* type) {
	if (storeManager == NULL) {
		return;
	}
	for (int i = 0; i < storeManager->noOfStores; i++) {
		for (int j = 0; j < storeManager->stores[i]->noOfDepartments; j++) {
			if (storeManager->stores[i]->departments[j].type->id == type->id) {
				Product* tmp = (Product*)realloc(storeManager->stores[i]->departments[j].products, sizeof(Product) * type->noOfProducts);
				if (!tmp) {
					return;
				}
				storeManager->stores[i]->departments[j].products = tmp;
				storeManager->stores[i]->departments[j].products[type->noOfProducts - 1] = type->products[type->noOfProducts - 1];
				storeManager->stores[i]->departments[j].noOfProducts = type->noOfProducts;
			}
		
		}
	}
}

Store* getStore(StoreManager* storeManager, int storeID) {
	if (storeManager == NULL) {
		return NULL;
	}
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (storeManager->stores[i]->storeID == storeID) {
			return storeManager->stores[i];
		}
	}
	return NULL;
}

Store* enterStore(StoreManager* storeManager) {
	if (storeManager == NULL) {
		return NULL;
	}
	for (int i = 0; i < storeManager->noOfStores; i++)
	{
		printStoreReduced(storeManager->stores[i]);
	}
	int storeID;
	printf("Enter the store ID: ");
	scanf("%d", &storeID);
	Store* store = getStore(storeManager, storeID);
	if (!store) {
		printf("Store not found!\n");
	}
	return store;
}

void printAllStores(const StoreManager* storeManager) {
	if (storeManager->stores == NULL) {
		printf("no stores!\n");
		return;
	}
	for (int i = 0; i < storeManager->noOfStores; i++) {
		printStore(storeManager->stores[i]);
	}
}

void printAllDepartmentTypes(const StoreManager* storeManager) {
	if (storeManager->departments == NULL) {
		printf("no department types!\n");
		return;
	}
	for (int i = 0; i < storeManager->noOfDepartmentTypes; i++) {
		printDepartmentType(&storeManager->departments[i]);
	}
}

void printAllDepartmentTypesFull(const StoreManager* storeManager) {
	if (storeManager->departments == NULL) {
		printf("no department types!\n");
		return;
	}
	for (int i = 0; i < storeManager->noOfDepartmentTypes; i++) {
		printDepartmentTypeFull(&storeManager->departments[i]);
	}
}