import socket

def main():
    server_host = '127.0.0.1'
    server_port = 12345

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_host, server_port))
    print("Connected to server.")

    try:
        while True:
            message = input("Enter message: ")
            if message.lower() == 'exit':
                break
            client_socket.sendall(message.encode())
            response = client_socket.recv(1024).decode()
            print("Server response:", response)
    except KeyboardInterrupt:
        print("\nClient interrupted.")
    finally:
        client_socket.close()
        print("Disconnected from server.")

if __name__ == "__main__":
    main()
