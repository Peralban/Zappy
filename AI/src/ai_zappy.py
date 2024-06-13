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

        for i in range(y):
            line = []

            for u in range(x):
                tile = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0}
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
        self.waiting_command = []

    def run(self):
        self.send_instruction("Look")
        while self.alive == True:
            self.get_result()
        return

    def send_instruction(self, instruction):
        if len(self.waiting_command) < 10:
            self.waiting_command.append(instruction)
            client_module.send_instruction(instruction)
            return True
        else:
            return False

    def get_result(self):
        results = client_module.get_next_instruction()
        for result in results:
            if "dead" in result:
                self.alive = False
            elif "message" in result:
                self.broadcast_analyse(result)
            else:
                self.manage_result(result)
        return
    
    def manage_result(self, result):
        if self.waiting_command[0] == "Forward" and "ok" in result:
            self.forward()
        if self.waiting_command[0] == "Right" and "ok" in result:
            self.right()
        if self.waiting_command[0] == "Left" and "ok" in result:
            self.left()
        if self.waiting_command[0] == "Inventory":
            self.update_inventory()
        if "Take" in self.waiting_command[0] and "ok" in result:
            self.take(self.waiting_command[0][:' '])
        if "Set" in self.waiting_command[0] and "ok" in result:
            self.left(self.waiting_command[0][:' '])
        if self.waiting_command[0] == "Connect_nbr":
            self.connect_nbr(result)
        if self.waiting_command[0] == "Fork" and "ok" in result:
            self.fork(result)
        if self.waiting_command[0] == "Incantation" and not "ko" in result:
            self.incantation()
        if self.waiting_command[0] == "Look":
            self.look(result)

        self.waiting_command.pop(0)
        return
        
    def forward(self):
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
        self.direction -= 1
        if self.direction == 0:
            self.direction = 4
        return

    def left(self):
        self.direction += 1
        if self.direction == 4:
            self.direction = 0
        return

    def look(self, results):
        data = []
        datas = []

        results = str(results[1:-1])
        results = results.split(',')
        for result in results:
            result = str(result)
            data = result.split(' ')
            for object in data:
                if object == "":
                    data.remove(object)
            datas.append(data)

        print(datas)

        if self.direction == 1:
            for i in range(self.level + 1):
                for data in datas[i]:
                    self.map[self.position['y']][self.position['x'] + i][data] += 1
                for u in range(i):
                    for data in datas[i - u]:
                        self.map[self.position['y'] - u][self.position['x'] + i][data] += 1
                    for data in datas[i + u]:
                        self.map[self.position['y'] + u][self.position['x'] + i][data] += 1
                for y in range(i * 2 + 1):
                    results.pop(0)
        
        elif self.direction == 2:
            for i in range(self.level + 1):
                for data in datas[i]:
                    self.map[self.position['y'] + i][self.position['x']][data] += 1
                for u in range(i):
                    for data in datas[i - u]:
                        self.map[self.position['y'] + i][self.position['x'] - u][data] += 1
                    for data in datas[i + u]:
                        self.map[self.position['y'] + i][self.position['x'] + u][data] += 1
                for y in range(i * 2 + 1):
                    results.pop(0)

        elif self.direction == 3:
            for i in range(self.level + 1):
                for data in datas[i]:
                    self.map[self.position['y']][self.position['x'] - i][data] += 1
                for u in range(i):
                    for data in datas[i - u]:
                        self.map[self.position['y'] - u][self.position['x'] - i][data] += 1
                    for data in datas[i + u]:
                        self.map[self.position['y'] + u][self.position['x'] - i][data] += 1
                for y in range(i * 2 + 1):
                    results.pop(0)

        else:
            for i in range(self.level + 1):
                for data in datas[i]:
                    self.map[self.position['y'] - i][self.position['x']][data] += 1
                for u in range(i):
                    for data in datas[i - u]:
                        self.map[self.position['y'] - i][self.position['x'] - u][data] += 1
                    for data in datas[i + u]:
                        self.map[self.position['y'] - i][self.position['x'] + u][data] += 1
                for y in range(i * 2 + 1):
                    results.pop(0)
        print(datas)
        print(self.map)
        return

    def update_inventory(self):
        res = res.split(',')
        for object in res:
            object = object.split()
            self.inventory[object[0]] = int(object[1])
        return

    def connect_nbr(self, nb):
        if int(nb) > 0:
            client_module.parsing.sub_process()
        return

    def fork(self):
        client_module.parsing.sub_process()
        return

    def eject(self):
        return

    def take(self, object_name):
        self.inventory[object_name] += 1
        return

    def set(self, object_name):
        self.inventory[object_name] -= 1
        return

    def incantation(self):
        self.level += 1
        return

    def create_broadcast(self):
        return

    def broadcast_analyse(self, message):
        return
