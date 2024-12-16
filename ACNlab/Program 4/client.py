import socket
def calculate_checksum(segments):
    checksum = 0
    for segment in segments:
        # Convert segment to an integer
        value = int(segment, 16)
        checksum += value

        # Handle overflow by adding the carry bit
        checksum = (checksum & 0xFFFF) + (checksum >> 16)

    checksum = ~checksum & 0xFFFF
    return checksum

def main():
    # Client setup
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(("127.0.0.1", 65432))  # Connect to the server

    # Read 10 hexadecimal segments
    segments = []
    print("Enter 10 16-bit hexadecimal segments:")

    for i in range(10):
        segment = input(f"Segment {i + 1}: ").strip()
        segments.append(segment)

    data_to_send = " ".join(segments)
    client_socket.sendall(data_to_send.encode())

    checksum_from_server = client_socket.recv(1024).decode()
    print(f"Checksum received from server: {checksum_from_server}")

    checksum_calculated = calculate_checksum(segments)
    print(f"Checksum calculated on client-side: 0x{checksum_calculated:04X}")

    if f"0x{checksum_calculated:04X}" == checksum_from_server:
        print("Checksum is valid.")
    else:
        print("Checksum is invalid.")

    client_socket.close()

if __name__ == "__main__":
    main()
