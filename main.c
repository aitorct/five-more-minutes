#include "main.h"

char website_list[100][50];


char* deleteNewline(char str[50]){

	int k;
	k = strlen(str)-1;
	if(str[k] == '\n') 
		str[k] = '\0';
	return str;
}


int createBackup(){

    system("sudo cp /private/etc/hosts /private/etc/hosts_backup");

    return 0;
}


int revertOriginal(){

	if (access("/private/etc/hosts_backup", 0) == 0) { 
    	system("sudo rm /private/etc/hosts");
    	system("mv /private/etc/hosts_backup /private/etc/hosts");
    	printf("Websites unblocked. Original hosts file restored.\n");
	} 
	else { 
	    printf("ERROR: Original backup hosts file not found. It's not possible to 'unblock' websites. Consider doing it manually.  \n");
	}

	return 0;
}


int getWebsites(){
	
	int i = 0;
	printf("Enter a website to block. Once you are done, just press Enter.\n");

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


int getTime(){

	int time = 0;
	printf("How long do you want to block? (time in minutes, 0 for permanent block): ");
	scanf("%d", &time);
	return time;
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
	int time = getTime();
	createBackup();
	appendToFile(nWebsites);
	printf("Requested websites have been blocked successfully!\n");

	if(time){
		printf("Blocking for %d minutes. Countdown started.\n", time);
		sleep(time*60);
		printf("Time has expired. Unblocking websites...\n");
		revertOriginal();
	}else{
		printf("A copy of the original hosts file has been saved as hosts_backup.\n");
	}

	return 0;
}