#include <stdio.h>
#include <stdlib.h>

// Function to calculate checksum
unsigned short calculateChecksum(unsigned short segments[], int count) {
    unsigned long sum = 0;
    for (int i = 0; i < count; i++) {
        sum += segments[i];
    }
    // Handle overflow by wrapping around
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    return (unsigned short)(~sum); // Return the bitwise negation of the sum
}

int main() {
    printf("Connected to the server.\n");

    unsigned short segments[10]; // Array to store 10 segments
    char input[6]; // For reading hexadecimal input (5 digits + null terminator)

    // Reading 10 hexadecimal segments from the user
    for (int i = 0; i < 10; i++) {
        printf("Segment %d: ", i + 1);
        scanf("%5s", input);
        segments[i] = (unsigned short)strtol(input, NULL, 16); // Convert hex input to 16-bit unsigned integer
    }

    // Calculate checksum
    unsigned short checksum = calculateChecksum(segments, 10);
    printf("Computed checksum: 0x%04X\n", checksum);

    // Predefined received checksum for validation
    unsigned short receivedChecksum = 0x8BB1;
    printf("Received checksum from server: 0x%04X\n", receivedChecksum);

    // Validate checksum
    if (checksum == receivedChecksum) {
        printf("Checksum verification PASSED: The header is valid\n");
    } else {
        printf("Checksum verification FAILED: The header is invalid\n");
    }

    return 0;
}
