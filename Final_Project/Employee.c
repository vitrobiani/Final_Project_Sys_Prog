#include "Employee.h"

void printEmployee(const Employee* employee) {
	printf("Employee ID: %d\t Employee Name: %s\t Position: %s\t salary: %d\n", employee->id, employee->name, ePositionStr[employee->position], employee->salary);
}

int getSalary() {
	printf("Enter the salary: ");
	int salary;
	do {
		scanf("%d", &salary);
		if (salary <= 0)
			printf("Salary must be a positive number, try again.\n");
	} while (salary <= 0);
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
		if (position < 1 || position > eNumOfPositions)
			printf("\nInvalid position, please enter a number between 1 - %d: ", eNumOfPositions);
	} while (position < 1 || position > eNumOfPositions);
	return position - 1;
}

void freeEmployee(Employee* employee) {
	free(employee->name);
}

int saveEmployeeToTextFile(const Employee* employee, FILE* file) {
	if (!writeIntToTextFile(employee->id, file, "Error saving ID")) return 0;
	if (!writeStringToTextFile(employee->name, file, "Error saving Name")) return 0;
	if (!writeIntToTextFile(employee->position, file, "Error saving Position")) return 0;
	if (!writeIntToTextFile(employee->salary, file, "Error saving Salary")) return 0;
	return 1;
}

int loadEmployeeFromTextFile(Employee* employee, FILE* file) {
	if (!readIntFromTextFile(&employee->id, file, "Error loading ID")) return 0;

	char tmp[MAX_STR_LEN];
	myGetsFile(tmp, MAX_STR_LEN, file);
	employee->name = getDynStr(tmp);
	
	int position;
	if (!readIntFromTextFile(&position, file, "Error loading Position")) return 0;
	employee->position = position;
	if (!readIntFromTextFile(&employee->salary, file, "Error loading Salary")) return 0;
	return 1;
}

int saveEmployeeToBinaryFile(const Employee* employee, FILE* file)
{
	if (!writeIntToFile(employee->id, file, "Error writing employee ID to file\n"))
		return 0;
	if (!writeStringToFile(employee->name, file, "Error writing employee name to file\n"))
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

int loadEmployeeFromBinaryFile(Employee* employee, FILE* file)
{
	if (!readIntFromFile(&employee->id, file, "Error reading employee ID from file\n"))
		return 0;
	employee->name = readStringFromFile(file, "Error reading employee name from file\n");
	if (!employee->name)
		return 0;
	if (fread(&employee->position, sizeof(ePosition), 1, file) != 1)
	{
		puts("Error reading employee position from file");
		return 0;
	}
	if (!readIntFromFile(&employee->salary, file, "Error reading employee salary from file\n"))
		return 0;
	return 1;
}
