#include "gameHandler.h"

Game *game_list = NULL;
int createNewGame(int client_send_challange_socket_turn_X,int client_receive_challange_socket_turn_O, int gameID)
{
    pthread_mutex_lock(&mutex);
    Game *new_game = (Game *)malloc(sizeof(Game));
    new_game->socket_id = client_send_challange_socket_turn_X;
    new_game->client_send_challange_socket_turn_X = client_send_challange_socket_turn_X;
    new_game->client_receive_challange_socket_turn_O = client_receive_challange_socket_turn_O;
    new_game->gameID = gameID;
    new_game->next = NULL;
    game_list = new_game;
    pthread_mutex_unlock(&mutex);
    
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    send_with_error_handling(
        client_send_challange_socket_turn_X,
        buffer,
        int_to_string(CREATE_GAME_SUCCESSFULLY),
        "Send message user turn error");
    send_with_error_handling(
        client_receive_challange_socket_turn_O,
        buffer,
        int_to_string(CREATE_GAME_SUCCESSFULLY),
        "Send message user turn error");
    return gameID;
}
int sendUserTurn(int client_socket, int userTurn)
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    sprintf(buffer, "%d", userTurn);
    send_with_error_handling(
        client_socket,
        buffer,
        int_to_string(userTurn),
        "Send message user turn error");
    return userTurn;
}   


int sendBoard(int client_socket, int board[BOARD][BOARD])
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    for (int i = 0; i < BOARD; i++)
    {
        for (int j = 0; j < BOARD; j++)
        {
            sprintf(buffer, "%d", board[i][j]);
            send_with_error_handling(
                client_socket,
                buffer,
                int_to_string(board[i][j]),
                "Send message board error");
        }
    }
    return 0;
}

int sendGameID(int client_socket, int gameID)
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    sprintf(buffer, "%d", gameID);
    send_with_error_handling(
        client_socket,
        buffer,
        int_to_string(gameID),
        "Send message gameID error");
    return gameID;
}


int sendChallange(int client_send_challange_socket, char *params)
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    sprintf(buffer, "%s", params);
    send_with_error_handling(
        client_send_challange_socket,
        buffer,
        params,
        "Send message challange error");
    return 0;
}

int updateMove(int client_send_challange_socket_turn_X,int client_receive_challange_socket_turn_O, char *params)
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    // sprintf(buffer, "%d", move);
    send_with_error_handling(
        client_send_challange_socket_turn_X,
        buffer,
        int_to_string(move),
        "Send message move error");
    send_with_error_handling(
        client_receive_challange_socket_turn_O,
        buffer,
        int_to_string(move),
        "Send message move error");

    return 0;
}



int sendResult(int client_socket, int result)
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    sprintf(buffer, "%d", result);
    send_with_error_handling(
        client_socket,
        buffer,
        int_to_string(result),
        "Send message result error");
    return result;
}

int sendWinner(int client_socket, int winner)
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    sprintf(buffer, "%d", winner);
    send_with_error_handling(
        client_socket,
        buffer,
        int_to_string(winner),
        "Send message winner error");
    return winner;
}


int sendLoser(int client_socket, int loser)
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    sprintf(buffer, "%d", loser);
    send_with_error_handling(
        client_socket,
        buffer,
        int_to_string(loser),
        "Send message loser error");
    return loser;
}


int sendDraw(int client_socket, int draw)
{
    char buffer[STRING_LENGTH];
    memset(buffer, 0, STRING_LENGTH);
    sprintf(buffer, "%d", draw);
    send_with_error_handling(
        client_socket,
        buffer,
        int_to_string(draw),
        "Send message draw error");
    return draw;
}

int checkWinner(int board[BOARD][BOARD])
{
    // printf("check winner\n");
    // clearInputBuffer(); // Clear the input buffer
    // getchar();
    // Check rows and columns for a win
    for (int i = 0; i < BOARD; i++)
    {

        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) || (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0))
        {
            printf("checked  winner\n");
            return board[i][i]; // Return the player symbol (1 or 2) who won
        }
    }

    // Check diagonals for a win
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) || (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0))
    {
        return board[1][1]; // Return the player symbol (1 or 2) who won
    }

    return 0; // Return 0 if there is no winner yet
}
int checkOver(int board[BOARD][BOARD])
{
    for (int i = 0; i < BOARD; i++)
    {
        for (int j = 0; j < BOARD; j++)
        {
            if (board[i][j] == 0)
            {
                return 0; // If any cell is empty, the game is not over
            }
        }
    }
    return DRAW; // If no cell is empty, the game is over, set to draw 
}