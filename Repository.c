#include "Repository.h"



Repository * createRepository(int(*compareMedicines)(Element, Element), void(*destroyMedicine)(Element), Element(*copyMedicine)(Element))
{
	//creates a repository
	Repository *repo;
	repo = malloc(sizeof(Repository));
	repo->compareMedicines = compareMedicines;
	repo->copyMedicine = copyMedicine;
	repo->destroyMedicine = destroyMedicine;
	repo->content = createArray(2);
	return repo;
}


void destroyRepository(Repository *Repo) {
	//function that destroys the repository
	destroyArray(Repo->content, Repo->destroyMedicine);
	free(Repo);
}

void addMedicineRepo(Repository *repo, Element *med,float(*getQuantity)(Element*)) {
	//this function adds a new medicine in the
	//repository
	int position;
	position = isInArray(repo->content, med,compareMedicines);
	if (position > -1) {
		//we have the medicine in the array
		//we only have to update the quantity
		//DynamicArr ar[1000];
		float quant;
		quant = returnQuantity(repo->content, position, getQuantity);
		increaseQuantity(med, quant);
		removeElementFromDynamicArr(repo->content, med, compareMedicines,destroyMedicine);
		addElement(repo->content, med, repo->copyMedicine);

	}
	else {
		//its a new medicine and it has to be added
		addElement(repo->content, med, repo->copyMedicine);
	}
}

int removeMedicineRepo(Repository* repo, Element* med) {
	//this function will remove an medicine from the 
	//repository. Ret 1 --> element deleted
	int initialSize;
	initialSize = getSize(repo->content);
	removeElementFromDynamicArr(repo->content, med, compareMedicines,destroyMedicine);
    if (initialSize != getSize(repo->content))
		return 1;
	return 0;
}


int updateMedicineRepo(Repository* repo, Element* old, Element* newE) {
	//this function will replace an medicine -old- with another one -newE-
	//if the acction will be a success 1 is returned, else --> 0
	int positonOld, posNew;
	positonOld = isInArray(repo->content, old, compareMedicines);
	
	if (positonOld == -1) {
		//we can not replace the medicine
        return 0;
	}
	 
	//check if we already have this item in the repo

	posNew = isInArray(repo->content, newE, compareMedicines);

	if (posNew != -1) {
		//means that we have a registration of the medicine
		return 0;
	}

	removeMedicineRepo(repo, old);
	addMedicineRepo(repo, newE,getQuantity);

	return 1;
}