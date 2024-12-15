import socket

def send_message():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('localhost', 12345)

    message = "Hello, Server!"
    client_socket.sendto(message.encode(), server_address)

    response, _ = client_socket.recvfrom(1024)
    print(f"Response from server: {response.decode()}")
    client_socket.close()

if __name__ == "__main__":
    send_message()
