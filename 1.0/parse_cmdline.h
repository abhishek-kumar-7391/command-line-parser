#ifndef PARSE_CMDLINE
#define PARSE_CMDLINE

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

#define ASCII_MAX_CHAR 128

/** 
 * Data structure to maintain all the command line options 
 * and their corresponding arguments entered by the user.
 */
struct args{
	const struct option* opt;	/* points to one of the "struct option" instances 
					   provided by the user.*/
	
	const char* optarg;		/* points to the argument corresponding to the 
					   long/short option */
};


/** Array of long/short options and their corresponding arguments */
struct args* arg_list[ASCII_MAX_CHAR];

/** Return codes */
enum retcodes{
	NULL_LONGOPTS_INSTANCE,
	NULL_SHORTOPTS_INSTANCE,
	INSUFFICIENT_MEMORY,
	INVALID_OPTINDEX_VALUE
};

/**
 * Get the argument corresponding to a longoption
 * @param longoption string
 */
const char* get_optarg_by_longopt(const char*);

/**
 * Get the argument corresponding to the supplied shortoption
 * @param shortoption unsigned char
 */
const char* get_optarg_by_shortopt(unsigned int);

/**
 * Parse command line and populate the global arg_list[] array with
 * arguments at index given by the shortoption, if any.
 * Main routine to be called by the user application.
 */
int parse_cmdline(int, char**, const struct option*, const char*);

/**
 * Dump all the populated command line arguments on
 * a given file descriptor.
 * Mainly for debugging purposes.
 */
void dump_cmdline_args(struct args**, FILE*);
#endif
