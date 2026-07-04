#include "functions.h"

int main() {
    int choice, search_choice;
    
    // Load historical data from storage file at startup
    load_from_file();
    
    while (1) {
        // Clearing terminal screen compatible with both Linux (Ubuntu) and Windows
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("   === SMART PARKING MANAGEMENT SYSTEM ===\n");
        printf("1. Park a New Vehicle\n");
        printf("2. Vehicle Exit & Checkout (Leave)\n");
        printf("3. View Parking Overview & Available Slots\n");
        printf("4. Search for a Vehicle\n");
        printf("5. Edit Vehicle Information\n");
        printf("6. Exit Program\n");
        printf("==========================================\n");
        printf("Enter Your Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("[Error] Invalid numeric input!\n");
            getchar(); // Clear invalid input character
            continue;
        }
        getchar(); // Clear newline buffer trailing after scanf

        switch (choice) {
            case 1:
                add_vehicle();
                // If a vehicle was successfully added, auto-assign a physical slot
                if (vehicle_count > 0 && parking_list[vehicle_count - 1].slot_number == -1) {
                    assign_slot(parking_list[vehicle_count - 1].vehicle_id);
                }
                save_to_file();
                break;

            case 2:
                remove_vehicle();
                save_to_file();
                break;

            case 3:
                display_overview();
                break;

            case 4:
                printf("\n--- Search Menu ---\n");
                printf("1. Search By Vehicle ID\n");
                printf("2. Search By Plate Number\n");
                printf("Enter Choice: ");
                scanf("%d", &search_choice);
                getchar(); // Clear buffer

                switch (search_choice) {
                    case 1:
                        search_vehicle_by_id();
                        break;
                    case 2:
                        search_vehicle_by_plate();
                        break;
                    default:
                        printf("[Error] Invalid search option selected.\n");
                        break;
                }
                break;

            case 5:
                edit_vehicle();
                save_to_file();
                break;

            case 6:
                printf("\nSaving database... Goodbye!\n");
                save_to_file();
                return 0;

            default:
                printf("[Warning] Invalid Selection! Please pick between 1 and 6.\n");
                break;
        }

        // Pause system execution so the student/teacher can read the operational response
        printf("\nPress [Enter] key to continue...");
        getchar();
    }

    return 0;
}