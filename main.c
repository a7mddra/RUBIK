#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "terminal/colors.h"

const char* color(char cube[55], int i, int j)
{
    int c = cube[i + j*9];
    switch (c)
    {
    case 79: return strorange("■"); break;
    case 89: return stryellow("■"); break;
    case 71: return strgreen( "■"); break;
    case 66: return strblue(  "■"); break;
    case 82: return strred(   "■"); break;
    case 87: return           "■" ; break;
    default:                        break;
    }
}

void decoding(const char *input, char *output)
{
    for (int i = 0; i < 54; i++) {
    switch (input[i]) {
    case 'R': output[i] = 'U'; break; 
    case 'B': output[i] = 'R'; break; 
    case 'W': output[i] = 'F'; break; 
    case 'O': output[i] = 'D'; break; 
    case 'G': output[i] = 'L'; break; 
    case 'Y': output[i] = 'B'; break; 
    default : output[i] = 'e'; break; 
    }}
    output[54] = '\0'; 
}

void reorder(char *cube, char *cubee)
{
    strncpy(cubee +  0, cube + 0 * 9, 9);
    strncpy(cubee +  9, cube + 4 * 9, 9);
    strncpy(cubee + 18, cube + 2 * 9, 9);
    strncpy(cubee + 27, cube + 1 * 9, 9);
    strncpy(cubee + 36, cube + 5 * 9, 9);
    strncpy(cubee + 45, cube + 3 * 9, 9);
    cubee[54] = '\0';
}

void cw(char *cube, int i)
{
    int u=0, r=1, f=2,
        d=3, l=4, b=5;
    int x, y, z, t;
    int m, n, o;

    char   temp = cube[0+i*9];
    cube[0+i*9] = cube[6+i*9];
    cube[6+i*9] = cube[8+i*9];
    cube[8+i*9] = cube[2+i*9];
    cube[2+i*9] = temp;
    
    temp        = cube[7+i*9];
    cube[7+i*9] = cube[5+i*9];
    cube[5+i*9] = cube[1+i*9];
    cube[1+i*9] = cube[3+i*9];
    cube[3+i*9] = temp;
    
    int adj[6][4][3] = {
    {{0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}},
    {{2, 5, 8}, {2, 5, 8}, {2, 5, 8}, {6, 3, 0}},
    {{6, 7, 8}, {8, 5, 2}, {2, 1, 0}, {0, 3, 6}},
    {{6, 7, 8}, {6, 7, 8}, {6, 7, 8}, {6, 7, 8}},
    {{0, 3, 6}, {8, 5, 2}, {0, 3, 6}, {0, 3, 6}},
    {{0, 1, 2}, {2, 5, 8}, {8, 7, 6}, {6, 3, 0}},
    };

    switch (i) {
    case 0: x = b; y = l; z = f; t = r; break;
    case 1: x = u; y = f; z = d; t = b; break;
    case 2: x = u; y = l; z = d; t = r; break;
    case 3: x = f; y = l; z = b; t = r; break;
    case 4: x = u; y = b; z = d; t = f; break;
    case 5: x = u; y = r; z = d; t = l; break;
    default: break;
    }

    char tmp0              = cube[x*9+adj[i][0][0]];
    char tmp1              = cube[x*9+adj[i][0][1]];
    char tmp2              = cube[x*9+adj[i][0][2]];

    cube[x*9+adj[i][0][0]] = cube[y*9+adj[i][1][0]];
    cube[x*9+adj[i][0][1]] = cube[y*9+adj[i][1][1]];
    cube[x*9+adj[i][0][2]] = cube[y*9+adj[i][1][2]];
    
    cube[y*9+adj[i][1][0]] = cube[z*9+adj[i][2][0]];
    cube[y*9+adj[i][1][1]] = cube[z*9+adj[i][2][1]];
    cube[y*9+adj[i][1][2]] = cube[z*9+adj[i][2][2]];
   
    cube[z*9+adj[i][2][0]] = cube[t*9+adj[i][3][0]];
    cube[z*9+adj[i][2][1]] = cube[t*9+adj[i][3][1]];
    cube[z*9+adj[i][2][2]] = cube[t*9+adj[i][3][2]];

    cube[t*9+adj[i][3][0]] = tmp0;
    cube[t*9+adj[i][3][1]] = tmp1;
    cube[t*9+adj[i][3][2]] = tmp2;
}

void move(char *cube, int f, int j)
{
    for (int i = 0 ; i < j ; i++) {
        cw(cube, f);
    }
}

void print(char *cubee)
{
    printf("\033[H\033[2J");

    for (int i = 0; i < 3; i++) {
        printf("       %s %s %s\n",
        color(cubee, i*3+0, 0),
        color(cubee, i*3+1, 0),
        color(cubee, i*3+2, 0));
    }

    for (int i = 0; i < 3; i++) {
        printf(" ");
        for (int j = 0; j < 12; j++) {
            printf("%s ",
            color(cubee, i*3+j%3, 1 + j / 3));
        }
        printf("\n");
    }

    for (int i = 0; i < 3; i++) {
        printf("       %s %s %s\n",
        color(cubee, i*3+0, 5),
        color(cubee, i*3+1, 5),
        color(cubee, i*3+2, 5));
    }

    printf("\n");
}

int main()
{
    char input[100];
    char cube[55];
    char cubee[55];
    char decoded[55];
    char command[100];
    char result[1024];
    char sol[1024] = "";
    char prnt[1024] = "";
    char moves[50][10];
    char *user = getenv("USER");
    char prompt[256];

    printf("\033[H\033[2J");
    strcpy(cube, white);
    print(cube);
    snprintf(prompt, sizeof(prompt),
                    "%s@rubik", user);
    printf("%s:%s$ ",
    strgreen(prompt), strblue("~"));

    int ln = 0;
    while (1)
    {
        char c = getchar();
        if ( c == '\n' ) {
            input[ln] = '\0';
            break;
        } if (ln < sizeof(input) - 1) {
            input[ln++] = c;
            printf("%c", c);
            fflush(stdout);
        }
    }

    if (strlen(input) != 54)
    {
        return 1;
    }

    strncpy(cube, input, 54);
    cube[54] = '\0';

    decoding(input, decoded);

    snprintf(command, sizeof(command),
            "./ckociemba/bin/kociemba %s", decoded);

    FILE *fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("Error running kociemba");
        return 1;
    }
    
    sol[0] = '\0';  

    while (fgets(result, sizeof(result), fp) != NULL)
    {
        size_t len = strlen(result);
        if (len > 0 && result[len - 1] == '\n') {
            result[len - 1] = '\0';
        }

        strcat(sol, result);
    }

    fclose(fp);

    char *token = strtok(sol, " ");
    int cnt = 0;

    const char *valid = "URLFDB'2";
    while (token != NULL && cnt < 50)
    {
        
        int vld = 1;
        for (size_t i = 0; i < strlen(token); i++) {
            if (strchr(valid, token[i]) == NULL) {
                vld = 0;  
                break;
            }
        }
        if (vld && strlen(token) > 0) {
            strncpy(moves[cnt], token, 10 - 1);
            moves[cnt][10 - 1] = '\0';  
            cnt++;
        }
        token = strtok(NULL, " ");
    }

    int i = 0;
    while (1) {
        /*****************
            U R F D L B
         => U L F R B D
        ******************/
        reorder(cube, cubee);
        print(cubee);

        char *user = getenv("USER");
        char prompt[256];
        snprintf(prompt, sizeof(prompt),
                      "%s@rubik", user);
        printf("%s",prnt);
        printf("\n%s:%s$ ",
        strgreen(prompt), strblue("~"));
        char input[10];        
        int ln = 0;
        while (1)
        {
            char c = getchar();
            if ( c == '\n' ) {
                input[ln] = '\0';
                break;
            } if (ln < sizeof(input) - 1) {
                input[ln++] = c;
                printf("%c", c);
                fflush(stdout);
            }
        }
        if (strcmp(input, "s") == 0 && i < cnt && moves[i][0] != '\0') {
        char temp[11];
        snprintf(temp, sizeof(temp), "%s", moves[i]);
        strcat(prnt, temp);
        int sum = 0;
        for (int j = 0; j < strlen(moves[i]); j++) {
            sum += (int)moves[i][j];
            
        }
        switch (sum)
        {
        case 85 : move(cube, 0, 1); break;
        case 135: move(cube, 0, 2); break;
        case 124: move(cube, 0, 3); break;
        
        case 82 : move(cube, 1, 1); break;
        case 132: move(cube, 1, 2); break;
        case 121: move(cube, 1, 3); break;
        
        case 70 : move(cube, 2, 1); break;
        case 120: move(cube, 2, 2); break;
        case 109: move(cube, 2, 3); break;
        
        case 68 : move(cube, 3, 1); break;
        case 118: move(cube, 3, 2); break;
        case 107: move(cube, 3, 3); break;
        
        case 76 : move(cube, 4, 1); break;
        case 126: move(cube, 4, 2); break;
        case 115: move(cube, 4, 3); break;
        
        case 66 : move(cube, 5, 1); break;
        case 116: move(cube, 5, 2); break;
        case 105: move(cube, 5, 3); break;

        default: break;
        }
        i++;
    } else if (strcmp(input, "c") == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd),
        "gnome-terminal -- bash -c 'sleep 0.5; xdotool key ctrl+0; ./cube %s; exec bash'", 
        cube);

        int res = system(cmd);
    }
    }
    return 0;
}
