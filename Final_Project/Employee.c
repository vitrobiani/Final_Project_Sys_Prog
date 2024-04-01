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
	printf("Enter the yearly salary: ");
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
	fprintf(file, "%d\n", employee->id);
	fprintf(file, "%s\n", employee->name);
	fprintf(file, "%d\n", employee->position);
	fprintf(file, "%d\n", employee->salary);
}

void loadEmployeeFromTextFile(Employee* employee, FILE* file) {
	fscanf(file, "%d", &employee->id);
	fgetc(file);
		
	char tmp[MAX_STR_LEN];
	myGetsFile(tmp, MAX_STR_LEN, file);
	employee->name = getDynStr(tmp);
	
	fscanf(file, "%d", &employee->position);
	fgetc(file);
	fscanf(file, "%d", &employee->salary);
	fgetc(file);
}

int saveEmployeeToBinaryFile(const Employee* employee, FILE* file)
{
	if (!writeIntToFile(employee->id, file, "Error writing employee ID to file\n"))
		return 0;
	if(!writeStringToFile(employee->name, file, "Error writing employee name to file\n"))
		return 0;
	if (fwrite(&employee->position, sizeof(ePosition), 1, file) != 1)
		{
			puts("Error writing employee position to file");
			return 0;
		}
	if (!writeIntToFile(employee->salary, file, "Error writing employee salary to file\n"))
		return 0;
	return 1;
}
