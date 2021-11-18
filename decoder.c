#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
	// read from fifo 
	char text[1000];
	int fd;
	char *MainToDecoder = "MainToDecoder";
	mkfifo(MainToDecoder, 0666);
	fd = open(MainToDecoder, O_RDONLY);
	read(fd, text, 1000);
	//printf("from decoder i got text : %s\n", text);
	// decode the text
	int i = 0;
	while(text[i] != '\0'){
		if(text[i] >= 'A' && text[i] <= 'Z'){
			if(text[i] == 'A'){
				text[i] = 'X';
			}			
			else if(text[i] == 'B'){
				text[i] = 'Y';
			}
			else if(text[i] == 'C'){
				text[i] = 'Z';
			}
			else{
				text[i] -= 3;
			}
			
		}
		if(text[i] >= 'a' && text[i] <= 'z'){
			if(text[i] == 'a'){
				text[i] = 'x';
			}			
			else if(text[i] == 'b'){
				text[i] = 'y';
			}
			else if(text[i] == 'c'){
				text[i] = 'z';
			}
			else{
				text[i] -= 3;
			}		
		}
		i++;
	}
	//printf("from dercoder decode : %s\n", text);

	// send to finder
	char *DecoderToFinder = "DecoderToFinder";
	mkfifo(DecoderToFinder, 0666);
	fd = open(DecoderToFinder, O_WRONLY);
	write(fd, text, i+1);
	close(fd);



	// write to file
	FILE *f = fopen("decoder.txt", "w");
	fprintf(f, "%s", text);
	
	
}
