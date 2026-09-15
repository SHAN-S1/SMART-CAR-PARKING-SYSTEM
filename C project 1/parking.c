#include <stdio.h>
#include <string.h>

#define MAX_SLOTS 10

struct Vehicle
{
    int slotNumber;
    char vehicleNumber[20];
    char ownerName[50];
    int vehicleType;
    int isOccupied;
};

/* Function Prototypes */
void showMenu();

void parkVehicle(struct Vehicle parking[]);

void removeVehicle(struct Vehicle parking[],
                   int *totalRevenue,
                   int *totalVehiclesServed);

void searchVehicle(struct Vehicle parking[]);

void displayStatus(struct Vehicle parking[]);

void updateVehicle(struct Vehicle parking[]);

void parkingReport(struct Vehicle parking[],
                   int totalRevenue,
                   int totalVehiclesServed);

void searchFilter(struct Vehicle parking[]);

void saveData(struct Vehicle parking[],
              int totalRevenue,
              int totalVehiclesServed);

void loadData(struct Vehicle parking[],
              int *totalRevenue,
              int *totalVehiclesServed);


/* ================= MENU ================= */

void showMenu()
{
    printf("\n========== SMART PARKING ==========\n");
    printf("1. Park Vehicle\n");
    printf("2. Remove Vehicle\n");
    printf("3. Search Vehicle\n");
    printf("4. Display Parking Status\n");
    printf("5. Update Vehicle\n");
    printf("6. Parking Report\n");
    printf("7. Search / Filter\n");
    printf("8. Exit\n");
    printf("===================================\n");
}


/* ================= PARK VEHICLE ================= */

void parkVehicle(struct Vehicle parking[])
{
    int slot;
    int found = 0;

    printf("\n========== AVAILABLE SLOTS ==========\n");

    for(int i = 0; i < MAX_SLOTS; i++)
    {
        if(parking[i].isOccupied == 0)
        {
            printf("Slot %d : AVAILABLE\n", i + 1);
            found = 1;
        }
    }

    if(found == 0)
    {
        printf("\nParking Full! No slot available.\n");
        return;
    }

    printf("\nEnter Slot Number: ");

    if(scanf("%d", &slot) != 1)
    {
        printf("\nInvalid input! Please enter a number.\n");
        while(getchar() != '\n');
        return;
    }

    if(slot < 1 || slot > MAX_SLOTS)
    {
        printf("\nInvalid Slot Number!\n");
        return;
    }

    if(parking[slot - 1].isOccupied == 1)
    {
        printf("\nSlot %d is already occupied!\n", slot);
        return;
    }

    /* Vehicle Number */
    printf("\nEnter Vehicle Number: ");
    scanf("%19s", parking[slot - 1].vehicleNumber);

    /* Duplicate Vehicle Check */
    for(int i = 0; i < MAX_SLOTS; i++)
    {
        if(i != slot - 1 &&
           parking[i].isOccupied == 1 &&
           strcmp(parking[i].vehicleNumber,
                  parking[slot - 1].vehicleNumber) == 0)
        {
            printf("\nVehicle already parked!\n");

            parking[slot - 1].vehicleNumber[0] = '\0';

            return;
        }
    }

    /* Owner Name */
    printf("Enter Owner Name: ");
    scanf(" %49[^\n]", parking[slot - 1].ownerName);

    /* Vehicle Type */
    printf("Enter Vehicle Type (1-Car, 2-Bike): ");

    if(scanf("%d", &parking[slot - 1].vehicleType) != 1)
    {
        printf("\nInvalid Vehicle Type!\n");

        while(getchar() != '\n');

        parking[slot - 1].vehicleNumber[0] = '\0';
        parking[slot - 1].ownerName[0] = '\0';

        return;
    }

    if(parking[slot - 1].vehicleType != 1 &&
       parking[slot - 1].vehicleType != 2)
    {
        printf("\nInvalid Vehicle Type!\n");

        parking[slot - 1].vehicleNumber[0] = '\0';
        parking[slot - 1].ownerName[0] = '\0';
        parking[slot - 1].vehicleType = 0;

        return;
    }

    /* Store Slot Information */
    parking[slot - 1].slotNumber = slot;
    parking[slot - 1].isOccupied = 1;

    printf("\n=================================\n");
    printf("Vehicle parked successfully!\n");
    printf("Your Parking Slot: %d\n", slot);
    printf("=================================\n");
}


/* ================= REMOVE VEHICLE ================= */

void removeVehicle(struct Vehicle parking[],
                   int *totalRevenue,
                   int *totalVehiclesServed)
{
    char vehicleNumber[20];

    int found = 0;
    int hours;
    int fee;

    printf("\nEnter Vehicle Number: ");
    scanf("%19s", vehicleNumber);

    for(int i = 0; i < MAX_SLOTS; i++)
    {
        if(parking[i].isOccupied == 1 &&
           strcmp(parking[i].vehicleNumber,
                  vehicleNumber) == 0)
        {
            printf("\nVehicle Found!");

            printf("\nOwner Name: %s",
                   parking[i].ownerName);

            printf("\nParking Slot: %d",
                   parking[i].slotNumber);

            printf("\n\nEnter Parking Hours: ");

            if(scanf("%d", &hours) != 1)
            {
                printf("\nInvalid input! Please enter a number.\n");
                while(getchar() != '\n');
                return;
            }

            if(hours <= 0)
            {
                printf("\nInvalid number of hours!\n");
                return;
            }

            /* Calculate Fee */
            if(parking[i].vehicleType == 1)
                fee = hours * 40;
            else
                fee = hours * 20;

            /* Update Statistics */
            *totalRevenue = *totalRevenue + fee;
            *totalVehiclesServed =
                *totalVehiclesServed + 1;

            /* Bill */
            printf("\n========== BILL ==========\n");

            printf("Vehicle Number : %s\n",
                   parking[i].vehicleNumber);

            printf("Owner Name     : %s\n",
                   parking[i].ownerName);

            printf("Parking Slot   : %d\n",
                   parking[i].slotNumber);

            printf("Parking Hours  : %d\n",
                   hours);

            printf("Total Fee      : Rs.%d\n",
                   fee);

            printf("===========================\n");

            /* Clear Slot */
            parking[i].isOccupied = 0;
            parking[i].slotNumber = 0;
            parking[i].vehicleNumber[0] = '\0';
            parking[i].ownerName[0] = '\0';
            parking[i].vehicleType = 0;

            printf("\nVehicle removed successfully!\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("\nVehicle not found!\n");
}


/* ================= SEARCH VEHICLE ================= */

void searchVehicle(struct Vehicle parking[])
{
    char vehicleNumber[20];
    int found = 0;

    printf("\nEnter Vehicle Number to Search: ");
    scanf("%19s", vehicleNumber);

    for(int i = 0; i < MAX_SLOTS; i++)
    {
        if(parking[i].isOccupied == 1 &&
           strcmp(parking[i].vehicleNumber,
                  vehicleNumber) == 0)
        {
            printf("\n========== VEHICLE FOUND ==========\n");

            printf("Vehicle Number : %s\n",
                   parking[i].vehicleNumber);

            printf("Owner Name     : %s\n",
                   parking[i].ownerName);

            printf("Parking Slot   : %d\n",
                   parking[i].slotNumber);

            if(parking[i].vehicleType == 1)
                printf("Vehicle Type   : Car\n");
            else
                printf("Vehicle Type   : Bike\n");

            printf("===================================\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("\nVehicle not found!\n");
}


/* ================= DISPLAY STATUS ================= */

void displayStatus(struct Vehicle parking[])
{
    int occupied = 0;
    int available = 0;

    printf("\n========== PARKING STATUS ==========\n");

    for(int i = 0; i < MAX_SLOTS; i++)
    {
        printf("\nSlot %d : ", i + 1);

        if(parking[i].isOccupied == 1)
        {
            printf("OCCUPIED\n");

            printf("Vehicle : %s\n",
                   parking[i].vehicleNumber);

            printf("Owner   : %s\n",
                   parking[i].ownerName);

            if(parking[i].vehicleType == 1)
                printf("Type    : Car\n");
            else
                printf("Type    : Bike\n");

            occupied++;
        }
        else
        {
            printf("EMPTY\n");
            available++;
        }
    }

    printf("\n=====================================\n");

    printf("Occupied Slots  : %d\n",
           occupied);

    printf("Available Slots : %d\n",
           available);

    printf("=====================================\n");
}


/* ================= UPDATE VEHICLE ================= */

void updateVehicle(struct Vehicle parking[])
{
    char vehicleNumber[20];

    int found = 0;
    int newType;

    printf("\nEnter Vehicle Number to Update: ");
    scanf("%19s", vehicleNumber);

    for(int i = 0; i < MAX_SLOTS; i++)
    {
        if(parking[i].isOccupied == 1 &&
           strcmp(parking[i].vehicleNumber,
                  vehicleNumber) == 0)
        {
            printf("\n========== VEHICLE FOUND ==========\n");

            printf("Vehicle Number : %s\n",
                   parking[i].vehicleNumber);

            printf("Current Owner  : %s\n",
                   parking[i].ownerName);

            if(parking[i].vehicleType == 1)
                printf("Current Type   : Car\n");
            else
                printf("Current Type   : Bike\n");

            printf("Parking Slot   : %d\n",
                   parking[i].slotNumber);

            printf("===================================\n");

            /* Update Owner */
            printf("\nEnter New Owner Name: ");
            scanf(" %49[^\n]",
                  parking[i].ownerName);

            /* Update Vehicle Type */
            printf("Enter New Vehicle Type (1-Car, 2-Bike): ");

            if(scanf("%d", &newType) != 1)
            {
                printf("\nInvalid input!\n");
                while(getchar() != '\n');
                return;
            }

            if(newType != 1 && newType != 2)
            {
                printf("\nInvalid Vehicle Type!\n");
                return;
            }

            parking[i].vehicleType = newType;

            printf("\nVehicle details updated successfully!\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("\nVehicle not found!\n");
}


/* ================= PARKING REPORT ================= */

void parkingReport(struct Vehicle parking[],
                   int totalRevenue,
                   int totalVehiclesServed)
{
    int currentlyOccupied = 0;

    for(int i = 0; i < MAX_SLOTS; i++)
    {
        if(parking[i].isOccupied == 1)
            currentlyOccupied++;
    }

    printf("\n========== PARKING REPORT ==========\n");

    printf("Total Vehicles Served : %d\n",
           totalVehiclesServed);

    printf("Total Revenue         : Rs.%d\n",
           totalRevenue);

    printf("Currently Occupied    : %d\n",
           currentlyOccupied);

    printf("Currently Available   : %d\n",
           MAX_SLOTS - currentlyOccupied);

    printf("====================================\n");
}


/* ================= SEARCH / FILTER ================= */

void searchFilter(struct Vehicle parking[])
{
    int choice;
    int found = 0;

    printf("\n========== SEARCH / FILTER ==========\n");

    printf("1. All Cars\n");
    printf("2. All Bikes\n");
    printf("3. Occupied Slots\n");
    printf("4. Available Slots\n");

    printf("=====================================\n");

    printf("\nEnter your choice: ");

    if(scanf("%d", &choice) != 1)
    {
        printf("\nInvalid input!\n");
        while(getchar() != '\n');
        return;
    }

    /* All Cars */
    if(choice == 1)
    {
        printf("\n========== ALL CARS ==========\n");

        for(int i = 0; i < MAX_SLOTS; i++)
        {
            if(parking[i].isOccupied == 1 &&
               parking[i].vehicleType == 1)
            {
                printf("\nSlot          : %d",
                       parking[i].slotNumber);

                printf("\nVehicle Number: %s",
                       parking[i].vehicleNumber);

                printf("\nOwner         : %s\n",
                       parking[i].ownerName);

                found = 1;
            }
        }

        if(found == 0)
            printf("\nNo cars currently parked.\n");
    }

    /* All Bikes */
    else if(choice == 2)
    {
        printf("\n========== ALL BIKES ==========\n");

        for(int i = 0; i < MAX_SLOTS; i++)
        {
            if(parking[i].isOccupied == 1 &&
               parking[i].vehicleType == 2)
            {
                printf("\nSlot          : %d",
                       parking[i].slotNumber);

                printf("\nVehicle Number: %s",
                       parking[i].vehicleNumber);

                printf("\nOwner         : %s\n",
                       parking[i].ownerName);

                found = 1;
            }
        }

        if(found == 0)
            printf("\nNo bikes currently parked.\n");
    }

    /* Occupied Slots */
    else if(choice == 3)
    {
        printf("\n========== OCCUPIED SLOTS ==========\n");

        for(int i = 0; i < MAX_SLOTS; i++)
        {
            if(parking[i].isOccupied == 1)
            {
                printf("\nSlot %d : OCCUPIED",
                       i + 1);

                printf("\nVehicle : %s",
                       parking[i].vehicleNumber);

                printf("\nOwner   : %s\n",
                       parking[i].ownerName);

                found = 1;
            }
        }

        if(found == 0)
            printf("\nNo occupied slots.\n");
    }

    /* Available Slots */
    else if(choice == 4)
    {
        printf("\n========== AVAILABLE SLOTS ==========\n");

        for(int i = 0; i < MAX_SLOTS; i++)
        {
            if(parking[i].isOccupied == 0)
            {
                printf("Slot %d : AVAILABLE\n",
                       i + 1);

                found = 1;
            }
        }

        if(found == 0)
            printf("\nNo available slots.\n");
    }

    else
    {
        printf("\nInvalid Choice!\n");
    }
}


/* ================= SAVE DATA ================= */

void saveData(struct Vehicle parking[],
              int totalRevenue,
              int totalVehiclesServed)
{
    FILE *fp;

    fp = fopen("parking.dat", "wb");

    if(fp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    fwrite(parking,
           sizeof(struct Vehicle),
           MAX_SLOTS,
           fp);

    fwrite(&totalRevenue,
           sizeof(int),
           1,
           fp);

    fwrite(&totalVehiclesServed,
           sizeof(int),
           1,
           fp);

    fclose(fp);
}


/* ================= LOAD DATA ================= */

void loadData(struct Vehicle parking[],
              int *totalRevenue,
              int *totalVehiclesServed)
{
    FILE *fp;

    fp = fopen("parking.dat", "rb");

    if(fp == NULL)
        return;

    fread(parking,
          sizeof(struct Vehicle),
          MAX_SLOTS,
          fp);

    fread(totalRevenue,
          sizeof(int),
          1,
          fp);

    fread(totalVehiclesServed,
          sizeof(int),
          1,
          fp);

    fclose(fp);
}


/* ================= MAIN ================= */

int main()
{
    struct Vehicle parking[MAX_SLOTS] = {0};

    int choice;

    int totalRevenue = 0;
    int totalVehiclesServed = 0;

    /* Load previous data */
    loadData(parking,
             &totalRevenue,
             &totalVehiclesServed);

    printf("\n====================================\n");
    printf("     SMART PARKING MANAGEMENT\n");
    printf("====================================\n");

    do
    {
        showMenu();

        printf("\nEnter your choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");

            while(getchar() != '\n');

            continue;
        }

        switch(choice)
        {
            case 1:
                parkVehicle(parking);

                saveData(parking,
                         totalRevenue,
                         totalVehiclesServed);
                break;

            case 2:
                removeVehicle(parking,
                              &totalRevenue,
                              &totalVehiclesServed);

                saveData(parking,
                         totalRevenue,
                         totalVehiclesServed);
                break;

            case 3:
                searchVehicle(parking);
                break;

            case 4:
                displayStatus(parking);
                break;

            case 5:
                updateVehicle(parking);

                saveData(parking,
                         totalRevenue,
                         totalVehiclesServed);
                break;

            case 6:
                parkingReport(parking,
                              totalRevenue,
                              totalVehiclesServed);
                break;

            case 7:
                searchFilter(parking);
                break;

            case 8:
                printf("\nThank you for using Smart Parking System!\n");
                break;

            default:
                printf("\nInvalid Choice! Please choose 1-8.\n");
        }

    } while(choice != 8);

    return 0;
}