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
	printf("Employee ID: %d\t Employee Name: %s\t Position: %s\n", employee->id, employee->name, ePositionStr[employee->position]);
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

void freeEmployee(Employee* employee) {
	free(employee->name);
}

void saveEmployeeToTextFile(const Employee* employee, FILE* file) {
	printf("Saving employee to file...\n");//debug
	fprintf(file, "%d\n", employee->id);
	fprintf(file, "%zu\n", strlen(employee->name));
	fprintf(file, "%s\n", employee->name);
	fprintf(file, "%d\n", employee->position);
	fprintf(file, "%d\n", employee->salary);
}

void loadEmployeeFromTextFile(Employee* employee, FILE* file) {
	fscanf(file, "%d\n", &employee->id);
	printf("Employee ID: %d\n", employee->id); //debug
	int nameLength;
	fscanf(file, "%d", &nameLength);
	employee->name = (char*)malloc(nameLength * sizeof(char));
	if (!employee->name) {
		return;
	}
	fscanf(file, "%s", employee->name);
	printf("Employee name: %s\n", employee->name); //debug
	fscanf(file, "%d", &employee->position);
	fscanf(file, "%d", &employee->salary);
	//printf("Emplyee name: %s position: %s salary: %d\n", employee->name, ePositionStr[employee->position], employee->salary); //debug
}