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
        self.dimension = {'x' : x, 'y' : y}
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.position = {'x' : 0, 'y' : 0}
        self.direction = 1
        self.level = 1
        self.alive = True
        self.waiting_command = []
        self.nb_message = 0
        self.key = 0
        for i in range(len(self.team_name)):
            self.key += ord(self.team_name[i]) - 65
        self.key %= 91

    def run(self):
        self.create_broadcast("hey les boys")
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

        if self.position['y'] >= self.dimension['y']:
            self.position['y'] == 0
        if self.position['y'] < 0:
            self.position['y'] += self.dimension['y']
        if self.position['x'] >= self.dimension['x']:
            self.position['x'] == 0
        if self.position['x'] < 0:
            self.position['x'] += self.dimension['x']
        return

    def left(self):
        self.direction -= 1
        if self.direction == 0:
            self.direction = 4
        return

    def right(self):
        self.direction += 1
        if self.direction == 4:
            self.direction = 0
        return
    
    def update_map_x(self, datas, indicator):
        tiles_refill = []

        for i in range(self.level + 1):
            x = self.position['x'] + i * indicator
            y = self.position['y']

            if x < 0:
                x += self.dimension['x']
            elif x >= self.dimension['x']:
                x -= self.dimension['x']
                    
            if {'x' : x, 'y' : y} not in tiles_refill:
                self.map[y][x] = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0}
                for data in datas[i]:
                    self.map[y][x][data] += 1
                    tiles_refill.append({'x' : x, 'y' : y})

            for u in range(i):
                y = self.position['y'] - (u + 1)

                if y < 0:
                    y += self.dimension['y']

                if {'x' : x, 'y' : y} not in tiles_refill:
                    self.map[y][x] = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0}
                    for data in datas[i - (u + 1)]:
                        self.map[y][x][data] += 1
                    tiles_refill.append({'x' : x, 'y' : y})


                y = self.position['y'] + (u + 1)

                if y >= self.dimension['y']:
                    y -= self.dimension['y']

                if {'x' : x, 'y' : y} not in tiles_refill:
                    self.map[y][x] = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0}
                    for data in datas[i + (u + 1)]:
                        self.map[y][x][data] += 1
                    tiles_refill.append({'x' : x, 'y' : y})

            for y in range(i * 2 + 1):
                    datas.pop(0)
        return
    
    def update_map_y(self, datas, indicator):
        tiles_refill = []

        for i in range(self.level + 1):
            y = self.position['y'] + i * indicator
            x = self.position['x']

            if y < 0:
                y += self.dimension['y']
            elif y >= self.dimension['y']:
                y -= self.dimension['y']
                    
            if {'x' : x, 'y' : y} not in tiles_refill:
                self.map[y][x] = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0}
                for data in datas[i]:
                    self.map[y][x][data] += 1
                    tiles_refill.append({'x' : x, 'y' : y})

            for u in range(i):
                x = self.position['x'] - (u + 1)

                if x < 0:
                    x += self.dimension['x']

                if {'x' : x, 'y' : y} not in tiles_refill:
                    self.map[y][x] = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0}
                    for data in datas[i - (u + 1)]:
                        self.map[y][x][data] += 1
                    tiles_refill.append({'x' : x, 'y' : y})


                x = self.position['x'] + (u + 1)

                if x >= self.dimension['x']:
                    x -= self.dimension['x']

                if {'x' : x, 'y' : y} not in tiles_refill:
                    self.map[y][x] = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0}
                    for data in datas[i + (u + 1)]:
                        self.map[y][x][data] += 1
                    tiles_refill.append({'x' : x, 'y' : y})

            for y in range(i * 2 + 1):
                    datas.pop(0)
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
            if data == ['']:
                data = []
            datas.append(data)

        print(datas)


        if self.direction == 1:
            self.update_map_x(datas, 1)
        elif self.direction == 2:
            self.update_map_y(datas, 1)
        elif self.direction == 3:
            self.update_map_x(datas, -1)
        else:
            self.update_map_y(datas, -1)
            
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

    def create_broadcast(self, message):
        broadcast = self.team_name + " " + str(self.nb_message) + ":" + message
        encrypted_broadcast = ""
        
        for i in range(len(broadcast)):
            encrypted_char = ord(broadcast[i]) + self.key
            if encrypted_char > 122:
                encrypted_char -= 91
            encrypted_broadcast += chr(encrypted_char)

        self.send_instruction("Broadcast " + encrypted_broadcast)

        self.nb_message += 1
        return

    def broadcast_analyse(self, message):
        decrypted_broadcast = ""
        temp = str(message).split(' ', 2)
        direction = int(str(temp[1][0]))
        broadcast = str(temp[2])

        for i in range(len(broadcast)):
            encrypted_char = ord(str(broadcast[i])) - self.key
            if encrypted_char < 32:
                encrypted_char += 91

            decrypted_broadcast += str(chr(int(encrypted_char)))

        team  = decrypted_broadcast.split(' ')[0]
        nb_message = int(decrypted_broadcast.split(' ')[1].split(':')[0])

        self.nb_message += 1

        print(decrypted_broadcast)

        return
