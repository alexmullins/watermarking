
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef unsigned int uint32;
typedef char* caddr_t;
typedef uint32* waddr_t;

uint32 the_player_key = 0xbabeca75;   
FILE* audio;

int activation_code = 42;                            
uint32 play(uint32 user_key, uint32 encrypted_media[], int media_len) {
   int code;
   printf("Please enter activation code: ");
   scanf("%i",&code);                       
   if (code!=activation_code) {
      fprintf(stderr,"%s\n","wrong code");
      *((int*)NULL)=99;
   }

   int i;
   for(i=0;i<media_len;i++) {
      uint32 key = user_key ^ the_player_key;
      uint32 decrypted = key ^ encrypted_media[i];
      float decoded = (float)decrypted;
      fprintf(audio,"%f\n",decoded); fflush(audio);
   }
}

uint32 player_main (uint32 argc, char *argv[]) {
   uint32 user_key = atoi(argv[1]);
   int i;
   uint32 encrypted_media[100];

   for(i=2; i<argc; i++)
      encrypted_media[i-2] = atoi(argv[i]);
   int media_len = argc-2;

   play(user_key,encrypted_media,media_len);   
}

int main (uint32 argc, char *argv[]) {
   audio = fopen("audio", "w");
   player_main(argc,argv);
   return 0;
}




