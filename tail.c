#include "types.h"
#include "stat.h"
#include "user.h"

char buf[4096];


void tail(int fd, char *name) {

	int n, total_number_of_lines, i;
	total_number_of_lines = 0;

	n = read(fd, buf, sizeof(buf));

	if(n > 0){
		for(i = 0; i<n; i++){
			if(buf[i] == '\n')
				total_number_of_lines++;
		}
	}

	if(n < 0) {
		printf(1, "tail: read error\n");
		exit();
	}

	int index_of_first_line = total_number_of_lines - 10;
	int current_line_number = 0;
	
	for(i = 0; i<n; i++) {
		if(buf[i] == '\n') {
			current_line_number++;
		}
		if(current_line_number == index_of_first_line) {
			write(1, &buf[i], n);
			break;
		}
	}
	
}

int main(int argc, char *argv[]) {
	
	int fd, x;

	if(argc <= 1) {
		tail(0, "");
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
