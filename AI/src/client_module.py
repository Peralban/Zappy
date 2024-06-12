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
    sock_file = sock.makefile('r')
    inputs = [sock_file]
    readable, _, _ = select.select(inputs, [], [])
    for s in readable:
        if s is sock_file:
            data = []
            for i, message in enumerate(s):
                data.append(message.strip())
                break
    return data

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
                            if current_line == 2:
                                if message.strip() == 'ko':
                                    sys.exit(84)
                                else:
                                    nb_players = int(message.strip())
                                    send_instruction(str(nb_players))
                                    if nb_players != 0:
                                        parsing.sub_process()
                            if current_line == 3:
                                LatLng = (int(parts[0]), int(parts[1]))
                                Bot = ai_zappy.Bot(name, LatLng[0], LatLng[1])
                                Bot.run()
                                return
                else:
                    message = sys.stdin.readline()
                    sock.sendall(message.encode())
                    sys.stdout.write('<You> ')
                    sys.stdout.write(message)
                    sys.stdout.flush()
    except KeyboardInterrupt:
        send_instruction('quit')
        sock.close()
        print("\nClient interrupted.")
    finally:
        sock.close()
