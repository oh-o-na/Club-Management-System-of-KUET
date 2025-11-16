#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin_events.h" 
#include "admin_utils.h"  

void createEvent(const char *clubName) {
    Event newEvent;

    char eventFilePath[100];
    snprintf(eventFilePath, sizeof(eventFilePath), "%s_events.txt", clubName);

    printf("--- Create New Event for %s ---\n", clubName);
    printf("Enter Event Name: ");
    fgets(newEvent.name, sizeof(newEvent.name), stdin);
    clearNewline(newEvent.name);

    printf("Enter 'About' (description): ");
    fgets(newEvent.about, sizeof(newEvent.about), stdin);
    clearNewline(newEvent.about);

    printf("Enter Event Date (e.g., 25-Dec-2025): ");
    fgets(newEvent.date, sizeof(newEvent.date), stdin);
    clearNewline(newEvent.date);

    printf("Enter Event Venue: ");
    fgets(newEvent.venue, sizeof(newEvent.venue), stdin);
    clearNewline(newEvent.venue);

    FILE *file = fopen(eventFilePath, "a");
    if (file == NULL) {
        printf("Error: Could not open events file for %s.\n", clubName);
        return;
    }

    fprintf(file, "%s|%s|%s|%s\n",
            newEvent.name, newEvent.about, newEvent.date, newEvent.venue);

    fclose(file);
    printf("Success: Event '%s' has been created for %s!\n", newEvent.name, clubName);
}

void viewAllEvents(const char *clubName) {
    char eventFilePath[100];
    snprintf(eventFilePath, sizeof(eventFilePath), "%s_events.txt", clubName);
    
    FILE *file = fopen(eventFilePath, "r");
    if (file == NULL) {
        printf("No events found for %s or file cannot be opened.\n", clubName);
        return;
    }
    printf("\n--- All Upcoming Events for %s ---\n", clubName);
    char line[512];
    int count = 0;
    Event e;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^\n]",
                    e.name, e.about, e.date, e.venue) == 4) {
            printEvent(e);
            count++;
        }
    }

    fclose(file);
    if (count == 0) {
        printf("There are no events scheduled for %s.\n", clubName);
    }
    printf("--- End of List ---\n");
}

void cancelEvent(const char *clubName) {
    char nameToRemove[100];
    char line[512];
    int found = 0;
    
    char eventFilePath[100];
    char tempFilePath[100];
    snprintf(eventFilePath, sizeof(eventFilePath), "%s_events.txt", clubName);
    snprintf(tempFilePath, sizeof(tempFilePath), "%s_temp.txt", clubName);

    viewAllEvents(clubName); 
    
    printf("\nEnter the exact Event Name to cancel/finish: ");
    fgets(nameToRemove, sizeof(nameToRemove), stdin);
    clearNewline(nameToRemove);

    FILE *eventFile = fopen(eventFilePath, "r");
    FILE *tempFile = fopen(tempFilePath, "w");

    if (eventFile == NULL || tempFile == NULL) {
        printf("Error: Could not open files for processing.\n");
        if(eventFile) fclose(eventFile);
        if(tempFile) fclose(tempFile);
        return;
    }
    while (fgets(line, sizeof(line), eventFile)) {
        char lineCopy[512];
        strcpy(lineCopy, line);
        char *eventName = strtok(lineCopy, "|");
        if (eventName && strcmp(eventName, nameToRemove) == 0) {
            found = 1;
        } else {
            fprintf(tempFile, "%s", line);
        }
    }
    fclose(eventFile);
    fclose(tempFile);

    remove(eventFilePath);
    rename(tempFilePath, eventFilePath);
    
    if (found) {
        printf("Success: Event '%s' has been removed from %s.\n", nameToRemove, clubName);
    } else {
        printf("Error: No event found with the name '%s' for %s.\n", nameToRemove, clubName);
    }

}
