#!/usr/bin/env python3

# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
main.py
Description:
Retrieve value from arguments given by the user.
"""

import sys
from AI.src.client_module import connect_to_server, communicate_with_server
from AI.src.parsing import parse_arguments

def main():
    port, name, host = parse_arguments()
    client_socket = connect_to_server(host, port)
    communicate_with_server(client_socket, name)

if __name__ == "__main__":
    main()
