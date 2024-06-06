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
import ai_zappy

current_line = 0
sock_file = None
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def get_next_instruction(current_command):
    nbr_line = current_line + current_command
    if nbr_line.strip():
        for line in sock_file:
            if line.strip():
                return line.strip()
    return None

def send_instruction(instruction):
    sock.sendall((instruction + '\n').encode())

def connect_to_server(host, port, name):
    global current_line
    server_address = (host, port)
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
                        current_line += 1
                        if not message:
                            print('Disconnected from server')
                            sys.exit()
                        else:
                            print(message.strip())
                            parts = message.strip().split()
                            if len(parts) == 2:
                                LatLng = (int(parts[0]), int(parts[1]))
                                Bot = ai_zappy.Bot(name, LatLng[0], LatLng[1])
                                Bot.run()
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
