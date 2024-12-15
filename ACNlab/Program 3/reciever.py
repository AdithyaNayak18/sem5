import socket
port = 6003
def crc_division(data, generator):
    data = data + '0' * (len(generator) - 1)
    data = list(data)
    generator = list(generator)
    for i in range(len(data) - len(generator) + 1):
        if data[i] == '1':
            for j in range(len(generator)):
                data[i + j] = str(int(data[i + j]) ^ int(generator[j]))
    return ''.join(data[-(len(generator) - 1):])

def client():
    while True:
        size = input("Enter number of bits: ")
        message = input("Enter message (binary) type 'exit' to quit: ")
        if message == 'exit':
            break
        generator = input("Enter generator (binary): ")
        checksum = crc_division(message, generator)
        print("Checksum code:", checksum)
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.sendto(f"{message},{checksum}".encode(), ('localhost', port))

if __name__ == "__main__":
    client()
