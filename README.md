# Battleship_Game_Project
### Game Description :
	Battle ship is a strategy type coordinate guessing game. It is played on grid where both the players have their ships placed. The location of the ships are hidden to other player and both player have a chance to fire any guessed location turn by turn until the game is over. This game includes 5 Battle ships named as Aircraft (length 5), Battleship (length  4), Submarine (length 3) , Destroyer (length 3) and a patrol boat (length 2). For this term project we are using a 10 X 10 grid layout to place ships. The player who sunk all the battleship of the opponent will be a winner of the game.

### How to play game  : 
	1.  Players need to place their ships manually using the code function named setships(). This function is responsible for setting up all the ships locations using struct functionality.  
	2. Once the ships are set, the game will be load into the STM 32 nucleo63-f103rb board.
	3. Both the player will have their own game unit and they will mutually decide who will go first.
	4. Let's call Player 1 have game unit 1 and player 2 have game unit 2.
	5. 
		situation  1 :   Player 1 : attacker and player 2 : Victim
				   The Attacker  will give a value of row and column to the Victim. For instance, Row 5, and Column 6.
				   Victim will insert the binary value for row 5 and column 6 respectively using the 4 dip switches and press blue button from STM 32 nuclei board. 
				   The Victim\'92s game unit process the code and turnOn any of the four LEDs to indicate the result of the attack. 
				   Possible scenarios : 
			 		1. The attacker gave the wrong input out of the bound of 10 X 10 grid. (Error message indicating LEDs)
					2. The attack was a \'93miss\'94 event. (Miss event indicating LED)
					3. The attack was a \'93 Hit \'94 event. (Hit event indicating LED)
					4. The attack was a \'93Hit and Sunk\'94 event. (Hit and Sunk event indicating LED)
					5. Both the player noticed the guessed location into their bottom grid (using paper and pencil).
						==> If the event is either Hit or Hit and sunk event then the above situation repeats which means the attacker will have one more chance to play and guess the location.
		
		Situation 2 : Player 2 : attacker and Player 1: Victim
					The above Situation 1 repeats with the roles and game units are changed. 
		Situation3  : Same as Situation 1. 

