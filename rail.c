#include <stdio.h>
#include <string.h>

#define MAX_SEATS 3
#define MAX_WAIT 3
    
struct Passenger {
    char name[50];
    int age;
    int ticketID;
};

struct Queue {
    struct Passenger waitlist[MAX_WAIT];
    int front;
    int rear;
};

struct Passenger confirmed_list[MAX_SEATS];
int confirmed_count = 0;
struct Queue waiting_queue; 
int next_ticket_id = 1001; 


void enqueue(struct Passenger p) {
    if (waiting_queue.rear == MAX_WAIT - 1) {
        printf("\n[!] Sorry, the waiting list is also full. Cannot book.\n");
        return;
    }
    if (waiting_queue.front == -1) {
        waiting_queue.front = 0;
    }
    waiting_queue.rear++;
    waiting_queue.waitlist[waiting_queue.rear] = p;
    printf("\n[*] Train is full. Added %s to the Waiting List.\n", p.name);
}

struct Passenger dequeue() {
    struct Passenger p;
    p.ticketID = -1; 

    if (waiting_queue.front == -1) {
        return p;
    }

    p = waiting_queue.waitlist[waiting_queue.front];


    if (waiting_queue.front == waiting_queue.rear) {
        waiting_queue.front = -1;
        waiting_queue.rear = -1;
    } else {
        waiting_queue.front++;
    }
    return p;
}


void bookTicket() {
    struct Passenger p;
    printf("\n--- Book Ticket ---\n");
    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    
    p.ticketID = next_ticket_id++;


    if (confirmed_count < MAX_SEATS) {
        confirmed_list[confirmed_count] = p;
        confirmed_count++;
        printf("\n[+] SUCCESS: Ticket Confirmed for %s! Ticket ID: %d\n", p.name, p.ticketID);
    } else {
        
        enqueue(p);
    }
}

void cancelTicket() {
    int id, i, j, found = 0;
    struct Passenger luckyPerson;
    
    printf("\n--- Cancel Ticket ---\n");
    printf("Enter Ticket ID to cancel: ");
    scanf("%d", &id);


    for (i = 0; i < confirmed_count; i++) {
        if (confirmed_list[i].ticketID == id) {
            found = 1;
            printf("\n[-] Ticket ID %d for %s has been cancelled.\n", id, confirmed_list[i].name);
            
            
            for (j = i; j < confirmed_count - 1; j++) {
                confirmed_list[j] = confirmed_list[j + 1];
            }
            confirmed_count--;

            
            if (waiting_queue.front != -1) {
                luckyPerson = dequeue();
                if (luckyPerson.ticketID != -1) {
                    confirmed_list[confirmed_count] = luckyPerson;
                    confirmed_count++;
                    printf("[^] ALERT: %s has been promoted from the Waiting List to Confirmed!\n", luckyPerson.name);
                }
            }
            break; 
        }
    }

    if (!found) {
        printf("\n[!] Error: Ticket ID %d not found in confirmed bookings.\n", id);
    }
}

void displayStatus() {
    int i; 
    
    printf("\n==================================\n");
    printf("      CURRENT TRAIN STATUS        \n");
    printf("==================================\n");
    
    printf("CONFIRMED TICKETS (%d/%d):\n", confirmed_count, MAX_SEATS);
    if (confirmed_count == 0) {
        printf("  (None)\n");
    } else {
        for (i = 0; i < confirmed_count; i++) {
            printf("  [%d] %s (Age: %d)\n", confirmed_list[i].ticketID, confirmed_list[i].name, confirmed_list[i].age);
        }
    }

    printf("\nWAITING LIST:\n");
    if (waiting_queue.front == -1) {
        printf("  (Empty)\n");
    } else {
        for (i = waiting_queue.front; i <= waiting_queue.rear; i++) {
            printf("  [%d] %s (Age: %d)\n", waiting_queue.waitlist[i].ticketID, waiting_queue.waitlist[i].name, waiting_queue.waitlist[i].age);
        }
    }
    printf("==================================\n");
}

// --- 4. Main Menu ---
int main() {
    int choice;
    
    
    waiting_queue.front = -1;
    waiting_queue.rear = -1;

    while (1) {
        printf("\n+--------------------------------+\n");
        printf("|   RAILWAY RESERVATION SYSTEM   |\n");
        printf("+--------------------------------+\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. View Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookTicket();
                break;
            case 2:
                cancelTicket();
                break;
            case 3:
                displayStatus();
                break;
            case 4:
                printf("\nExiting system. Have a safe journey!\n");
                return 0;
            default:
                printf("\n[!] Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
