#include "Customer.h"

void initCustomer(Customer* customer, int CustomerID, const char* CustomerName, int contactNumber) {
	customer->CustomerID = CustomerID;
	customer->CustomerName = (char*)CustomerName;
	customer->contactNumber = contactNumber;
}

void printCustomer(const Customer* customer) {
	printf("Customer ID: %d\nCustomer Name: %s\nContact Number: %d\n", customer->CustomerID, customer->CustomerName, customer->contactNumber);
}