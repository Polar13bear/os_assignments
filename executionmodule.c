#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MEMORY_ROWS 100
#define MEMORY_COLS 4
#define GREEN "\x1b[92m"
#define WHITE "\e[0;37m"

char memory[MEMORY_ROWS][MEMORY_COLS + 1];
char outputBuffer[1000];
int outputIndex = 0;

void initializeSystem() {
    memset(memory, '*', sizeof(memory)); 
    for(int i = 0; i < MEMORY_ROWS; i++) {
        memory[i][MEMORY_COLS] = '\0';
    }
    outputBuffer[0] = '\0';

    printf(GREEN "----------" WHITE "SYSTEM INITIALIZATION" GREEN "----------" WHITE "\n");
    printf("External Memory:\n");
    for(int i = 0; i < 100; i++) {
        printf("Address %02d: ", i);
        for(int j = 0; j < 4; j++) {
            printf("%c ", memory[i][j]);
        }
        printf("\n");
    }

    printf("\nToggle Flag (C): %c\n", '*');
    printf("General Purpose Register (R): %s\n", "****");
    printf("Instruction Register (IR): %s\n", "****");
    printf("Instruction Counter (IC): %c\n", '*');
}

void loadProgram(FILE *inputFile) {
    char line[256];
    int memoryIndex = 0;
    int isDataSection = 0;
    char dataLines[10][256] = {0};
    int dataLineCount = 0;

    while (fgets(line, sizeof(line), inputFile)) { 
        if (strncmp(line, "$DTA", 4) == 0) { 
            isDataSection = 1;
        } else if (strncmp(line, "$END", 4) == 0) {
            break;
        } else if (isDataSection) {
            line[strcspn(line, "\n")] = '\0';
            strcpy(dataLines[dataLineCount], line);
            dataLineCount++;
        }
    }

    rewind(inputFile);
    isDataSection = 0;
    memoryIndex = 0;
    int currentDataLine = 0;

    while (fgets(line, sizeof(line), inputFile)) { 
        if (strncmp(line, "$AMJ", 4) == 0) {
            memoryIndex = 0;
            isDataSection = 0;
        } else if (strncmp(line, "$DTA", 4) == 0) {
            isDataSection = 1;
        } else if (strncmp(line, "$END", 4) == 0) {
            break;
        } else if (!isDataSection) {
            for (int i = 0; i < strlen(line) && line[i] != '\n'; i += 4) {
                if (memoryIndex >= 20) break;

                strncpy(memory[memoryIndex], &line[i], MEMORY_COLS);
                
                if (memory[memoryIndex][0] == 'G' && memory[memoryIndex][1] == 'D') {
                    int address = (memory[memoryIndex][2] - '0') * 10 + 
                                 (memory[memoryIndex][3] - '0');
                    
                    if (currentDataLine < dataLineCount) {
                        char *data = dataLines[currentDataLine];
                        int dataLength = strlen(data);
                        int memPos = address;
                        
                        for (int j = 0; j < dataLength; j += 4) {
                            if (memPos >= MEMORY_ROWS) break;
                            
                            int charsToCopy = (dataLength - j) > 4 ? 4 : (dataLength - j);
                            strncpy(memory[memPos], &data[j], charsToCopy);
                            
                            for (int k = charsToCopy; k < 4; k++) {
                                memory[memPos][k] = ' ';
                            }
                            memory[memPos][4] = '\0';
                            memPos++;
                        }
                        currentDataLine++;
                    }
                }
                memoryIndex++;
            }
        }
    }
}

void displayMemory() {
    printf(GREEN "\n----------" WHITE "LOADED MEMORY" GREEN "----------\n" WHITE);
    for (int i = 0; i < MEMORY_ROWS; i++) {
        if (strncmp(memory[i], "****", 4) != 0) {
            printf("Address %02d: %.4s\n", i, memory[i]);
        }
    }
}

void executeProgram() {
    char instructionRegister[5] = {0};
    char generalRegister[5] = {0};
    int instructionCounter = 0;
    int toggleFlag = 0;
    int haltFlag = 0;

    printf(GREEN "\n----------" WHITE "PROGRAM EXECUTION" GREEN "----------\n" WHITE);

    while (!haltFlag && instructionCounter < 20) {
        strncpy(instructionRegister, memory[instructionCounter], 4);
        instructionRegister[4] = '\0';
        printf("Executing Instruction at %02d: %.4s\n", instructionCounter, instructionRegister);
        instructionCounter++;

        char opcode[3] = {instructionRegister[0], instructionRegister[1], '\0'};
        int address = (instructionRegister[2] - '0') * 10 + (instructionRegister[3] - '0');

        if (strcmp(opcode, "PD") == 0) { 
            printf("PD: Printing data from block starting at %02d: ", address);
            
            int memPos = address; 
            char dataBlock[256] = {0};
            int dataPos = 0; 
            
            while (memPos < MEMORY_ROWS) {
                if (strncmp(memory[memPos], "****", 4) == 0) break;
                
                for (int i = 0; i < 4; i++) {
                    if (memory[memPos][i] != ' ' && memory[memPos][i] != '*') {
                        dataBlock[dataPos++] = memory[memPos][i];
                    }
                }
                memPos++;
            }
            dataBlock[dataPos] = '\0';
            
            int len = strlen(dataBlock);
            while (len > 0 && isspace(dataBlock[len - 1])) {
                dataBlock[--len] = '\0';
            }
            
            printf("%s\n", dataBlock);
            
            if (outputIndex > 0) {
                strcat(outputBuffer, "\n");
            }
            strcat(outputBuffer, dataBlock);
            outputIndex++;
        }
        else if (strcmp(opcode, "SR") == 0) {
            strncpy(memory[address], generalRegister, 4);
            printf("SR: Stored Register '%.4s' into memory at address %02d\n", generalRegister, address);
        }
        else if (strcmp(opcode, "LR") == 0) { 
            strncpy(generalRegister, memory[address], 4);
            generalRegister[4] = '\0';
            printf("LR: Loaded '%.4s' from address %02d into Register\n", generalRegister, address);
        }
        else if (strcmp(opcode, "CR") == 0) { 
            if (strncmp(generalRegister, memory[address], 4) == 0) {
                toggleFlag = 1;
                printf("CR: Register '%.4s' equals Memory '%.4s' at address %02d -> Toggle set to 1\n", generalRegister, memory[address], address);
            } else {
                toggleFlag = 0;
                printf("CR: Register '%.4s' does not equal Memory '%.4s' at address %02d -> Toggle set to 0\n", generalRegister, memory[address], address);
            }
        }
        else if (strcmp(opcode, "BT") == 0) { 
            if (toggleFlag == 1) {
                instructionCounter = address;
                printf("BT: Toggle is 1 -> Branching to address %02d\n", instructionCounter);
            } else {
                printf("BT: Toggle is 0 -> No Branch\n");
            }
        }
        else if (strncmp(instructionRegister, "H", 1) == 0) { 
            printf("Halt encountered. Stopping execution.\n");
            haltFlag = 1;
        }
        else if (strcmp(opcode, "GD") == 0) { 
            printf("GD: Data already loaded during initialization\n");
        }
        else {
            printf("Unknown instruction: %.4s\n", instructionRegister);
        }
    }

    printf(GREEN "\n----------" WHITE "FINAL OUTPUT" GREEN "----------\n" WHITE);
    printf("%s\n", outputBuffer);

    printf(GREEN "\n----------" WHITE "EXECUTION COMPLETE" GREEN "----------\n" WHITE);
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    initializeSystem();
    loadProgram(inputFile);
    fclose(inputFile);
    displayMemory();
    executeProgram();

    return 0;
}
 

