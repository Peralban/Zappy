# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
client_module.py
Description:
Add socket client functionalities.
"""

import socket
import select

def connect_to_server(server_host, server_port):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_host, server_port))
    print("Connected to server.")
    return client_socket


def communicate_with_server(client_socket, team_name):
    inputs = [client_socket.makefile('r')]
    while inputs:
        readable, _, exceptional = select.select(inputs, [], inputs)
        for s in readable:
            if s is client_socket.makefile('r'):
                message = s.readline().strip()
                if message:
                    print("Server message:", message)
                    if "Welcome" in message:
                        client_socket.sendall(f"{team_name}\n".encode())
                    elif "number" in message:
                        client_num = int(message.split()[1])
                        if client_num >= 1:
                            print("Slots available for the team. Ready to connect new clients.")
                        else:
                            print("No slots available for the team. Disconnecting.")
                            inputs.remove(s)
                            s.close()
                else:
                    print("Disconnected from server.")
                    inputs.remove(s)
                    s.close()
        for s in exceptional:
            print("Handling exceptional condition for", s.getpeername())
            inputs.remove(s)
            s.close()