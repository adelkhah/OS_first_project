#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


int main()
{	
	// open input.txt
	FILE *f = fopen("input.txt", "r");
	if(f == NULL){
		printf("no such a file");
		return 0;
	}
	char decoder_text[1000];
	char finder_text[1000];
	char placer_text[1000];
	int di = 0;
	int fi = 0;
	int pi = 0;
	char c;
	// read the first text for decoder
	while((c = getc(f)) != '#'){
		if(c != '\n' && c != ' '){
			decoder_text[di] = c;
			di++;		
		}
	}
	//skip the ###
	getc(f);
	getc(f);
	getc(f);
	//read the second text for finder	
	while((c = getc(f)) != '#'){
		if(c != '\n'){
			finder_text[fi] = c;
			fi++;		
		}
	}
	//skip the ###
	getc(f);
	getc(f);
	getc(f);
	//read the third text for placer
	while((c = getc(f)) != EOF){
		placer_text[pi] = c;
		pi++;		
		
	}
	// put null at the end of the strings
	decoder_text[di] = '\0';
	finder_text[fi] = '\0';
	placer_text[pi] = '\0';
	

	//create process for decoder , finder , placer	
	if(fork() == 0){
		char *args[] = {"./decoder", NULL};
		execvp(args[0], args);
	}
	if(fork() == 0){
		char *args[] = {"./finder", NULL};
		execvp(args[0], args);
	}
	if(fork() == 0){
		char *args[] = {"./placer", NULL};
		execvp(args[0], args);
	}


	// send the first text to decoder
	int fd;
	char *MainToDecoder = "MainToDecoder";
	mkfifo(MainToDecoder, 0666);
	fd = open(MainToDecoder, O_WRONLY);
	write(fd, decoder_text, di+1);
	close(fd);

	// send the second text to finder
	char *MainToFinder = "MainToFinder";
	mkfifo(MainToFinder, 0666);
	fd = open(MainToFinder, O_WRONLY);
	write(fd, finder_text, fi+1);
	close(fd);

	// send the third text to placer
	char *MainToPlacer = "MainToPlacer";
	mkfifo(MainToPlacer, 0666);
	fd = open(MainToPlacer, O_WRONLY);
	write(fd, placer_text, pi+1);
	close(fd);


	
	// get the result from placer
	char res[2000];
	char *PlacerToMain = "PlacerToMain";
	mkfifo(PlacerToMain, 0666);
	fd = open(PlacerToMain, O_RDONLY);
	read(fd, res, 2000);
	

	printf("result text : %s\n", res);
	

	


	
	
	
	
}
