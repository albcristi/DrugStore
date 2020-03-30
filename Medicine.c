#include "Medicine.h"
#include <stdlib.h>
#include <string.h>


Medicine * createMedicine(char* name, int quantity, float price, float concentration) {
	//allocates into the memory a new Medicine 
	Medicine *med;
	med = malloc(sizeof(Medicine));
	med->concentration = concentration;
	med->price = price;
	med->quantity = quantity;
	med->name = malloc((strlen(name) + 1) * sizeof(char));
	strcpy_s(med->name,strlen(name)+1, name);

	return med;
}


void destroyMedicine(Medicine *med) {
	free(med->name);
	free(med);
}



int compareMedicines(Medicine* med1, Medicine* med2) {
	//this function compares 2 separate medicines 
	//returns 1 if the medicines are equal and
	//0 otherwise
	if (strcmp(med1->name, med2->name) != 0)
		return 0;
	else if (med1->concentration != med2->concentration)
		return 0;
	return 1;
}


Medicine * copyMedicine(Medicine* original) {
	//makes a copy of a given medicine 
	Medicine *copy;
	copy = malloc(sizeof(Medicine));
	copy->concentration = original->concentration;
	copy->price = original->price;
	copy->quantity = original->quantity;
	copy->name = malloc(strlen(original->name) + 1);
	strcpy_s(copy->name, strlen(original->name) + 1, original->name);

	return copy;
}

float getQuantity(Medicine* med) {
	return med->quantity;
}

void increaseQuantity(Medicine* med,float quantity) {

	med->quantity += quantity;
}

char* getName(Medicine* med) {
	return med->name;
}

int stringMatch(char str[], char partialStr[]){
	//this function will return 1 if partialStr 
	//can be found in str, 0 otherwise
	if ((strlen(str)) < strlen(partialStr))
		return 0;
	if (strlen(str) == strlen(partialStr)) {
		if (strcmp(str, partialStr) == 0)
			return 1;
		else
			return 0;
	}

	//we have to go through the array
	int i, j, flag;
	char aux[100];
	for (i = 0; i < strlen(str) - strlen(partialStr)+1; i++) {
		flag = 0;
		aux[0] = NULL;
		j = i;
		while (flag<strlen(partialStr)&&j<strlen(str)){
			aux[flag] = str[j];
			j++;
			flag++;
		}
		aux[flag] = NULL;
		if (strcmp(aux, partialStr) == 0)
			return 1;
	}

	return 0;
}