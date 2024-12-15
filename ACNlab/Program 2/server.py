import socket

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(('localhost', 12345))
    print("Server is listening on port 12345...")

    while True:
        message, client_address = server_socket.recvfrom(1024)
        message = message.decode().upper()
        length = len(message)
        print(f"Message from client: {message}, Length: {length}")
        response = f"Message received! Uppercase: {message}, Length: {length}"
        server_socket.sendto(response.encode(), client_address)

if __name__ == "__main__":
    start_server()
