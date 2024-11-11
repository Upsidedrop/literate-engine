# Travelling Salesman Problem (Genetic Algorithm)

This is a fun venture I decided to pursue that attempts to solve the travelling salesman problem.

In case you are unfamiliar, the travelling salesman problem is trying to find the optimal path between several destinations.
Computing all of the possibilities through brute force runs in factorial time, and is therefore completely off the table for large amounts of locations.
There are other approaches that are able to reduce this time significantly and still get the optimal solution, however the solution I settled on is more familiar to me.
What I finally decided on was to use a genetic algorithm (not AI!!) to find a decent solution in minimal time.

## Genetic algorithms
Genetic algorithms don't always give the best response, they're just meant to be a whole lot better than humans.
The general process of a genetic algorithm is demonstrated with the following steps: Mutate, Evaluate, Reproduce, Repeat.

### Mutate
Mutations are all about introducing randomness into the selection to break out of local minimums.

A mutation is where a random genome is selected and one (or more) of its genes are altered.
This alteration could vary anywhere from a small change that will be filtered out immediately, to a massive mutation that completely reprograms the population.

### Evaluate
Some would argue that the most important part of any genetic algorithm is natural selection.
However, as we don't have any predators, we need to create our own.

Genomes are evaluated based on either a cost function or a fitness function. The only difference is that one congratulates the genome whereas the other punishes it.
Genomes are then sorted on how well they did, and the top 50% get to reproduce.
Choosing a good cost/fitness function is very important in any genetic algorithm, as it's one of the programmer's only inputs for the algorithm's development.

### Reproduce
Reproduction is the process of combining two genomes to (hopefully) get an even better one to come out.
Reproduction (more frequently referred to as crossover) can be and usually is implemented in many different ways depending on your needs.

#### Average
One common method of combining genomes is by averaging their genes together to get a truly perfect mix between them.
I don't think this needs much explaining, just add the values together and divide by two.

Ex:

| Genome A   |Genome B    |Result      |
|------------|------------|------------|
|      3     |       9    |      7.5   |
|        6   |       4    |        5   |
|     4      |       2    |      3     |
|      8     |       1    |      4.5   |
|        1   |      5     |      3     |

#### Random Selection
Another method, (the one I used in this project) is to take samples from either Genome A or Genome B and return an amalgamation of the two.
This helps maintain the actual original values so that the result remains true to both the father and the mother.

Ex:

| Genome A   |Genome B    |Result      |
|------------|------------|------------|
|      3     |       9    |      9     |
|        6   |       4    |        6   |
|     4      |       2    |      4     |
|      8     |       1    |      1     |
|        1   |      5     |      5     |

## My Implementation

### Genome Structure
The first big problem came before I even started coding, I needed a way to structure the genome.
In my eyes, the requirements for a genome are the following:
- The genes need to have continuous values, so that mutations are natural
- Every possible combination needs to be reachable
- Each output should have an approximately equal likelihood of occurring

I settled on a matrix of sorts that has all inputs on the left side and all matching outputs on the right.
The values in the matrix determine how likely it is for a line to be travelled across, and every connection has a value.
Here's an example:
```
[0,  1,  2,  3,  4]
[0,  0,  5,  6,  7]
[0,  8,  0,  9, 10] 
[0, 11, 12,  0, 13]
[0, 14, 15, 16,  0]
```
After just one look, you can see a glaringly obvious pattern.
The zeros lining the left side are so that the genome doesn't go back to the start until it has visited all other nodes.
The one on a diagonal through the center are to prevent an instance from going to the spot where it is currently standing.

### Evaluation
In this project I decided to use a cost function to score the genomes.
To define this function, I had to make yet another matrix, but of half the size.
The matrix consists of the distances between each destination, but since the distance to and from somewhere are the same, we don't need nearly as many values.
Ex:
```
[1, 2, 3, 4, 0]
[5, 6, 7, 0]
[8, 9, 0]
[10,0]
[0]
```
The placement of the zeros here still hold a pattern, but it makes a whole lot less sense.
The reason, is because I've actually withheld some information from you.

Along the vertical axis, it still corresponds to destinations 1, 2, 3, 4, and 5 respectively.

However, along the x axis, the order is flipped.

(0,0) represents the connection between destination 1 and 5, (0,1) -> 1 and 4, (2,0) -> 3 and 5.

This added complexity is for the sole purpose of giving the matrix its triangular shape, and thus saving space.

I then find the average cost and only allow genomes with a cost higher or equal to the average to proceed.
