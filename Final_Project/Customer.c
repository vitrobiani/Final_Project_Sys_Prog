#include "Customer.h"

void setCustomerID(Customer* customer) {
	printf("Enter the ID of the customer: ");
	int id;
	do {
		scanf("%d", &id);
		if (id <= 0) {
			printf("Invalid ID, try again.\n");
		}
	} while (id <= 0);
	customer->id = id;
}

void setCustomerName(Customer* customer) {
	customer->name = getStrExactName("Enter the name of the customer: ");
}

void setContactNumber(Customer* customer) {
	printf("Enter the contact number of the customer: ");
	int contactNumber;
	do {
		scanf("%d", &contactNumber);
		if (contactNumber <= 0) {
			printf("Invalid contact number, try again.\n");
		}
	} while (contactNumber <= 0);
	customer->contactNumber = contactNumber;
}

void printCustomer(const Customer* customer) {
	printf("ID: %d\tName: %s\tContact Number: %d\n", customer->id, customer->name, customer->contactNumber);
}

int saveCustomerToBinaryFile(const Customer* customer, FILE* file)
{
	if (!writeIntToFile(customer->id, file, "Error writing customer ID to file\n"))
		return 0;
	if (!writeStringToFile(customer->name, file, "Error writing customer name to file\n"))
		return 0;
	if (!writeIntToFile(customer->contactNumber, file, "Error writing customer contact number to file\n"))
		return 0;
	return 1;
}

int loadCustomerFromBinaryFile(Customer* customer, FILE* file)
{
	if (!readIntFromFile(&customer->id, file, "Error reading customer ID from file\n"))
		return 0;
	customer->name = readStringFromFile(file, "Error reading customer name from file\n");
	if(!customer->name)
		return 0;
	if (!readIntFromFile(&customer->contactNumber, file, "Error reading customer contact number from file\n"))
		return 0;
	return 1;
}
