#include "UserInterface.h"
#include <assert.h>
#include <stdio.h>
#include "Medicine.h"
#include "Repository.h"
#include "DynamicArray.h"
#include "UndoRedo.h"


void testFunction() {
	Medicine *med, *copy, *med2;
	DynamicArr * arr;
	Repository *repo;
	//create REPO

	repo = createRepository(compareMedicines, destroyMedicine, copyMedicine);
	arr = createArray(2);
	
	//create medicine
	med = createMedicine("name", 1, 1, 1);

	//make a copy of the medicine
	copy = copyMedicine(med);
	//add an element in the dynamic array
	addElement(arr, med, copyMedicine);
	
	//make sure that the element was introduced in 
	//the array
	assert(isInArray(arr, copy, compareMedicines) > -1);
	//check the size of the array
	assert(getSize(arr) == 1);

	//add the medicine in the repository
	addMedicineRepo(repo, med,getQuantity);

	//create a new medicine and insert it
	//in the repository
	med2 = createMedicine("Paracetamol", 1, 1, 1);
	addMedicineRepo(repo, med2,getQuantity);
	//destroy the allocated memory for the medicine
	destroyMedicine(med2);

	//same with previous
	med2 = createMedicine("Paracetam2", 1, 1, 1);
	addMedicineRepo(repo, med2,getQuantity);
	assert(getSize(repo->content) == 3);
	destroyMedicine(med2);

	//same with previous
	med2 = createMedicine("Paracetam2", 1, 1, 1);
	assert(removeMedicineRepo(repo, med2) == 1);
	assert(getSize(repo->content) == 2);
	destroyMedicine(med2);

	//deallocate the memory allocated for
	//the dynamic array
	destroyArray(arr, destroyMedicine);

	//deallocate the memory used for med
	//and for the copy of the med
	destroyMedicine(med);
	destroyMedicine(copy);

	//deallocate the memory allocated for 
	//the repository
	destroyRepository(repo);
	/*
	//create an undoredo array
	UndoRedo *arrr;
	//allocate memory for the array of type undoRedo
	arrr = createUndoRedo(createRepository(compareMedicines, destroyMedicine, copyMedicine));
	destroyUndoRedo(arrr, destroyRepository); */
	struc_undoRedo *Nebunie;
	Nebunie = createUndoRedo();
	destroyUndoRedo(Nebunie);

}

void mainMenu() {
	printf("1 - Add,Delete or Update a medicine\n");
	printf("2 - Search medicines\n");
	printf("3 - Medicines in a limited stock\n");
	printf("4 - Undo\n");
	printf("5 - Redo\n");
	printf("x - exit\n");
}

void getMainCommand(char command[]) {
	printf("Enter your command\n> ");
	scanf_s("%s", command, sizeof(command));
	printf("\n");
}

void initializeData(Repository *repo) {
	//this function will initialize the array
	//with some data
	Medicine* med;
	med =createMedicine("Paracetamol", 100, 15, 250);
	addMedicineRepo(repo, med, getQuantity);
	destroyMedicine(med);
	
	med = createMedicine("Paracetamol", 40, 15, 500);
	addMedicineRepo(repo, med, getQuantity);
	destroyMedicine(med);

	med = createMedicine("Ospena", 60, 20, 250);
	addMedicineRepo(repo, med, getQuantity);
	destroyMedicine(med);

	med = createMedicine("ACC", 10, 15, 300);
	addMedicineRepo(repo, med, getQuantity);
	destroyMedicine(med);

	med = createMedicine("Nurofen", 100, 20, 450);
	addMedicineRepo(repo, med, getQuantity);
	destroyMedicine(med);

	med = createMedicine("Tussin", 150, 15, 20);
	addMedicineRepo(repo, med, getQuantity);
	destroyMedicine(med);

	med = createMedicine("Rivanol", 40, 15, 100);
	addMedicineRepo(repo, med, getQuantity);
	destroyMedicine(med);

}


Medicine * readMedicine() {
	Medicine *med;
	char name[50];
	int quant;
	float price, conc;
	printf("Enter the name of the medicine:\n> ");
	scanf_s("%s", name, sizeof(name));
	printf("\nConcentration:\n> ");
	scanf_s("%f", &conc);
	printf("\nQuantity:\n> ");
	scanf_s("%d", &quant);
	printf("\nPrice:\n> ");
	scanf_s("%f", &price);
	med = createMedicine(name, quant, price, conc);
	return med;
}

Medicine * readKeys() {
	Medicine *med;
	char name[50];
	float conc;
	printf("Enter the name of the medicine:\n> ");
	scanf_s("%s", name, sizeof(name));
	printf("\nConcentration:\n> ");
	scanf_s("%f", &conc);
	med = createMedicine(name, 0, 0, conc);
	return med;
}

void menuFeature1() {
	printf("\nAVAILABLE COMMANDS:\n");
	printf("1 - Add a new medicine\n");
	printf("2 - Remove a medicine \n");
	printf("3 - Update a medicine with \n another medicine \n");
	printf("x - back to main menu\n");
}

void printMedicine(Medicine *med) {
	printf("\nName: %s\n", med->name);
	printf("Quantity: %d\n", med->quantity);
	printf("Concentration: %6.2f \n", med->concentration);
	printf("Price: %6.2f \n\n", med->price);
}

void printDynamicArray(DynamicArr *arr) {
	//this function prints the content of arr
	int i;
	for (i = 0; i < arr->size; i++)
		printMedicine(arr->elements[i]);
}



int feature1(Repository *repo, struc_undoRedo *undo) {
	//add, delete or update a medicine
	char command[50];
	int flag = 0;

	while (1) {
		menuFeature1();
		getMainCommand(command);
		if (strcmp(command, "x") == 0)
			return 0;
		else if (strcmp(command, "1") == 0) {
			//add a new medicine
			Medicine *med;
			med = readMedicine();
			addMedicineRepo(repo, med,getQuantity);
			addUndoRedo(undo, repo->content);
			destroyMedicine(med);
		}
		else if (strcmp(command, "2") == 0) {
			//delete a medicine
			int ok = 0;
			Medicine *med;
			med = readKeys();
			ok = removeMedicineRepo(repo, med);
			if (ok == 0)
				printf("\nNo medicine registered like the provided data\n");
			else
				printf("\mMedicine deleted\n");
			destroyMedicine(med);
			addUndoRedo(undo, repo->content);
			flag = 1;
		}
		else if (strcmp(command,"3")==0){
			Medicine *med1, *med2;
			med1 = readKeys();
			printf("Enter the new medicine\n");
			med2 = readMedicine();
			int situation;
			situation = updateMedicineRepo(repo, med1, med2);

			if (situation == 0)
				printf("Operation failed...Make sure that the data that you provide is valid\n");
			else
				printf("Medicine updated\n");
			destroyMedicine(med1);
			destroyMedicine(med2);
			addUndoRedo(undo, repo->content);
			flag = 1;
		}
		else if (flag == 0)
			printf("\n INVALID COMMAND!\n");
	}

	
}

void feature2(Repository *repo) {
	//search for an element
	char partial[100];
	printf("Enter the partial name of the medicine\n");
	_fgetchar();
	fgets(partial, 99, stdin);
	
	if (strcmp(partial, "\n") == 0) {
		DynamicArr *partialArr;
		int i;
		partialArr = createArray(2);
		for (i = 0; i < repo->content->size; i++)
			addElement(partialArr, repo->content->elements[i], copyMedicine);
		printf("RESULT:\n");
		sortArray(partialArr, getName, destroyMedicine, copyMedicine);
		printDynamicArray(partialArr);
		destroyArray(partialArr,destroyMedicine);
	}
	else {
		
		partial[strlen(partial) - 1] = NULL;
	
		DynamicArr *ara;
	    ara = createArray(2);
		similarElements(repo->content, ara, partial, stringMatch, getName, copyMedicine);
		//printDynamicArray(ara);
		sortArray(ara, getName, destroyMedicine, copyMedicine);
		printDynamicArray(ara);
		destroyArray(ara,destroyMedicine);
	}
}

void feature3(Repository *repo) {
	float quant;
	printf("\n Enter the maximum quantity:\n> ");
	scanf_s("%f", &quant);
	printf("\n");
	DynamicArr *tempArray;
	tempArray = createArray(2);
	limitedStock(repo->content, tempArray, quant, getQuantity, copyMedicine);
	if (tempArray->size == 0)
		printf("No results!\n");
	else
		printDynamicArray(tempArray);
	destroyArray(tempArray,destroyMedicine);
}

void feature4(Repository *repo, struc_undoRedo *undo) {
	if (undo->currentUndo < 0)
		printf("\nNo more undos!\n");
	else {
		
		//destroyRepository(repo);
		//repo = createRepository(compareMedicines,destroyMedicine,copyMedicine);
		int i;
		//DynamicArr *arr;
		//r = createArray(50);
		//copyArray(undo->elements[undo->currentUndo], arr,copyMedicine);
		//printDynamicArray(arr);
		repo->content = undo->elements[undo->currentUndo];
		//destroyArray(arr,destroyMedicine);
		undo->currentUndo--;
		undo->currentRedo = undo->currentUndo + 1;
	}
}

void feature5(Repository *Repo, struc_undoRedo *undo) {
	if (undo->currentRedo >= undo->size)
		printf("No more redos!\n");
	else {
		Repo->content = undo->elements[undo->currentRedo-1];
		undo->currentRedo++;
		undo->currentUndo = undo->currentRedo - 1;
	}
}

int mainExe() {
	//this function points to the main-menu
	char command[50];
	Repository* repo;
	struc_undoRedo *undo;
	undo = createUndoRedo();
	int flag = 0;
	repo = createRepository(compareMedicines, destroyMedicine, copyMedicine);
	initializeData(repo);
	addUndoRedo(undo, repo->content);
	undo->currentUndo = -1;
	undo->currentRedo = 1;
	while (1) {
		mainMenu();
		getMainCommand(command);
		int flag = 0;
		if (strcmp(command, "x") == 0) {
			destroyRepository(repo);
			destroyUndoRedo(undo);
			return 0;
		}
		else if (strcmp(command, "1") == 0) {
			flag = 1;
			feature1(repo,undo);
			printf("\n%d\n", undo->size);
		}
		else if (strcmp(command, "2") == 0) {
			flag = 1;
			feature2(repo);
		}
		else if (strcmp(command, "3") == 0) {
			flag = 1;
			feature3(repo);
		}
		else if (strcmp(command, "4") == 0) {
			flag = 1;
			/*
			printf("SIZE: %d, UNDOP:%d\n", undo->size, undo->currentUndo);
			printf("ARRAYS:\n");
			int i;
			for (i = 0; i < undo->size; i++) {
				printf("SIZE: %d, UNDOP:%d\n", undo->size, undo->currentUndo);
				printDynamicArray(undo->elements[i]);
			}*/
			feature4(repo, undo);

		}
		else if (strcmp(command, "5") == 0) {
			feature5(repo,undo);
			flag = 1;
		}
		else if (flag == 0)
			printf("\n INVALID COMMAND!\n");
	}
}