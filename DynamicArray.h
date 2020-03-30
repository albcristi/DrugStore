#pragma once


typedef void* Element;

typedef struct {
	//this is the structure of our 
	//dynamic vector
	Element* elements;
	int size;
	int capacity;

}DynamicArr;


DynamicArr* createArray(int);

void destroyArray(DynamicArr *, void(*remove)(Element));

int getSize(DynamicArr*);

void addElement(DynamicArr*, Element*, Element(*makeCopy)(Element));

int isInArray(DynamicArr*, Element, Element(*compareMedicines)(Element, Element));

void removeElementFromDynamicArr(DynamicArr*, Element,Element(*compareMedicines)(Element,Element));

float returnQuantity(DynamicArr*, int, float(*getQuant)(Element*));

void similarElements(DynamicArr*, DynamicArr*, char*, int(*stringMatch)(char*, char*),char*(*getName)(Element*), Element(*copy)(Element*));

void sortArray(DynamicArr*, char*(*getName)(Element*), void(*destroy)(Element*), Element(*copy)(Element*));

void limitedStock(DynamicArr*, DynamicArr*,float, float(*getQuant)(Element*), Element(*copy)(Element*));

void copyArray(DynamicArr*, DynamicArr*, Element(*makeCopy)(Element));