import socket
import os

# Define the server's address and port
HOST = '127.0.0.1'  # Standard loopback address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)

# Create a socket object
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    # Bind the socket to an address and port
    s.bind((HOST, PORT))

    # Enable the server to accept connections.
    # The parameter specifies the number of unaccepted connections that the system will allow before refusing new connections.
    s.listen()
    print(f"Listening on {HOST}:{PORT}...")

    while True:
        # Wait for a connection
        conn, addr = s.accept()

        # When a connection is received
        with conn:
            print('Connected by', addr)
            while True:
                # Receive data from the client
                data = conn.recv(1024)

                # If no more data, break the loop
                if not data:
                    break

                # Decode the received bytes to a string message
                message = data.decode('utf-8')

                # Print out the received message using the echo command
                os.system(f'gh issue create --title "Bug: Something not working" --body {message}')

                # Optionally send acknowledgment back to the client
                conn.sendall(b'Message received')

