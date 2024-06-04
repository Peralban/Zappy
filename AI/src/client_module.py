# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
client_module.py
Description:
Socket connection to the server.
"""

import socket
import select
import sys

def connect_to_server(host, port, name):
    server_address = (host, port)
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    LatLng = ()

    try:
        sock.connect(server_address)
        sock.sendall((name + '\n').encode())
    except ConnectionRefusedError:
        sys.exit(84)

    sock_file = sock.makefile('r')
    inputs = [sock_file, sys.stdin]

    try:
        while True:
            readable, _, _ = select.select(inputs, [], [])
            for s in readable:
                if s is sock_file:
                    for message in s:
                        if not message:
                            print('Disconnected from server')
                            sys.exit()
                        else:
                            print(message.strip())
                            parts = message.strip().split()
                            if len(parts) == 2:
                                LatLng = (int(parts[0]), int(parts[1]))
                else:
                    message = sys.stdin.readline()
                    sock.sendall(message.encode())
                    sys.stdout.write('<You> ')
                    sys.stdout.write(message)
                    sys.stdout.flush()
    except KeyboardInterrupt:
        print("\nClient interrupted.")
    finally:
        sock.close()