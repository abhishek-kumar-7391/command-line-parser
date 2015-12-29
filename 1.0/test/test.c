#include <stdio.h>
#include <getopt.h>
#include <parse_cmdline.h>

//struct args* arg_list[ASCII_MAX_CHAR];
#define somevalue 10
int sv;

int main(int argc, char* argv[]){
	const struct option longopts[]={
		{"src", required_argument, 0, 's'},
		{"dst", required_argument, 0, 'd'},
		{"sv", no_argument, &sv, somevalue},
		{0,0,0,0}
	};

	const char* shortopts="s:d:";
	const char* temp;
	
	
	if(parse_cmdline(argc, argv, longopts, shortopts)<0)
		exit(EXIT_FAILURE);
	
	fprintf(stdout, "getting optarg by shortopt\n");
	temp = get_optarg_by_shortopt('s');
	if(temp)
		fprintf(stdout, "temp = %s\n", temp);
	temp = get_optarg_by_shortopt('d');
	if(temp)
		fprintf(stdout, "temp = %s\n", temp);
	
	fprintf(stdout, "getting optarg by longopt\n");
	temp = get_optarg_by_longopt("src");
	if(temp)
		fprintf(stdout, "temp = %s\n", temp);
	temp = get_optarg_by_longopt("dst");
	if(temp)
		fprintf(stdout, "temp = %s\n", temp);
	return 1;	
	

}

