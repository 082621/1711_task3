int tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    char *endPtr;
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                long val = strtol(ptr, &endPtr, 10);
                if (*endPtr != '\0' || val < 0) {
                    // Not a valid integer or negative number
                    return 1;
                }
                *steps = (int)val;
                return 0;
            }
        }
    }
    return 1; // Return error if any of the tokens are missing
}

