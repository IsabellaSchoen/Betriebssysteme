
vector_t v[2 * MAX_THREADS];

// used to ensure print outs make sense
pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;

void usage(char *prog) {
    fprintf(stderr, "usage: %s [-d (turn on deadlocking behavior)] [-l loops] [-n num_threads] [-t (do timing)] [-v (for verbose)]\n", prog);
    exit(1);
}

// only called by one thread (not thread-safe)
void vector_init(vector_t *v, int value) {
    int i;
    for (i = 0; i < VECTOR_SIZE; i++) {
		v->values[i] = value;
    }
    Pthread_mutex_init(&v->lock, NULL); 
}

// only called by one thread (not thread-safe)
void vector_print(vector_t *v, char *str) {
    int i;
    for (i = 0; i < VECTOR_SIZE; i++) {
		printf("%s[%d] %d\n", str, i, v->values[i]);
    }
}

void print_info(int call_return, int thread_id, int v0, int v1) {
    if (verbose == 0)
	return;
    Pthread_mutex_lock(&print_lock);
    int j;
    for (j = 0; j < thread_id; j++) printf("              ");
    if (call_return) 
		printf("<-add(%d, %d)\n", v0, v1); //abgeben der Locks
    else
		printf("->add(%d, %d)\n", v0, v1); //holen der Locks
    Pthread_mutex_unlock(&print_lock);
}

typedef struct __thread_arg_t {
    int tid;
    int vector_add_order;
    int vector_0;
    int vector_1;
} thread_arg_t;

void *worker(void *arg) {
    thread_arg_t *args = (thread_arg_t *) arg;
    int i, v0, v1;
    for (i = 0; i < loops; i++) {
		if (args->vector_add_order == 0) { 
		    v0 = args->vector_0;
		    v1 = args->vector_1;
		} else {
		    v0 = args->vector_1;
		    v1 = args->vector_0;
		}

		print_info(0, args->tid, v0, v1); //Zeile 38

		vector_add(&v[v0], &v[v1]); //pro Code abhängig

		print_info(1, args->tid, v0, v1); //Zeile 36
    }
    return NULL;
}

int main(int argc, char *argv[]) {
//Opportunities--------------------------------------
    opterr = 0;
    int c;
    while ((c = getopt (argc, argv, "l:n:vtdp")) != -1) {
		switch (c) {
		case 'l':
		    loops = atoi(optarg);
		    break;
		case 'n':
		    num_threads = atoi(optarg);
		    break;
		case 'v':
		    verbose = 1;
		    break;
		case 't':
		    do_timing = 1;
		    break;
		case 'd':
		    cause_deadlock = 1;
		    break;
		case 'p':
		    enable_parallelism = 1;
		    break;
		default:
		    usage(argv[0]);
		}
    }

//"n"-----------------------------------------
    assert(num_threads < MAX_THREADS); //CHECK

    pthread_t pid[MAX_THREADS]; //Thread0
    thread_arg_t args[MAX_THREADS]; //Thread1

    int i;
    for (i = 0; i < num_threads; i++) {
	args[i].tid = i; //args: array der threads; tid: thread ID
		if (enable_parallelism == 0) { //Anzahl verschiedener Vectoren -> je mehr desto weniger deadlocks
		    args[i].vector_0 = 0;
		    args[i].vector_1 = 1;
		} else {
		    args[i].vector_0 = i * 2;
		    args[i].vector_1 = i * 2 + 1;
	}

//"d"---------------------------------------
	if (cause_deadlock && i % 2 == 1)
	    args[i].vector_add_order = 1;
	else
	    args[i].vector_add_order = 0;
    }


//-------------------------------------------
    for (i = 0; i < 2 * MAX_THREADS; i++) 
	vector_init(&v[i], i);


//TIMING---------------------------------------------
    double t1 = Time_GetSeconds();

    for (i = 0; i < num_threads; i++) 
	Pthread_create(&pid[i], NULL, worker, (void *) &args[i]);
    for (i = 0; i < num_threads; i++) 
	Pthread_join(pid[i], NULL); 

    double t2 = Time_GetSeconds();

    fini();
    if (do_timing) {
	printf("Time: %.2f seconds\n", t2 - t1);
    }


//---------------------------------------------------
    //vector_print(&v[0], "v1");
    //vector_print(&v[1], "v2");
    return 0;
}
