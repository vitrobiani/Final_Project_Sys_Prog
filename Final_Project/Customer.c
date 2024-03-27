#include "Customer.h"

void initCustomer(Customer* customer, int CustomerID, const char* CustomerName, int contactNumber) {
	customer->id = CustomerID;
	customer->name = (char*)CustomerName;
	customer->contactNumber = contactNumber;
}

void printCustomer(const Customer* customer) {
	printf("Customer ID: %d\nCustomer Name: %s\nContact Number: %d\n", customer->id, customer->name, customer->contactNumber);
}