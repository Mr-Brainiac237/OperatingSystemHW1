#include <stdio.h> // For standard I/O operations
#include <math.h> // For mathematical functions
#include <stdlib.h> // For memory allocation and exit() function
#include <time.h> // For seeding the random number generator
#include <string.h> // For string manipulation
#include <sys/stat.h> // For mkdir()
#include <errno.h> // For error handling

// Macros for generating random numbers
#define frand() (rand() / (double)RAND_MAX) // Uniform random number in [0, 1)
#define nrand() (sqrt(-2 * log(frand())) * cos(2 * M_PI * frand())) // Normal
#define HISTOGRAM_BINS 50

void generate_random_numbers_to_file(const char* filename, int type, double m, double M, double mu, double sigma, int N);
void calculate_statistics_from_file(const char* filename, int N);
void generate_histogram_from_file(const char* input_filename, const char* output_filename, int bins, double min, double max);
int generate_uniform_integer(double m, double M);
double generate_uniform_real(double m, double M);
double generate_normal_real(double mu, double sigma);
int generate_normal_integer(double mu, double sigma);
double generate_truncated_normal_real(double m, double M, double mu, double sigma);
int generate_truncated_normal_integer(double m, double M, double mu, double sigma);
double calculate_mean(double* data, int n);
double calculate_std_dev(double* data, int n, double mean);
int create_directory(const char* path);

int main()
{
	srand(time(NULL));
	double scenarios[3][5] = {
	{5, 1, 1, 8, 20},
	{pow(2, 10), pow(2, 8), 1, 2000, 200000},
	{pow(2, 12), 1.3 * pow(2, 10), 1, 8100, 2000000}
	};
	char* subfolders[3] = {"DATA/Scenario1", "DATA/Scenario2", "DATA/Scenario3"};
	char* histogram_folder = "HISTOGRAM";
	

	
	for(int i = 0; i < 3; i++){
		char dirPath[50], filePath[100];
		sprintf(dirPath, "DATA/Scenario%d", i + 1);
		create_directory("DATA");
		create_directory(dirPath);
		double mu = scenarios[i][0];
		double sigma = scenarios[i][1];
		double m = scenarios[i][2];
		double M = scenarios[i][3];
		int sample = scenarios[i][4];
		double *inputs = (double *)malloc(sample * sizeof(double));
		if (inputs == NULL) {
			// Handle memory allocation failure
			printf("Memory allocation failed!\n");
			return -1;
		}
		sprintf(filePath, "%s/Scenario%dTable.txt", dirPath, i + 1);
		FILE* file = fopen(filePath, "a");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		for(int j = 0; j < 53; j++){fprintf(file, "-");}
		fprintf(file, "\n| Sequence Names | Sample Mean | Standard Deviation |\n");
		for(int j = 0; j < 53; j++){fprintf(file, "-");}
		fclose(file);
		
		sprintf(filePath, "%s/uniform_integers.txt", dirPath);
		file = fopen(filePath, "w");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		for(int j = 0; j < sample;j++){
		    inputs[j] = generate_uniform_real(m, M);
			fprintf(file, "%d ", inputs[j]);
		}
		fclose(file);
		sprintf(filePath, "%s/Scenario%dTable.txt", dirPath, i + 1);
		file = fopen(filePath, "a");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		fprintf(file, "\n| Uniform Ints   | %-11.2f | %-18.2f |\n", calculate_mean(inputs, sample), calculate_std_dev(inputs, sample, calculate_mean(inputs, sample)));
		fclose(file);
		
		sprintf(filePath, "%s/uniform_real_number.txt", dirPath);
		file = fopen(filePath, "w");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		for(int j = 0; j < sample;j++){
		    inputs[j] =generate_uniform_real(m, M);
			fprintf(file, "%f ", inputs[j]);
		}
		fclose(file);
		sprintf(filePath, "%s/Scenario%dTable.txt", dirPath, i + 1);
		file = fopen(filePath, "a");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		fprintf(file, "| Uniform Reals  | %-11.2f | %-18.2f |\n", calculate_mean(inputs, sample), calculate_std_dev(inputs, sample, calculate_mean(inputs, sample)));
		fclose(file);
		
		sprintf(filePath, "%s/normal_integers.txt", dirPath);
		file = fopen(filePath, "w");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		for(int j = 0; j < sample;j++){
		    inputs[j] =generate_normal_integer(mu, sigma);
			fprintf(file, "%d ", inputs[j]);
		}
		fclose(file);
		sprintf(filePath, "%s/Scenario%dTable.txt", dirPath, i + 1);
		file = fopen(filePath, "a");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		fprintf(file, "| Normal Ints    | %-11.2f | %-18.2f |\n", calculate_mean(inputs, sample), calculate_std_dev(inputs, sample, calculate_mean(inputs, sample)));
		fclose(file);
		
		sprintf(filePath, "%s/normal_real_number.txt", dirPath);
		file = fopen(filePath, "w");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		for(int j = 0; j < sample;j++){
		    inputs[j] =generate_normal_integer(mu, sigma);
			fprintf(file, "%f ", inputs[j]);
		}
		fclose(file);
		sprintf(filePath, "%s/Scenario%dTable.txt", dirPath, i + 1);
		file = fopen(filePath, "a");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		fprintf(file, "| Normal Reals   | %-11.2f | %-18.2f |\n", calculate_mean(inputs, sample), calculate_std_dev(inputs, sample, calculate_mean(inputs, sample)));
		fclose(file);
		
		sprintf(filePath, "%s/truncated_normal_integers.txt", dirPath);
		file = fopen(filePath, "w");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		for(int j = 0; j < sample;j++){
		    inputs[j] =generate_truncated_normal_integer(m, M, mu, sigma);
			fprintf(file, "%d ", inputs[j]);
		}
		fclose(file);
		sprintf(filePath, "%s/Scenario%dTable.txt", dirPath, i + 1);
		file = fopen(filePath, "a");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		fprintf(file, "| Truncated Ints | %-11.2f | %-18.2f |\n", calculate_mean(inputs, sample), calculate_std_dev(inputs, sample, calculate_mean(inputs, sample)));
		fclose(file);
		
		sprintf(filePath, "%s/truncated_normal_real_number.txt", dirPath);
		file = fopen(filePath, "w");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		for(int j = 0; j < sample;j++){
		    inputs[j] =generate_truncated_normal_real(m, M, mu, sigma);
			fprintf(file, "%f ", inputs[j]);
		}
		fclose(file);
		sprintf(filePath, "%s/Scenario%dTable.txt", dirPath, i + 1);
		file = fopen(filePath, "a");
		if (!file) {
			perror("Error opening file");
			return 1;
		}
		fprintf(file, "| Truncated Real | %-11.2f | %-18.2f |\n", calculate_mean(inputs, sample), calculate_std_dev(inputs, sample, calculate_mean(inputs, sample)));
	
		for(int j = 0; j < 53; j++){fprintf(file, "-");}
		fclose(file);
	}
	return 0;
}

int create_directory(const char* path) {
    mkdir(path, 0777);
	return 0;
}


int generate_uniform_integer(double m, double M)
{
    return rand()%((int)M-(int)m+1) +m;
}

double generate_uniform_real(double m, double M)
{
    return frand()*(M-m) +m;
}

int generate_normal_integer(double mu, double sigma)
{
    return (nrand()*sigma) +mu;
}

double generate_normal_real(double mu, double sigma)
{
        return (nrand()*sigma) +mu;
}

int generate_truncated_normal_integer(double m, double M, double mu, double
sigma)
{
    double truncated_int;
    do 
    {
        truncated_int = (nrand()*sigma) +mu;
    } while (truncated_int < m || truncated_int > M);
    return (int)truncated_int;
}

double generate_truncated_normal_real(double m, double M, double mu, double
sigma)
{
    double truncated_real;
    do 
    {
        truncated_real = (nrand()*sigma) +mu;
    } while (truncated_real < m || truncated_real > M);
    return truncated_real;
}	

double calculate_std_dev(double* data, int n, double mean)
{
    double stdInter = 0;
    for (int i = 0; i < n; i++) 
    {
        stdInter = stdInter+pow((data[i]-mean), 2);
    }
    return sqrt((stdInter)/(n-1)); 
}

double calculate_mean(double* data, int n)
{
    double meanInter = 0;
    for (int i = 0; i < n; i++) 
    {
        meanInter = meanInter+data[i];
    }
    return (meanInter/n);
}
	
	
