#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#define WRITE_END 1
#define READ_END 0

struct board {
	int address;
	char name[32];
	int dir;
	int power;
	int mode;
	int target_pos;
	int target_spd;
};

struct board *cur;
int direction, run;
int cbn;
int stopsince;
int lastps;

void set_mode(int p, int id, int mode){
	char str[64];
	sprintf(str, "true\n\n2\n%d\n0\n%d\nfalse\ntrue\n", id, mode);
	write(p, str, strlen(str));
}


void set_power(int p, int id, int power, int direction){
	char str[64];
	sprintf(str, "true\n\n2\n%d\n2\n%d\n%d\nfalse\ntrue\n", id, power, direction);
	write(p, str, strlen(str));
}

void set_target(int p, int id, int tp, int ts){
	char str[64];
	uint16_t tp_u = (int16_t)tp;
	sprintf(str, "true\n\n2\n%d\n4\n%d\n%d\nfalse\ntrue\n", id, tp_u, ts);
	write(p, str, strlen(str));
}


pid_t open_pipe(int fd[2]){
	pid_t pid;
	pipe(fd);
	pid = fork();
	if(pid == 0){
		dup2(fd[READ_END], STDIN_FILENO);
		dup2(STDERR_FILENO, STDOUT_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		execlp("mono", "mono", "CanTester.exe", NULL);
//		execlp("./debug_dump", "debug_dump", NULL);
	} else {
		return pid;
	}
}
void stopall(struct board *boards, int fd[2]){
	run = 0;
	int i;
	for(i = 0;i < 6;i++){
		cur = &boards[i];
		if(cur->mode != -1){
			cur->mode = 0;
			set_mode(fd[WRITE_END], cur->address, cur->mode);
			cur->power = 0;
			set_power(fd[WRITE_END], cur->address, cur->power, 0);
		}
		cur = &boards[cbn];
	}

}
int main(){
	int ch;
	int status;
	int fd[2];
	struct board boards[7] = {{0x10, "Base rotation", 0, 128, -1}, {0x11, "Shoulder", 0, 192, -1}, {0x12, "Elbow", 0, 64, -1}, {0x13, "Forearm rotation", 0, 64, -1}, {0x14, "Differential wrist 1", 0, 128, -1}, {0x15, "Differential wrist 2", 0, 128, -1}, {0x16, "Hand", 0, 128, -1}};
	cur = boards;
	direction = cur->dir;
	initscr();
	noecho();
	cbreak();
	timeout(500);
	pid_t pid = open_pipe(fd);
	while((ch = getch()) != 'q'){
		usleep(50000);
		timeout(0);
		while(getch() != ERR);
		timeout(500);
		erase();
		switch(ch){
			case 'm':
				cur->mode = 0;
				set_mode(fd[WRITE_END], cur->address, cur->mode);
				break;
			case 'M':
				cur->mode = 1;
				set_mode(fd[WRITE_END], cur->address, cur->mode);
				break;
			case 'p':
				if(cbn < 6)
					cur = &boards[++cbn];
				break;
			case 'o':
				if(cbn > 0)
					cur = &boards[--cbn];
				break;
			case 'a':
				if(cur->power == 255){
					cur->power++;
				}
				if(cur->power > 0){
					cur->power -= 8;
				}
				break;
			case 'd':
				if(cur->power < 255){
					cur->power += 8;
				}
				if(cur->power == 256){
					cur->power = 255;
				}
				break;
			case 'w':
				direction = cur->dir;
				run = 1;
				break;
			case 's':
				direction = !cur->dir;
				run = 1;
				break;	
			case ' ': 
				stopall(boards, fd);			
				break;
			case 'g':
				if(!cur->mode){break;}
				run = 0;
				erase();
				echo();
				timeout(10000);
				mvprintw(1, 0, "Enter target position and velocity: ");
				scanw("%d %d", &cur->target_pos, &cur->target_spd);
				erase();
				noecho();
				timeout(500);
				set_target(fd[WRITE_END], cur->address, cur->target_pos, cur->target_spd);
				break;

			case ERR:
				stopsince++;
				if(stopsince > 1){
					run = 0;
					stopsince = 0;
				}
				break;
			
		}
		if(run && clock() - lastps > 200){
			set_power(fd[WRITE_END], cur->address, cur->power, direction);	
			lastps = clock();
		} else if(cur->mode != 1){
			set_power(fd[WRITE_END], cur->address, 0, direction);
		}
		mvprintw(1, 0, "Board: %s (0x%X)", cur->name, cur->address);
		mvprintw(2, 0, "Mode: %d", cur->mode);
		if(cur->mode == 0){
			mvprintw(3, 0, "Power: %d (%02.1f%%)", cur->power, cur->power*100.0/255);
			mvprintw(4, 0, "Direction: %d", direction);
		}
		if(cur->mode == 1){
			mvprintw(3, 0, "Target position: %d", cur->target_pos);
			mvprintw(4, 0, "Target velocity: %d", cur->target_spd);
		} else {
			mvprintw(5, 0, "%s", run? "Running" : "Stopped");
		}
		refresh();
		status = waitpid(pid, NULL, WNOHANG);
		if(status){
			printf("Exited!\n");
			break;
		}
	}
	stopall(boards, fd);
	kill(pid, 9);
	waitpid(pid, NULL, 0);
	endwin();
	return 0;
}
