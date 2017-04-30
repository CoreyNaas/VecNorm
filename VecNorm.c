#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

int Normalize(float a[]);
void NormalizeASM(float a[]);
float * generate10k();
void Over10kCalculations();

int main(){
	float a[3];
	float *vectors;
	
	printf( "Enter a vector like so: 3.5 7.3 1.1; or three zeros to generate vectors\n");
	scanf("%lf %lf %lf", &a[0], &a[1], &a[2]);
	if(a[0] == 0){
		vectors = generate10k();
		Over10kCalculations(vectors);
	}
	
	printf("You entered: %f %f %f\n", a[0], a[1], a[2]);
	
	printf("Passing to C function...\n");
	Normalize(a);
	
	printf("Passing to x86 function...\n");
	
	
    return(0);
}

int Normalize(float a[]){
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	
	float aN[3]; 
	float aMag;
	
	aMag = sqrt(a[0]*a[0] + a[1]*a[1] +a[2]*a[2]);
	
	aN[0] = a[0]/aMag;
	aN[1] = a[1]/aMag;
	aN[2] = a[2]/aMag;
	
	printf("Normalized vector:[%f %f %f]\n", aN[0], aN[1], aN[2]);
	
	gettimeofday(&stop, NULL);
	printf("Operation took %lums to complete\n", stop.tv_usec - start.tv_usec);
	
	int timedist = stop.tv_usec - start.tv_usec;
	return timedist;
}

void NormalizeASM(float a[]){
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	
	float aN[3]; 
	float aMag;
	
	printf("Normalized vector:[%f %f %f]\n", aN[0], aN[1], aN[2]);
	
	gettimeofday(&stop, NULL);
	printf("Operation took %lums to complete\n", stop.tv_usec - start.tv_usec);

}

float * generate10k(){
	FILE *fp;
	srand((unsigned int)time(NULL));
	float b = 5.0;
	float vec[30000];
	
	printf("Generating 10,000 floating point vectors and saving them to 10kVectors.txt...\n");
	
	fp = fopen("10kVectors.txt", "w+");
	
	for (int i=0;i<30000;i++){
		vec[i] = ((float)rand()/(float)(RAND_MAX)) * b;
        fprintf(fp, "%f\n", vec[i]);
    }
    return vec;
}

void Over10kCalculations(float * vec){
	float temp[3];
	int avgTime[10000];
	int sumTime;
	double totalAvg;
	
	printf("hey there :)\n");
	
	for (int i=0;i<10000;i+=3){
		temp[0] = vec[i+0];
		temp[1] = vec[i+1];
		temp[2] = vec[i+2];
		avgTime[i] = Normalize(temp);
		printf("Avg time for vector #%i: %ims\n", i, avgTime[i]);
	}
	
	for (int i=0;i<10000;i++){
		sumTime += avgTime[i];
	}
	
	totalAvg = (sumTime);
	
	printf("The average Calculation time is %fms\n", totalAvg);
	
	return;
}



//http://stackoverflow.com/questions/10192903/time-in-milliseconds
//http://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c