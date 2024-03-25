#include "StoreManager.h"

void addStore(StoreManager* storeManager) {
	Store* store = (Store*)malloc(sizeof(Store));
	if (storeManager == NULL || store == NULL) {
		return;
	}
	storeManager->stores = (Store**)realloc(storeManager->stores, (storeManager->noOfStores + 1) * sizeof(Store*));
	storeManager->stores[storeManager->noOfStores++] = store;
}

void removeStore(StoreManager* storeManager, int storeID) {
	if (storeManager == NULL) {
		return;
	}
	for (int i = 0; i < storeManager->noOfStores; i++) {
		if (storeManager->stores[i]->storeID == storeID) {
			free(storeManager->stores[i]);
			for (int j = i; j < storeManager->noOfStores - 1; j++) {
				storeManager->stores[j] = storeManager->stores[j + 1];
			}
			storeManager->stores = (Store**)realloc(storeManager->stores, (storeManager->noOfStores - 1) * sizeof(Store*));
			storeManager->noOfStores--;
			return;
		}
	}
}