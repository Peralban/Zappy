#!/usr/bin/env python3

# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
main.py
Description:
Entry point of the AI.
"""

from AI.src.client_module import connect_to_server, send_receive_messages

def main():
    server_host = '127.0.0.1'
    server_port = 12345

    client_socket = connect_to_server(server_host, server_port)
    send_receive_messages(client_socket)

if __name__ == "__main__":
    main()
