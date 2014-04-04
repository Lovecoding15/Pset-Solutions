/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

#define BLANK 542

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int value = d*d-1;

    // Fill the values in the board in descending order
    for (int i = 0; i < d; i++)
    {    
        for (int j = 0; j < d; j++)
        {
            board[i][j] = value;
            value--;
        }   
    }
    
    //Assign the 0 tile to BLANK Space
    if (board[d-1][d-1] == 0)
        board[d-1][d-1] = BLANK;
    
    // If d is even, reverse the values of the tile 1 and 2.
    if (d % 2 == 0)
    {
        int temp        = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;   
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
   // create board with dimensions given by user
       
      
    // this sets up the rows
   for (int i = 0; i < d; i++)
    {
        // this fills the numbers in the rows
        for (int j = 0; j < d; j++)
        
            if (board[i][j] == BLANK && j != d-1)
                    printf("   _");
                    
            else if (board[i][j] == BLANK && j == d-1)
                printf("   _\n\n");
            
            else if (j == d-1)
            {
                printf("  %2d  \n\n", board[i][j]);
            }
            
            else
            {
                printf("  %2d", board[i][j]);
            }
            
    }
      
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
        // Move the title and blank      
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                if (board[i][j] == tile)
                {
                   
                    if (board[i][j-1] == BLANK)
                    {
                        int temp = tile;
                        board[i][j] = BLANK;
                        board[i][j-1] = temp;
                        return true;
                    }
                    
                    if (board[i][j+1] == BLANK)
                    {
                        int temp = tile;
                        board[i][j] = BLANK;
                        board[i][j+1] = temp;
                        return true;
                    }
                    if (board[i-1][j] == BLANK)
                    {
                        int temp = tile;
                        board[i][j] = BLANK;
                        board[i-1][j] = temp;
                        return true;
                    }
                    
                    if (board[i+1][j] == BLANK)
                    {
                        int temp = tile;
                        board[i][j] = BLANK;
                        board[i+1][j] = temp;
                        return true;
                    }
                    
                }   
                 
            }        
        
        }    
    
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // check if all values are in ascending order
    int old = 0;
    int k   = 0;
    
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                
                if (board[i][j] < old)
                {
                    return false;
                }
                else if (board[i][j] > old)
                {
                    k += 1;
                    if ( k == d * d)
                    {
                        return true;
                    }    
                }
 
                 old = board[i][j]; 
            }   
                         
        }        
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
