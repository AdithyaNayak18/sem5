#include <stdio.h>
#include <stdlib.h>
unsigned short calculateChecksum(unsigned short segments[], int count) {
unsigned long sum = 0;
for (int i = 0; i < count; i++) {
sum += segments[i];
}
while (sum >> 16) {
sum = (sum & 0xFFFF) + (sum >> 16);
}
return (unsigned short)(~sum);
}
int main() {
printf("Connected to the server.\n");
unsigned short segments[10];
char input[6]; // For reading hexadecimal input

for (int i = 0; i < 10; i++) {
printf("Segment %d: ", i + 1);
scanf("%5s", input);
segments[i] = (unsigned short)strtol(input, NULL, 16);
}

unsigned short checksum = calculateChecksum(segments, 10);
printf("Computed checksum: 0x%04X\n", checksum);
unsigned short receivedChecksum = 0x8BB1; // Example checksum for validation
printf("Received checksum from server: 0x%04X\n", receivedChecksum);
if (checksum == receivedChecksum) {
printf("Checksum verification PASSED: The header is valid\n");
} else {
printf("Checksum verification FAILED: The header is invalid\n");
}
return 0;
}
