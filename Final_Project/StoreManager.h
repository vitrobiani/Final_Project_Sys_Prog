#pragma once

#ifndef STOREMANAGER
#define STOREMANAGER
#include "Store.h"
#include <stdio.h>
#include <stdlib.h>
#include "Macros.h"

typedef enum { eNone, eID, eRent, eLocation, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = { "NotSorted", "ID", "Rent", "Location" };

typedef enum { eLoadFromTextFile, eLoadFromBinaryFile, eLoadNewSystem, eNoOfLoadOptions} eLoadOptions;
static const char* loadOptionsStr[eNoOfLoadOptions] = { "Load From Text File", "Load From Binary File", "Load New System" };

typedef struct StoreManager {
	Store** stores;
	int noOfStores;
	eSortOption storeSortOpt;
} StoreManager;

void initStoreManager(StoreManager* storeManager);

void loadSystem(StoreManager* storeManager);

void generateHQ(StoreManager* storeManager);

int generateStoreID(const StoreManager* storeManager);

void addStore(StoreManager* storeManager);

Store* getStore(StoreManager* storeManager, int storeID);

void addProductToDepartmentType(StoreManager* storeManager);

void addProductToMainStore(StoreManager* storeManager, int departmentID ,Product* product);

void updateAllStoreDepartments(StoreManager* storeManager);

int checkIfProductCodeExists(const StoreManager* storeManager, const char* productCode);

void printAllChainEmployees(const StoreManager* storeManager);

void addEmployeeToStore(StoreManager* storeManager, Store* store);

void initEmployee(StoreManager* storeManager, Employee* employee);

int getEmployeeID(StoreManager* storeManager);

int isEmployeeIDUnique(StoreManager* storeManager, int id);

Store* enterStore(StoreManager* storeManager);

void sortAllStoresBy(StoreManager* storeManager);

eSortOption showSortMenu();

void findStore(const StoreManager* storeManager);

void printAllStores(const StoreManager* storeManager);

void freeStoreManager(StoreManager* storeManager);

void findChainBestSalesMan(const StoreManager* storeManager);

Product* getChainBestSellerProduct(const StoreManager* storeManager, int* quantity, int year, int mouth);

void findChainBestSellerProduct(const StoreManager* storeManager);

void saveStoreManagerToTextFile(const StoreManager* storeManager, const char* fileName);

void loadStoreManagerFromTextFile(StoreManager* storeManager, const char* fileName);

int saveStoreManagerToBinaryFile(const StoreManager* storeManager, const char* fileName);

int createStoreArr(StoreManager* storeManager);

int loadStoreManagerFromBinaryFile(StoreManager* storeManager, const char* fileName);

void initStoreManagerFromBinaryFile(StoreManager* storeManager, const char* fileName);

#endif // !1