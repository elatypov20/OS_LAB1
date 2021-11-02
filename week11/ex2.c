#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define dirname "/"

int main(int argc, char *argv[]){
	chroot(dirname);

	DIR *dir = opendir(dirname);

	if (dir == NULL){
		printf("Error opening /\n");
		return 1;
	}

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL){
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			continue;
		printf("%s\n", entry->d_name);
	}

	closedir(dir);
}