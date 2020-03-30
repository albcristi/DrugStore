#pragma once


typedef struct {
	//medicine struct
	char *name;
	int quantity;
	float price, concentration;
}Medicine;

Medicine* createMedicine(char*, int, float, float);

void destroyMedicine(Medicine*);

int compareMedicines(Medicine*, Medicine*);

Medicine* copyMedicine(Medicine*);

float getQuantity(Medicine*);

void increaseQuantity(Medicine*,float);

char* getName(Medicine*);

int stringMatch(char*, char*);