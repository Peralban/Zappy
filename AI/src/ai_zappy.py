#!/usr/bin/env python3

def init_map(x, y):
        game_map = []
        object = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}

        for i in range(y):
            temp = []

            for u in range(x):
                temp.append(object)
            
            game_map.append(temp)
 
        return (game_map)

class Bot:
    def __init__(self, team_name, x, y):
        self.team_name = team_name
        self.map = init_map(x, y)
        self.invantory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.position_x = 0
        self.position_y = 0

    def Forward(self):
        return
    
    def Right(self):
        return
    
    def Left(self):
        return
    
    def Look(self):
        return
    
    def Inventory(self):
        return
    
    def Connect_nbr(self):
        return
    
    def Fork(self):
        return
    
    def Eject(self):
        return
    
    def Take(self):
        return
    
    def Set(self):
        return
    
    def Incantation(self):
        return
