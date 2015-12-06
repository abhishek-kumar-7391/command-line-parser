#include "parse_cmdline.h"

/**
 * Check if a given short option is present in the user provided 
 * list of options.
 * @param longopts a pointer to the long options provided by the 
 * user
 * @param c the short option to be searched
 * 
 * returns 1 for success -1 for failure
 */
static int is_in_option(const struct option* longopts, int c){
	int i;

	i = 0;
	
	if(!longopts || c<0){
#ifdef DEBUG
		fprintf(stderr, "[ %s ] Invalid input.\n", __func__);
#endif
		return -1;
	}

	for(i=0; longopts[i].name!=NULL;++i){
		if(longopts[i].val == c)
			return i;
	}
	return -1;
}

/**
 * Populate the arg_list[] array with the command line argument
 * provided by the user.
 * @param longopts a pointer to the long options provided by the 
 * user
 * @param c the short option encountered
 * @param optindex index value as per the long option selected.
 */
static int populate_args(const struct option* longopts, int c,
			int optindex){
	int i;


	if(!longopts)
		return -1;
	
	i = -1;
	
	if(c > 0){
		/* if arg_list already contains the incoming option, then bail out */
		if(arg_list[c]){
			fprintf(stderr, "Option '%c' used multiple times\n", c);
			exit(EXIT_FAILURE);;
		}

		arg_list[c] = malloc(sizeof(struct args));
		if(!arg_list[c]){
			perror("Memory");
			exit(INSUFFICIENT_MEMORY);
		}

		memset(arg_list[c], '\0', sizeof(struct args));
	
		/* if shortopt is used on command line */
		if(optindex == -1){ 
			/* look for shortopt in longopts table */
			i = is_in_option(longopts, c);
			if(i<0)  // unlikely to happen ; but still a defensive check
				return -1;
		}else if(optindex >=0) // when longopt is used
			i = optindex;
		else{
			free(arg_list[c]);
#ifdef DEBUG
			fprintf(stderr, "Invalid optindex value\n");
#endif
			return INVALID_OPTINDEX_VALUE;
		}
		
		/* populate one of the array indexes in the arg_list */
		arg_list[c]->opt = &longopts[i];
		arg_list[c]->optarg = strdup(optarg);
		return 1;
	}
#ifdef DEBUG
	fprintf("Invalid value %d for 'c'\n", c);
#endif
	return -1;
}

int parse_cmdline(int argc, char** argv, const struct option* longopts, 
			const char* shortopts){
	int c;
	int optindex;

	c = -1;
	if(argc==1){
		fprintf(stderr, "No command line inputs\n");
		return -1;
	}

	for(;;){
		optindex = -1;
		c = getopt_long(argc, argv, shortopts, longopts, 
				&optindex);
		if(c<0){
#ifdef DEBUG
			fprintf(stdout, "End of command line inputs\n");
#endif
			break;
		}

		switch(c){
			case 0:
				break;
			case '?':
#ifdef DEBUG
				fprintf(stderr, "Unknown or ambiguous option '%c'\n", c);
#endif
				return -1;
			default:
#ifdef DEBUG
				if(optindex >=0)
					fprintf(stdout, "parsing option '%s'\n", longopts[optindex].name);
				else if(optindex < 0)
					fprintf(stdout, "parsing option '%c'\n", c);
#endif
				if(populate_args(longopts, c, optindex)!=1){
					fprintf(stderr, "Error parsing input '%c'\n", c);
					return -1;
				}

#ifdef DEBUG
				if(optindex >=0)
					fprintf(stdout, "parsing done for option '%s'\n", longopts[optindex].name);
				else if(optindex < 0)
					fprintf(stdout, "parsing done for option '%c'\n", c);
#endif
		}
		
	}
	return 1;
}

/** get arguments by long option */
const char* get_optarg_by_longopt(const char* name){
#ifdef DEBUG
	fprintf(stdout, "looking optarg for name = %s\n", name);
#endif
	int i;
	for(i=0;i<ASCII_MAX_CHAR;++i){
		if(arg_list[i] && !strcmp(name, arg_list[i]->opt->name))
			return arg_list[i]->optarg;
	}
	return NULL;
}

/** get arguments by short option */
const char* get_optarg_by_shortopt(unsigned int c){
#ifdef DEBUG
	fprintf(stdout, "looking optarg for c = %u\n", c);
#endif
	if(arg_list[c])
		return arg_list[c]->optarg;
	return NULL;
}

void dump_cmdline_args(struct args** arg_list, FILE* fp){
	int i;
	const struct option* temp;
	for(i=0; i < ASCII_MAX_CHAR;++i){
		if(arg_list[i] && arg_list[i]->opt){
			temp = arg_list[i]->opt;
			fprintf(fp, "name = %s\n", temp->name);
			fprintf(fp, "val = %d\n", temp->val);
			fprintf(fp, "has arg = %d\n", temp->has_arg);
			fprintf(fp, "flag = %d\n", temp->flag?*(temp->flag):0);
			fprintf(fp, "optarg = %s\n", arg_list[i]->optarg);
		}
	}
}
