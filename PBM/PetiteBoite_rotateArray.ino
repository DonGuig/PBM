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
