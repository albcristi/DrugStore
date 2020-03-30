#include "DynamicArray.h"
#include <stdlib.h>

DynamicArr * createArray(int capacity) {
	//this function will create a dynamically allocated
	// array of a given capacity
	DynamicArr *vector;
	//allocate memory
	vector = malloc(sizeof(DynamicArr));
	vector->size = 0;
	vector->capacity = capacity;
	vector->elements = malloc(capacity * sizeof(Element));
	//return the dynamic array
	return vector;

}


void destroyArray(DynamicArr *vector,void(*remove)(Element)){
	//destroy the dynamic array
	int i;
	for (i = 0; i< vector->size; i++) {
		remove(vector->elements[i]);
	}
	free(vector->elements);
	free(vector);
}

int getSize(DynamicArr *arr) {
	//returns the size of the array
	return arr->size;
}

void resizeArr(DynamicArr *arr) {
	//this function will increase the 
	//capacity of our dynamic vector
	int i;
	Element *newElements;
	//increase the capacity
	arr->capacity *= 2;

	newElements = malloc(arr->capacity * sizeof(Element));
	for (i = 0; i < arr->size; i++) {
		newElements[i] = arr->elements[i];
	}
	free(arr->elements);
	arr->elements = newElements;
}

void addElement(DynamicArr* vector, Element medicine, Element(*makeCopy)(Element)) {
	//this function adds a new element into the array
	Element *copy;
	copy = makeCopy(medicine);

	//check to see if there is still enough space
	//in our vector
	if (vector->size == vector->capacity) {
		resizeArr(vector);
	}
	vector->elements[vector->size] = copy;
	vector->size++;
}

int isInArray(DynamicArr *arr, Element lookFor, Element(*compareMedicines)(Element, Element))
{
	//checks if a medicine is already in the array
	int i;
	for (i = 0; i < arr->size; i++) {
		if (compareMedicines(lookFor, arr->elements[i]) == 1) {
			return i;
		}
	}
	return -1;
}

void removeElementFromDynamicArr(DynamicArr *arr, Element med, Element(*compareMedicines)(Element, Element),Element(*removeMed)(Element)) {
	//this function removes an element from the dynamic array
	int i, position;
	position = isInArray(arr, med, compareMedicines);
	if (position != -1) {
		//it means that the element is in the array
		removeMed(arr->elements[position]);
		for (i = position; i < arr->size - 1; i++) {
			arr->elements[i] = arr->elements[i + 1];
		}
		arr->size--;
	}
}

float returnQuantity(DynamicArr* arr, int position,float(*getQuant)(Element*)) {
	//returns the value from a given position
	float quant;
	quant = getQuant(arr->elements[position]);
	return quant;
}

void similarElements(DynamicArr *original, DynamicArr * partialArray, char *partString, int(*stringMatch)(char *, char *),char*(*getName)(Element*), Element(*copy)(Element*))
{
	int i;
	for (i = 0; i < original->size; i++)
		if (stringMatch(getName(original->elements[i]),partString) == 1)
			addElement(partialArray, original->elements[i], copy);
}

void sortArray(DynamicArr *arr, char*(*getName)(Element*),void(*destroy)(Element*),Element(*copy)(Element*)) {
	//this function will sort aplhabetically an array
	//that contains 'objcts' of type Medicine
	Element *aux;
	int i, j;
	for (i = 0; i < arr->size - 1; i++) {
		for (j = i + 1; j < arr ->size; j++) {
			if (strcmp(getName(arr->elements[i]), getName(arr->elements[j])) > 0) {
				aux = arr->elements[i];
				arr->elements[i] = arr->elements[j];
				arr->elements[j] = aux;

			}
		}
	}
}

void limitedStock(DynamicArr *original, DynamicArr *newArr,float maxQuant, float(*getQuant)(Element *),Element(*copy)(Element*)){
	int i;
	for (i = 0; i < original->size; i++)
		if (getQuant(original->elements[i]) <= maxQuant)
			addElement(newArr, original->elements[i], copy);
	
}

void copyArray(DynamicArr *orig, DynamicArr *fake, Element(*makeCopy)(Element)) {
	int i;
	fake->capacity = orig->capacity;
	fake->size = orig->size;
	for (i = 0; i < fake->size; i++) {
		fake->elements[i] = makeCopy(orig->elements[i]);
		
	}
}





