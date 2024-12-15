import socket

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 65432))
    server_socket.listen(1)
    print("Server is listening on port 65432...")

    while True:
        conn, addr = server_socket.accept()
        print(f"Connected by {addr}")
        file_name = conn.recv(1024).decode()

        try:
            with open(file_name, 'r') as file:
                file_contents = file.read()
                conn.sendall(file_contents.encode())
        except FileNotFoundError:
            conn.sendall(b"File not found")

        conn.close()

if __name__ == "__main__":
    start_server()
