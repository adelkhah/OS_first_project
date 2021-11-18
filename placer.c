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
	char *MainToPlacer = "MainToPlacer";
	mkfifo(MainToPlacer, 0666);
	fd = open(MainToPlacer, O_RDONLY);
	read(fd, text, 1000);
	
	// read the words from placer
	char words[1000];
	char *FinderToPlacer = "FinderToPlacer";
	mkfifo(FinderToPlacer, 0666);
	fd = open(FinderToPlacer, O_RDONLY);
	read(fd, words, 1000);
	
	//printf("from placer i got text from main : %s\n", text);
	//printf("from placer i got words from finder : %s\n", words);
	//place the words
	char ans[2000];
	int n = 0;	
	int j = 0;
	for(int i = 0; text[i] != '\0'; i++){
		
		if(text[i] == '$'){
			while(words[j] != ' '){
				ans[n] = words[j];
				n++;
				j++;
			}
			j++;
		}
		else{
			ans[n] = text[i];
			n++;
		}
	}
	
	ans[n] = '\0';
	//printf("from placer ans : %s\n", ans);
	// send the result to MainProcessor
	char *PlacerToMain = "PlacerToMain";
	mkfifo(PlacerToMain, 0666);
	fd = open(PlacerToMain, O_WRONLY);
	write(fd, ans, n+1);
	close(fd);
	
	//write to file
	FILE *f = fopen("placer.txt", "w");
	fprintf(f, "%s", ans);

}
