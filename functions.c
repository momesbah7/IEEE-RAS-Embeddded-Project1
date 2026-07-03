#include"functions.h"


void remove_vehicle(int vehicle_id){
    for(int i = 0; i < MAX_VEHICLES; i++){
        if(parking_list[i].vehicle_id == vehicle_id){
            for(i ; i < vehicle_count - 1; i++ ){
            parking_list[i] = parking_list [i + 1];
            }
            vehicle_count-- ;
            break;
        }
    }
}

void display_overview(){
    printf("Number Of Vehicles: %d\n", vehicle_count);
    printf("Avilable Solts: %d\n\n", MAX_SLOTS - vehicle_count);
}


void save_to_file(){
    
    FILE *fp = NULL;
    fp = fopen("parking.txt", "w");
    if(fp == NULL){
        printf("Error: Could not open file!\n");
        return;
    }

    for(int i =0; i < vehicle_count; i++){
        fprintf(fp, "Vehicle ID: %d\n", parking_list[i].vehicle_id);        
        fprintf(fp, "Owner Name: %s\n", parking_list[i].owner_name);        
        fprintf(fp, "Plate Number: %s\n", parking_list[i].plate_number);        
        fprintf(fp, "Vehicle Type: %s\n", parking_list[i].vehicle_type);        
        fprintf(fp, "Entry Time: %s\n", ctime(&parking_list[i].entry_time));
        fprintf(fp, "Slot Number: %d\n", parking_list[i].slot_number);       
        fprintf(fp, "-----------------------------\n");  
    }
    fclose(fp);
}

void load_from_file(){
    FILE *fp = NULL;
    fp = fopen("parking.txt", "r");
    if(fp == NULL){
        printf("Error: Could not open file!\n");
        return;
    }

    char skip_line[100]; 
    vehicle_count = 0;

    while(fscanf(fp, "Vehicle ID: %d\n", &parking_list[vehicle_count].vehicle_id) == 1){
        fscanf(fp, "Owner Name: %[^\n]\n", parking_list[vehicle_count].owner_name);
        fscanf(fp, "Plate Number: %[^\n]\n", parking_list[vehicle_count].plate_number);
        fscanf(fp, "Vehicle Type: %[^\n]\n", parking_list[vehicle_count].vehicle_type);

        fgets(skip_line, sizeof(skip_line), fp);
        fgets(skip_line, sizeof(skip_line), fp);

        fscanf(fp, "Slot Number: %d\n", &parking_list[vehicle_count].slot_number);
        fgets(skip_line, sizeof(skip_line), fp);

        vehicle_count++ ;
    }

    fclose(fp);
}

void search_by_id(int vehicle_id){
    int flage = 0;
    for(int i = 0; i < vehicle_count; i++){
        if(parking_list[i].vehicle_id == vehicle_id){
            printf("Details Of Vehicles\n");
            printf("Vehicle ID: %d\n", parking_list[i].vehicle_id);        
            printf("Owner Name: %s\n", parking_list[i].owner_name);        
            printf("Plate Number: %s\n", parking_list[i].plate_number);        
            printf("Vehicle Type: %s\n", parking_list[i].vehicle_type);        
            printf("Entry Time: %s\n", ctime(&parking_list[i].entry_time));
            printf("Slot Number: %d\n", parking_list[i].slot_number);       
            flage = 1;
            break;
        }
        
    }
    if(flage == 0){
        printf("Not Found!!");
    }
}


void search_by_plate(char plate[20]){
    int flage = 0;
    for(int i = 0; i < vehicle_count; i++){
        if(strcmp(parking_list[i].plate_number ,plate) == 0){
            printf("Details Of Vehicles\n");
            printf("Vehicle ID: %d\n", parking_list[i].vehicle_id);        
            printf("Owner Name: %s\n", parking_list[i].owner_name);        
            printf("Plate Number: %s\n", parking_list[i].plate_number);        
            printf("Vehicle Type: %s\n", parking_list[i].vehicle_type);        
            printf("Entry Time: %s\n", ctime(&parking_list[i].entry_time));
            printf("Slot Number: %d\n", parking_list[i].slot_number);       
            flage = 1;
            break;
        }
        
    }
    if(flage == 0){
        printf("Not Found!!");
    }
}