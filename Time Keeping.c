#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 25
#define FILENAME "admin.txt"
#define EMPLOYEE_FILENAME "employees.dat"
#define PUNISHMENT_AMOUNT 20000
#define WORKING_HOURS_PER_MONTH 184




// Admin structure
struct Admin 
{
    char id[10];
    char password[20];
};

// Employee structure
struct Employee 
{
    char id[10];
    char fullName[100];
    int basicSalary;
    time_t checkInTime;
    time_t checkOutTime;
    int totalWorkingHours;
    int totalSalary;
};

// Function prototypes
void initialize();
void login();
void changeAdminPassword();
void inputEmployeeInformation();
void recordCheckIn();
void recordCheckOut();
void calculateSalary();
void AdminMode();
void NormalMode();
int main() {
    initialize();
    char mode;
    do
	{
        // Xóa màn hình, ch?y l?nh "clear" trên Linux/Mac ho?c "cls" trên Windows
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        printf("\n");
        printf("   +--------------------------------------+\n");
        printf("   |                                      |\n");
        printf("   |             MAIN MENU                |\n");
        printf("   |                                      |\n");
        printf("   +--------------------------------------+\n\n");

        printf("   Choose Mode:\n");
        printf("   Enter '1' for Admin Mode\n");
        printf("   Enter '2' for Normal Mode\n");
        printf("   Enter '3' to Exit\n\n");
        printf("   Mode: ");
        scanf(" %c", &mode); // Read user option

        switch (mode)
        {
            case '1': 
                //login();
                // Xóa màn hình, ch?y l?nh "clear" trên Linux/Mac ho?c "cls" trên Windows
                #ifdef _WIN32
                system("cls");
                #else
                system("clear");
                #endif             
                AdminMode();
                break;
            case '2':
                NormalMode();
                break;
            case '3':
                printf("Exiting program...\n");
                return 0;
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }while(1);
}

// Function to switch to admin mode
void AdminMode()
{
    char option;
        printf("\n");
    printf("   +--------------------------------------+\n");
    printf("   |                                      |\n");
    printf("   |             ADMIN MODE               |\n");
    printf("   |                                      |\n");
    printf("   +--------------------------------------+\n\n");

    printf("   Choose Option:\n");
    printf("   Enter '1' to Change Admin password\n");
    printf("   Enter '2' to Input Employee Information\n");
    printf("   Enter '3' to Calculate salary\n");
    printf("   Enter '4' to Return Main Meunu\n\n");

        
    do
    {
  
        printf("Option: ");
        scanf(" %c", &option); // Read user option

        switch (option)
        {
            case '1':
                changeAdminPassword();
                break;
            case '2':
                inputEmployeeInformation();
                break;
            case '3':
                calculateSalary();
                break;
            case '4':
               // returnToModeSelection = 0; // Set flag to exit loop
                return;               
                break;    
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
        printf("\n\n");
    }while(1);
}

// Function to switch to normal mode
void NormalMode() {
    char option;
   // int returnToModeSelection = 1; // Flag to control loop
      // Xóa màn hình, ch?y l?nh "clear" trên Linux/Mac ho?c "cls" trên Windows
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        printf("\n");
    printf("   +--------------------------------------+\n");
    printf("   |                                      |\n");
    printf("   |             NORMAL MODE              |\n");
    printf("   |                                      |\n");
    printf("   +--------------------------------------+\n\n");

    printf("   Choose Option:\n");
    printf("   Enter '1' to Record check-in\n");
    printf("   Enter '2' to Record check-out\n");
    printf("   Enter '3' to Return Main Menu\n\n");

    while (1) 
	{

        printf("Option: ");
        scanf(" %c", &option); // Read user option

        switch (option) {
            case '1':
                recordCheckIn();
                break;
            case '2':
                recordCheckOut();
                break;
            case '3':
                return; // Exit function
               // returnToModeSelection = 0; // Set flag to exit loop
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
        printf("\n\n");
    }
}

// Function to initialize the system
void initialize() 
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        // First time running, create admin file
        file = fopen(FILENAME, "w");
        struct Admin admin;
        strcpy(admin.id, "admin");
        strcpy(admin.password, "12345678");
        fwrite(&admin, sizeof(struct Admin), 1, file);
        fclose(file);
        printf("Admin file created. Default ID: admin, Default password: 12345678\n");
        login();
        changeAdminPassword();
    } else {
        fclose(file);
    }
}

// Function to log in as admin
void login() 
{
    struct Admin admin;
    FILE *file = fopen(FILENAME, "r");
    fread(&admin, sizeof(struct Admin), 1, file);
    fclose(file);

    char inputID[10];
    char inputPassword[20];

    printf("Enter admin ID: ");
    scanf("%s", inputID);
    do
	{
	    printf("Enter password: ");
	    scanf("%s", inputPassword);
	
	    if (strcmp(inputID, admin.id) == 0 && strcmp(inputPassword, admin.password) == 0) 
		{
	        printf("Login successful!\n");
	        // Proceed with admin actions
    	} 
		else 
		{
	        printf("Invalid credentials. Please try again.\n");
	    }
    }while(strcmp(inputID, admin.id) != 0 || strcmp(inputPassword, admin.password) != 0);
}

// Function to change admin password
void changeAdminPassword() 
{
    struct Admin admin;
    FILE *file = fopen(FILENAME, "r+");
    fread(&admin, sizeof(struct Admin), 1, file);

    char newPassword[20];

    printf("Enter new password: ");
    scanf("%s", newPassword);
    strcpy(admin.password, newPassword);

    fseek(file, 0, SEEK_SET);
    fwrite(&admin, sizeof(struct Admin), 1, file);
    fclose(file);

    printf("Password changed successfully!\n");
}

// Function to input employee informationa
void inputEmployeeInformation() {
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    // Open the file for reading to see if it exists and to load existing data
    FILE *file = fopen(EMPLOYEE_FILENAME, "r");
    if (file == NULL) {
        // If file doesn't exist, initialize number of employees to 0
        file = fopen(EMPLOYEE_FILENAME, "w"); // Create the file
        if (file) {
            fwrite(&numEmployees, sizeof(int), 1, file); // Write 0 employees initially
        }
        fclose(file);
    } else {
        // Read the number of employees and their data
        fread(&numEmployees, sizeof(int), 1, file);
        fread(employees, sizeof(struct Employee), numEmployees, file);
        fclose(file);
    }

    char continueAdding = 'y'; // Variable to control the loop

    while (continueAdding == 'y') {
        if (numEmployees >= MAX_EMPLOYEES) {
            printf("Maximum number of employees reached.\n");
            break;
        }

        printf("Enter employee ID: ");
        scanf("%s", employees[numEmployees].id);
        while (getchar() != '\n'); // Clear input buffer

        printf("Enter employee full name: ");
        fgets(employees[numEmployees].fullName, MAX_NAME_LENGTH, stdin);
        employees[numEmployees].fullName[strcspn(employees[numEmployees].fullName, "\n")] = '\0'; // Remove trailing newline

        printf("Enter employee basic salary: ");
        scanf("%d", &employees[numEmployees].basicSalary);
        while (getchar() != '\n'); // Clear input buffer after reading int

        numEmployees++; // Increase the count of employees

        // Ask if user wants to add another employee
        printf("Do you want to add another employee? (y/n): ");
        scanf("%c", &continueAdding);
        while (getchar() != '\n'); // Clear buffer after reading char
    }

    // Open the file for writing to save the updated data
    file = fopen(EMPLOYEE_FILENAME, "w");
    if (file != NULL) {
        fwrite(&numEmployees, sizeof(int), 1, file);
        fwrite(employees, sizeof(struct Employee), numEmployees, file);
        fclose(file);
    }
}

void recordCheckIn() {
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees;

    FILE *file = fopen(EMPLOYEE_FILENAME, "r");
    fread(&numEmployees, sizeof(int), 1, file);
    fread(employees, sizeof(struct Employee), numEmployees, file);
    fclose(file);

    char employeeID[10];
    printf("Enter employee ID for check-in: ");
    scanf("%s", employeeID);

    int i, confirmation;
    for (i = 0; i < numEmployees; i++) {
        if (strcmp(employees[i].id, employeeID) == 0) {
            printf("Employee found: %s. Is this you? (1 for Yes, 0 for No): ", employees[i].fullName);
            scanf("%d", &confirmation);
            if (confirmation == 1) {
                // Get current time
                time_t currentTime;
                time(&currentTime);

                // Calculate difference in minutes between check-in time and 8:00 AM
                struct tm *tm_struct = localtime(&currentTime);
                int checkInHour = tm_struct->tm_hour;
                int checkInMinute = tm_struct->tm_min;
                int checkInTotalMinutes = checkInHour * 60 + checkInMinute;
                int standardCheckInTotalMinutes = 8 * 60; // 8:00 AM

                int minutesLate = checkInTotalMinutes - standardCheckInTotalMinutes;
                if (minutesLate > 30) {
                    printf("You are more than 30 minutes late. Salary will be deducted by %d VND.\n", PUNISHMENT_AMOUNT);
                    employees[i].basicSalary -= PUNISHMENT_AMOUNT;
                }

                employees[i].checkInTime = currentTime;
                printf("Check-in recorded for %s at %02d:%02d.\n", employees[i].fullName, checkInHour, checkInMinute);
            } else {
                printf("Check-in cancelled.\n");
            }
            break;
        }
    }

    if (i == numEmployees) {
        printf("Employee ID not found.\n");
    }

    file = fopen(EMPLOYEE_FILENAME, "w");
    fwrite(&numEmployees, sizeof(int), 1, file);
    fwrite(employees, sizeof(struct Employee), numEmployees, file);
    fclose(file);
}





void recordCheckOut() {
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees;

    FILE *file = fopen(EMPLOYEE_FILENAME, "r");
    if (!file) {
        printf("Failed to open file for reading.\n");
        return;
    }
    fread(&numEmployees, sizeof(int), 1, file);
    fread(employees, sizeof(struct Employee), numEmployees, file);
    fclose(file);

    char employeeID[10];
    printf("Enter employee ID for check-out: ");
    scanf("%s", employeeID);

    int i, confirmation;
    for (i = 0; i < numEmployees; i++) {
        if (strcmp(employees[i].id, employeeID) == 0) {
            printf("Employee found: %s. Is this you? (1 for Yes, 0 for No): ", employees[i].fullName);
            scanf("%d", &confirmation);
            if (confirmation == 1) {
                time_t currentTime;
                time(&currentTime);

                // Calculate the number of hours worked
                double hoursWorked = difftime(currentTime, employees[i].checkInTime) / 3600.0;  //convert seconds to hours
                employees[i].totalWorkingHours += hoursWorked;  // Update total working hours

                if (hoursWorked < 8.0) {
                    double hoursShort = 8.0 - hoursWorked;
                    printf("You have worked only %.2f hours. You are %.2f hours short of the required 8 hours.\n", hoursWorked, hoursShort);
                    printf("Salary may be deducted accordingly.\n");
                    // Consider adding specific penalty handling here
                }

                employees[i].checkOutTime = currentTime;
                printf("Check-out recorded for %s at %02d:%02d. Total working hours this month: %.2f\n", employees[i].fullName, localtime(&currentTime)->tm_hour, localtime(&currentTime)->tm_min, employees[i].totalWorkingHours);
            } else {
                printf("Check-out cancelled.\n");
            }
            break;
        }
    }

    if (i == numEmployees) {
        printf("Employee ID not found.\n");
    }

    file = fopen(EMPLOYEE_FILENAME, "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }
    fwrite(&numEmployees, sizeof(int), 1, file);
    fwrite(employees, sizeof(struct Employee), numEmployees, file);
    fclose(file);
}

void calculateSalary() {
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees;

    FILE *file = fopen(EMPLOYEE_FILENAME, "r");
    if (file == NULL) {
        printf("You need to input Employee Information\n");
        return;
    }

    fread(&numEmployees, sizeof(int), 1, file);
    fread(employees, sizeof(struct Employee), numEmployees, file);
    fclose(file);

    printf("%5s %25s %20s %20s %20s %20s\n", "ID", "Full Name","Basic Salary", " Actual Salary", "Working Hours","Total Salary");
    for (int i = 0; i < numEmployees; i++) {
        // Access stored total working hours directly
        double workingHours = employees[i].totalWorkingHours;
		double hoursWorked = difftime(employees[i].checkOutTime, employees[i].checkInTime) / 3600.0;



        // Calculate salary based on rules
        double actualSalary = employees[i].basicSalary * hoursWorked;
        if (workingHours > WORKING_HOURS_PER_MONTH) {
           // employees[i].totalSalary = employees[i].basicSalary * WORKING_HOURS_PER_MONTH; // Cap at maximum monthly hours
        }

        // Check for late check-in or early check-out
        struct tm *inTime = localtime(&employees[i].checkInTime);
        struct tm *outTime = localtime(&employees[i].checkOutTime);

        // Assume 8 AM is standard check-in time
        int latePenalty = 0;
        if (inTime->tm_hour > 8 || (inTime->tm_hour == 8 && inTime->tm_min > 30)) {
            actualSalary -= PUNISHMENT_AMOUNT;
        }

       // // Assume 5 PM is standard check-out time (only for the last recorded check-out time)
        int earlyPenalty = 0;
        if ( workingHours*60 < 7*60 + 30) {
            actualSalary -= PUNISHMENT_AMOUNT;
        }
		employees[i].totalSalary+=actualSalary;
        // Apply penalties
        //actualSalary -= (latePenalty + earlyPenalty);

        printf("%5s %25s %20d %20d %20d %20d\n", employees[i].id, employees[i].fullName, employees[i].basicSalary, actualSalary, workingHours,employees[i].totalSalary );
    }
}

