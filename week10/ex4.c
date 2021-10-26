#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct file_info{
	int inode;
	char name[256];
} file_info_t;

int main(int argc, char *argv[]){
	
	if (argc < 2){
		printf("dirname is not specifies\n");
		return 1;
	}

	char *dirname = argv[1];
	chroot(dirname);

	DIR *dir = opendir(dirname);

	if (dir == NULL){
		printf("Error opening dir\n");
		return 1;
	}

	file_info_t *files = NULL;
	int p = 0;

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL){
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			continue;

		int inode = entry->d_ino;
		char *name = entry->d_name;
		
		file_info_t new_file = {.inode = inode};
		strcpy(new_file.name, name);

		p++;
		files = realloc(files, p * sizeof(file_info_t));
		files[p - 1] = new_file;
	}


	file_info_t *filtered = (file_info_t*) malloc(p * sizeof(file_info_t));
	// detect unique elements and ignore them
	for (int i = 0; i < p; ++i){
		file_info_t empty = {.name="", .inode=-1};	
		filtered[i] = empty;
		for (int j = 0; j < p; ++j){
			if (i == j)
				continue;

			if (files[i].inode == files[j].inode){
				filtered[i] = files[i];
			}
		}
	}	

	for (int i = 0; i < p; ++i){
		if (filtered[i].inode == -1)
			continue;
		
		printf("%s: ", filtered[i].name);
		for (int j = 0; j < p; ++j){
			if (filtered[i].inode != filtered[j].inode)
				continue;

			printf("%s ", filtered[j].name);
		}
		printf("\n");
	}

	closedir(dir);
}