#include "request.h"

void handle_request(int client_socket, const char *opponent_name)
{
    print_all_sessions();
    char buffer[STRING_LENGTH];

    // Check opponent_name in session
    Session *session = find_session_by_username(opponent_name);

    if (session != NULL && session->socket_id != client_socket)
    {
        int opponent_socket = session->socket_id;
        send_with_error_handling(
            opponent_socket,
            buffer,
            "RECV_REQUEST Recv request",
            "Send message login status error");

        send_with_error_handling(
            client_socket,
            buffer,
            "REQUEST Wait for opponent accept",
            "Send message login status error");

        recv_with_error_handling(
            opponent_socket,
            buffer,
            sizeof(buffer),
            "Error receiving data from the client");

        if (strncmp(buffer, "REPLY_REQUEST", strlen("REPLY_REQUEST")) == 0)
        {
            const char *message = buffer + strlen("REPLY_REQUEST");
            int compare = strcmp(message, "yes");

            if (compare == 1)
            {
                // Handle yes
                send_with_error_handling(
                    opponent_socket,
                    buffer,
                    "RESULT_REQUEST Start game",
                    "Send message login status error");

                send_with_error_handling(
                    client_socket,
                    buffer,
                    "RESULT_REQUEST Start game",
                    "Send message login status error");
            }
            else
            {
                // Handle no
                send_with_error_handling(
                    client_socket,
                    buffer,
                    "RESULT_REQUEST Opponent reply no",
                    "Send message login status error");
            }
        }

        return;
    }

    // If existed, send request to opponent_name, send waiting to client_socket
    send_with_error_handling(
        client_socket,
        buffer,
        "FAILED_REQUEST Username invalid",
        "Send message login status error");
    return;
}