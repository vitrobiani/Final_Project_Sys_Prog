#include "Store.h"

int createStore(Store* store) {
	if (store == NULL) {
		return 0;
	}
	printf("Enter the rent of the store: ");
	scanf("%d", &store->rent);
	initStore(store);

	return 1;
}

int initStore(Store* store) {
	store->storeID = createStoreID;
	store->employees = NULL;
	store->noOfEmployees = 0;
	store->departments = NULL;
	store->noOfDepartments = 0;

	L_init(&store->invoiceList);
	return 1;
}

int createStoreID() {
	static int storeID = 0;
	return ++storeID;
}