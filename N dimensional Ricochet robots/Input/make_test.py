from asyncore import read
import random

NUM_OF_EDGES = 1000000
GRAPH_SIZE = 1000000

def main():
    file = open("input.txt", "w")
    for i in range(NUM_OF_EDGES):
        a = random.randrange(0, GRAPH_SIZE)
        b = random.randrange(0, GRAPH_SIZE)
        file.write(str(a) +" " + str(b) + "\n")
        

if __name__ == "__main__":
    main()
