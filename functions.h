#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// === Constants ===

#define MAX_VEHICLES 100
#define MAX_SLOTS 20


// === Data Structures ===

/**
 * @brief Structure to store vehicle information and entry state.
 */
typedef struct {
    int vehicle_id;         // Unique identifier for the vehicle
    char owner_name[50];    // Name of the vehicle owner
    char plate_number[20];  // License plate number
    char vehicle_type[20];  // Type/Category of the vehicle
    time_t entry_time;        // Timestamp of entry time in seconds
    int slot_number;        // Assigned parking slot number (-1 if unassigned)
} Vehicle;

/**
 * @brief Structure to manage individual parking slots.
 */
typedef struct {
    int slot_id;            // Slot identifier (1 to 20)
    int is_occupied;        // 0 if available, 1 if occupied
} Slot;


// === Global Variables ===

extern Vehicle parking_list[MAX_VEHICLES];
extern Slot slots[MAX_SLOTS];
extern int vehicle_count;


// === Parking Section ===

/**
 * @brief Adds a new vehicle to the system after validation.
 */
void add_vehicle();

/**
 * @brief Assigns an available parking slot to a specific vehicle.
 * @param id The unique ID of the vehicle.
 */
void assign_slot(int id);

/**
 * @brief Calculates parking fees depending on fixed and extra hour rates.
 * @param entry_time The unix timestamp of vehicle entry.
 * @return The total calculated fee.
 */
double calculate_fees(long entry_time);

/**
 * @brief Removes a vehicle from the system, shifts array, and triggers release.
 */
void remove_vehicle();

/**
 * @brief Frees a specific parking slot making it available.
 * @param slot_num The slot number to release.
 */
void release_slot(int slot_num);

/**
 * @brief Edits the information of an existing vehicle using a valid ID.
 */
void edit_vehicle();

/**
 * @brief Searches for a vehicle using its unique ID.
 */
void search_vehicle_by_id();

/**
 * @brief Searches for a vehicle using its license plate number.
 */
void search_vehicle_by_plate();

/**
 * @brief Displays overall parking statistics and occupancy percentage.
 */
void display_overview();

/**
 * @brief Prints detailed information of a specific vehicle.
 * @param v Pointer to the vehicle structure.
 */
void print_vehicle_data(Vehicle *v);


// === Persistence Section ===

/**
 * @brief Saves all parking records in a readable text format to parking.txt.
 */
void save_to_file();

/**
 * @brief Loads parking records from parking.txt and populates the array at startup.
 */
void load_from_file();


// === Helper Section ===

/**
 * @brief Finds the index of a vehicle in the array by ID.
 * @param id The vehicle ID to search for.
 * @return Index in array, or -1 if not found.
 */
int find_vehicle_index(int id);

#endif