 #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include<sched.h>  


#define dprintf printf


struct config
{
	unsigned long sleep;	/* sleep time in 	us */
	unsigned long load;		/* load time in	us */
	unsigned long cycles;	/* calculation cycles with the same sleep/load time */
	unsigned long time;		/*  time in ms */
	unsigned int cpu;		/*  affinity mask */
	unsigned int verbose;	/* verbose output */
};


struct config *prepare_default_config()
{
	struct config *config = malloc(sizeof(struct config));
	config->sleep = 5000;
	config->load =5000;
	config->cycles = 0;
	config->time =  60 * 1000 * 1000;
	config->cpu = 0xff;
	config->verbose = 0;
	return config;
}

static struct option long_options[] = {
	{"sleep",	1,	0,	's'},
	{"load",	1,	0,	'l'},
	{"verbose",	0,	0,	'v'},
	{"cpu",		1,	0,	'c'},
	{"cycles",	1,	0,	'n'},
	{"time",	1,	0,	't'},
	{"help",	0,	0,	'h'},
	{0, 0, 0, 0}
};

/*******************************************************************
 usage
*******************************************************************/

void usage()
{
	printf("usage: ./bench\n");
	printf("Options:\n");
	printf(" -l <long>  busy us\n");
	printf(" -s <long>  idle us\n");
	printf(" -c <mask>  CPU mask\n");
	printf(" -n <int>   repeat cycles\n");
	printf(" -t <int>   total time in ms, 1: forever\n");
	printf(" -v         verbose output on/off\n");
	printf(" -h         Print this help screen\n");
	exit(1);
}


int set_cpu_affinity(unsigned int cpumask)
{
	cpu_set_t cpuset;
	int cpu = 0;

	CPU_ZERO(&cpuset);
	while(cpumask)
	{
		CPU_SET(cpu, &cpuset);
		cpu ++;
		cpumask = cpumask >> 1;
	}

	if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset) < 0) {
		perror("sched_setaffinity");
		fprintf(stderr, "warning: unable to set cpu affinity\n");
		return -1;
	}
	return 0;
}


long long int get_time()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (long long int)(now.tv_sec * 1000000LL + now.tv_usec);
}

void udelay_x(long long dly)
{
	long long  t1, t2;
	volatile unsigned long cnt = 0, cnt1;
	t1 = get_time();
	while( (get_time() - t1) < dly)
	{
		for(cnt <0; cnt < 50; cnt++)
			cnt1 = (cnt *17+cnt*3)/7;
	}

}

void start_test(struct config *config) 
{
	long long  t1;
	unsigned long time = config->time;
	if(!config->time)
		time = (config->load +  config->sleep) * config->cycles;

	
	t1 = get_time();
	while( (get_time() - t1) < time || time ==1000)
	{
		usleep(config->sleep);
		udelay_x(config->load);
	}
	if (config->verbose) 
		printf("End cpufreqbench.\n");
	
}

/*******************************************************************
 main
*******************************************************************/

int main(int argc, char **argv)
{
	int c;
	int option_index = 0;
	struct config *config = NULL;

	config = prepare_default_config();

	if (config == NULL)
		return EXIT_FAILURE;

	while (1) {
		c = getopt_long (argc, argv, "h:s:l:vc:n:t:",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 's':
			sscanf(optarg, "%li", &config->sleep);
			break;
		case 'l':
			sscanf(optarg, "%li", &config->load);
			break;
		case 'c':
			sscanf(optarg, "%x", &config->cpu);
			config->cpu &= 0xff;
			break;
		case 'n':
			sscanf(optarg, "%ld", &config->cycles);
			break;
		case 't':
			sscanf(optarg, "%ld", &config->time);
			config->time *=1000;
			break;
		case 'v':
			config->verbose = 1;
			break;
		case 'h':
		case '?':
		default:
			if (config != NULL) {
				free(config);
			}
			usage();
		}
	}

	if (config->verbose) 
		printf("\n\nStarting loadbench:\n idle=%li, busy=%li ms>\n cpumask=0x%x\n time=%ld ms, cycles=%ld\n",
		       config->sleep, config->load, config->cpu, config->time/1000, config->cycles);
	set_cpu_affinity(config->cpu);

	start_test(config);
	free(config);
	
	return EXIT_SUCCESS;
}


