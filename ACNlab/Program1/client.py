import socket

def request_file(file_name):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 65432))
    client_socket.sendall(file_name.encode())

    file_contents = client_socket.recv(1024).decode()
    print(f"Received from server: {file_contents}")

    client_socket.close()

if __name__ == "__main__":
    file_name = input("Enter the file name: ")
    request_file(file_name)
