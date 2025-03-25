#include <stdio.h>
#include <unistd.h>

int player_1, player_2;
char A = '1', B = '2', C = '3', D = '4', E = '5', F = '6', G = '7', H = '8', I = '9';

void board()
{
    printf("\n!!         BOARD         !!\n");
    printf("%c |%c |%c \n", A, B, C);
    printf("__|__|__\n");
    printf("%c |%c |%c \n", D, E, F);
    printf("__|__|__\n");
    printf("%c |%c |%c \n", G, H, I);
    printf("  |  |  \n\n");
}

void player_1_move()
{
    scanf("%d", &player_1);
    // sleep(1);

    if (player_1 == player_2)
    {
        printf("please choose any no. available in board\n");
        board();
        player_1_move();
    }
    else if (player_1 == 1)
    {
        A = 'X';
    }
    else if (player_1 == 2)
    {
        B = 'X';
    }
    else if (player_1 == 3)
    {
        C = 'X';
    }
    else if (player_1 == 4)
    {
        D = 'X';
    }
    else if (player_1 == 5)
    {
        E = 'X';
    }
    else if (player_1 == 6)
    {
        F = 'X';
    }
    else if (player_1 == 7)
    {
        G = 'X';
    }
    else if (player_1 == 8)
    {
        H = 'X';
    }
    else if (player_1 == 9)
    {
        I = 'X';
    }
    else
    {
        printf("Choose a no. given in board\n");
        board();
        player_1_move();
    }
    // sleep(1);
}

void player_2_move()
{
    scanf("%d", &player_2);
    // sleep(1);

    if (player_2 == player_1)
    {
        printf("please choose any no. available in board\n");
        board();
        player_2_move();
    }
    else if (player_2 == 1)
    {
        A = 'O';
    }
    else if (player_2 == 2)
    {
        B = 'O';
    }
    else if (player_2 == 3)
    {
        C = 'O';
    }
    else if (player_2 == 4)
    {
        D = 'O';
    }
    else if (player_2 == 5)
    {
        E = 'O';
    }
    else if (player_2 == 6)
    {
        F = 'O';
    }
    else if (player_2 == 7)
    {
        G = 'O';
    }
    else if (player_2 == 8)
    {
        H = 'O';
    }
    else if (player_2 == 9)
    {
        I = 'O';
    }
    else
    {
        printf("Choose a no. given in board\n");
        board();
        player_2_move();
    }
    // sleep(1);
}

int win = 0;

void win_condition()
{

    if ((A == B) && (B == C))
    {
        if (A == 'X')
        {
            win = 1;
        }
        else
        {
            win = 2;
        }
    }
    else if ((D == E) && (E == F))
    {
        if (D == 'X')
        {
            win = 1;
        }
        else
        {
            win = 2;
        }
    }
    else if ((G == H) && (H == I))
    {
        if (G == 'X')
        {
            win = 1;
        }
        else
        {
            win = 2;
        }
    }
    else if ((A == D) && (D == G))
    {
        if (A == 'X')
        {
            win = 1;
        }
        else
        {
            win = 2;
        }
    }
    else if ((B == E) && (E == H))
    {
        if (B == 'X')
        {
            win = 1;
        }
        else
        {
            win = 2;
        }
    }
    else if ((C == F) && (F == I))
    {
        if (C == 'X')
        {
            win = 1;
        }
        else
        {
            win = 2;
        }
    }
    else if ((A == E) && (E == I))
    {
        if (A == 'X')
        {
            win = 1;
        }
        else
        {
            win = 2;
        }
    }
    else if ((C == E) && (E == G))
    {
        if (C == 'X')
        {
            win = 1;
        }
        else
        {
            win = 2;
        }
    }
}

// main->

int main()
{

    board();

    // sleep(2);
    printf("Choose any no. displayed above!   -> to mark X or O\n");

    // sleep(1);
    for (int i = 0; i < 5; i++)
    {

        printf("Player-1's move: ");
        player_1_move();
        win_condition();
        board();

        if (win == 1)
        {
            printf("PLAYER-1 WINS!\n");
            break;
        }

        if ((A != '1') && (B != '2') && (C != '3') && (D != '4') && (E != '5') && (F != '6') && (G != '7') && (H != '8') && (I != '9'))
        {
            printf("!!          TIE         !!\n");
            break;
        }

        printf("Player-2's move: ");
        player_2_move();
        win_condition();
        board();

        if (win == 2)
        {
            printf("PLAYER-2 WINS!\n");
            break;
        }
    }

    printf("\n!!       GAME ENDS       !!\n");

    return 0;
}