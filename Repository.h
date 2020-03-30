#pragma once
#include "DynamicArray.h"
#include "Medicine.h"

typedef struct {
	//this is the repository
	DynamicArr *content;
	int(*compareMedicines)(Element, Element);
	void(*destroyMedicine)(Element);
	Element(*copyMedicine)(Element);
}Repository;


Repository* createRepository(int(*compareMedicines)(Element, Element), void(*destroyMedicine)(Element), Element(*copyMedicine)(Element));

void destroyRepository(Repository*);

void addMedicineRepo(Repository*, Element*,float(*getQuant)(Element*));

int removeMedicineRepo(Repository*, Element*);

int updateMedicineRepo(Repository*, Element*, Element*);