#include "types.h"
#include "stat.h"
#include "user.h"

char buf[4096];


void tail(int fd, char *name) {
	
	//int y = read(fd, buf, sizeof(buf));
	//write(1, buf, y);

	int n, m, total_number_of_lines, i;
	total_number_of_lines = 0;

	while((n = read(fd, buf, sizeof(buf))) > 0) {
		for(i = 0; i<n; i++){
			if(buf[i] == '\n')
				total_number_of_lines++;
		}
	}
	close(fd);
	fd = open(name, 0);

	int index_of_first_line = total_number_of_lines - 10;
	int current_line_number;
	
	while((m = read(fd, buf, sizeof(buf))) > 0) {
		for(i = 0; i<m; i++) {
			if(buf[i] == '\n') {
				current_line_number++;
			}
			if(current_line_number == index_of_first_line) {
				write(1, &buf[i], m);
				break;
			}
		}
	}
		
}

int main(int argc, char *argv[]) {
	
	int fd, x;

	if(argc <= 1) {
		printf(1, "Must enter file name!\n");
		exit();
	}

	for(x = 1; x < argc; x++){
		if((fd = open(argv[x], 0)) < 0){ 
			printf(1, "tail: cannot open %s\n", argv[x]);
			exit();
		}
		tail(fd, argv[x]);
		close(fd);
	}

	exit();
}
