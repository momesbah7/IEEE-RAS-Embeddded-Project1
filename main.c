#include"functions.h"

int main(){

    int choise, id, num;
    char plate[20];
    load_from_file();
    while(1){
        system("cls");
        printf("Welcom In Your Home\n");
        printf("what Do You Want?");
        printf("1. Parking\n2. Leave\n3. See Avilable Slots\n4. Search\n5. Exit");
        printf("Enter Your Choise: ");
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
            add_vehicle();
            save_to_file();             
            break;
        case 2:
            printf("Entre Vehicle ID: ");
            scanf("%d", &id);
            printf("You entered ID: %d. Confirm delete? (y/n): ", id);
            char confirm;
            scanf(" %c", &confirm);  
            if(confirm == 'y'){
                remove_vehicle(id);
                save_to_file();
            } 
            else {
                printf("Cancelled.\n");
            }
            break;
        case 3:
            display_overview();
            break;
        case 4:
            printf("1. Search By ID\n2. Search By Plate Number\nChoise: ");
            scanf("%d", &num);
            switch (num){ 
                case 1:
                    printf("Enter Your ID: ");
                    scanf("%d", &id);
                    search_by_id(id);
                    break;
                case 2:
                    printf("Enter Your Plate Number: ");
                    scanf(" %[^\n]", plate);
                    search_by_plate(plate);
                    break; 
                default:
                    break;                  
            }
            break;
        case 5:
            printf("Goodbye!\n");
            return 0;
            break;
        default:
            printf("Invalid Choice!\n");
            break;
        }
    }

    return 0;
}