//Corey Naas & Brian Scott
//COSC 3303
//2017/05/04
//A program to generate 10,000 vectors, and to compare the time it takes to 
//normalize all 10,000 vectors using C and x86 assembly.
//
//Special thanks to Brian Scott for collaboration on the x86 assembly function. 50/50 contribution.
//Special thanks to the people of StackOverflow for helping me fix the little problems and re-teaching 
//	me the basics of programming as a junior CS student.
//Special thanks to my mom for keeping me alive those first nine months, and then 21 years after that.

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

int Normalize(float a[]);
int NormalizeASM(float a[]);
float * generate10k();
void Over10kCalculations();

int main(){
	float a[3];
	float *vectors;
	
	printf( "Enter a vector like so: 3.5 7.3 1.1; or three zeros to run test\n");
	scanf("%f %f %f", &a[0], &a[1], &a[2]);
	
	//If the vector is zero, generate 10k vectors and run normalization test
	if(a[0] == 0 && a[1] == 0 && a[2] == 0 ){
		vectors = generate10k();
		Over10kCalculations(vectors);
		printf("Goodbye!\n");
		return(0);
	}
	
	//print what was enter for proofing purposes
	printf("You entered: %f %f %f\n", a[0], a[1], a[2]);
	
	//pass the given vectors to the c function
	printf("Passing to C function...\n");
	Normalize(a);
	
	//pass the given vectors to the x86 function
	printf("Passing to x86 function...\n");
	NormalizeASM(a);
	
	printf("Goodbye!\n");
    return(0);
}

int Normalize(float a[]){
	//establish timekeeping and start timer
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	
	float aN[3]; 
	float aMag;
	
	printf("Vector being normalized:[%f %f %f]\n", a[0], a[1], a[2]);
	
	//Magnitude equals the square root of the sum of squares
	aMag = sqrt(a[0]*a[0] + a[1]*a[1] +a[2]*a[2]);
	
	//normalized vector equals vector over magnitude
	aN[0] = a[0]/aMag;
	aN[1] = a[1]/aMag;
	aN[2] = a[2]/aMag;
	
	printf("Normalized vector by C:[%f %f %f]\n", aN[0], aN[1], aN[2]);
	
	//stop timer and print time
	gettimeofday(&stop, NULL);
	printf("Operation by C took %dms to complete\n", stop.tv_usec - start.tv_usec);
	
	int timedist = stop.tv_usec - start.tv_usec;
	return timedist;
}

int NormalizeASM(float a[]){
	//establish timekeeping and start timer
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	
	float aN[3]; 
	float aMag;
	
	printf("Vector being normalized:[%f %f %f]\n", a[0], a[1], a[2]);
	
	//Requirements of the x86 function:
	//Input: 	An array of three floating point numbers
	//Stuff do:	-Square each vector element
	//			-sum them together
	//			-take the square root of the sum = magnitude
	//			-divide each original element by the magnitude = normalized vector
	//Output: 	console print of the normalized vector OR normalized vector returned
	//				to be printed below
	
	//Call to x86 assembly vector normalization function
	//goes
	//here
	//plox
		
	printf("Normalized vector:[%f %f %f]\n", aN[0], aN[1], aN[2]);
	
	//stop timer and print time
	gettimeofday(&stop, NULL);
	printf("Operation by x86 took %dms to complete\n", stop.tv_usec - start.tv_usec);
	
	int timedist = stop.tv_usec - start.tv_usec;
	return timedist;
}

float * generate10k(){
	FILE *fp;
	srand((unsigned int)time(NULL));
	float b = 5.0;
	static float vec[30000];
	
	printf("Generating 10,000 floating point vectors and saving them to 10kVectors.txt...\n");
	
	fp = fopen("10kVectors.txt", "w+");
	
	//generates float array of 30,000 random floating point numbers 
	//between 0 and b for 10,000 random floating point vectors
	for (int i=0;i<30000;i++){
		vec[i] = ((float)rand()/(float)(RAND_MAX)) * b;
        fprintf(fp, "%f\n", vec[i]);
    }
    
    fclose(fp);
    
    return vec;
}

void Over10kCalculations(float * vec){
	float temp[3];
	int avgTime[10000];
	int sumTimeC;
	int sumTimeASM;
	double totalAvgC;
	double totalAvgASM;
	int j = 0;

	//normalize each and every vector using the C function. All of them. 
	for (int i=0;i<30000;i+=3){
		temp[0] = vec[i+0];
		temp[1] = vec[i+1];
		temp[2] = vec[i+2];
		avgTime[j] = Normalize(temp);
		printf("Time for vector #%i: %ims\n -----\n", j, avgTime[j]);
		
		sumTimeC += avgTime[j];
		j++;
	}
	
	//normalize each and every vector using the x86 function. All of them. 
	//on second thought, it might be better to pass all of the vectors to the function and let the asm function loop, and calculate all of the normalized vectors, and time that, then divide it to find the average. instead of passing them one by one. 
	j=0;
	for (int i=0;i<30000;i+=3){
		temp[0] = vec[i+0];
		temp[1] = vec[i+1];
		temp[2] = vec[i+2];
		avgTime[j] = NormalizeASM(temp);
		printf("Time for vector #%i: %ims\n -----\n", j, avgTime[j]);
		
		sumTimeASM += avgTime[j];
		j++;
	}

	//divide by number of vectors to get average
	totalAvgC = sumTimeC/10000.0;
	totalAvgASM = sumTimeASM/10000.0;

	printf("The total calculation time in C is %dms\n", sumTimeC);	
	printf("The average calculation time in C is %fms\n", totalAvgC);
		
	printf("The total calculation time in x86 is %dms\n", sumTimeASM);	
	printf("The average calculation time in x86 is %fms\n", totalAvgASM);
	
	return;
}



//http://stackoverflow.com/questions/10192903/time-in-milliseconds
//http://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c
//https://www.3dbuzz.com/forum/threads/104753-HowTo-Inline-Assembly-amp-SSE-Vector-normalization-done-fast!