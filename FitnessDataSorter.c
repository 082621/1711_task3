#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
int tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL && strlen(ptr) > 2) {
                *steps = atoi(ptr);
                return 0;
            }
        }
    }
    return 1;
}

void sortFitnessData(FitnessData *data, int count) {
    int swapped;
    for (int i = 0; i < count - 1; i++) {
        swapped = 0;
        for (int j = 0; j < count - i - 1; j++) {
            if (data[j].steps < data[j + 1].steps) > 0) {
                FitnessData temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
}

int main() {
    char filename[100]; 
    printf("Enter Filename: ");
    scanf("%99s", filename); 
    FILE *file = fopen(filename, "r"); 
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    FitnessData data[100]; 
    int count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (tokeniseRecord(line, ',', data[count].date, data[count].time, &data[count].steps) != 0) {
            fprintf(stderr, "Error: Invalid record format\n");
            fclose(file);
            return 1;
        }
        count++;
    }
    sortFitnessData(data, count);
    fclose(file);

    char newFilename[110];
    snprintf(newFilename, sizeof(newFilename), "%s.tsv", filename);
    FILE *newFile = fopen(newFilename, "w"); 
    if (newFile == NULL) {
        perror("Error opening new file");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        fprintf(newFile, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }
    fclose(newFile);
    printf("Data sorted and written to %s\n", newFilename);

    return 0;
    
}
