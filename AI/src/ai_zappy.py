# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
ai_zappy.py
Description:
AI algorithm for the Zappy project.
"""
import random

import AI.src.client_module as client_module
import time

class Bot:
    def __init__(self, team_name, x, y):
        self.team_name = team_name
        self.dimension = {'x' : x, 'y' : y}
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.level = 1
        self.alive = True
        self.waiting_command = []
        self.doing_action = False
        self.nb_message = 0
        self.wolrd_dimension = 5
        self.world = [[{'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0} for _ in range(0, self.wolrd_dimension)] for _ in range(0, self.wolrd_dimension)]
        self.mid_x = len(self.world[0]) // 2
        self.mid_y = len(self.world) // 2
        self.world[self.mid_y][self.mid_x]['player'] = 1
        self.queen_position = {'x' : 0, 'y' : 0}
        self.mode = "survive"

    def run(self):
        while self.alive:
            self.get_result()
            self.send_commands()
            self.change_mode()
            self.do_action()
            self.print_stuff(seconds=3, mode=True, inventory=True)
        return

    def move_to(self, x, y):

        if x < 0 or x >= len(self.world[0]) or y < 0 or y >= len(self.world):
            return

        def move_to_x(xa):
            if xa > self.mid_x:
                self.push_command("Right")
            elif xa < self.mid_x:
                self.push_command("Left")
            for _ in range(abs(xa - self.mid_x)):
                self.push_command("Forward")
            return

        if y > self.mid_y:
            move_to_x(x)
            if x > self.mid_x:
                self.push_command("Right")
            elif x < self.mid_x:
                self.push_command("Left")
            for _ in range(abs(y - self.mid_y)):
                self.push_command("Forward")
        elif y < self.mid_y:
            for _ in range(abs(y - self.mid_y)):
                self.push_command("Forward")
            move_to_x(x)
        else:
            move_to_x(x)
        return

    # mode functions

    def change_mode(self):
        if self.doing_action:
            return
        if self.inventory['food'] < 10:
            self.mode = "survive"
        if self.mode == "survive" and self.inventory['food'] >= 30:
            self.mode = "other"
        return

    def survive(self):

        def find_nearest_food():
            min_distance = float('inf')
            nearest_food = None
            for i in range(len(self.world)):
                for j in range(len(self.world[i])):
                    if self.world[i][j]['food'] > 0:
                        distance = abs(self.mid_x - j) + abs(self.mid_y - i)
                        if distance < min_distance:
                            min_distance = distance
                            nearest_food = (j, i)
            return nearest_food

        nearest_food = find_nearest_food()

        if nearest_food is None:
            self.push_command(random.choice(["Forward", "Right", "Left"]))
            self.push_command("Look")
        else:
            self.move_to(nearest_food[0], nearest_food[1])
            self.push_command("Take food")
        return

    # temporary function while we don't have the other mode
    def other(self):
        self.push_command("Inventory")
        return

    # end of mode functions

    def do_action(self):
        if self.doing_action:
            return
        if self.mode == "survive":
            self.survive()
        if self.mode == "other":
            self.other()
        return

    def push_command(self, command):
        self.waiting_command.append(command)
        return

    def send_commands(self):
        if len(self.waiting_command) == 0:
            return
        if self.doing_action:
            return
        client_module.send_instruction(self.waiting_command[0])
        self.doing_action = True
        return

    def get_result(self):
        results = client_module.get_next_instruction()
        for result in results:
            if "dead" in result:
                self.alive = False
                return
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
            self.update_inventory(result)
        if "Take" in self.waiting_command[0] and "ok" in result:
            self.take(self.waiting_command[0][5:])
        if "Set" in self.waiting_command[0] and "ok" in result:
            self.set(self.waiting_command[0][4:])
        if self.waiting_command[0] == "Connect_nbr":
            self.connect_nbr(result)
        if self.waiting_command[0] == "Fork" and "ok" in result:
            self.fork()
        if self.waiting_command[0] == "Incantation" and not "ko" in result:
            self.incantation()
        if self.waiting_command[0] == "Look":
            self.look(result)

        self.waiting_command.pop(0)
        self.doing_action = False
        return


    # Debugging functions
    def print_world(self, food=False, linemate=False, deraumere=False, sibur=False, mendiane=False, phiras=False, thystame=False, player=True):
        for i in range(len(self.world)):
            for j in range(len(self.world[i])):
                print(f"({j}, {i})", end=" ")
                if food:
                    print(f"Fo: {self.world[i][j]['food']}", end=" ")
                if linemate:
                    print(f"Li: {self.world[i][j]['linemate']}", end=" ")
                if deraumere:
                    print(f"De: {self.world[i][j]['deraumere']}", end=" ")
                if sibur:
                    print(f"Si: {self.world[i][j]['sibur']}", end=" ")
                if mendiane:
                    print(f"Me: {self.world[i][j]['mendiane']}", end=" ")
                if phiras:
                    print(f"Ph: {self.world[i][j]['phiras']}", end=" ")
                if thystame:
                    print(f"Th: {self.world[i][j]['thystame']}", end=" ")
                if player:
                    print(f"Pl: {self.world[i][j]['player']}", end=" ")
                print("", end="|")
            print()
        return

    ctime = time.time()
    def print_stuff(self, seconds=1, mode=False, inventory=False):
        if time.time() - self.ctime < seconds:
            return
        self.ctime = time.time()
        if mode:
            print(self.mode)
        if inventory:
            print(self.inventory)
        return

    # End of debugging functions

        
    def forward(self):
        self.world[self.mid_y][self.mid_x]['player'] -= 1
        self.world = ([[{'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0} for _ in range(0, self.wolrd_dimension)]] + self.world)[:-1]
        self.world[self.mid_y][self.mid_x]['player'] += 1
        self.queen_position['y'] = (self.queen_position['y'] + 1)
        return

    def left(self):
        self.world = [list(row) for row in zip(*self.world[::-1])]
        self.queen_position['x'], self.queen_position['y'] = -self.queen_position['y'], self.queen_position['x']
        return

    def right(self):
        self.world = [list(row) for row in zip(*self.world)][::-1]
        self.queen_position['x'], self.queen_position['y'] = self.queen_position['y'], -self.queen_position['x']
        return

    def look(self, result):
        results = result[1:-1].split(', ')

        print(results)

        def init_dict(t_result):
            t_dict = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0}
            t_results = t_result.split()
            while len(t_results):
                t_dict[t_results.pop(0)] += 1
            return t_dict
        k = 1
        while len(results) > 0:
            if (k // 2) + self.mid_y >= len(self.world) or (k // 2) + self.mid_x >= len(self.world[0]):
                break
            for i in range(0, k):
                self.world[self.mid_y - (k // 2)][self.mid_x - (k // 2) + i] = init_dict(results.pop(0))
            k += 2
        self.print_world(food=True, player=True)
        print(self.queen_position)

    def update_inventory(self, res):
        res = res[1:-1].split(', ')
        for objects in res:
            objects = objects.split()
            self.inventory[objects[0]] = int(objects[1])
        return

    def connect_nbr(self, nb):
        if int(nb) > 0:
            for i in range(int(nb)):
                client_module.parsing.sub_process()
        return

    def fork(self):
        client_module.parsing.sub_process()
        return

    def eject(self):
        return

    def take(self, object_name):
        self.world[self.mid_y][self.mid_x][object_name] -= 1
        self.inventory[object_name] += 1
        return

    def set(self, object_name):
        self.world[self.mid_y][self.mid_x][object_name] += 1
        self.inventory[object_name] -= 1
        return

    def incantation(self):
        self.level += 1
        return

    def create_broadcast(self, message):
        broadcast = self.team_name + " " + str(self.nb_message) + ":" + message
        encrypted_broadcast = ""
        
        for i in range(len(broadcast)):
            encrypted_char = ord(broadcast[i]) + ord(self.team_name[i % len(self.team_name)])
            if encrypted_char > 122:
                encrypted_char -= 91
            encrypted_broadcast += chr(encrypted_char)

        self.push_command("Broadcast " + encrypted_broadcast)

        self.nb_message += 1
        return

    def broadcast_analyse(self, message):
        decrypted_broadcast = ""
        temp = str(message).split(' ', 2)
        direction = int(str(temp[1][0]))
        broadcast = str(temp[2])

        for i in range(len(broadcast)):
            encrypted_char = ord(str(broadcast[i])) - ord(self.team_name[i % len(self.team_name)])
            if encrypted_char < 32:
                encrypted_char += 91

            decrypted_broadcast += str(chr(int(encrypted_char)))

        team = decrypted_broadcast.split(' ')[0]
        nb_message = int(decrypted_broadcast.split(' ')[1].split(':')[0])

        print(decrypted_broadcast)

        return
