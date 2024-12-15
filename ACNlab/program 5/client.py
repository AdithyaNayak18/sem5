import socket

def send_message():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('localhost', 12345)

    packet = input("Enter the data to be sent: ")
    df_flag = input("Set 'Do Not Fragment' flag (1 for Yes, 0 for No): ")
    message = f"{packet}|{df_flag}"
    client_socket.sendto(message.encode(), server_address)
    print(f"Sent packet: {packet}, DF Flag: {df_flag}")

    response, _ = client_socket.recvfrom(4096)
    print(f"Response from server: {response.decode()}")
    client_socket.close()

if __name__ == "__main__":
    send_message()
