#include "QuickStats.h"

QuickStats stats;

// Function to shift all elements in an array, discard the oldest one and add a new one instead.

void setup_speed_array (float array[], int array_size, float speed) {

	for (int i = 0; i < array_size; i ++) {
		array[i] = speed;
	}
}

void rotate_array(float param[], int param_size) {

	for (int i = param_size - 1; i > 0; i--) {
		param[i] = param[i-1];
	}
	param[0] = 0;
}

void enqueue_and_rotate_array(float param[], int param_size, float element) {
	rotate_array(param, param_size);
	param[0] = element;
}

float array_average(float array[], int array_size) {

	float sum = 0.0;

	for (int i = 0; i < array_size; i++) {
		sum = sum + array[i];
	}

	return float(sum / array_size);
}

void print_array(float param[], int param_size) {

	for (int j = 0; j < param_size; j++) {
		Serial.print(param[j]); Serial.print(" ");
	}

	Serial.println();
}

// Used to predict the speed that will reach the system in n loops
// We use the "resistant line" statistical method (droite robuste de Tukey ou methode mediane-mediane)
float compute_statistics(float param[], int param_size, int num_loops) {
	// We will have a line that goes by :
	// y = a * x + b

	// if there are less than 3 values, it makes no sense
	if (param_size < 3) {
		return param[param_size - 1];
	}

	// We split the values in 3 domains
	int first_part_index = 0;
	int second_part_index = param_size / 3;
	int third_part_index = param_size * 2 / 3;

	// We make three corresponding arrays
	float first_part_array[second_part_index - first_part_index];
	float second_part_array[third_part_index - second_part_index];
	float third_part_array[param_size - third_part_index];

	int j = 0;
	for (int i = first_part_index; i < second_part_index; i++) {
		first_part_array[j] = param[i];
		j++;
	}

	j = 0;
	for (int i = second_part_index; i < third_part_index; i++) {
		second_part_array[j] = param[i];
		j++;
	}

	j = 0;
	for (int i = third_part_index; i < param_size; i++) {
		third_part_array[j] = param[i];
		j++;
	}

	// We calculate the median for each array
	float first_part_median_y = stats.median(first_part_array, (second_part_index - first_part_index));
	float second_part_median_y = stats.median(second_part_array, (third_part_index - second_part_index));
	float third_part_median_y = stats.median(third_part_array, (param_size - third_part_index));

	// It's easy to calculate the median for the time scale
	// but instead we're going to cheat by using the mean
	float first_part_median_x = (first_part_index + second_part_index) / 2.0;
	float second_part_median_x = (second_part_index + third_part_index) / 2.0;
	float third_part_median_x = (third_part_index + param_size) / 2.0;

	// we calculate statistical_slope and b
	statistical_slope = (third_part_median_y - first_part_median_y) / (third_part_median_x - first_part_median_x);

	float sumY = first_part_median_y + second_part_median_y + third_part_median_y;
	float sumX = first_part_median_x + second_part_median_x + third_part_median_x;

	float b = (sumY - statistical_slope * sumX) / 3;

	// We now have our resistant line in order to predict the next speed, or the speed in num_loops
	// WARNING : keep in mind the list is in reverse chronological order
	// (the first element is the most recent)
	// so if we want to anticipate the future, we need to go backward !
	statistical_slope = - statistical_slope;
	next_speed = ( statistical_slope * (1 - num_loops) + b);


}