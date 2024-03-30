#include "Customer.h"

void initCustomer(Customer* customer) {
	setCustomerID(customer);
	setCustomerName(customer);
	setContactNumber(customer);
}

void setCustomerID(Customer* customer) {
	printf("Enter the ID of the customer: ");
	int id;
	do {
		scanf("%d", &id);
		if (id < 0) {
			printf("Invalid ID\n");
		}
	} while (id < 0);
	customer->id = id;
}

void setCustomerName(Customer* customer) {
	printf("Enter the name of the customer: ");
	char name[MAX_STR_LEN];
	myGets(name, MAX_STR_LEN);
	customer->name = malloc(strlen(name)*sizeof(char));
	if(!customer->name)
	{
		printf("error in allocating memory\n");
		return;
	}
	strcpy(customer->name, name);
}

void setContactNumber(Customer* customer) {
	printf("Enter the contact number of the customer: ");
	int contactNumber;
	do {
		scanf("%d", &contactNumber);
		if (contactNumber < 0) {
			printf("Invalid contact number\n");
		}
	} while (contactNumber < 0);
	customer->contactNumber = contactNumber;
}

void printCustomer(const Customer* customer) {
	printf("Customer ID: %d\nCustomer Name: %s\nContact Number: %d\n", customer->id, customer->name, customer->contactNumber);
}