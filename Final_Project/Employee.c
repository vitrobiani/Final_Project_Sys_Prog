#include "Employee.h"

void initEmployee(Employee* employee, int employeeID, const char* employeeName, int contactNumber) {
	employee->id = employeeID;
	employee->name = (char*)employeeName;
	employee->salary = getSalary();
}

void printEmployee(const Employee* employee) {
	printf("Employee ID: %d\nEmployee Name: %s\nContact Number: %d\n", employee->id, employee->name);
}

int getSalary() {
	printf("Enter the salary: ");
	//TODO: validate input
	int salary;
	scanf("%d", &salary);
	return salary;
}

void printPositions() {
	printf("Positions: ");
	for (int i = 0; i < eNumOfPositions; i++) {
		printf("%d. %s\n", i + 1, ePositionStr[i]);
	}
}

ePosition getPosition() {
	printf("Enter the position: ");
	printPositions();
	int position;
	scanf("%d", &position);
	return position - 1;
}