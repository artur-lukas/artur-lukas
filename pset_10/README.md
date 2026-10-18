# Ultimate Tic-Tac-Toe

#### Video Demo: <https://youtu.be/A500EEcTodk>


## Project Description

For this project, I developed a game that is played entirely in the terminal.   
At first, I wanted to program the classic version of Tic-Tac-Toe.   
However, because this version seemed too simple to me and the gameplay was too monotonous, I expanded the idea and created Ultimate Tic-Tac-Toe. 

Ultimate Tic-Tac-Toe consists of nine individual Tic-Tac-Toe boards.   
These smaller boards are arranged in such a way that they form one large Tic-Tac-Toe board. 

```text
     A=?   |   B=?   |   C=?  
   1  2  3 | 1  2  3 | 1  2  3 
   4  5  6 | 4  5  6 | 4  5  6 
   7  8  9 | 7  8  9 | 7  8  9 
  ---------+---------+---------
     D=?   |   E=?   |   F=?   
   1  2  3 | 1  2  3 | 1  2  3 
   4  5  6 | 4  5  6 | 4  5  6 
   7  8  9 | 7  8  9 | 7  8  9 
  ---------+---------+--------- 
     G=?   |   H=?   |   I=?    
   1  2  3 | 1  2  3 | 1  2  3 
   4  5  6 | 4  5  6 | 4  5  6 
   7  8  9 | 7  8  9 | 7  8  9 
```

The smaller boards are called **sectors** in the program and are identified by the letters `A` to `I`.   
When a player wins a sector, that sector belongs to the player on the large board.   
The sector board can be represented in a simplified form like this: 

```text
 A | B | C
---+---+---
 D | E | F
---+---+---
 G | H | I
```

### Game Objective

The objective is to win the large sector board.   
Just like in classic Tic-Tac-Toe, a player wins when they have three of their symbols in a row, column, or diagonal. 

To claim a sector on the large board, a player must first win the small Tic-Tac-Toe game inside that sector.   
For example, if a player wins sector `E`, that sector is marked with their symbol, either `X` or `O`, on the large board. 

### Game Flow

At the beginning, one player chooses any available sector.   
Afterwards, a field from `1` to `9` is selected within that sector.   
The two players take turns playing: Player 1 uses the symbol `X`, while Player 2 uses the symbol `O`. 

The number of the last selected field determines the sector in which the next player must make their move.   
For example, if player `X` selects field `6` in the current sector, player `O` must make their next move in sector `F`.   
If player `O` then places their symbol in field `1`, player `X` must continue their turn in sector `A`. 

This creates an additional strategic level because players must not only try to win small sectors, but also consider which sector they send their opponent to. 

### Sector Status

Each sector can have one of four possible states: 

- `?` – The sector is still free and can be played in. 
- `X` – Player `X` has won this sector. 
- `O` – Player `O` has won this sector. 
- `V` – The sector is full without either player winning it. It ends in a draw and is blocked. 

At the beginning, all sectors are free and have the status `?`.   
As soon as a player places three of their symbols horizontally, vertically, or diagonally in a small board, that player wins the sector.   
If all nine fields of a sector are occupied and nobody has won, the sector receives the status `V`. 

If a player is sent to a sector that has already been won or is full, that player may choose another free sector instead. 

### Terminal Output

The program first prints the complete game board in the terminal.   
Afterwards, it also displays the sector in which the current player has to make their move.   
Free fields are represented by the numbers `1` to `9`.   
Occupied fields contain either an `X` or an `O`. 

For invalid input, for example a number outside the range from `1` to `9` or an already occupied field, the program displays an error message.   
The player can then enter another value. 

### End of the Game

The game ends as soon as a player has won three sectors in a row, column, or diagonal on the large sector board.   
That player wins the game. 

The game can also end in a draw if there are no free sectors left and no player has achieved a winning row on the large board. 

## Code

### Game Board

I use several arrays to store the game board. 

The variable `SektorenBuch` stores the names of the nine individual sectors from `A` to `I`. 

```cpp
char SektorenBuch[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
```

The array `Sektoren` stores the status of each sector. 

```cpp
char Sektoren[1][9] = {'?', '?', '?', '?', '?', '?', '?', '?', '?'};
```

The two-dimensional array `AlleFeld` stores the nine fields of all nine small Tic-Tac-Toe sectors.   
The first dimension represents the current sector, while the second dimension represents a field within that sector. 

```cpp
char AlleFeld[9][9];
```

At the beginning of the program, all fields are filled with the characters `1` to `9`.   
The outer `for` loop goes through the nine sectors, while the inner `for` loop initializes the nine fields of each sector. 

```cpp
int main() {
  for (int i = 0; i < 9; i++) {
    for (int a = 0; a < 9; a++) {
      AlleFeld[i][a] = a + '1';
    }
  }
}
```

### `priAll()` Function

The function `priAll()` prints the complete game board with all nine sectors in the terminal.   
It also displays the names and the current status of the sectors.   
For this purpose, it uses the arrays `SektorenBuch`, `Sektoren`, and `AlleFeld`. 

### `priSek()` Function

The function `priSek()` prints one selected sector as an individual game board.   
It also displays the name and the current status of that sector. 

### `Sekwahl()` Function

The function `Sekwahl()` asks the player to select a sector using a letter from `A` to `I`.   
If the input is invalid, it displays an error message and asks for input again.   
If the input is valid, the selected sector is returned. 

### Turn Sequence

The turn sequence for Player 1 and Player 2 is almost identical.   
First, the current player selects a field in the specified sector.   
Afterwards, the program checks whether the sector that was just played has ended.   
Then it checks whether the complete sector board has been won.   
If the game has not ended yet, the number of the selected field determines the sector for the next turn. 

```cpp
// Player 1
printf("\n\n|-Player 1 (X)-|\n");
Feld = feldwahl(player1, Sektor) - 1;
EndSektor(Sektor);
Ende = Endcheck(Sektoren, 0);
if (Ende != '?') break;
Sektor = Sekbestimmung(Feld);
```

### `feldwahl()` Function

The function `feldwahl()` receives two values: the symbol of the current player and the sector in which the player has to play.   
The first argument is, for example, `X` or `O`, while the second argument contains a sector such as `A` or `B`.   
The function calls `priAll()` and `priSek()` so that the complete board and the current sector are displayed.   
Afterwards, a number from `1` to `9` is requested.   
If the selected field is free, it is assigned the symbol of the current player and the field number is returned.   
Already occupied fields and numbers outside the range from `1` to `9` are rejected. 

### `EndSektor()` Function

The function `EndSektor()` receives a sector as input, for example `A`.   
It searches for the corresponding position of this sector in the `SektorenBuch` array.   
Then it calls the function `Endcheck()` for the corresponding small game board.   
The return value of `Endcheck()` is stored as the new status in the `Sektoren` array. 

### `Endcheck()` Function

The function `Endcheck()` checks whether a Tic-Tac-Toe board has ended.   
As input, it receives a game board, either `AlleFeld` for the small sectors or `Sektoren` for the large board.   
The second value determines which sector or which row of the array should be checked.   
The function checks all rows, columns, and diagonals for three equal symbols.   
It returns `X` or `O` if one of the players has won.   
If all fields are occupied and nobody has won, it returns `V`.   
If the board has not ended yet, it returns `?`. 

### `Sekbestimmung()` Function

The function `Sekbestimmung()` receives the number of the last selected field as input.   
This field number determines the sector for the next turn.   
For example, field `1` leads to sector `A`, field `2` leads to sector `B`, and field `9` leads to sector `I`.   
If the specified sector is still free, it is returned directly.
If the sector has already ended, `Sekwahl()` is called so that another sector can be selected.