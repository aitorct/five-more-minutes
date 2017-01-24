#include "main.h"

char website_list[100][50];


char* deleteNewline(char str[50]){
	int k;
	k = strlen(str)-1;
	if(str[k] == '\n') 
		str[k] = '\0';
	return str;
}


int getWebsites(){
	
	int i = 0;
	printf("Enter a website to block. Once you are done, just press Enter. \n");

	while(1){
		printf("Website #%d: ", i+1);
		char user_input[50];
		fgets(user_input, 40, stdin);
		if(strcmp(user_input, "\n")){
			strcpy(website_list[i], deleteNewline(user_input));
		}else{
			break;
		}
		i++;
	}

	return i;
}


int appendToFile(int max){

	int n = 0;
	FILE* fileW;

	fileW = fopen("/private/etc/hosts", "a");
	if(fileW != NULL){
		fputs("\n# Five more minutes - Block IPv4 and IPv6", fileW);
		for(n=0; n<max; n++){
			fputs("\nfe80::1%lo0	", fileW);
			fprintf(fileW, "%s", website_list[n]);
			fprintf(fileW, "\n127.0.0.1	%s", website_list[n]);
			fputs("\nfe80::1%lo0	", fileW);
			fprintf(fileW, "www.%s", website_list[n]);
			fprintf(fileW, "\n127.0.0.1	www.%s", website_list[n]);
		}
		fprintf(fileW, "\n");
		fflush(fileW);
		fclose(fileW);
	}

	return 0;
}


int main() {

	int nWebsites = getWebsites();
	appendToFile(nWebsites);
	printf("Requested websites have been blocked successfully!\n");

	return 0;
}