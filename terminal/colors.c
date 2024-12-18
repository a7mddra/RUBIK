#include <stdio.h>
#include <string.h>
#include "colors.h"

// colored chars
const char* red(char ch) {
    static char coloredCh[16]; 
    snprintf(coloredCh, sizeof(coloredCh), "\033[1;31m%c\033[0m", ch); 
    return coloredCh;
}

const char* green(char ch) {
    static char coloredCh[32]; 
    snprintf(coloredCh, sizeof(coloredCh), "\033[38;2;68;198;98m%c\033[0m", ch); 
    return coloredCh;
}

const char* blue(char ch) {
    static char coloredCh[32];
    snprintf(coloredCh, sizeof(coloredCh), "\033[38;2;13;146;244m%c\033[0m", ch);
    return coloredCh;
}

const char* orange(char ch) {
    static char coloredCh[32];
    snprintf(coloredCh, sizeof(coloredCh), "\033[38;2;255;102;0m%c\033[0m", ch);
    return coloredCh;
}

const char* yellow(char ch) {
    static char coloredCh[32];
    snprintf(coloredCh, sizeof(coloredCh), "\033[38;2;255;244;85m%c\033[0m", ch);
    return coloredCh;
}

// colored strings
const char* strred(const char *str) {
    static char coloredStr[1024]; 
    snprintf(coloredStr, sizeof(coloredStr), "\033[1;31m%s\033[0m", str); 
    return coloredStr;
}

const char* strgreen(const char *str) {
    static char coloredStr[1024]; 
    snprintf(coloredStr, sizeof(coloredStr), "\033[1;32m%s\033[0m", str); 
    return coloredStr;
}

const char* strblue(const char *str) {
    static char coloredStr[1024];
    snprintf(coloredStr, sizeof(coloredStr), "\033[38;2;13;146;244m%s\033[0m", str);
    return coloredStr;
}

const char* strorange(const char *str) {
    static char coloredStr[1024];
    snprintf(coloredStr, sizeof(coloredStr), "\033[38;2;255;102;0m%s\033[0m", str);
    return coloredStr;
}

const char* stryellow(const char *str) {
    static char coloredStr[1024];
    snprintf(coloredStr, sizeof(coloredStr), "\033[38;2;255;244;85m%s\033[0m", str);
    return coloredStr;
}

const char white[55] = "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
