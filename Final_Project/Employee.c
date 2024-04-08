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
