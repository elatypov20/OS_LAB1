#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_FILE_SIZE 2048

struct Process{
	int AT, BT, CT, TAT, WT, id;
};

int n = 0; // number of processes
double sumTAT = 0, sumWT = 0;

struct Process *processes;

void read_data(int fd){
	char buffer[MAX_FILE_SIZE];
	read(fd, buffer, MAX_FILE_SIZE);

	int pt = 0;
	while (pt < MAX_FILE_SIZE && buffer[pt]){
		if (buffer[pt] && buffer[pt] == '\n')
			n++;

		if (buffer[pt] == ',' || buffer[pt] == '\n')
			buffer[pt] = 0;

		pt++;
	}

	processes = (struct Process*) malloc(sizeof(struct Process) * n);
	int mode = 0; // 0 - AT, 1 - BT
	int k = n * 2, i = 0, res = 0;
	while (k > 0){
		if (buffer[i] != 0){
			sscanf(&buffer[i], "%d", &res);
			int id = (n * 2 - k) / 2;
			if (!mode)
				processes[id].AT =  res;
			else
				processes[id].BT =  res;

			processes[id].id = id;
			mode = ++mode % 2;
			k--;

			while (k != 0 && buffer[++i] != 0);
		}
		i++;
	}

}

void swap(struct Process *a, struct Process *b){
	struct Process t = *a;
	*a = *b;
	*b = t;
}

void sort(){
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j){
			if (processes[j].AT < processes[i].AT
				|| (processes[j].AT == processes[i].AT 
					&& processes[j].BT < processes[i].BT))
				swap(&processes[i], &processes[j]);
		}
	}
}


void render_output(){
	printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");

	for (int i = 0; i < n; ++i) {
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
			processes[i].id, processes[i].AT, 
			processes[i].BT, processes[i].CT,
			processes[i].TAT, processes[i].WT);
	}

	printf("Average Turnaround Time = %f\n", sumTAT / (double)n);
	printf("AverageWT = %f\n", sumWT / (double)n);
}

int main(){
	read_data(open("input.csv", O_RDONLY));
	sort();
	
	int current_time = processes[0].AT;
	for (int i = 0; i < n; ++i){
		
		if (current_time > processes[i].AT){
			processes[i].WT = current_time - processes[i].AT;
		} else{
			processes[i].WT = 0;
			current_time = processes[i].AT;
		}

		processes[i].CT = current_time + processes[i].BT;
		processes[i].TAT = processes[i].BT + processes[i].WT;

		sumTAT += processes[i].TAT;
		sumWT += processes[i].WT;

		processes[i].id = i;
		current_time += processes[i].BT;
	}

	render_output();
	free(processes);
}