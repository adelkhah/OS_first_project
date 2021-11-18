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
	char *MainToFinder = "MainToFinder";
	mkfifo(MainToFinder, 0666);
	fd = open(MainToFinder, O_RDONLY);
	read(fd, text, 1000);
		
	//read decoded text from decoder
	char decode[1000];
	char *DecoderToFinder = "DecoderToFinder";
	mkfifo(DecoderToFinder, 0666);
	fd = open(DecoderToFinder, O_RDONLY);
	read(fd, decode, 1000);
	

	//printf("from finder i got text from Main : %s\n", text);
	//printf("from finer i got decode from decoder : %s\n", decode);
	// find words
	char words[1000];
	int wi = 0;
	int i = 0;
	int l = 0;
	int r = 0;
	int index = 0;
	int len = 0;
	
	while(text[i] != '\0'){
		l = i;
		index = 0;
		len = 0;
		while(text[i] != ' '){
			i++;
		}
		r = i;
		i++;
		for(int j = l; j < r; j++){
			index *= 10;
			index += (text[j] - '0');
		}	
		l = i;		
		while(text[i] != '$'){
			i++;
		}
		r = i;
		i++;
		for(int j = l; j < r; j++){
			len *= 10;
			len += (text[j] - '0');
		}	
		
		for(int j = index; j < index + len; j++){
			
			words[wi] = decode[j];
			wi++;
		}
		words[wi] = ' ';
		wi++;
	}
	words[wi] = '\0';
	//printf("from finder words : %s\n", words);
	//send words to placer 
	char *FinderToPlacer = "FinderToPlacer";
	mkfifo(FinderToPlacer, 0666);
	fd = open(FinderToPlacer, O_WRONLY);
	write(fd, words, wi+1);
	close(fd);

	// write to file
	FILE *f = fopen("finder.txt", "w");
	fprintf(f, "%s", words);
	
}
