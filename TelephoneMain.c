#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define MAX_CALLS 100
struct Call {
    char timestamp[20]; // Format: YYYY-MM-DD HH:MM
    float duration;     // Call duration in minutes
};
struct CustomerDetails {
    char customerName[50];
    char phoneNumber[16];
    float billingRate; 
    struct Call calls[MAX_CALLS];
    int callCount;
};
// Function prototype
void addCustomer(struct CustomerDetails customers[], int *customerCount);
void recordCall(struct CustomerDetails customers[], int customerCount);
void generateBill(struct CustomerDetails customers[], int customerCount);


int main(){
    struct CustomerDetails customers[MAX_CUSTOMERS];
    int customerCount = 0;
    int choice;

    do{
        printf("\nTelephone Billing System\n");
        printf("1. Add Customer\n");
        printf("2. Record Call\n");
        printf("3. Generate Bill\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: addCustomer(customers, &customerCount); break;
            case 2:
                recordCall(customers, customerCount);
                break;
            case 3: generateBill(customers, customerCount); break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while(choice != 4);
    
    return 0;
}

void addCustomer(struct CustomerDetails customers[], int *customerCount){
    if(*customerCount < MAX_CUSTOMERS){
        printf("Enter customer customerName: ");
        getchar(); // Clear the newline character from the buffer
        fgets(customers[*customerCount].customerName, sizeof(customers[*customerCount].customerName), stdin);
        customers[*customerCount].customerName[strcspn(customers[*customerCount].customerName, "\n")] = 0; // Remove newline

        printf("Enter phone number: ");
        fgets(customers[*customerCount].phoneNumber, sizeof(customers[*customerCount].phoneNumber), stdin);
        customers[*customerCount].phoneNumber[strcspn(customers[*customerCount].phoneNumber, "\n")] = 0; // Remove newline

        printf("Enter billing rate per minute: ");
        scanf("%f", &customers[*customerCount].billingRate);
        
        customers[*customerCount].callCount = 0; // Initialize call count
        (*customerCount)++;
    }
    else{
        printf("Customer limit reached. Cannot add more customers.\n");
    }
}

void recordCall(struct CustomerDetails customers[], int customerCount) {
    char phoneNumber[15];
    printf("Enter customer phone number to record a call: ");
    getchar(); // Clear the newline character
    fgets(phoneNumber, sizeof(phoneNumber), stdin);
    phoneNumber[strcspn(phoneNumber, "\n")] = 0; // Remove newline

    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].phoneNumber, phoneNumber) == 0) {
            if (customers[i].callCount < MAX_CALLS) {
                printf("Enter call duration (in minutes): ");
                scanf("%f", &customers[i].calls[customers[i].callCount].duration);
                printf("Enter call timestamp (YYYY-MM-DD HH:MM): ");
                getchar(); // Clear the newline character
                fgets(customers[i].calls[customers[i].callCount].timestamp, sizeof(customers[i].calls[customers[i].callCount].timestamp), stdin);
                customers[i].calls[customers[i].callCount].timestamp[strcspn(customers[i].calls[customers[i].callCount].timestamp, "\n")] = 0; // Remove newline

                customers[i].callCount++;
                printf("Call recorded successfully!\n");
            } else {
                printf("Call limit reached for this customer.\n");
            }
            return;
        }
    }
    printf("Customer with phone number %s not found.\n", phoneNumber);
}

void generateBill(struct CustomerDetails customers[], int customerCount){
    char phoneNumber[15];
    printf("Enter the phone number to generate phone bill: \n");
    getchar();
    fgets(phoneNumber, sizeof(phoneNumber), stdin);
    phoneNumber[strcspn(phoneNumber, "\n")] = 0; //Remove newline;

    for(int i = 0; i < customerCount; i++){
        if(strcmp(customers[i].phoneNumber, phoneNumber) == 0){
            float totalBill = 0;
            printf("Total bill for %s with phone number %s: \n", customers[i].customerName, customers[i].phoneNumber);
            for(int j = 0; j < customers[i].callCount; j++){
                totalBill = totalBill + customers[i].calls[j].duration*customers[i].billingRate;
                printf("Call Duration: %.2f minutes, Timestamp: %s\n", customers[i].calls[j].duration, customers[i].calls[j].timestamp);
            }
            printf("Total Bill %.2f \n", totalBill);
            return;
        }
    }
    printf("Customer with phone number %s not found.\n", phoneNumber);
}