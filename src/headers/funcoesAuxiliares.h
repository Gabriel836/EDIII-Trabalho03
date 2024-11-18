#ifndef __AUXILIARES__
#define __AUXILIARES__

#define MAX_LINE_CSV 501
#define MAX_STRING_SIZE 150
#define DISK_PAGE_SIZE 1600
#define REGISTER_SIZE 160
#define N_DELIMITERS 6

#include <stdio.h>
#include "grafo.h"

/// @brief Type that represents the fixed and variable data of a species.
typedef struct dino {
    int population;
    int velocity;
    float size;
    char unitMeasure[2];
    char name[MAX_STRING_SIZE];
    char species[MAX_STRING_SIZE];
    char habitat[MAX_STRING_SIZE];
    char type[MAX_STRING_SIZE];
    char diet[MAX_STRING_SIZE];
    char food[MAX_STRING_SIZE];
} Dino;

/// @brief Type that represents the register data.
typedef struct reg {
    char removed;
    int chaining;
    Dino data;
} Reg;

Reg* criarRegistro(char* nome, char* especie, char* habitat, char* dieta, char* food, char* tipo, const int populacao);

/// @brief Reads a single variable field and stores in a destination string. Reads a single field per call.
/// @param ptrStr Pointer (string) with all/the rest of the variable fields to read.
/// @param ptrDest Destination string (where the separate field will be stored).
/// @return Returns the length of the string read.
int readVariableFields(char* ptrStr, char *ptrDest);

/// @brief Read the data of a register in the file (assumes that the file pointer is positioned) and stores in a register.
/// @param fp Pointer to a binary file (open in reading mode).
/// @param regPtr Pointer to a record to be filled with data.
/// @return Returns -1 if register was removed, 2 if the record was not found in the file (reached EOF) and 0 if it was read.
int readRegister(FILE *fp, Reg *regPtr);

/// @brief prints all the data fields of the register.
/// @param fp Pointer to a binary file (open in reading mode).
/// @param RRN RRN of the register to be printed.
/// @return Returns -1 if register was removed, 2 if the record was not found in the file (reached EOF) and 0 if it was printed;
int readRegisterSaveVertex(FILE *fp, Reg** NewReg, int RRN);

/// @brief Prints a error message warning that there's a error with the sent file. 
void printFileErrorMessage();

/// @brief Prints a message warning that the search found no registers.
void printRegNotFoundMessage();

/// @brief Check if the file pointer exists.
/// @param fp Pointer to a binary file (open in reading mode).
/// @return Return -1 if the file exists and 0 otherwise.
int checkFileExistence(FILE* fp);

/// @brief Reads the 'status' field in the file header.
/// @param fp Pointer to a binary file (open in reading mode).
/// @return Return -1 if the file is inconsistent and 0 otherwise.
int checkFileConsistency(FILE* fp);

/// @brief Remove quotes, new-lines and carriage-returns.
/// @param str String that will be manipulated.
void removequotes(char *str);
void imprimirRegistro(Reg* NewReg);

/// @brief Prints graph vertex.
/// @param g Graph pointer
int imprimeVertices(Grafo *g);

#endif