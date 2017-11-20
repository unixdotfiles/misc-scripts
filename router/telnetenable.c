/*
 * GPL. Details here: https://github.com/insanid/NetgearTelnetEnable/blob/master/telnetenable.c
 */
#include <sys/types.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <openssl/md5.h>
#include "blowfish.h"

#define PORT 23

void usage(char * progname) __attribute__ ((noreturn));
unsigned int GetOutputLength(unsigned int lInputLong);
int EncodeString(BLOWFISH_CTX *ctx,char *pInput,char *pOutput, int lSize);

static char output_buf[0x100];

static BLOWFISH_CTX ctx;

struct PAYLOAD
{
	char signature[0x10];
	char mac[0x10];
	char username[0x10];
	char password[0x10];
	char reserved[0x40];
} payload;

void usage(char * progname)
{
	fprintf(stderr,
		"Usage: %s <host ip> <host mac> <user name> [password]\n",
		progname);
	exit(1);
}

int socket_connect(char *host, in_port_t port){
   struct hostent *hp;
   struct sockaddr_in addr;
   int on = 1, sock;

   if((hp = gethostbyname(host)) == NULL){
      herror("gethostbyname");
      exit(1);
   }
   bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
   addr.sin_port = htons(port);
   addr.sin_family = AF_INET;
   sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
   setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
   if(sock == -1){
      perror("setsockopt");
      exit(1);
   }
   if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
      perror("connect");
      exit(1);
   }
   return sock;
}

unsigned int GetOutputLength(unsigned int lInputLong)
{
	unsigned int lVal = lInputLong % 8;

	if (lVal!=0)
		return lInputLong+8-lVal;
	else
		return lInputLong;
}

int EncodeString(BLOWFISH_CTX *ctx,char *pInput,char *pOutput, int lSize)
{
	int lCount;
	unsigned int lOutSize;
	int i;

	lOutSize = GetOutputLength(lSize);
	lCount=0;
	while (lCount<lOutSize)
	{
		unsigned int xl=0;
		unsigned int xr=0;

		for (i=3; i>=0; i--) {
			xl = (xl << 8) | (*(pInput+i) & 0xff);
			xr = (xr << 8) | (*(pInput+i+4) & 0xff);
		}
		Blowfish_Encrypt(ctx, &xl, &xr);
		for (i=0; i<4; i++) {
			*(pOutput+i) = xl & 0xff;
			xl >>= 8;
			*(pOutput+i+4) = xr & 0xff;
			xr >>= 8;
		}
		pInput+=8;
		pOutput+=8;
		lCount+=8;
	}

	return lCount;
}

int fill_payload(int argc, char * input[])
{
	MD5_CTX MD;
	unsigned char MD5_key[0x10];
	char secret_key[0x100]="AMBIT_TELNET_ENABLE+";
	unsigned char u_secret_key[0x100]="AMBIT_TELNET_ENABLE+";
	int encoded_len;
	
	memset(&payload, 0, sizeof(payload));

	strncpy(payload.mac, input[2], 0x10);
	strncpy(payload.username, input[3], 0x10);

	if (argc==5)
		strncpy(payload.password, input[4], 0x10);

	MD5_Init(&MD);
	MD5_Update(&MD,payload.mac,0x70);
	MD5_Final(MD5_key,&MD);

	memcpy(payload.signature, MD5_key, 0x10);

	if (argc==5)
		strncat(secret_key,input[4], 0x10);

	Blowfish_Init(&ctx,u_secret_key,strlen(secret_key));

	encoded_len = EncodeString(&ctx, (char*)&payload,
		(char*)&output_buf, 0x80);
	
	return encoded_len;
}
	
int main(int argc, char * argv[])
{
	int datasize;
	int i;

	if ( argc!=4 && argc!=5 )
		usage(argv[0]);

	if ( strlen(argv[2]) != 12 ) {
		fprintf( stderr, "MAC address length must be %d\n", 12 );
		exit(1);
	}
	for( i=0; i<12; i++) {
		if ( !isxdigit(argv[2][i]) ) {
			fprintf( stderr,
				"Invalid characters in MAC address\n" );
			exit(1);
		}
	}
	if ( strlen(argv[3]) > 15 ) {
		fprintf( stderr, "Username too long\n" );
		exit(1);
	}
	if ( argc==5 && strlen(argv[4]) > 15 ) {
		fprintf( stderr, "Password too long\n" );
		exit(1);
	}

	datasize = fill_payload(argc, argv);

	if ( strcmp(argv[1], "-") == 0 ) {
		for (i=0; i<datasize; i++) {
			printf("%c", output_buf[i]);
		}
	} else {
		int sock = socket_connect(argv[1], PORT);
		write(sock, output_buf, datasize );
		close(sock);
	}

	return 0;
}
