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

def connect_to_server(host, port,name):
    server_address = (host, port)
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        sock.connect(server_address)
    except ConnectionRefusedError:
        sys.exit(84)

    sock_file = sock.makefile('r')
    inputs = [sock_file, sys.stdin]

    try:
        while True:
            readable, _, _ = select.select(inputs, [], [])
            for s in readable:
                if s is sock_file:
                    message = s.readline()
                    if not message:
                        print('Disconnected from server')
                        sys.exit()
                    else:
                        print(message.strip())
                else:
                    message = sys.stdin.readline()
                    sock.sendall(message.encode())
                    sys.stdout.write('<You> ')
                    sys.stdout.write(message)
                    sys.stdout.flush()
    except KeyboardInterrupt:
        print('')
    finally:
        sock.close()