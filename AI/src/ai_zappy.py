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

    def run(self):
        return

    def forward(self):
        res = 0

        #function calling for connection
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
        res = 0

        #function calling for connection
        if res == "ok":
            self.direction -= 1
            if self.direction == 0:
                self.direction = 4
        return
    
    def left(self):
        res = 0

        #function calling for connection
        if res == "ok":
            self.direction += 1
            if self.direction == 4:
                self.direction = 0
        return
    
    def look(self):
        return
    
    def update_inventory(self):
        res = ""

        #function calling for connection
        res = res.split(',')
        for object in res:
            object = object.split()
            self.inventory[object[0]] = int(object[1])
        return
    
    def connect_nbr(self):
        return
    
    def fork(self):
        return
    
    def eject(self):
        return
    
    def take(self, object_name):
        res = ""

        #function calling for connection
        if res == "ok":
            self.inventory[object_name] += 1
        return
    
    def set(self, object_name):
        res = ""

        #function calling for connection
        if res == "ok":
            self.inventory[object_name] -= 1
        return
    
    def incantation(self):
        res = ""

        #function calling for connection
        if res != "ko":
            self.level += 1
            self.update_inventory()
        return
