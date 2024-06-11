# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
ai_zappy.py
Description:
AI algorithm for the Zappy project.
"""

import AI.src.client_module as client_module

def init_map(x, y):
        game_map = []
        tile = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}

        for i in range(y):
            line = []

            for u in range(x):
                line.append(tile)

            game_map.append(line)

        return (game_map)

class Bot:
    def __init__(self, team_name, x, y):
        self.team_name = team_name
        self.map = init_map(x, y)
        self.dimension = {'x' : x - 1, 'y' : y - 1}
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.position = {'x' : 0, 'y' : 0}
        self.direction = 1
        self.level = 1
        self.alive = True
        self.command_number = 0

    def run(self):
        while self.alive:
            self.forward()
        return

    def forward(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Forward")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        if res == "ok":
            if self.direction == 1:
                self.position['x'] += 1
            if self.direction == 2:
                self.position['y'] += 1
            if self.direction == 3:
                self.position['x'] -= 1
            if self.direction == 4:
                self.position['y'] -= 1

            if self.position['y'] > self.dimension['y']:
                self.position['y'] == 0
            if self.position['y'] < 0:
                self.position['y'] == self.dimension['y']
            if self.position['x'] >= self.dimension['x']:
                self.position['x'] == 0
            if self.position['x'] < 0:
                self.position['x'] == self.dimension['x']
        return

    def right(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Right")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        if res == "ok":
            self.direction -= 1
            if self.direction == 0:
                self.direction = 4
        return

    def left(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Left")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        if res == "ok":
            self.direction += 1
            if self.direction == 4:
                self.direction = 0
        return

    def look(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Look")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        return

    def update_inventory(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Inventory")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        res = res.split(',')
        for object in res:
            object = object.split()
            self.inventory[object[0]] = int(object[1])
        return

    def connect_nbr(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Connect_nbr")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        if res > 0:
            self.fork()
        return

    def fork(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Fork")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        return

    def eject(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Eject")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        if res == "ko":
            self.eject()
        return

    def take(self, object_name):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Take " + object_name)
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        if res == "ok":
            self.inventory[object_name] += 1
        return

    def set(self, object_name):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Set "+ object_name)
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        if res == "ok":
            self.inventory[object_name] -= 1
        return

    def incantation(self):
        self.command_number += 1
        res = 0

        client_module.send_instruction("Incantation")
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False
        if res != "ko":
            self.level += 1
        return

    def broadcast(self, message):
        self.command_number += 1
        res = 0

        client_module.send_instruction("broadcast " + message)
        res = client_module.get_next_instruction(self.command_number)
        while "message" in res:
            self.broadcast_analyse(res)
            self.command_number += 1
            res = client_module.get_next_instruction(self.command_number)
        if res == "dead":
            self.alive = False 
        return

    def broadcast_analyse(self, message):
        return
