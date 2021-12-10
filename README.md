# Connect 4
This is the *Connect 4* game that I have developed as a first project for the subject *Advanced Programming*. There are seven different game modes and three levels of difficulty. I provide the code for the MiniMax algorithm, which the computer uses to create the tree of possible future moves and decide, using the cited algorithm, in which column it will make its move; the code for the heuristic function, that allows the computer to give a value for each possible board status while creating the MiniMax tree; the code for the seven different game modes and finally the code for all functions that concern printing the board.

All the code is based on a C struct, `struct node` which I later recall as `Node`, with four different members. These are `char tauler[NFILES][NCOLS]`, that simply consists on the game board for that given node; `struct node* *fills`, that is an array of pointers to the descendents of the current node; `int n_fills`, that is the value of descendents according to the number of non-full columns of the board; and `double valor`, which is the value given by the heuristic function according to the board status. 

The three levels of difficulty depend on the depth of the MiniMax tree, whose available depths are 2, 4 and 6. Hence I've given each difficulty level half of this values, i.e 1, 2 and 3, respectively. The MiniMax tree always starts with the board containing the last throw and creates a level where each node is a possible movement, i.e. if one column is full the tree will generate one node less as there is one throw that can't be done. As the computer is the only one that uses this algorithm to decide its throw, odd levels of the tree always correspond to possible computer throws while pair levels correspond to possible player throws. 

Next I provide a little explanation for each possible game mode. Except for the **two players** mode, the second player will be the computer and whoever starts will be drawn before the game starts, with a probability of 0.5 of starting each one.  

- **Two players**: Do you want to play with a friend so as to practice before facing the powerful machine? This is your chance to train. Challenge someone and win!
- **Normal**: This is the simplest, most basic mode. Just you and the machine. A face to face. Who will win?
- **Rotate the board!**: This mode introduces rotations into the board. You can choose doing them by yourself at the beginning of each turn or let them appear randomly at the beginning of your turn with a probability of 0.5. No matter which mode you take, you'll end up losing anyway.
- **Zero gravity**: Do you want to travel to the International Space Station to play Connect 4 but can't afford it? Be the first to experience zero gravity with this mode before anyone gets ahead of you! 
- **Timetrial**: Not satisfied with extreme difficulty? So try to win the machine with time limit! And if still that's not enough, you can add zero gravity!
- **Tetris**: When the last row of the board fills up, it disappears. It is not the tetris itself, but it does retain its essence.
- **Swap and win**: At random with a probability 0.5 you will be able to swap two columns and later do your throw. Maybe that's the only way you can win the computer...

Furthermore, the tiles will be printed in different colors to make the game easier, and when someone wins a new board will be printed with the winning combination well differentiated from the rest of the board.

All the information across the code is written in catalan, as it is the language I use in lessons at university. I'll try to improve this repository and its explanations if I have more spare time, but I think this is a nice beginning.
