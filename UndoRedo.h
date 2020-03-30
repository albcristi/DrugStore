#pragma once
#include "DynamicArray.h"
#include "Medicine.h"

typedef struct {
	DynamicArr *elements[50];
	int size;
	int capacity;
	int currentUndo;
	int currentRedo;
}struc_undoRedo;

struc_undoRedo* createUndoRedo();

void destroyUndoRedo(struc_undoRedo*);

void addUndoRedo(struc_undoRedo*, DynamicArr*);

