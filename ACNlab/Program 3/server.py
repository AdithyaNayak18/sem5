import socket
port = 6003
def crc_division(data, generator):
    """ Perform CRC division and return the checksum. """
    data = data + '0' * (len(generator) - 1)
    data_len = len(data)
    generator_len = len(generator)
    data = list(data)
    generator = list(generator)
    for i in range(data_len - generator_len + 1):
        if data[i] == '1':  # Only divide if the leading bit is 1
            for j in range(generator_len):
                data[i + j] = str(int(data[i + j]) ^ int(generator[j]))
    return ''.join(data[-(generator_len - 1):])

def server():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind(('localhost', port))
        print("Server is listening on port " + str(port) + "...")
        while True:
            data, addr = s.recvfrom(1024)
            received_message, received_checksum = data.decode().split(',')
            generator = input("Enter generator (binary): ")
            computed_checksum = crc_division(received_message + received_checksum, generator)
            if all(bit == '0' for bit in computed_checksum):
                print(f"Data from {addr} is valid.")
            else:
                print(f"Data from {addr} is invalid.")

if __name__ == "__main__":
    server()
