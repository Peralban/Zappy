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
import AI.src.ai_zappy as ai_zappy
import AI.src.parsing as parsing

current_line = 0
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock_file = None
data = []

def get_next_instruction():
    cdata = []

    csock_file = sock.makefile('r')
    inputs = [csock_file]
    readable, _, _ = select.select(inputs, [], [], 0)
    for s in readable:
        if s is csock_file:
            for i, message in enumerate(s):
                cdata.append(message.strip())
                break
    return cdata

def send_instruction(instruction):
    sock.sendall((instruction + '\n').encode())

def connect_to_server(host, port, name):
    current_line = 0
    server_address = (host, port)
    LatLng = ()

    try:
        sock.connect(server_address)
        sock.sendall((name + '\n').encode())
    except ConnectionRefusedError:
        print('Connection refused by server')
        sys.exit(84)

    sock_file = sock.makefile('r')
    inputs = [sock_file, sys.stdin]
    nb = 0

    #try:
    while True:
        readable, _, _ = select.select(inputs, [], [], 0)
        for s in readable:
            if s is sock_file:
                for message in s:
                    current_line += 1
                    if not message:
                        print('Disconnected from server')
                        sock.close()
                        sys.exit()
                    else:
                        print(message.strip())
                        parts = message.strip().split()
                        if current_line == 2:
                            if message.strip() == 'ko':
                                sys.exit(84)
                            else:
                                nb = int(parts[0])
                        if current_line == 3:
                            LatLng = (int(parts[0]), int(parts[1]))
                            Bot = ai_zappy.Bot(name, LatLng[0], LatLng[1], nb)
                            Bot.run()
                            sock.close()
                            sock_file.close()
                            sys.exit(0)
    #except KeyboardInterrupt:
    #    print("\nClient interrupted.")
    #    sock.close()
    #    sock_file.close()
    #    sys.exit(0)
    #finally:
    sock.close()
    sock_file.close()
    sys.exit(0)
