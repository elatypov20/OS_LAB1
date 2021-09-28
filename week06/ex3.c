#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_SIZE 2048
#define INF 100000000

#define MIN(a, b) a <= b ? a : b

struct Process{
	int AT, BT, CT, TAT, WT, id;

	int AT_STATIC, BT_STATIC;
};


struct ProcQueue{
	struct Process *q;
	int size, p, used;
};

struct ProcQueue CreateQueue(int size){
	struct ProcQueue ret = {
		.q = (struct Process*) malloc(size * sizeof(struct Process)),
		.size = size,
		.p = 0,
		.used = 0
	};

	return ret;
}


int qadd(struct ProcQueue *q, struct Process p){
	if (q->used + 1 > q->size)
		return 0;
	int np = (q->p + q->used) % q->size;
	q->used++;
	q->q[np] = p;

	return 1;
}

struct Process qpeek(struct ProcQueue *q){
	return q->q[q->p];
}

struct Process qpoll(struct ProcQueue *q){
	struct Process ret = q->q[q->p];
	q->p++;
	q->p %= q->size;
	q->used--;
	return ret;
}


int n = 0; // number of processes
double sumTAT = 0, sumWT = 0;
int quantum = 0;

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

			processes[id].AT_STATIC = processes[id].AT;
			processes[id].BT_STATIC = processes[id].BT;
			
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

void sortAT(){
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j){
			if (processes[j].AT < processes[i].AT)
				swap(&processes[i], &processes[j]);
		}
	}
}


void render_output(){
	printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");

	for (int i = 0; i < n; ++i) {
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
			i, processes[i].AT_STATIC, 
			processes[i].BT_STATIC, processes[i].CT,
			processes[i].TAT, processes[i].WT);
	}

	printf("Average Turnaround Time = %f\n", sumTAT / (double)n);
	printf("AverageWT = %f\n", sumWT / (double)n);
}


int main(int argc, char *argv[]){

	if (argc < 2){
		printf("Quantum not provided!\n");
		return 1;
	}

	sscanf(argv[1], "%d", &quantum);

	read_data(open("input.csv", O_RDONLY));
	
	sortAT();

	// solution

	int current_time = processes[0].AT;
	struct ProcQueue pq = CreateQueue(n);
	struct ProcQueue pq_result = CreateQueue(n);

	qadd(&pq, processes[0]);
	processes[0].AT = INF;

	int next_add = 1;

	while (pq.used != 0){
		struct Process current = qpoll(&pq);

		int to_add = 0;
		struct Process to_add_proc;

		int cur_bt = current.BT;

		if (current.BT <= quantum){
			current.CT = current_time + current.BT;
			current_time += current.BT;
			current.BT = 0;
			qadd(&pq_result, current);
		}else{
			current_time += quantum;
			current.BT -= quantum;
			to_add = 1;
			to_add_proc = current;
		}

		int qend = (pq.p + pq.used) % pq.size;
		for (int i = pq.p; i != qend; i = (i + 1) % pq.size){
			pq.q[i].WT += MIN(cur_bt, quantum);
		}

		next_add = -1;
		for (int i = 0; i < n; ++i){
			if (processes[i].AT <= current_time){
				processes[i].WT = current_time - processes[i].AT;
				qadd(&pq, processes[i]);
				processes[i].AT = INF;
			} else if (processes[i].AT != INF && next_add == -1){
				next_add = i;
			}
		}

		if (to_add)
			qadd(&pq, current);

		if (next_add != -1 && next_add <= n && pq.used == 0){
			int new_at = processes[next_add].AT;

			current_time = processes[next_add].AT;
			while (next_add < n && processes[next_add].AT == new_at){
				qadd(&pq, processes[next_add]);
				processes[next_add].AT = INF;
				next_add++;
			}
		
		}

	}

	for (int i = 0; i < n; ++i){
		processes[i] = qpoll(&pq_result);
		processes[i].TAT = processes[i].BT_STATIC + processes[i].WT;

		sumWT += processes[i].WT;
		sumTAT += processes[i].TAT;
	}

	// solution end

	render_output();
	free(processes);
}