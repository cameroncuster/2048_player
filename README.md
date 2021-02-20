2048 – Player (Brayden and Cameron)
	The algorithm denoted as player in the repository is designed to maximize the score of a 2048 game. The algorithm works by calculating the state of the game after playing about 5 to 7 moves. The state of the game is calculated by the computer simulating all four moves a player could make and then simulating the placement of a tile on the game board at every possible position accounting for the probability of a 2 or 4 being placed on the game board. The algorithm takes the expected value or average of scores after the tiles have been placed and returns the average of scores. The score is calculated by a heuristic function because the actual game scoring weighs the merging of tiles to heavily and fails to account for the actual arrangement of tiles on the game board. The heuristic function used is a combination of the arrangement of tiles on the board along with the location of the tiles on the board. The speedups of the function are found in the storage of the board in a 64 bit integer, and the memoization of individual recursive calls for the algorithm. The pruning at each recursive call for a given board state has also been effective in reducing run time.

	Change Log
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
	changed to store board states at every recursive call exclusively and this
	was much more effective at both reducing run time and improving the overall
	score by allowing for an increase in recursive depth.

	Other memoization approaches were attempted such as storing the scores by
	depth of the recursive tree and agent at a given recursive call, but
	neither were more successful than just memoizing each recursive call individually.

	The heuristic needs to be tuned and the overall player has the potential for
	much better performance, but in the interest of time this is as optimized as
	the player will be for the purposes of this course.
