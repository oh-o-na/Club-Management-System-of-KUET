#ifndef ADMIN_UTILS_H
#define ADMIN_UTILS_H
#include "common_structs.h"
void clearInputBuffer();
void clearNewline(char *str);
void printMember(Member m); // Struct definition is now in common_structs.h
void printEvent(Event e);   // Struct definition is now in common_structs.h
void showMenu();
#endif
