#include "types.h"
#include "stat.h"
#include "user.h"

char buf[4096];

int main() {

	int n, m, total_number_of_lines, i;
	total_number_of_lines = 0;
	int fd = open("README", 0);
	
	while((n = read(fd, buf, sizeof(buf))) > 0) { 
		for(i = 0; i<n; i++){
			if(buf[i] == '\n')
				total_number_of_lines++;
		}
	}
	close(fd);
	fd = open("README", 0);

	int index_of_first_line, current_line_number;
	index_of_first_line = total_number_of_lines - 10;
	printf(1,"Total number of lines: %d\n", total_number_of_lines);
	printf(1,"First line we want to print: %d\n", index_of_first_line);
	//index -10 to account for 0 start, instead of t - 10 + 1


	while((m = read(fd, buf, sizeof(buf))) > 0) {
		for(i = 0; i <m; i++) {
			if(buf[i] == '\n') {
				current_line_number++;
			}
			if(current_line_number == index_of_first_line) {
				write(1, &buf[i], m);
				break;
			} 
		}
	}


	exit();
}
