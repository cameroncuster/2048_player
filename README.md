# 2048 Player
An awesome player for the game 2048!

## Desc. of the Algorithm
The algorithm denoted as player in the repository is designed to maximize the
score of a 2048 game. The algorithm works by calculating the state of the game
after playing about 5 to 7 moves. The state of the game is calculated by the
computer simulating all four moves a player could make and then simulating the
placement of a tile on the game board at every possible position accounting for
the probability of a 2 or 4 being placed on the game board. The algorithm takes
the expected value or average of scores after the tiles have been placed and
returns the average of scores. The score is calculated by a heuristic function
because the actual game scoring weighs the merging of tiles to heavily and fails
to account for the actual arrangement of tiles on the game board. The heuristic
function used is a combination of the arrangement of tiles on the board along
with the location of the tiles on the board. The speedups of the function are
found in the storage of the board in a 64 bit integer, and the memoization of
individual recursive calls for the algorithm. The pruning at each recursive call
for a given board state has also been effective in reducing run time.

[Development of the Algorithm (CHANGELOG)](CHANGELOG.md)

## Action Shots
![Gif of 2048 player with high speed execution](Images/exec.gif)

## Improvements
The heurisitic could be better defined for the player to allow to greater
distances. I have considered that boards which are incredible deep in the
recursive tree are highly unlikely to be reached, perhaps this could be
utilized to optimize the algorithm, but thus far I have not done so.
