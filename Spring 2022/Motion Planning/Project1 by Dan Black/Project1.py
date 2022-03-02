import sys
import json
from abc import ABC, abstractmethod


# abstract class to contain build queue classes from
class Queue(ABC):
    def __init__(self):
        self.queue = []
        self.visited = []
        self.parents = {}

    # pops first element of queue
    def pop(self):
        return self.queue.pop(0)

    # abstract insert to ensure all queue classes have the method
    @abstractmethod
    def insert(self, x, parent):
        pass

    @abstractmethod
    def outputString(self):
        pass

    # returns the length of the queue
    def length(self):
        return len(self.queue)

    # returns the path taken given the achieved goal state
    def listPath(self, x):
        path = [x]
        parent = self.parents[tuple(x)]
        while parent != "null":
            path.insert(0, parent)
            parent = self.parents[tuple(parent)]
        return path

    # returns the list of visited nodes
    def listVisited(self):
        return self.visited

# Queue to support BFS by implementing a FIFO append on insert
class QueueBFS(Queue):

    def insert(self, x, parent):
        if x not in self.visited:
            self.visited.append(x)
            self.queue.append(x)
            self.parents[tuple(x)] = parent

    # output string for bfs alg
    def outputString(self):
        return "project1_bfs.json"


# Queue to support DFS by implementing a LIFO append on insert
class QueueDFS(Queue):

    def insert(self, x, parent):
        if x not in self.visited:
            self.visited.append(x)
            self.queue.insert(0, x)
            self.parents[tuple(x)] = parent

    # output string for dfs alg
    def outputString(self):
        return "project1_dfs.json"

# Queue to support DFS by implementing a LIFO append on insert
class QueueAstar(Queue):
    # adds variables relevent to Astar alg handling
    def __init__(self, XG):
        super().__init__()
        self.goals = XG
        self.CostToCome = {}
        self.CostToGo = {}

    # Calculates cost to go value for x based on the minimum value from XG
    def costtogoInt(self, x):
        cost = 999999999
        for i in self.goals:
            costI = abs(x[0] - i[0]) + abs(x[1] - i[1])
            if costI < cost:
                cost = costI
        return cost

    # compares cost through list to determine where to insert node
    def compareInsert(self, x):
        count = 0
        for i in self.queue:
            if (self.CostToGo[tuple(x)] + self.CostToCome[tuple(x)]) < (
                    self.CostToGo[tuple(i)] + self.CostToCome[tuple(i)]):
                self.queue.insert(count, x)
                return
            count += 1
        self.queue.append(x)

    # Will insert x into queue as needed inline with Astar alg
    def insert(self, x, parent):
        if parent == "null" and x not in self.visited:
            # adds x into visited list
            self.visited.append(x)
            # appends x to the front of list
            self.queue.insert(0, x)
            # stores parent of x in dictionary
            self.parents[tuple(x)] = parent
            # stores CTC of x in dictionary
            self.CostToCome[tuple(x)] = 0
            # stores CTG of x in dictionary
            self.CostToGo[tuple(x)] = self.costtogoInt(x)
        elif x not in self.visited:
            # adds x into visited list
            self.visited.append(x)
            # stores parent of x in dictionary
            self.parents[tuple(x)] = parent
            # stores CTC of x in dictionary
            self.CostToCome[tuple(x)] = 1 + self.CostToCome[tuple(parent)]
            # stores CTG of x in dictionary
            self.CostToGo[tuple(x)] = self.costtogoInt(x)
            # calls compareInsert method to insert x based on estimated cost to goal
            self.compareInsert(x)
        elif x in self.visited:
            if (1 + self.CostToCome[tuple(parent)]) < self.CostToCome[tuple(x)]:
                # updates parent of x
                self.parents[tuple(x)] = parent
                # updates CTC of x
                self.CostToCome[tuple(x)] = 1 + self.CostToCome[tuple(parent)]
                # removes x from queue to update position later
                self.queue.remove(x)
                # puts x in queue with updates estimated cost
                self.compareInsert(x)

    # output string for astar alg
    def outputString(self):
        return "project1_astar.json"

# Forward search algorithm where G is the graph to be searched, U is the list of possible actions, xI is the starting
# position in the graph, XG is a list of possible goal points in the graph, and Q is the queue the graph will use to
# determine what the next point being searched is.
def fsearch(G, U, xI, XG, Q):
    # puts initial state in queue
    Q.insert(xI, "null")
    # runs while queue is not empty
    while Q.length() > 0:
        # pops first element in queue
        x = Q.pop()
        # checks if x is a goal state. if it is search is done and json file is filled with data
        if x in XG:

            print("search complete. Check for project1_'alg'.json where 'alg' is the algorithm chosen")
            output = {
                "visited": Q.listVisited(),
                "path": Q.listPath(x)
            }
            # creates json output
            with open(Q.outputString(), 'w') as outfile:
                json.dump(output, outfile)
            return
        # if x is not a goal state then all actions are checked if they are in G and then inserted into queue for handling
        for i in U:
            xprime = [x[0] + i[0], x[1] + i[1]]
            if (-1 < xprime[0] < len(G[0])) and (-1 < xprime[1] < len(G)) and (G[xprime[1]][xprime[0]] == 0):
                Q.insert(xprime, x)
    # if this is printed in cmd then the search is over without finding a goal state
    print("Failure")
    return


# Get input arguments at CMD (argv[1] hold location of description file in json file format| argv[2] holds a string
# determining what search queue to use)
inputFile = sys.argv[1]
search = sys.argv[2]

# opens file to be read
f = open(inputFile)
# grabs description from the file
data = json.load(f)
# closes the file to be read
f.close()
# assigns json file values to variables to be used in search
G = data['G']
xI = data['xI']
XG = data['XG']

# checks if xI is in G
if not ((-1 < xI[0] < len(G[0])) and (-1 < xI[1] < len(G)) and (G[xI[1]][xI[0]] == 0)) :
    print("initial state is not in G. Search terminated")
    quit()

# statically defined up, down, left, right
U = [[0, 1], [0, -1], [-1, 0], [1, 0]]

# Builds the Queue for the forward search based on the sys.argv[2].
# If argument isn't DFS, BFS, or Astar it prints a message.
if search == "DFS":
    Q = QueueDFS()
elif search == "BFS":
    Q = QueueBFS()
elif search == "Astar":
    Q = QueueAstar(XG)
else:
    print(
        "Second parameter does not meet specifications. Please type DFS, BFS, or Astar to select the search algorithm")
    quit()

fsearch(G, U, xI, XG, Q)
