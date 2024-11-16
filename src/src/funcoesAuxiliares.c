#include <string.h>
#include <stdlib.h>
#include "funcoesAuxiliares.h"

Reg* criarRegistro(const char* nome, const char* especie, const char* habitat,
                    const char* dieta, const char* tipo, const int populacao) {
    Reg* novoRegistro = (Reg*)malloc(sizeof(Reg));
    strncpy(novoRegistro->data.name, nome, MAX_STRING_SIZE);
    strncpy(novoRegistro->data.species, especie, MAX_STRING_SIZE);
    strncpy(novoRegistro->data.habitat, habitat, MAX_STRING_SIZE);
    strncpy(novoRegistro->data.diet, dieta, MAX_STRING_SIZE);
    strncpy(novoRegistro->data.type, tipo, MAX_STRING_SIZE);
    novoRegistro->data.population = populacao;
    return novoRegistro;
}

int readVariableFields(char* ptrStr, char *ptrDest)
{
    char strBuf[MAX_STRING_SIZE]; //Buffer to hold the extracted string
    int i;

    //Separates the first field read from the rest
    for(i = 0; ; i++) //Loop through the input string
    {
        if(*ptrStr == '#' || *ptrStr == '\0') //Stop if a '#' or end of string is encountered
        {
            strBuf[i] = '\0'; //Null-terminate the buffer
            break;
        }
        strBuf[i] = *ptrStr; //Copy the current character to the buffer
        ptrStr++; //Move to the next character
    }
    strcpy(ptrDest, strBuf); //Copy the buffer content to the destination string
    
    return i+1; // Return the number of characters read, including the terminator
}

int readRegister(FILE *fp, Reg *regPtr)
{
    char regBuff[REGISTER_SIZE], *ptrStr;

    if(fread(&(regPtr->removed), sizeof(char), 1, fp)<=0) //If 'fread' returns 0 (EOF), the register was not found
        return 2; //returns
    if(regPtr->removed == '1') //If the register was logically removed
        return -1; //returns
    //If the register was found, read the rest of the data
    fread(&(regPtr->chaining), sizeof(int), 1 ,fp);
    fread(&(regPtr->data.population), sizeof(int), 1, fp);
    fread(&(regPtr->data.size), sizeof(float), 1, fp);
    fread(regPtr->data.unitMeasure, sizeof(char), 1, fp);
    fread(&(regPtr->data.velocity), sizeof(int), 1, fp);

    //Read the data after the non-variable fields (i.e., all the variable fields) to a buffer
    fread(regBuff, REGISTER_SIZE-18, 1, fp);
    regBuff[strlen(regBuff)] = '\0'; //Places a '/0' in the end
    ptrStr = regBuff; //The beginning of the buffer string is copied to 'ptrStr'

    //On each call of the functions 'readVariableFields', stores the read field and increments the pointer (jumping to the next field)
    ptrStr += readVariableFields(ptrStr, regPtr->data.name);
    ptrStr += readVariableFields(ptrStr, regPtr->data.species);
    ptrStr += readVariableFields(ptrStr, regPtr->data.habitat);
    ptrStr += readVariableFields(ptrStr, regPtr->data.type);
    ptrStr += readVariableFields(ptrStr, regPtr->data.diet);
    readVariableFields(ptrStr, regPtr->data.food); //last field, no need to increment pointer

    return 0;
}

int readRegisterSaveVertex(FILE *fp, Reg* NewReg, int RRN)
{
    Reg reg;
    int ret;

    fseek(fp, DISK_PAGE_SIZE, SEEK_SET); //Jumps the first page (header)
    fseek(fp, RRN*REGISTER_SIZE, SEEK_CUR); //Moves the pointer to the register position

    //Read the data and stores in 'reg'
    ret = readRegister(fp, &reg);
    if(ret == -1 || ret == 2) //If 'readRegister' returns a error, returns
        return ret;
    
    NewReg = criarRegistro(reg.data.name, reg.data.species, reg.data.habitat, reg.data.diet, reg.data.type, reg.data.population);

    printf("Nome: %s\n", NewReg->data.name);
    printf("Especie: %s\n", NewReg->data.species);
    if(strlen(NewReg->data.type)>0)
        printf("Tipo: %s\n", NewReg->data.type);
    printf("Dieta: %s\n", NewReg->data.diet);
    if(strlen(NewReg->data.habitat)>0)
        printf("Lugar que habitava: %s\n", NewReg->data.habitat);
    printf("Populacao: %d\n", NewReg->data.population);
    printf("Comida: %s", reg.data.food);
    printf("\n");

    return 0;
}

void removequotes(char *str)
{
    int size;

    //Removes newline '\n' and carriage return '\r' characters if present.
    if(strchr(str, '\n') != NULL)
        str[strcspn(str, "\n")] = '\0';
    if(strchr(str, '\r') != NULL)
        str[strcspn(str, "\r")] = '\0';

    //Checks if the first character is a quote (ASCII 34), removes the starting and ending quotes from the string.
    if(str[0] == 34)
    {
        size = strlen(str) - 2; //Calculates the new size of the string without the quotes
        memmove(str, str + 1, size); //Moves the string 1 position to the left
        str[size] = '\0'; //Inserts the null terminator at the new end of the string
    }
    return;
}

void printFileErrorMessage() {
    printf("Falha no processamento do arquivo.\n");
}

void printRegNotFoundMessage() {
    printf("Registro inexistente.\n");
}

int checkFileExistence(FILE* fp) {
    //Checks if the file pointer is NULL (unallocated, etc)
    if (fp == NULL) {
        printFileErrorMessage();
        return -1;
    } 

    return 0;
}

int checkFileConsistency(FILE* fp) {
    char status;

    fseek(fp, 0, SEEK_SET); //Goes to the beginning of the file
    fread(&status, sizeof(char), 1, fp); //Reads the status field (1 char)
    
    if(status != '1') {
        printFileErrorMessage();
        return -1;
    }

    return 0;
}