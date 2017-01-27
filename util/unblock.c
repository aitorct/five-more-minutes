#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){

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