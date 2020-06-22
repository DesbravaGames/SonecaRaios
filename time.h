#ifndef NK_TIME_H
#define NK_TIME_H

void time_init();
float time_elapsed();

long time_elapsed_millis();
long time_elapsed_micro();

float time_delta();
void time_update();
int time_fps();

#include <stdlib.h>
#include <sys/time.h>

long initial_time=0;
long last_update_time=0;
float delta=0;

/**
 * Returns the current time in microseconds using posix function,
 */

static long getSysMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

void time_init() {
	initial_time=getSysMicrotime();
	last_update_time=initial_time;
}
float time_elapsed() {
	return (float) (getSysMicrotime()-initial_time)/1e6f;
};

long time_elapsed_millis() {
	return (getSysMicrotime()-initial_time)/1000;
}
long time_elapsed_micro(){
	return getSysMicrotime()-initial_time;
};

float time_delta() {
	return delta;
}
void time_update(){
	long now_micro=getSysMicrotime();

	delta=(float)((now_micro-last_update_time)/1e6f);
	last_update_time=now_micro;
};

int time_fps() {
	return (int)(1.0/delta);
};


#endif