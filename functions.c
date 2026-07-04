#include "functions.h"

// === Global Variables Definition ===

Vehicle parking_list[MAX_VEHICLES];
Slot slots[MAX_SLOTS];
int vehicle_count = 0;


// === Helper Section ===


/**
 * @brief Finds the index of a vehicle in the array by its ID.
 * @param id The unique vehicle ID to search for.
 * @return Index of the vehicle in the array, or -1 if not found.
 */
int find_vehicle_index(int id) {
    for (int i = 0; i < vehicle_count; i++) {
        if (parking_list[i].vehicle_id == id) {
            return i;
        }
    }
    return -1;
}

// === Parking Section ===

/**
 * @brief Adds a new vehicle to the system after strict validation checks.
 */
void add_vehicle() {
    // Validation: Check if the system storage has reached its maximum limit
    if (vehicle_count >= MAX_VEHICLES) {
        printf("\n[Error] System storage is full! Cannot add more vehicles.\n");
        return;
    }

    int id;
    printf("\nEnter Vehicle ID: ");
    scanf("%d", &id);
    getchar(); // Clear the input buffer to prevent fgets from skipping

    // Validation: Ensure the Vehicle ID is unique and does not already exist
    if (find_vehicle_index(id) != -1) {
        printf("[Error] Vehicle ID %d already exists in the system!\n", id);
        return;
    }

    parking_list[vehicle_count].vehicle_id = id;

    printf("Enter Owner Name: ");
    fgets(parking_list[vehicle_count].owner_name, 50, stdin);
    parking_list[vehicle_count].owner_name[strcspn(parking_list[vehicle_count].owner_name, "\n")] = 0;

    printf("Enter Plate Number: ");
    fgets(parking_list[vehicle_count].plate_number, 20, stdin);
    parking_list[vehicle_count].plate_number[strcspn(parking_list[vehicle_count].plate_number, "\n")] = 0;

    printf("Enter Vehicle Type: ");
    fgets(parking_list[vehicle_count].vehicle_type, 20, stdin);
    parking_list[vehicle_count].vehicle_type[strcspn(parking_list[vehicle_count].vehicle_type, "\n")] = 0;

    // Set standard entry parameters
    parking_list[vehicle_count].entry_time = time(NULL);
    parking_list[vehicle_count].slot_number = -1; // -1 indicates no slot assigned yet

    printf("\n[Success] Vehicle record created successfully.\n");
    vehicle_count++;
}

/**
 * @brief Assigns an available parking slot to a specific vehicle.
 * @param id The unique ID of the vehicle.
 */
void assign_slot(int id) {
    int index = find_vehicle_index(id);
    
    // Validation: Check if the vehicle exists in the system
    if (index == -1) {
        printf("\n[Error] Vehicle ID not found in system.\n");
        return;
    }

    // Validation: Check if the vehicle has already been assigned a slot
    if (parking_list[index].slot_number != -1) {
        printf("\n[Error] Vehicle already has an assigned slot: Slot %d\n", parking_list[index].slot_number);
        return;
    }

    // Search for the first unoccupied slot and assign it
    for (int j = 0; j < MAX_SLOTS; j++) {
        if (slots[j].is_occupied == 0) {
            slots[j].is_occupied = 1;
            parking_list[index].slot_number = slots[j].slot_id;
            printf("\n[Success] Slot %d assigned to Vehicle ID %d.\n", slots[j].slot_id, id);
            return;
        }
    }

    printf("\n[Error] No available slots in the parking!\n");
}

/**
 * @brief Calculates parking fees depending on fixed and extra hour rates.
 * @param entry_time The unix timestamp of vehicle entry.
 * @return The total calculated fee.
 */
double calculate_fees(long entry_time) {
    long exit_time = time(NULL);
    long duration_seconds = exit_time - entry_time;

    // Simulation mapping: 1 second equals 1 hour for practical demonstration purposes
    double total_hours = duration_seconds / 1.0; 
    double fixed_fee = 10.0;           
    double extra_charge_per_hour = 5.0; 
    double total_fee = 0.0;

    if (total_hours <= 1.0) {
        total_fee = fixed_fee;
    } else {
        total_fee = fixed_fee + ((total_hours - 1.0) * extra_charge_per_hour);
    }
    return total_fee;
}

// === Persistence Section ===

/**
 * @brief Saves all parking records in a readable text format to parking.txt.
 */
void save_to_file() {
    FILE *file = fopen("parking.txt", "w");
    if (file == NULL) {
        printf("\n[Error] Could not open file to save data.\n");
        return;
    }

    // Write the global counter on the very first line for reliable loading sequence
    fprintf(file, "%d\n", vehicle_count);

    // Loop through records and print structured text data
    for (int i = 0; i < vehicle_count; i++) {
        fprintf(file, "%d\n%s\n%s\n%s\n%ld\n%d\n",
                parking_list[i].vehicle_id,
                parking_list[i].owner_name,
                parking_list[i].plate_number,
                parking_list[i].vehicle_type,
                parking_list[i].entry_time,
                parking_list[i].slot_number);
    }

    fclose(file);
    printf("\n[Success] Data saved to parking.txt successfully.\n");
}

/**
 * @brief Loads parking records from parking.txt and populates the array at startup.
 */
void load_from_file() {
    FILE *file = fopen("parking.txt", "r");
    if (file == NULL) {
        // If file does not exist, initialize empty tracking layout for slots and exit safely
        for (int j = 0; j < MAX_SLOTS; j++) {
            slots[j].slot_id = j + 1;
            slots[j].is_occupied = 0;
        }
        return;
    }

    // Read the primary vehicle global counter
    if (fscanf(file, "%d\n", &vehicle_count) != 1) {
        vehicle_count = 0;
    }

    // Populate data structures back into volatile RAM memory
    for (int i = 0; i < vehicle_count; i++) {
        fscanf(file, "%d\n", &parking_list[i].vehicle_id);
        
        fgets(parking_list[i].owner_name, 50, file);
        parking_list[i].owner_name[strcspn(parking_list[i].owner_name, "\n")] = 0;

        fgets(parking_list[i].plate_number, 20, file);
        parking_list[i].plate_number[strcspn(parking_list[i].plate_number, "\n")] = 0;

        fgets(parking_list[i].vehicle_type, 20, file);
        parking_list[i].vehicle_type[strcspn(parking_list[i].vehicle_type, "\n")] = 0;

        fscanf(file, "%ld\n", &parking_list[i].entry_time);
        fscanf(file, "%d\n", &parking_list[i].slot_number);
    }

    // Reset base hardware mapping fields for slots layout
    for (int j = 0; j < MAX_SLOTS; j++) {
        slots[j].slot_id = j + 1;
        slots[j].is_occupied = 0;
    }

    // Synchronize and lock active slots according to imported data logs
    for (int i = 0; i < vehicle_count; i++) {
        if (parking_list[i].slot_number != -1) {
            int slot_idx = parking_list[i].slot_number - 1;
            if (slot_idx >= 0 && slot_idx < MAX_SLOTS) {
                slots[slot_idx].is_occupied = 1;
            }
        }
    }

    fclose(file);
    printf("\n[Success] Data loaded from parking.txt successfully.\n");
}