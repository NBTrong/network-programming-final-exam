# Network Programing final project HUST 
0. Description:
- IT-E6 subject
- Project is about launching caro 3x3 game, with client-server socket based design, multi thread.

1. Documentations:
- Requirements: [here](https://husteduvn.sharepoint.com/:x:/s/IT4062-NetworkProgramming/EaiVQboox9FNhOQ03aUX9tEBeZgx6ZjDvyIdA3nAaKsALA?e=tctWmG "Excel")
- Protocol design: [here](https://docs.google.com/spreadsheets/d/1g8We2uJ0GnHIN76XDzrEh2YiaAjk6aptdtH3NwFhAoU/edit#gid=0 "Google sheet")
- Assign tasks: [here](https://noiseless-gallon-558.notion.site/Network-programming-final-project-7859cc8c16064d298025c26100008075 "Notion")
2. Test screen.c to see screens for client

```bash
gcc screen.c -o screen
./screen
```
3. To launch project
```bash
make clean
make
./TCP_server/server 5500
./TCP_client/client 127.0.0.1 5500
```