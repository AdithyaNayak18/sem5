import socket

def fragment_packet(packet, mtu):
    header_size = 20  # Assuming a fixed header size for simplicity
    max_data_size = mtu - header_size
    fragments = []

    offset = 0
    while offset < len(packet):
        fragment_data = packet[offset:offset + max_data_size]
        more_fragments = 1 if offset + max_data_size < len(packet) else 0
        fragment = {
            'offset': offset,
            'data': fragment_data,
            'more_fragments': more_fragments
        }
        fragments.append(fragment)
        offset += max_data_size

    return fragments

def start_server(mtu_values):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(('localhost', 12345))
    print("Server is listening on port 12345...")

    while True:
        data, client_address = server_socket.recvfrom(4096)
        packet, df_flag = data.decode().split('|')
        df_flag = int(df_flag)
        print(f"Received packet: {packet}, DF Flag: {df_flag}")

        if df_flag and len(packet) > min(mtu_values):
            response = "Packet too large to fragment with DF flag set."
        else:
            response = ""
            for mtu in mtu_values:
                fragments = fragment_packet(packet, mtu)
                response += f"\nMTU={mtu}\n"
                for i, fragment in enumerate(fragments):
                    response += f"Fragment {i+1}: Offset={fragment['offset']}, More Fragments={fragment['more_fragments']}, Data={fragment['data']}\n"

        server_socket.sendto(response.encode(), client_address)

if __name__ == "__main__":
    mtu_values = [40, 50, 45]  # Example MTU values for different links
    start_server(mtu_values)
