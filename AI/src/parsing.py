# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
parsing.py
Description:
Retrieve value from arguments given by the user.
"""

import argparse
import sys
import subprocess

def parse_arguments():
    parser = argparse.ArgumentParser(
        description='Zappy AI Client Arguments',
        usage='./zappy_ai -p port -n name -h machine',
        add_help=False
    )
    parser.add_argument('-p', '--port', type=int, required=True, help='Port number to connect to')
    parser.add_argument('-n', '--name', type=str, required=True, help='Name of the client')
    parser.add_argument('-h', '--host', type=str, default='127.0.0.1', help='Host to connect to')
    parser.add_argument('-help', action='help', help='Show this help message and exit')

    try:
        args = parser.parse_args()
        return args.port, args.name, args.host
    except SystemExit as e:
        sys.exit(84)

if __name__ == "__main__":
    try:
        port, name, host = parse_arguments()
        print(f"Port: {port}, Name: {name}, Host: {host}")
    except SystemExit as e:
        if e.code == 2:
            print("Usage: ./zappy_ai -p port -n name -h machine", file=sys.stderr)
            sys.exit(84)
        else:
            raise

def sub_process():
    port, name, host = parse_arguments()
    subprocess.run(["python3", "zappy_ai", "-p", str(port), "-n", str(name), "-h", str(host)])
