#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int xMax = 20; // i should start to take into account that a computer starts counting from zero.
int yMax = 20;
int x1, yI, x2, y2, x3, y3; // I KNOW yI IS A BUILT IN THING IM OVERWRITING! I DON'T REMEMBER ASKING!

void drawLine(char grid[][xMax], float k, int m, int DfMin, int DfMax) {
    printf("%f\n", k);
    if (k>=1) {
        for (int x = DfMin; x < DfMax; x++) {
            for (int y = 0; y < k; y++) {
                printf("%d\n", (int)(yMax-1-m-k*x+y));
                if ((int)(yMax-1-m-k*x+y)>0) {
                    grid[(int)(yMax-1-m-k*x+y)][x] = '/';
                }                      
            }
        }
    } else if (k<1 && k!=0 && k>-1) {
        for (int x=DfMin;x<DfMax;x++) {
            grid[(int)(yMax-1-m-k*x)][x] = '~';
        }
    } else if (k<=-1) {
        for (int x=DfMin;x<DfMax;x++) {
            for (int y=0;y>k;y--) {
                if ((int)(yMax-1-m-k*x-y)<yMax) {
                    grid[(int)(yMax-1-m-k*x-y)][x] = '\\';
                }
            }
        }
    } else if (k==0) {
        for (int x=DfMin;x<DfMax;x++) {
            grid[(yMax-1-m)][x] = '-';
        }
    } 
}

void drawVerticalLine(char grid[][xMax], int x, int VfMin, int VfMax) {
    for (int y = VfMin; y < VfMax; y++) {
        if (y >= 0 && y <= yMax) {
            grid[y][x] = '|';
        }                      
    }
}

int main() {
    printf("=== Give And Give Good - Graph calculator ===\n");
    printf("Do you wish to draw a graph from an equation(1) or a line by cordinates(2) or a triangle by cordinates(3) or just spin a point around the orgin in 2D space(4)? (1/2/3/4): ");
    int input;
    scanf("%d", &input);
    float k, k2, k3;
    int m, m2, m3;

    // Create empty grid
    char grid[yMax][xMax];
    for(int i=0;i<yMax;i++) {
        for(int j=0;j<xMax;j++) {
            grid[i][j] = ' ';
        }
    }

    // I know what a switch statement is ok, just to lazy to switch to one.
    if (input == 1) {
        printf("y = kx + m\n");
        printf("Enter the float k: ");
        scanf("%f", &k);
        printf("Enter the int m: ");
        scanf("%d", &m);
        drawLine(grid, k, m, 0, xMax);
    } else if (input == 2) {
        printf("Enter coordinate x1 and yI with a space in between: ");
        scanf("%d %d", &x1, &yI);
        printf("Enter coordinate x2 and y2 with a space in between: ");
        scanf("%d %d", &x2, &y2);
        if (x1 == x2) {
            drawVerticalLine(grid, x1, yI, y2);
        } else {
            k = (float)(y2-yI)/(float)(x2-x1);
            printf("k=%f\n", k);
            m = y2-k*x2;
            printf("m=%d\n", m);
            drawLine(grid, k, m, x1+1, x2+1);
        }
    } else if (input == 3) {
        printf("Enter coordinate x1 and yI with a space in between: ");
        scanf("%d %d", &x1, &yI);
        printf("Enter coordinate x2 and y2 with a space in between: ");
        scanf("%d %d", &x2, &y2);
        printf("Enter coordinate x3 and y3 with a space in between: ");
        scanf("%d %d", &x3, &y3);
        k = (float)(y2-yI)/(float)(x2-x1);
        k2 = (float)(y3-y2)/(float)(x3-x2);
        k3 = (float)(yI-y3)/(float)(x1-x3);
        printf("k2=%f\n", k2);
        m = y2-k*x2;
        m2 = y3-k2*x3;
        m3 = y3-k3*x3;
        //the x value should be +1 when k > 1 but not when k < -1 for some reason.
        drawLine(grid, k, m, x1+1, x2+1);
        drawLine(grid, k2, m2, x2+1, x3+1);
        drawLine(grid, k3, m3, x1+1, x3+1);

    } else if (input == 4) {
        printf("Enter coordinate x and y with a space in between: ");
        float fx1, fy1;
        scanf("%f %f", &fx1, &fy1);
        float theta = 10*0.017; // About 10 degrees in radians
        int orginX = 0;
        int orginY = 0;
        while (1) {
            // You spin me right round round baby right round!
            float xt = fx1 * cos(theta) - fy1 * sin(theta);
            float yt = fx1 * sin(theta) + fy1 * cos(theta);
            printf("(%d, %d)\n", (int)round(xt), (int)round(yt));

            // Display grid
            for(int i=0;i<yMax;i++) {
                for(int j=0;j<xMax;j++) {
                    if ((int)round(xt) + orginX >= 0 && (int)round(xt) + orginX <= xMax && (int)round(yt) + orginY >= 0 && (int)round(yt) + orginY <= yMax && i == yMax-((int)round(yt)+orginY)-1 && j == (int)round(xt)) {
                        printf("o ");
                    } else {
                        printf("  ");
                    }
                    if(j==xMax-1) {
                        printf("\n");
                    }
                }
            }
            grid[yMax-1][0] = 'x';
            fx1 = xt;
            fy1 = yt;

            usleep(1000 * 250);
            system("clear");
        }
    } else {
        return -1;
    }

    // I'll just copy-paste it like the idiot i am.
    /*if (k>=1) {
        for (int x=0;x<xMax;x++) {
            for (int y=0;y<k;y++) {
                grid[(int)(yMax-1-m-k*x+y)][x] = '/';
            }
        }

    } else if (k<1 && k!=0 && k>-1) {
        for (int x=0;x<xMax;x++) {
            grid[(int)(yMax-1-m-k*x)][x] = '~';
        }
    } else if (k<=-1) {
        for (int x=0;x<xMax;x++) {
            for (int y=0;y<=(int)(k);y++) {
                if ((int)(yMax-1-m-k*x-y)<yMax) {
                    grid[(int)(yMax-1-m-k*x-y)][x] = '\\';
                }
            }
        }
    } else if (k==0) {
        for (int x=0;x<xMax;x++) {
            grid[(yMax-1-m)][x] = '-';
        }
    }*/

    // Indicates the orgin (0, 0) with an x
    grid[yMax-1][0] = 'x';
    if (input == 2) {
        grid[yMax-yI-1][x1] = 'o';
        grid[yMax-y2-1][x2] = 'o';
    } else if (input == 3) {
        grid[yMax-yI-1][x1] = 'o';
        grid[yMax-y2-1][x2] = 'o';
        grid[yMax-y3-1][x3] = 'o';
    }

    // Display grid
    for(int i=0;i<yMax;i++) {
        for(int j=0;j<xMax;j++) {
            printf("%c ", grid[i][j]);
            if(j==xMax-1) {
                printf("\n");
            }
        }
    }

    return 0;
}