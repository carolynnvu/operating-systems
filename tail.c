#include "types.h"
#include "stat.h"
#include "user.h"

#define DEFAULT_TAIL_LEN 10

int tail_len;
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

	int index_of_first_line = ((total_number_of_lines > tail_len) ? (total_number_of_lines - tail_len) : 0); 
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

void tail_stdi(int fd, char *name) {
	int n, total_number_of_lines;
	total_number_of_lines = 0;
	int char_count = 0;
	int i = 0;

	while((n = read(fd, &buf[char_count], sizeof(buf))) > 0){
		for(i = char_count; i < (n + char_count); i++){
			if(buf[i] == '\n')
				total_number_of_lines++;
		}
		char_count += n;
	}

	int current_line_number = 0;
	int index_of_first_line = (total_number_of_lines > DEFAULT_TAIL_LEN ? total_number_of_lines - DEFAULT_TAIL_LEN : 0);

	for(i = 0; i<char_count; i++){
		if(buf[i] == '\n') {
			current_line_number++;
		}
		if(current_line_number == index_of_first_line) {
			write(1, &buf[i], char_count);
			break;
		}
	}
}

void set_tail_len(char *str) {
	if(str[0] != '-') 
		tail_len = DEFAULT_TAIL_LEN;
	else {
		char * str_cp = str;
		str_cp = str_cp + 1;
		if(str_cp[0] == '\0') {
			tail_len = DEFAULT_TAIL_LEN;
		} else { 
			tail_len = atoi(str_cp);
		}
	}
}

int str_is_tail_len_flag(char *str) {
	return (str[0] == '-') ? 1 : 0;
}

int get_num_of_files(int tail_len_flag, int num_args) {
	int num_files = num_args - 1;
	if(tail_len_flag) num_files -= 1;
	return num_files;
}

int main(int argc, char *argv[]) {
	
	int fd, x, start_index;

	if(argc <= 1) {
		tail_stdi(0, "");
		exit();
	}

	char *str_cp = argv[1];
	int tail_len_flag = str_is_tail_len_flag(str_cp);
	if(tail_len_flag) {
		start_index = 2;
		set_tail_len(str_cp);
	} else {
		tail_len = DEFAULT_TAIL_LEN;
		start_index = 1;
	}

	int num_files = get_num_of_files(tail_len_flag, argc);

	for(x = start_index; x < argc; x++){
		if((fd = open(argv[x], 0)) < 0){ 
			printf(1, "tail: cannot open %s\n", argv[x]);
			exit();
		}
		if(num_files > 1) printf(1, "==> %s <==\n", argv[x]);
		tail(fd, argv[x]);
		close(fd);
		if((num_files > 1) && (x < argc-1)) printf(1, "\n");
	}

	exit();
}
