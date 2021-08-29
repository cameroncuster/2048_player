# Dev. Timeline

Attempted to optimize the algorithm by accounting for the similarity of
values across the board, and found that this must be done using the
exponential powers of 2 of the values ( e.a. log2 the board values )
otherwise the operation is too slow.

The exponent values stored as a hash table to be accessed in average constant time
as opposed to calculated. This was faster.

Attempted to alter the weights of the board for efficiency and scoring
techniques ( heuristics ). According to the scores our original weights
were relatively optimal.

Calculated the probability of a given board state and return if a board
state is highly unlikely ( < 2% ). This is an exponential prune which
should reduce the number of states exponentially.

Passed the board by reference everywhere to reduce operations for speed.

Attempted to optimize the heuristic by over calculating which resulted in
poor execution time and minimal results.

Returned the negative score if the game is over, which improved score by
averages of over 10,000.

Stored the board as a 64 bit unsigned long long integer as opposed to a
2d array. This improved operation time exponentially and allow for a
recursive depth increase of 1 and approximately a 20% increase in score.

The implementation of the class is done utilizing bitwise operators to
interact with the integer board.  Idea was from nneoneo.
Precalculated the values for every move up, down, left, right for any row
or column and stored in a transposition table for constant time moves from
the lookup table. This was successful, but only allowed for the depth
increase of 1 in conjunction with the integer board storage.

Precalculated the values for the score of every board utilizing the weight
heuristic and also stored in a lookup table to improve operation time and
allow for increase in depth. This was successful and allowed for depth to
be increased again to 7 which resulted in average score of approx. 100,000.

The depth pruning based on probability of a given board state was
re-introduced, but did not improve score only execution time.

The best improvement was memoizing the board states and storing the scores.
This allows for a depth of 9 to 12 depending on the amount of probability
pruning and is very effective. At first the memoization was done as a hash
table of values for any board state at any depth. This did not account for
the likelihood of a given board state and due to imperfections in the board
scoring heuristic this resulted in poor performance. The memoization was
