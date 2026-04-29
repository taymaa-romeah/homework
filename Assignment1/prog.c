#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define the maximum capacity of the Circular Buffer
#define SIZE 50

// Structure to define the Circular Buffer properties
typedef struct {
    char buffer[SIZE];
    int head;   // Write pointer
    int tail;   // Read pointer
    int count;  // Tracks the number of elements in the buffer
} CircularBuffer;

// Initialize the buffer indices and counter
void initBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// Function to add data to the buffer (Write Operation)
int writeBuffer(CircularBuffer *cb, char data) {
    // Check for Overflow: if buffer is full
    if (cb->count == SIZE) {
        printf("\nError: Buffer Overflow! Cannot add more data.\n");
        return 0; 
    }
    cb->buffer[cb->head] = data;
    // Circular increment of the head pointer
    cb->head = (cb->head + 1) % SIZE; 
    cb->count++;
    return 1;
}

// Function to retrieve data from the buffer (Read Operation)
int readBuffer(CircularBuffer *cb, char *data) {
    // Check for Underflow: if buffer is empty
    if (cb->count == 0) {
        printf("\nError: Buffer Underflow! No data to read.\n");
        return 0;
    }
    *data = cb->buffer[cb->tail];
    // Circular increment of the tail pointer
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count--;
    return 1;
}

int main() {
    CircularBuffer cb;
    initBuffer(&cb);

    char name[SIZE];
    char suffix[] = " CE-ESY";
    char fullName[100]; // Buffer to hold full string before storing

    // 1. Get user name from Standard Input
    printf("Please enter your name: ");
    if (fgets(name, sizeof(name), stdin)) {
        // Remove trailing newline character
        name[strcspn(name, "\n")] = 0;
    }

    // 2. Add the required suffix "CE-ESY"
    strcpy(fullName, name);
    strcat(fullName, suffix);

    // 3. Store the result into the Circular Buffer character by character
    printf("\n--- Storing data into Circular Buffer ---\n");
    for (int i = 0; i < strlen(fullName); i++) {
        writeBuffer(&cb, fullName[i]);
    }

    // 4. Read and display the data from the Circular Buffer
    printf("Result extracted from Buffer: ");
    char temp;
    while (cb.count > 0) {
        if (readBuffer(&cb, &temp)) {
            printf("%c", temp);
        }
    }
    printf("\n\nExecution finished successfully.\n");

    return 0;
}
