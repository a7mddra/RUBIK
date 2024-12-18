#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "terminal/colors.h"

float A, B, C;
float cubeW = 18;
int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int bgASCIIcode = ' ';
int distFromCam = 100;
float K1 = 50;
float incrementSpeed = 1;

float x, y, z;
float ooz;
int xp, yp;
int idx;

char cube[6][9] = {
    {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
    {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},
    {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},
    {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'}};

void modify(const char *colors)
{
    for (int i = 0; i < 54; i++)
    {
        cube[i / 9][i % 9] = colors[i];
    }
}

float calcX(int i, int j, int k)
{
    return j * sin(A) * sin(B) * cos(C) + j * cos(A) * sin(C) -
           k * cos(A) * sin(B) * cos(C) + k * sin(A) * sin(C) +
           i * cos(B) * cos(C);
}

float calcY(int i, int j, int k)
{
    return k * cos(A) * sin(B) * sin(C) + j * cos(A) * cos(C) -
           j * sin(A) * sin(B) * sin(C) + k * sin(A) * cos(C) -
           i * cos(B) * sin(C);
}

float calcZ(int i, int j, int k)
{
    return i * sin(B) + k * cos(A) * cos(B) -
           j * sin(A) * cos(B);
}

void calcForSurface(float cubeX, float cubeY, float cubeZ, int f)
{
    int i, j, k, ch = 35 + f * 9;

    switch (f) {
        case 0: i =  cubeX; j =  cubeY; k =  cubeZ; break;
        case 1: i =  cubeZ; j =  cubeY; k = -cubeX; break;
        case 2: i = -cubeZ; j =  cubeY; k =  cubeX; break;
        case 3: i = -cubeX; j =  cubeY; k = -cubeZ; break;
        case 4: i =  cubeX; j = -cubeZ; k =  cubeY; break;
        case 5: i =  cubeX; j =  cubeZ; k = -cubeY; break;
        default:                                    break;
    }

    int xReg = (i < -cubeW / 3) ? 0 : (i < cubeW / 3) ? 1 : 2;
    int yReg = (j < -cubeW / 3) ? 0 : (j < cubeW / 3) ? 1 : 2;

    int lkup[3][3] = {
        {3, 2, 1},  
        {6, 5, 4},  
        {9, 8, 7}   
    };

    ch += lkup[xReg][yReg];

    x = calcX(cubeX, cubeY, cubeZ) + 0          ;
    y = calcY(cubeX, cubeY, cubeZ) + 0          ;
    z = calcZ(cubeX, cubeY, cubeZ) + distFromCam;

    ooz = 1 / z;

    xp = (int)(width  / 2 - 2 * cubeW       - K1 * ooz * x * 2);
    yp = (int)(height / 2 -     cubeW / 4.4 + K1 * ooz * y    );

    idx = xp + yp * width;
    if (idx >= 0 && idx < width * height && ooz > zBuffer[idx])
    {
        zBuffer[idx] = ooz;
        buffer[idx] = (char)ch;
    }
}

void render()
{
    memset(buffer, bgASCIIcode, width * height);
    memset(zBuffer, 0, width * height * 4);
    for (float cubeX = -cubeW;
         cubeX < cubeW; cubeX += incrementSpeed)
    {
    for (float cubeY = -cubeW;
            cubeY < cubeW; cubeY += incrementSpeed)
    {
        calcForSurface( cubeX,  cubeY, -cubeW, 0);
        calcForSurface( cubeW,  cubeY,  cubeX, 1);
        calcForSurface(-cubeW,  cubeY, -cubeX, 2);
        calcForSurface(-cubeX,  cubeY,  cubeW, 3);
        calcForSurface( cubeX, -cubeW, -cubeY, 4);
        calcForSurface( cubeX,  cubeW,  cubeY, 5);
    }
    }
    printf("\x1b[H");
    for (int k = 0; k < width * height; k++)
    {
        if (k % width == 0)
        {
            putchar('\n');
        }
        else
        {
            char sqr[32];
            int s = (int)buffer[k] - 35 - 1;
            char sym = 
              (s / 9 == 0)   ? '#'
            : (s / 9 == 1)   ? '@'
            : (s / 9 == 2)   ? '&'
            : (s / 9 == 3)   ? '*'
            : (s / 9 == 4)   ? '%'
            : (s / 9 == 5)   ? '+'
            :                  ' ';

            const char* (*funcs[6])(char sym) = {
                red, green, blue, orange, yellow,
                NULL
            };

            if (s >= 0)
            {
                int cidx = -1;
                switch (cube[s / 9][s % 9]) {
                    case 'R': cidx = 0; break;
                    case 'G': cidx = 1; break;
                    case 'B': cidx = 2; break;
                    case 'O': cidx = 3; break;
                    case 'Y': cidx = 4; break;
                    case 'W': 
                        sqr[0] = sym;
                        sqr[1] = '\0';
                        break;
                    default: 
                        sqr[0] = '\0'; 
                        break;
                }

                if (cidx != -1) {
                    strcpy(sqr, funcs[cidx](sym));
                }

                printf("%s", sqr);
            } else putchar(buffer[k]);
        }
    }
}

int main(int argc, char *argv[]) {
    printf("\033[H\033[2J");

    if (argc > 1)
    {
        if (strlen(argv[1]) != 54)
        {
            fprintf(stderr, "Error");
            return 1;
        }
        modify(argv[1]);
    }

    while (1) {
        render(); 
        A += 0.005; 
        B += 0.005;
        usleep(1000); 
    }
    
    return 0;
}
