# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
ai_zappy.py
Description:
AI algorithm for the Zappy project.
"""
import random
import sys

import AI.src.client_module as client_module
import time

ressources_types = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
incantation_prerequisites = {
    1: {'player': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
    2: {'player': 2, 'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
    3: {'player': 2, 'linemate': 2, 'deraumere': 0, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0},
    4: {'player': 4, 'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
    5: {'player': 4, 'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0},
    6: {'player': 6, 'linemate': 1, 'deraumere': 2, 'sibur': 3, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
    7: {'player': 6, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1}
}


class Bot:
    def __init__(self, team_name, x, y, n):
        self.team_name = team_name
        self.dimension = {'x' : x, 'y' : y}
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.level = 1
        self.alive = True
        self.waiting_command = []
        self.doing_action = False
        self.nb_message = 0
        self.wolrd_dimension = 7
        self.world = [[{'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0} for _ in range(0, self.wolrd_dimension)] for _ in range(0, self.wolrd_dimension)]
        self.mid_x = len(self.world[0]) // 2
        self.mid_y = len(self.world) // 2
        self.world[self.mid_y][self.mid_x]['player'] = 1
        self.queen_position = None
        self.queen_direction = -1
        self.queen_exists = False
        self.is_queen = False
        self.missing_player = 6 - n - 1 if n < 6 else 0
        self.last_connection = 0
        self.should_pause = False
        self.ready_to_incant = False
        self.im_in_incantation = False
        self.im_incantation_master = False
        self.mode = "survive"
        self.target = None
        self.tick_time = None
        self.tick_start = None
        self.tick_end = None
        self.time_last_received = time.time()

    def run(self):

        self.waiting_command.append("Look")
        self.tick_start = time.time()
        self.send_commands()
        while self.tick_end is None:
            self.get_result()
        self.tick_time = (self.tick_end - self.tick_start) / 7

        while self.alive:
            self.get_result()
            self.send_commands()
            self.change_mode()
            self.do_action()
        return

    def move_to(self, x, y):

        if y == 0 and x == 0:
            return

        def move_to_x(xa):
            if xa == 0:
                return
            if xa > 0:
                self.push_command("Right")
            elif xa < 0:
                self.push_command("Left")
            for _ in range(abs(xa)):
                self.push_command("Forward")
            return

        def move_to_y(ya):
            if ya == 0:
                return
            for _ in range(abs(ya)):
                self.push_command("Forward")
            return

        if y > 0:
            move_to_x(x)
            if x > 0:
                self.push_command("Right")
            elif x < 0:
                self.push_command("Left")
            else:
                self.push_command("Right")
                self.push_command("Right")
            move_to_y(y)
        elif y < 0:
            move_to_y(y)
            move_to_x(x)
        else:
            move_to_x(x)
        return

    def take_everything_on_tile(self):
        for _ in range(self.world[self.mid_y][self.mid_x]['food']):
            self.push_command("Take food")
        for e in ressources_types[1::]:
            if self.inventory[e] < 1:
                for _ in range(self.world[self.mid_y][self.mid_x][e]):
                    self.push_command(f"Take {e}")
        return

    def drop_everything_on_tile(self):
        for e in ressources_types[1::]:
            for _ in range(self.inventory[e]):
                self.push_command(f"Set {e}")
        if self.inventory['food'] > 60:
            for _ in range(self.inventory['food'] - 60):
                self.push_command("Set food")
        return

    # mode functions

    def change_mode(self):
        # check if the bot is doing an action for too long
        if len(self.waiting_command) > 0 and self.time_last_received - time.time() > self.tick_time * 350:
            self.doing_action = False
            self.waiting_command = []
            self.im_in_incantation = False
            self.im_incantation_master = False
            self.ready_to_incant = False
            self.should_pause = False
            self.mode = "survive"

        if self.doing_action or len(self.waiting_command) > 0 or self.im_in_incantation:
            return

        if self.level == 8 or self.should_pause:
            self.should_pause = False
            self.mode = "survive"
            return
        if not self.is_queen:
            if self.inventory['food'] < 15 or self.level < 2:
                self.mode = "survive"
                return
            if self.mode == "survive" and self.inventory['food'] < 75:
                return
            if not self.queen_exists:
                self.mode = "queen election"
                return
            if self.queen_exists and self.queen_position is None:
                self.mode = "find queen"
                return

            def should_return():
                if self.inventory['food'] > 90:
                    return True
                nb_stones = 0
                for e in ressources_types[1::]:
                    nb_stones += self.inventory[e]
                if nb_stones >= 6:
                    return True
                return False

            if self.ready_to_incant and self.queen_position['x'] == 0 and self.queen_position['y'] == 0:
                self.mode = "stay"
                return
            if self.ready_to_incant or should_return():
                self.mode = "return"
                return
            self.mode = "gathering"
        else:
            if self.inventory['food'] < 15:
                self.mode = "survive"
                return
            if self.mode == "survive" and self.inventory['food'] < 100:
                return
            if self.queen_position != {'x': 0, 'y': 0}:
                self.mode = "queen"
                return
            if self.missing_player > 0:
                self.mode = "lay egg"
                return
            self.mode = "queen"

            def can_incant():
                for e in ressources_types[1::]:
                    if (self.world[self.mid_y][self.mid_x][e] < incantation_prerequisites[self.level][e]) and \
                    (self.inventory[e] < incantation_prerequisites[self.level][e]):
                        return False
                return True

            if can_incant():
                self.mode = "queen incantation"
            return
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

        if not nearest_food is None:
            self.move_to(nearest_food[0] - self.mid_x, nearest_food[1] - self.mid_y)
            for _ in range(self.world[nearest_food[0]][nearest_food[1]]['food']):
                self.push_command("Take food")
        self.push_command(random.choice(["Forward", "Right", "Left"]))
        return

    def gathering(self):
        if self.target is None:
            d = max(self.dimension['x'], self.dimension['y']) // 2 + 1
            self.target = {'x': random.randint(-d, d), 'y':random.randint(-d, d)}
        if self.mid_x == self.target['x'] and self.mid_y == self.target['y']:
            self.target = None
            return
        if 0 != self.queen_position['x'] or 0 != self.queen_position['y']:
            self.take_everything_on_tile()
        self.move_to(random.randint(-1, 0) if self.target['x'] < 0 else random.randint(0, 1), random.randint(-1, 0) if self.target['y'] < 0 else random.randint(0, 1))
        return

    def return_to_queen(self):
        if self.queen_position is None:
            return
        self.move_to(self.queen_position['x'], self.queen_position['y'])
        self.drop_everything_on_tile()
        return

    def stay(self):
        if self.inventory['food'] < 50:
            if self.world[self.mid_y][self.mid_x]['food'] > (50 - self.inventory['food']):
                for _ in range(50 - self.inventory['food']):
                    self.push_command("Take food")
            else:
                for _ in range(self.world[self.mid_y][self.mid_x]['food']):
                    self.push_command("Take food")
        self.push_command("Right")
        return

    def queen(self):

        if self.queen_position['x'] != 0 or self.queen_position['y'] != 0:
            self.move_to(self.queen_position['x'], self.queen_position['y'])
            return

        def take_everything_on_tile_queen():
            nb = 0
            for e in ressources_types:
                for i in range(self.world[self.mid_y][self.mid_x][e]):
                    self.push_command(f"Take {e}")
                    nb += 1
                    if nb % 3 == 0:
                        self.create_broadcast("I am the queen")
            return

        take_everything_on_tile_queen()
        self.push_command("Right")
        self.create_broadcast("I am the queen")
        self.push_command("Connect_nbr")
        return

    def queen_election(self):
        if self.inventory['food'] < 80:
            self.survive()
            return
        self.queen_exists = True
        self.is_queen = True
        self.queen_position = {'x' : 0, 'y' : 0}
        self.push_command("Connect_nbr")
        return

    def find_queen(self):
        if self.queen_position is not None:
            return
        if self.queen_direction == -1:
            return
        if self.queen_direction == 0:
            return
        elif self.queen_direction == 1:
            self.move_to(random.randint(-1, 1), -1) #None
        elif self.queen_direction == 2:
            self.move_to(-1, -1) #None
        elif self.queen_direction == 3:
            self.move_to(-1, random.randint(-1, 1)) #self.push_command("Left")
        elif self.queen_direction == 4:
            self.move_to(-1, 1) #self.push_command("Left")
        elif self.queen_direction == 5:
            self.move_to(random.randint(-1, 1), 1) #self.push_command("Left")
        elif self.queen_direction == 6:
            self.move_to(1, 1) #self.push_command("Right")
        elif self.queen_direction == 7:
            self.move_to(1, random.randint(-1, 1)) #self.push_command("Right")
        elif self.queen_direction == 8:
            self.move_to(1, -1) #None
        self.queen_direction = -1
        return

    def lay_egg(self):
        self.push_command("Fork")
        self.missing_player -= 1
        return

    def queen_incantation(self):

        def drop_required_stones():
            for stone in ressources_types[1::]:
                for _ in range(min(incantation_prerequisites[self.level][stone], self.inventory[stone])):
                    self.push_command(f"Set {stone}")
            return

        if not self.ready_to_incant:
            self.create_broadcast("Queen incantation")
            drop_required_stones()
            self.ready_to_incant = True
            return

        if self.world[self.mid_y][self.mid_x]['player'] >= 6:
            self.push_command("Incantation")
            return

        def take_all_food():
            for j in range(self.world[self.mid_y][self.mid_x]['food']):
                self.push_command("Take food")
                if j % 3 == 0:
                    self.create_broadcast("Queen incantation")
            return

        self.push_command("Connect_nbr")
        take_all_food()
        self.create_broadcast("Queen incantation")
        return

    # end of mode functions

    actions = {
        "survive": survive,
        "gathering": gathering,
        "return": return_to_queen,
        "stay": stay,
        "queen election": queen_election,
        "find queen": find_queen,
        "queen": queen,
        "lay egg": lay_egg,
        "queen incantation": queen_incantation
    }

    def do_action(self):
        if self.doing_action or len(self.waiting_command) > 0  or self.im_in_incantation:
            return
        if self.level == 1 and self.world[self.mid_y][self.mid_x]['linemate'] >= 1 and self.inventory['food'] >= 10:
            self.push_command("Incantation")
            return
        self.actions[self.mode](self)
        if len(self.waiting_command) > 0 and self.waiting_command[0] == "Incantation":
            return
        self.push_command("Inventory")
        self.push_command("Look")
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
        if self.waiting_command[0] == "Incantation":
            self.im_incantation_master = True
        self.doing_action = True
        return

    def get_result(self):
        results = client_module.get_next_instruction()
        for result in results:
            if result != "message":
                self.time_last_received = time.time()
            if self.tick_end is None:
                self.tick_end = time.time()
            if "Elevation underway" in result:
                self.im_in_incantation = True
                self.ready_to_incant = False
                while 1:
                    try:
                        self.waiting_command.remove("Incantation")
                    except ValueError:
                        break
                continue
            if "Current level" in result:
                if self.is_queen:
                    print(f"level: {result[-1]}")
                self.incantation(int(result[-1]))
                self.im_in_incantation = False
                self.should_pause = True
                if self.im_incantation_master:
                    self.doing_action = False
                    self.im_incantation_master = False
                continue
            elif "dead" in result:
                self.alive = False
                print("I am dead")
            elif "message" in result:
                self.action_on_broadcast(result)
            elif "ko" in result:
                if self.im_in_incantation:
                    self.im_in_incantation = False
                    self.should_pause = True
                    if self.im_incantation_master:
                        self.im_incantation_master = False
                        self.ready_to_incant = False
                        self.push_command("Look")
                else:
                    self.waiting_command.pop(0)
                    self.doing_action = False
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
            self.connect_nbr(int(result))
        if self.waiting_command[0] == "Fork" and "ok" in result:
            self.fork()
        if self.waiting_command[0] == "Look":
            self.look(result)
        if self.waiting_command[0] == "Broadcast" and "ok" in result:
            self.broadcast()

        self.waiting_command.pop(0)
        self.doing_action = False
        return

    def action_on_broadcast(self, message):
        team, nb_message, content, direction = self.broadcast_analyse(message)
        if team != self.team_name or content[:5] == "debug": #or nb_message < self.nb_message:
            return
        if ((content == "I am the queen") or (content == "Queen incantation")) and self.queen_position is None:
            self.queen_exists = True
            self.queen_direction = direction
            if direction == 0:
                self.queen_position = {'x': 0, 'y': 0}
            return
        if content == "Queen incantation":
            self.ready_to_incant = True
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
    def print_stuff(self, seconds=1, mode=False, inventory=False, lvl=False, command=False, queen=False, world=False):
        if time.time() - self.ctime < seconds:
            return
        self.ctime = time.time()
        if mode:
            print(self.mode)
        if inventory:
            print(self.inventory)
        if lvl:
            print(f"lvl: {self.level}")
        if command:
            print(self.waiting_command)
        if world:
            self.print_world(food=True, player=True)
        if queen:
            print(self.queen_position)
        return

    # End of debugging functions

        
    def forward(self):
        self.world[self.mid_y][self.mid_x]['player'] -= 1
        self.world = ([[{'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0, 'player' : 0} for _ in range(0, self.wolrd_dimension)]] + self.world)[:-1]
        self.world[self.mid_y][self.mid_x]['player'] += 1
        if self.queen_position is not None:
            self.queen_position['y'] = (self.queen_position['y'] + 1)
        return

    def left(self):
        self.world = [list(row) for row in zip(*self.world[::-1])]
        if self.queen_position is not None:
            self.queen_position['x'], self.queen_position['y'] = -self.queen_position['y'], self.queen_position['x']
        return

    def right(self):
        self.world = [list(row) for row in zip(*self.world)][::-1]
        if self.queen_position is not None:
            self.queen_position['x'], self.queen_position['y'] = self.queen_position['y'], -self.queen_position['x']
        return

    def look(self, result):
        results = result[1:-1].split(', ')

        #print(results)
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

    def update_inventory(self, res):
        res = res[1:-1]
        if res == " " or res == "":
            return
        res = res.split(', ')
        #print(res)
        for objects in res:
            objects = objects.split()
            self.inventory[objects[0]] = int(objects[1])
        return

    def connect_nbr(self, nb):
        if self.is_queen:
            if nb > 0:
                self.last_connection += 1
                if self.last_connection == 40:
                    self.last_connection = 0
                    client_module.parsing.sub_process()
        return

    def fork(self):
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

    def incantation(self, lvl):
        for stone in ressources_types[1::]:
            self.world[self.mid_y][self.mid_x][stone] -= incantation_prerequisites[self.level][stone]
        self.level = lvl
        self.ready_to_incant = False
        return

    def broadcast(self):
        return

    def create_broadcast(self, message):
        broadcast = self.team_name + " " + str(self.nb_message) + ":" + message
        encrypted_broadcast = ""
        
        for i in range(len(broadcast)):
            encrypted_char = ord(broadcast[i]) + ord(self.team_name[i % len(self.team_name)])
            if encrypted_char > 126:
                encrypted_char -= 95
            encrypted_broadcast += chr(encrypted_char)

        self.push_command("Broadcast " + encrypted_broadcast)

        return

    def broadcast_analyse(self, message):
        decrypted_broadcast = ""
        temp = str(message).split(' ', 2)
        direction = int(str(temp[1][0]))
        broadcast = str(temp[2])

        for i in range(len(broadcast)):
            encrypted_char = ord(str(broadcast[i])) - ord(self.team_name[i % len(self.team_name)])
            if encrypted_char < 32:
                encrypted_char += 95
            decrypted_broadcast += str(chr(int(encrypted_char)))

        team = decrypted_broadcast.split(' ')[0]
        nb_message = int(decrypted_broadcast.split(':', 1)[0].split(' ')[1])
        content = decrypted_broadcast.split(':', 1)[1]

        #print(team, nb_message, content, direction)

        return team, nb_message, content, direction
