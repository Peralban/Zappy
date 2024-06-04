#!/usr/bin/env python3

# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
main.py
Description:
Retrieve value from arguments given by the user.
"""

from AI.src.client_module import connect_to_server
from AI.src.parsing import parse_arguments

def main():
    port, name, host = parse_arguments()
    connect_to_server(host, port, name)

if __name__ == "__main__":
    main()
