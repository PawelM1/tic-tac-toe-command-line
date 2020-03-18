#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

void set_text_color(char sign)
{
    if(sign == 'O')
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    else if(sign == 'X')
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void drawing(char *tab) //board drawing
{
    for(int i = 0; i < 9; i++)
    {
        set_text_color(*tab);
        std::cout << *tab;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        std::cout << (i % 3 == 2 ? "\n" : "---");
        tab++;
    }
    std::cout << std::endl << std::endl;
}

bool check(char *tab)
{
    //horizontal checking
    for (int i = 0; i < 9; i = i + 3)
        if (tab[i] == tab[i + 1] && tab[i + 1] == tab[i + 2] && (tab[i] == 'O' || tab[i] == 'X' ))
            return true;

    //vertical checking
    for (int i = 0; i < 3; i++)
        if (tab[i] == tab[i + 3] && tab[i + 3] == tab[i + 6] && (tab[i] == 'O' || tab[i] == 'X' ))
            return true;

    //checking diagonally
    if(tab[0] == tab[4] && tab[4] == tab[8] && (tab[4] == 'O' || tab[4] == 'X' ))
        return true;
    if(tab[2] == tab[4] && tab[4] == tab[6] && (tab[4] == 'O' || tab[4] == 'X' ))
        return true;

    return false;
}

void choice_number_player(int &choice, char *tab, std::string &player)
{
    std::cout << player << " Select a field number: ";
    bool check = false;
    while (!check)
    {
        std::cin >> choice;
        if ( tab[choice-1] == 'O' || tab[choice-1] == 'X' || choice <= 0 || choice >= 10 )
            std::cout << "Wrong selection, select field again: ";
        else
            check = true;
    }
    choice--;
}

void choice_number_computer(int &choice, char *tab)
{
    do
    {
        choice = rand() % 9;
    }
    while (tab[choice] == 'O' || tab[choice] == 'X');
    std::cout << "AI chose field: " << choice + 1 << std::endl;
}

void player_name(std::string &player1, std::string &player2, int number_of_players)
{
    std::cout << "Enter your name" << std::endl;
    std::cin >> player1;
    if (number_of_players == 2)
    {
        std::cout << "Enter the name of the second player" << std::endl;
        std::cin >> player2;
    }
    else
        player2 = "AI";
}

void who_will_start(std::string &player1, std::string &player2)
{
    std::cout << "Draw who will start the game. Amazing emotions !!!" << std::endl;
    srand(time(NULL));
    int tmp = rand() % 2;
    if(tmp==1)
    {
        std::string bufor = player1;
        player1 = player2;
        player2 = bufor;
    }
    std::cout << "So this exciting game will begin:" << player1 << " (Begins O)" << std::endl << std::endl;
}

void draw_O_or_X(int choice, char sign, char *tab)
{
    tab[choice] = sign;
    drawing(tab);
}

int main()
{
    std::cout << "Tic Tac Toe v2.4502197317" << std::endl;
    char game_mode;
    std::cout << "Select game mode:" << std::endl;
    std::cout << "Type 1 to play with a friend, 2 to play with a computer" << std::endl;
    std::cin >> game_mode;
    std::string player1, player2, winner;
    char game{ 'y' };
    while (game == 'y' || game == 'Y')
    {
        char game_board[9] { '1','2','3','4','5','6','7','8','9' };
        int number_of_moves = 1, choice;
        switch (game_mode)
        {
        case '1':
            player_name(player1, player2, 2);
            who_will_start(player1, player2);
            drawing(game_board);
            while (!check(game_board))
            {
                if (number_of_moves % 2 == 0) winner = player2;
                else winner = player1;
                choice_number_player(choice,game_board,winner);
                winner == player1 ? draw_O_or_X(choice, 'O',game_board) : draw_O_or_X(choice, 'X', game_board);
                check(game_board);
                number_of_moves++;
                if (number_of_moves == 10) break;
            }
            break;

        case '2':
            player_name(player1, player2, 1);
            who_will_start(player1, player2);
            drawing(game_board);
            while (!check(game_board))
            {
                if (number_of_moves % 2 == 0) winner = player2;
                else winner = player1;

                if (winner == "AI") choice_number_computer(choice, game_board);
                else choice_number_player(choice, game_board, winner);

                winner == player1 ? draw_O_or_X(choice, 'O',game_board) : draw_O_or_X(choice, 'X', game_board);
                check(game_board);
                number_of_moves++;
                if (number_of_moves == 10) break;
            }
            break;
        }

        if (number_of_moves == 10) std::cout << "Draw, no winner" << std::endl;
        else std::cout << "Congratulations:" << winner << " you won this round" << std::endl;

        std::cout << "Again? If yes, enter y" << std::endl;
        std::cin >> game;
    }

    std::cin.get();
    return 0;
}
