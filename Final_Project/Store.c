#include "Store.h"

int createStore(Store* store) {
	printf("Enter the rent of the store: ");
	scanf("%d", &store->rent);

	store->location = getStrExactName("Enter the location of the store: ");

	initStore(store);

	return 1;
}

int initStore(Store* store) {
	store->storeID = createStoreID();
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

void addEmployee(Store* store) {
	if (store == NULL) {
		return;
	}
	Employee* emp = malloc(sizeof(Employee));
	if (emp == NULL) {
		return;
	}
	initEmployee(emp);
	Employee* tmp = (Employee*)realloc(store->employees, (store->noOfEmployees + 1) * sizeof(Employee));
	if (!tmp) {
		free(emp);
		return;
	}
	store->employees = tmp;
	store->employees[store->noOfEmployees] = *emp;
	store->noOfEmployees++;
}

void addDepartment(Store* store, DepartmentType* type) {
	Department* department = (Department*)malloc(sizeof(Department));
	if (store == NULL || department == NULL) {
		return;
	}
	
	printf("Enter the department type: ");

	initDepartment(department, type);

	Department* tmp = (Department*)realloc(store->departments, (store->noOfDepartments + 1) * sizeof(Department));
	if (!tmp) {
		return;
	}
	store->departments = tmp;
	store->departments[store->noOfDepartments] = *department;
	store->noOfDepartments++;
}

void printAllDepartments(const Store* store) {
	if (store == NULL) {
		return;
	}
	for (int i = 0; i < store->noOfDepartments; i++) {
		printDepartmentFull(&store->departments[i]);
	}
}

void printStoreReduced(const Store* store) {
	if (store == NULL) {
		return;
	}
	printf("\n# Store ID: %d\t", store->storeID);
	printf("Location: %s\n", store->location);
}

void printStore(const Store* store) {
	if (store == NULL) {
		return;
	}
	printf("\n# Store ID: %d\t", store->storeID);
	printf("Location: %s\n", store->location);
	printf("\tRent: %d\n", store->rent);
	printf("\tNumber of employees: %d\n", store->noOfEmployees);
	printf("departments in the store: \n");
	for (int i = 0; i < store->noOfDepartments; i++) {
		printf("\t%s\n", store->departments[i].type->name);
	}
}