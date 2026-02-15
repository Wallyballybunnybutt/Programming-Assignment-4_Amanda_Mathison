#include <stdio.h>
#include <string.h>
#define SEATS 24

typedef struct {
    char lastname[20];
    char firstname[20];
    int seat_num;
    int assigned_seat;
} Seat; //replaces struct Seat

void seats(Seat seats[]);
void second_menu(Seat seats[]);
void empty_count(Seat seats[]);
void empty_list(Seat seats[]);
void show_alphabetical(Seat seats[]);
void assign_seat(Seat seats[]);
void delete_seat(Seat seats[]);
void load_seats(const char *filename, Seat seats[]);
void save_seats(const char *filename, Seat seats[]);

int main(void) {
    Seat outbound[SEATS];
    Seat inbound[SEATS];
    char choice;

    load_seats("outbound.dat", outbound);
    load_seats("inbound.dat", inbound);
    do {
        printf("\n First Level Menu \n");
        printf("a) Outbound flight\n");
        printf("b) Inbound flight\n");
        printf("c) Quit\n");
        printf("Pick a choice: ");
        scanf(" %c", &choice);

        if (choice == 'a') { //goes through each choice
            second_menu(outbound);
            save_seats("outbound.dat", outbound);
        } else if (choice == 'b') {
            second_menu(inbound);
            save_seats("inbound.dat", inbound);
        }
    } 
    while (choice != 'c');
    save_seats("outbound.dat", outbound);
    save_seats("inbound.dat", inbound);
    return 0;
}

void second_menu(Seat seats[]) {
    char choice;
    do {
        printf("\n-- Second Level Menu --\n");
        printf("a) Show number of empty seats\n");
        printf("b) Show list of empty seats\n");
        printf("c) Show alphabetical list of seats\n");
        printf("d) Assign a customer to a seat assignment\n");
        printf("e) Delete a seat assignment\n");
        printf("f) Return to Main menu\n");

        scanf(" %c", &choice);

        switch (choice) { //goes through each choice again and goes to designated section
            case 'a':
                empty_count(seats);
                break;
            case 'b':
                empty_list(seats);
                break;
            case 'c':
                show_alphabetical(seats);
                break;
            case 'd':
                assign_seat(seats);
                break;
            case 'e':
                delete_seat(seats);
                break;
        }
    }
    while (choice != 'f'); //goes until user types f
}

void seats(Seat seats[]) {
    for (int i = 0; i < SEATS; i++) {
        seats[i].seat_num = i + 1; //seat numbers
        seats[i].assigned_seat = 0; //marks seat as empty
        seats[i].firstname[0] = '\0'; //empty strings
        seats[i].lastname[0] = '\0';
    }
}

void empty_count(Seat seats[]) {
    int count = 0;
    for (int i = 0; i < SEATS; i++) {
        if (seats[i].assigned_seat == 0) { //checks if seat is empty
            count++; //adds to empty seat count
        }
    }
    printf("The number of empty seats is: %d\n", count);
}

void show_alphabetical(Seat seats[]) { //use bubble sort instead of temporary placement
    Seat temp[SEATS];
    int count = 0;
    for (int i = 0; i < SEATS; i++) {
        if (seats[i].assigned_seat) { //is seat occupied?
            temp[count++] = seats[i];//goes into temp array
        }
    }
    if (count == 0) {
        printf("All the seats are currently open :)");
        return;
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(temp[j].lastname, temp[j+1].lastname) > 0 || (strcmp(temp[j].lastname, temp[j+1].lastname) == 0 && strcmp(temp[j].firstname, temp[j+1].firstname) > 0)) {
                Seat swap = temp[j];//temp variable //compares last names alphabetically, last names identical?, compare first names
                temp[j] = temp[j+1];//next seat into current spot
                temp[j+1] = swap;//seat in new position
            }
        }
    }
    printf("Here's an alphabetical list of assigned seats:\n");
    for(int i = 0; i < count; i++) {
        printf("Seat %d: %s, %s\n", temp[i].seat_num, temp[i].lastname, temp[i].firstname);
    }//seat number, lastname, firstname
}

void assign_seat(Seat seats[]) {
    int seat;
    printf("Enter the seat number to assign: "); 
    scanf("%d", &seat); //which seat you want

    if (seat == 0) {
        return;
    }

    if (seat < 1 || seat > SEATS || seats[seat - 1].assigned_seat) {
        printf("OCCUPIED SEAT.\n");
        return;
    } //if not occupied continue

    printf("Enter your first name: ");
    scanf("%s", seats[seat - 1].firstname);
    
    printf("Enter your last name: ");
    scanf("%s", seats[seat - 1].lastname);

    seats[seat - 1].assigned_seat = 1;
    printf("Your seat is now assigned. \n");
}

void delete_seat(Seat seats[]) {
    int seat;
    printf("Enter the seat number you wish to delete: ");
    scanf("%d", &seat);

    if (seat == 0) { //alows to cancel by entering 0
        return;
    }

    if (seat < 1 || seat > SEATS || !seats[seat - 1].assigned_seat) {
        printf("EMPTY SEAT\n"); //checks if empty seat
        return;
    }
    seats[seat - 1].assigned_seat = 0; //marks it as empty
    seats[seat - 1].firstname[0] = '\0'; //clears the names
    seats[seat - 1].lastname[0] = '\0';
    printf("The seat assigned was deleted\n");

}

void empty_list(Seat seats[]) {
    printf("Empty seats available: ");
    for (int i = 0; i < SEATS; i++) {
        if (seats[i].assigned_seat == 0) { //checks if empty
            printf("%d ", seats[i].seat_num); //prints the seat number
        }
    }
    printf("\n");
}

void save_seats(const char *filename, Seat seats[]) {
    FILE *fp = fopen(filename, "wb"); //write binary
    if (fp == NULL) { //if file fails to open
        printf("Error!");
        return;
    }
    fwrite(seats, sizeof(Seat), SEATS, fp); //writes data to file
    fclose(fp);
}

void load_seats(const char *filename, Seat seats[]) {
    FILE *fp = fopen(filename, "rb"); //reads file
    if (fp == NULL) { //if file failed to open
        for (int i = 0; i < SEATS; i++) {
            seats[i].seat_num = i + 1;
            seats[i].assigned_seat = 0;
            seats[i].firstname[0] = '\0';
            seats[i].lastname[0] = '\0';
        }
        return;
    }
    fread(seats, sizeof(Seat), SEATS, fp); //reads data from the file and puts it in
    fclose(fp);
}




