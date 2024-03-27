#include "Employee.h"

void initEmployee(Employee* employee) {
	employee->id = getEmployeeID();
	employee->name = getStrExactName("Enter Employee name: ");
	employee->salary = getSalary();
	employee->position = getPosition();
}

int getEmployeeID() {
	int id;
	printf("Enter the employee ID: ");
	do {
		scanf("%d", &id);
		if (id < 0) {
			printf("Invalid ID, please enter a positive number: ");
		}
	} while (id < 0);
	return id;
}

void printEmployee(const Employee* employee) {
	printf("Employee ID: %d\nEmployee Name: %s\n", employee->id, employee->name);
}

int getSalary() {
	printf("Enter the salary: ");
	//TODO: validate input
	int salary;
	scanf("%d", &salary);
	return salary;
}

void printPositions() {
	printf("Positions: \n");
	for (int i = 0; i < eNumOfPositions; i++) {
		printf("%d. %s\n", i + 1, ePositionStr[i]);
	}
}

ePosition getPosition() {
	printf("\nEnter the position: \n");
	printPositions();
	int position;
	do {
		scanf("%d", &position);
	} while (position < 1 || position > eNumOfPositions);
	return position - 1;
}