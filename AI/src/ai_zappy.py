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
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.position_x = 0
        self.position_y = 0
        self.level = 0

    def run(self):
        return

    def forward(self):
        return
    
    def right(self):
        return
    
    def left(self):
        return
    
    def look(self):
        return
    
    def inventory(self):
        return
    
    def connect_nbr(self):
        return
    
    def fork(self):
        return
    
    def eject(self):
        return
    
    def take(self):
        return
    
    def set(self):
        return
    
    def incantation(self):
        return