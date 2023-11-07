#include <iostream>
#include <list>
#include <Windows.h>
#include <vector>
using namespace std;

bool hit;
int pHits;
int eHits;
int col;
int row;
bool sameGuess;
int spacesLeft;

int flipTimes;
int initialDirectionChoice;
int hitCol;
int hitRow;
int startCol;
int startRow;
string lastTurn;
bool lastHit;
bool playing;
bool firstHit = true;
int loopTimes = 0;

int difficulty;

string winner;

void PlayerTurn();
void EnemyTurn();
void Win(string winner);

struct Boats //a struct for every boat in the game
{
    string boatName = "";
    string boatCharacter = "";
    int boatSize = 0;
    int hitsLeft = 0;
    string direction = "v";
    int col = -1; //at -1 so when it is checks for overlaps it doesn't count these before it's delcared by the player
    int row = -1;
};

struct Guesses
{
    int col;
    int row;
};

vector<Boats> mainBoats;
vector<Boats> playerBoats;
vector<Boats> enemyBoats;
Boats boats;

string gridMain[10][10];
string gridPlayer[10][10];
string gridEnemy[10][10];

list<Guesses> enemyGuesses;
list<Guesses> playerGuesses;
Guesses guess;

void CreateGrid(Boats boats, string grid[10][10])
{
    const string gridTop[11] = { "   ","1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 ","10" };
    const string gridSide[10] = { "1  ","2  ","3  ","4  ","5  ","6  ","7  ","8  ","9  ","10 " };

    //prints the letters at the top of the grid
    for (int i = 0; i < 11; i++)
    {
        cout << gridTop[i];
    }
    cout << endl;

    //prints the nummbers at the side of the grid, then prints a # for the size of specified grid which is 10 x 10
    for (int i = 0; i < 10; i++)
    {
        cout << gridSide[i];
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j] == "")
            {
                cout << grid[i][j] << "# ";
            }
            else if (grid[i][j] == "X ")
            {
                cout << grid[i][j];
            }
            else if (grid[i][j] == "0 ")
            {
                cout << grid[i][j];
            }
            else  //if it is a ship - each ship is a different character
            {
                cout << grid[i][j];
            }
        }

        cout << endl;
    }
    cout << endl;
}

bool CheckPlacement(string turn, Boats boatCheck, vector<Boats> boatList, int col, int row) //detecting if the boat placement doesn't overlap other boats and fits on the grid
{
    if (turn == "player")
    {
        for (Boats boats : playerBoats)
        {
            if (boats.direction == "h")
            {
                for (int k = 0; k < boats.boatSize; k++)
                {
                    if (gridPlayer[col][row + k] == boats.boatCharacter)
                    {
                        return false;
                    }
                }
            }
            if (boats.direction == "v")
            {
                for (int k = 0; k < boats.boatSize; k++)
                {
                    if (gridPlayer[col + k][row] == boats.boatCharacter)
                    {
                        return false;
                    }
                }
            }
        }
        return true;

        if (boatCheck.direction == "h") //checking if boat fits in the grid
        {
            if ((boatCheck.row + boatCheck.boatSize) > 11)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        if (boatCheck.direction == "v")
        {
            if ((boatCheck.col + boatCheck.boatSize) > 11)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    if (turn == "enemy")
    {
        for (Boats boats : enemyBoats)
        {
            if (boats.direction == "h")
            {
                for (int k = 0; k < boats.boatSize; k++)
                {
                    if (gridEnemy[col][row + k] == boats.boatCharacter)
                    {
                        return false;
                    }
                }
            }
            if (boats.direction == "v")
            {
                for (int k = 0; k < boats.boatSize; k++)
                {
                    if (gridEnemy[col + k][row] == boats.boatCharacter)
                    {
                        return false;
                    }
                }
            }
        }
        return true;

        if (boatCheck.direction == "h") //checking if boat fits in the grid
        {
            if ((boatCheck.row + boatCheck.boatSize) > 11)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        if (boatCheck.direction == "v")
        {
            if ((boatCheck.col + boatCheck.boatSize) > 11)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}

void ShipChoice() //the player's choice of the ship position
{
    //setting all the boats in the list
    boats.boatName = "Carrier";
    boats.boatCharacter = "C ";
    boats.boatSize = 5;
    boats.hitsLeft = 5;
    mainBoats.push_back(boats);

    boats.boatName = "Battleship";
    boats.boatCharacter = "B ";
    boats.boatSize = 4;
    boats.hitsLeft = 4;
    mainBoats.push_back(boats);

    boats.boatName = "Cruiser";
    boats.boatCharacter = "R ";
    boats.boatSize = 3;
    boats.hitsLeft = 3;
    mainBoats.push_back(boats);

    boats.boatName = "Submarine";
    boats.boatCharacter = "S ";
    boats.boatSize = 3;
    boats.hitsLeft = 3;
    mainBoats.push_back(boats);

    boats.boatName = "Destroyer";
    boats.boatCharacter = "D ";
    boats.boatSize = 2;
    boats.hitsLeft = 2;
    mainBoats.push_back(boats);

    for (int i = 0; i < mainBoats.size(); i++) //for every boat in player boat it will set it's direction and placement in the grid
    {
        cout << "What direction would you like your size " << mainBoats.at(i).boatSize << " boat - the " << mainBoats.at(i).boatName << " - to be? (v for vertical and h for horizontal)" << endl;
        cout << "Vertical will be from top to bottom, Horizontal will be from left to right" << endl;
        cin >> mainBoats.at(i).direction;
        cout << "Please enter a row coordinate" << endl;
        cin >> mainBoats.at(i).row;
        cout << "Please enter a collumn coordinate" << endl;
        cin >> mainBoats.at(i).col;

        system("CLS"); //re-drawing the grid with the ships in place

        while (!CheckPlacement("player", boats, playerBoats, mainBoats.at(i).col, mainBoats.at(i).row))//loops until the boat can be placed
        {
            cout << "The boat cannot be placed here" << endl;
            cout << "Please enter a new row coordinate" << endl;
            cin >> mainBoats.at(i).row;
            cout << "Please enter a new collumn coordinate" << endl;
            cin >> mainBoats.at(i).col;
        }
        playerBoats.push_back(mainBoats[i]);

        for (int k = 0; k < mainBoats.at(i).boatSize; k++) //sets the grid positions to the boat
        {
            if (mainBoats.at(i).direction == "v")
            {
                gridPlayer[((mainBoats.at(i).col - 1) + k)][(mainBoats.at(i).row - 1)] = mainBoats.at(i).boatCharacter;
            }
            if (mainBoats.at(i).direction == "h")
            {
                gridPlayer[(mainBoats.at(i).col - 1)][((mainBoats.at(i).row - 1) + k)] = mainBoats.at(i).boatCharacter;
            }
        }
        CreateGrid(mainBoats[i], gridPlayer);
    }

}

void RandomiseShips() //randomising boats for the enemies placement
{
    srand(time(0));
    for (int i = 0; i < mainBoats.size(); i++)
    {
        int d = rand() % 2 + 1; //picks a random number for the direction of said ship out of 2
        if (d == 1)
        {
            mainBoats.at(i).direction = "h";
        }
        else if (d == 2)
        {
            mainBoats.at(i).direction = "v";
        }
        mainBoats.at(i).col = rand() % 10;
        mainBoats.at(i).row = rand() % 10; //picks random placement for boat

        system("CLS"); //re-drawing the grid with the ships in place

        while (!CheckPlacement("enemy", mainBoats[i], enemyBoats, mainBoats.at(i).col, mainBoats.at(i).row))//loops until the boat can be placed
        {
            mainBoats.at(i).col = rand() % 10;
            mainBoats.at(i).row = rand() % 10;
        }

        for (int k = 0; k < mainBoats.at(i).boatSize; k++) //sets the grid positions to the boat
        {
            if (mainBoats.at(i).direction == "v")
            {
                gridEnemy[((mainBoats.at(i).col - 1) + k)][(mainBoats.at(i).row - 1)] = mainBoats.at(i).boatCharacter;
            }
            if (mainBoats.at(i).direction == "h")
            {
                gridEnemy[(mainBoats.at(i).col - 1)][((mainBoats.at(i).row - 1) + k)] = mainBoats.at(i).boatCharacter;
            }
        }

        enemyBoats.push_back(mainBoats[i]);
    }
}
string boatType;

void CheckPos(string turn, int row, int col) //checking if it's a hit or miss
{

    hit = false;

    if (turn == "enemy") //if it's the enemy's turn
    {
        for (int i = 0; i < playerBoats.size(); i++) //for the length of the boat array (5)
        {
            for (int k = 0; k < playerBoats[i].boatSize; k++) //for the size of each boat
            {
                if (playerBoats[i].direction == "h") //if it's horizontal then it gets each coordinate for the boat
                {
                    if (!hit)
                    {
                        if (row != (playerBoats[i].row + k) && col != playerBoats[i].col)
                        {
                            gridPlayer[col - 1][row - 1] = "0 ";
                            lastTurn = "miss";
                        }
                        if (row == (playerBoats[i].row + k) && col == playerBoats[i].col) //if the place you guess lines up with their ship then it's a hit
                        {
                            hit = true;
                            spacesLeft = playerBoats[i].hitsLeft;
                            spacesLeft--;
                            playerBoats.at(i).hitsLeft = spacesLeft;
                            boatType = playerBoats[i].boatName;
                            gridPlayer[col - 1][row - 1] = "X ";
                            lastTurn = "hit";
                        }
                    }
                }
                if (playerBoats[i].direction == "v")
                {
                    if (!hit) //if not already a hit so it doesn't replace it with a miss
                    {
                        if (row != playerBoats[i].row && col != (playerBoats[i].col + k))
                        {
                            gridPlayer[col - 1][row - 1] = "0 ";
                            lastTurn = "miss";
                        }
                        if (row == playerBoats[i].row && col == (playerBoats[i].col + k))
                        {
                            hit = true;
                            spacesLeft = playerBoats[i].hitsLeft;
                            spacesLeft--;
                            playerBoats.at(i).hitsLeft = spacesLeft;
                            boatType = playerBoats[i].boatName;
                            gridPlayer[col - 1][row - 1] = "X ";
                            lastTurn = "hit";
                        }
                    }
                }
            }
        }
    }

    if (turn == "player")
    {
        for (int i = 0; i < enemyBoats.size(); i++)
        {
            for (int k = 0; k < enemyBoats[i].boatSize; k++)
            {
                if (enemyBoats[i].direction == "h")
                {
                    if (!hit)
                    {
                        if (row != (enemyBoats[i].row + k) && col != enemyBoats[i].col)
                        {
                            gridMain[col - 1][row - 1] = "0 ";
                        }
                        if (row == (enemyBoats[i].row + k) && col == enemyBoats[i].col) //if the place you guess lines up with their ship then it's a hit
                        {
                            hit = true;
                            spacesLeft = enemyBoats[i].hitsLeft;
                            spacesLeft--;
                            enemyBoats.at(i).hitsLeft = spacesLeft;
                            boatType = enemyBoats[i].boatName;
                            gridMain[col - 1][row - 1] = "X ";
                        }
                    }
                }
                if (enemyBoats[i].direction == "v")
                {
                    if (!hit) //if not already a hit so it doesn't replace it with a miss
                    {
                        if (row != enemyBoats[i].row && col != (enemyBoats[i].col + k))
                        {
                            gridMain[col - 1][row - 1] = "0 ";
                        }
                        if (row == enemyBoats[i].row && col == (enemyBoats[i].col + k))
                        {
                            hit = true;
                            spacesLeft = enemyBoats[i].hitsLeft;
                            spacesLeft--;
                            enemyBoats.at(i).hitsLeft = spacesLeft;
                            boatType = enemyBoats[i].boatName;
                            gridMain[col - 1][row - 1] = "X ";

                        }
                    }
                }
            }
        }
    }
    system("CLS");
    CreateGrid(boats, gridMain);
    CreateGrid(boats, gridPlayer);
    if (hit)
    {
        if (turn == "player")
        {
            pHits++;
            if (spacesLeft > 0) //if the ship is still there
            {
                cout << "Congrats, you got a hit on their ship and therefore get another go!" << endl;
            }
            if (spacesLeft <= 0)
            {
                cout << "You have managed to sink their " << boatType << ", congrats! You get another turn." << endl;
            }
            PlayerTurn();
            return;
        }
        else if (turn == "enemy")
        {
            eHits++;
            if (spacesLeft > 0)
            {
                cout << "They guessed " << row << "," << col << " and it looks like they got a hit on your ship and therefore get another go!" << endl;
                lastHit = true;
            }
            if (spacesLeft <= 0)
            {
                cout << "They have managed to sink your " << boatType << ", unlucky! They get another turn." << endl;
                firstHit = true;
                lastHit = false;
            }
            system("pause");
            EnemyTurn();

            return;
        }
    }
    if (!hit)
    {
        if (turn == "player")
        {
            cout << "Unlucky! You missed their ship, now it is the enemy's turn against you!" << endl;
            system("pause");
            return;

        }
        else if (turn == "enemy")
        {
            cout << "They guessed " << row << "," << col << " but looks like they missed your ship, it is now your turn again!" << endl;
            return;
        }
    }
}

bool SameEnemyGuess(int col, int row)
{
    for (Guesses guess : enemyGuesses)
    {
        if (col == guess.col && row == guess.row) //so the enemy can't guess the same place twice
        {
            return true;
        }
    }
    return false;
}
void EnemyTurn()
{
    bool turn = true;
    while (turn) {
        loopTimes++;
        if (eHits >= 17)
        {
            playing = false;
            winner = "enemy";

            return;
        }

        if (!lastHit || difficulty == 1)
        {
            srand(time(0));
            col = (rand() % 10) + 1;
            row = (rand() % 10) + 1;

            turn = SameEnemyGuess(col, row);
        }

        if (lastHit && difficulty == 3)
        {
            for (Boats boats : playerBoats) //for each boat
            {
                if (boats.boatName == boatType) //if it is the boat that was just hit
                {
                    if (boats.direction == "v") //if it is vertical
                    {
                        initialDirectionChoice = 0;
                    }
                    else if (boats.direction == "h") //if it is horizontal
                    {
                        initialDirectionChoice = 2;
                    }
                }
            }
            startCol = col; //so these are stored after the players go if its a miss
            startRow = row;
            hitCol = col;
            hitRow = row;
            firstHit = false; //so the direction isn't randomised
        }

        //initial direction choice
        if (lastHit && difficulty != 1) //if the ship isn't sunk and it was last a hit so the enemy hits in close range
        {
            if (firstHit)
            {
                startCol = col; //so these are stored after the players go if its a miss
                startRow = row;
                hitCol = col;
                hitRow = row;
                initialDirectionChoice = rand() % 4;
                firstHit = false;
            }


            if (initialDirectionChoice == 0) //moving down
            {
                turn = false;
                hitCol++;
                hitRow = startRow;
                turn = SameEnemyGuess(hitCol, hitRow);

                if (turn || hitCol > 10 || lastTurn == "miss") //if they've guessed there before, it's off the grid or it's a miss space
                {
                    if (loopTimes >= 4)
                    {
                        hitCol++;
                    }
                    if (flipTimes > 0)
                    {
                        initialDirectionChoice = 2;
                        flipTimes = 0;
                        hitRow = startRow;
                        hitCol = startCol;
                    }
                    else
                    {
                        hitRow = startRow;
                        hitCol = startCol;
                        flipTimes++;
                        initialDirectionChoice = 1;
                    }
                    lastTurn = "";
                }
            }
            if (initialDirectionChoice == 1) //moving up
            {
                turn = false;
                hitCol--;
                hitRow = startRow;
                turn = SameEnemyGuess(hitCol, hitRow);

                if (turn || hitCol < 1 || lastTurn == "miss") //if they've guessed there before, it's off the grid or it's a miss space
                {
                    if (loopTimes >= 4)
                    {
                        hitCol--;
                    }
                    if (flipTimes > 0)
                    {
                        initialDirectionChoice = 3;
                        flipTimes = 0;
                        hitRow = startRow;
                        hitCol = startCol;
                    }
                    else
                    {
                        hitRow = startRow;
                        hitCol = startCol;
                        flipTimes++;
                        initialDirectionChoice = 0;
                    }
                    lastTurn = "";
                }
            }
            if (initialDirectionChoice == 2) //moving right
            {
                turn = false;
                hitCol = startCol;
                hitRow++;
                turn = SameEnemyGuess(hitCol, hitRow);

                if (turn || hitRow > 10 || lastTurn == "miss") //if they've guessed there before, it's off the grid or it's a miss space
                {
                    if (loopTimes >= 4)
                    {
                        hitRow++;
                    }
                    if (flipTimes > 0)
                    {
                        hitRow = startRow;
                        hitCol = startCol;
                        initialDirectionChoice = 0;
                        flipTimes = 0;
                    }
                    else
                    {
                        hitRow = startRow;
                        hitCol = startCol;
                        flipTimes++;
                        initialDirectionChoice = 3;
                    }
                    lastTurn = "";
                }
            }
            if (initialDirectionChoice == 3) //moving left
            {
                turn = false;
                hitCol = startCol;
                hitRow--;
                turn = SameEnemyGuess(hitCol, hitRow);

                if (turn || hitRow < 1 || lastTurn == "miss") //if they've guessed there before, it's off the grid or it's a miss space
                {
                    if (loopTimes >= 4)
                    {
                        hitRow--;
                    }
                    if (flipTimes > 0)
                    {
                        hitRow = startRow;
                        hitCol = startCol;
                        initialDirectionChoice = 1;
                        flipTimes = 0;
                    }
                    else
                    {
                        hitRow = startRow;
                        hitCol = startCol;
                        flipTimes++;
                        initialDirectionChoice = 2;
                    }
                    lastTurn = "";
                }
            }
            col = hitCol;
            row = hitRow;
        }
        if (turn) {
            // Same guess - loop again
        }
        else {
            // New guess - exit loop and check if hit
            loopTimes = 0;
            guess.col = col;
            guess.row = row;
            enemyGuesses.emplace_front(guess);

            CheckPos("enemy", row, col);

            return;
        }
    }
}

void PlayerTurn()
{
    bool turn = true;

    while (turn) {

        if (pHits >= 17) //if you hit all of their ships
        {
            //Win("player");
            playing = false;
            winner = "player";

            return;
        }

        cout << "Please enter a row coordinate for your guess" << endl;
        cin >> row;
        cout << "Please enter a collumn coordinate for your guess" << endl;
        cin >> col;

        turn = false;
        for (Guesses guess : playerGuesses)
        {
            if (col == guess.col && row == guess.row) //so you can't guess the same place twice
            {
                turn = true;
                break;
            }
        }

        if (turn)
        {
            // Same guess - loop again
            cout << "Looks like you have already guessed here, please guess again!" << endl;
        }
        else
        {
            // Guess not the same - check position
            guess.col = col; //if it's not already been guessed then it adds these positions to the list
            guess.row = row;

            playerGuesses.emplace_front(guess);
            CheckPos("player", row, col);

            return;
        }
    }
}

void Win(string winner)
{
    if (winner == "enemy")
    {
        cout << "Unlucky! They managed to sink all of your ships, meaning you lost!";
    }
    if (winner == "player")
    {
        cout << "Congrats! You managed to sink all of their ships! good job :D";
    }
}

int main()
{
    char play;

    cout << "Welcome to battleships. Press c to start the game" << endl;
    cout << "Each ship on the board will be represented with a different letter" << endl;
    cout << "a '0' is a miss and a 'X' is a hit" << endl;
    cin >> play;
    if (play == 'c')
    {
        cout << "Please select a difficulty before playing." << endl;
        cout << "1 - easy, 2 - medium, 3 - hard" << endl;
        cin >> difficulty; //easy guesses random every time. medium guesses as a player would when it gets a hit. hard knows the direction of the ship straight away
        CreateGrid(boats, gridMain);
        ShipChoice();
        RandomiseShips();

        playing = true;

        while (playing) {
            PlayerTurn();
            EnemyTurn();
        }

        Win(winner);
    }

}
