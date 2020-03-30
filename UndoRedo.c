#include "UndoRedo.h"


struc_undoRedo * createUndoRedo() {
	struc_undoRedo *arr;
	int i;
	arr = malloc(sizeof(struc_undoRedo));
	arr->capacity = 50;
	for (i = 0; i < 50; i++)
		arr->elements[i] = createArray(50);
	arr->currentRedo = 1;
	arr->currentUndo = -1;
	arr->size = 0;
	return arr;
}

void destroyUndoRedo(struc_undoRedo *arr) {
	int i;
	for (i = 0; i < 50; i++)
		destroyArray(arr->elements[i], destroyMedicine);
	free(arr);
}


void addUndoRedo(struc_undoRedo *arr, DynamicArr *medi) {
	copyArray(medi, arr->elements[arr->size],copyMedicine);
	arr->size++;
	arr->currentRedo = arr->size-1;
	arr->currentUndo = arr->size - 2;
}
