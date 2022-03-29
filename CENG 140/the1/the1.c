#include <stdio.h>
#define ROW 25
#define COLUMN 25

// I made all of them global since most of them needed to be static to make my implementation work, but static declarations was not allowed. Also, global variables should be 0 by default, but I wrote just to show it.
char rotation, operation;
int p1PointX=0, p1PointY=0, p2PointX=0, p2PointY=0, c1PointX=0, c1PointY=0, c2PointX=0, c2PointY=0, oldColor=0, newColor=0, selectedColorX=0, selectedColorY=0, initialPixelX=0, initialPixelY=0;
int degree=0, counter=0, differenceX=0, differenceY=0, smallC1X=0, smallC1Y=0, smallP1X=0, smallP1Y=0;
int coordinates[ROW][COLUMN];
int changed[ROW][COLUMN];
int will_be_copied[ROW][COLUMN];
int Transpose_will_be_copied[ROW][COLUMN];
int reversed_Transpose_will_be_copied[ROW][COLUMN];  // These arrays were not supposed to be with that lengths, but dynamic arrays are, also, not allowed, so this memory waste was happened.
int n=0, i=0, a=0, b=0, q=0, w=0, j=0, z=0, u=0, v=0, y=0, m=0; // Loop variables

int neighbourFinder(int x, int y) // This function recursively finds the suitable positions to the given coordinates. If 
{
    if(oldColor != coordinates[x][y]) {return 0;}
    else if(x<0 || y<0 || x>=ROW || y>=COLUMN) {return 0;}
    else if(changed[x][y]==1) {return 0;}
    else
    {
        coordinates[x][y] = newColor;
        changed[x][y] = 1;
        return neighbourFinder(x-1, y-1) + neighbourFinder(x-1, y) + neighbourFinder(x-1, y+1) + neighbourFinder(x, y+1) + 
               neighbourFinder(x+1, y+1) + neighbourFinder(x+1, y) + neighbourFinder(x+1, y-1) + neighbourFinder(x, y-1);
    }
}
int main()
{
    // int a = 0, b = 0; // For the 2d version, but check for any name collusions.

    // This is exactly how you shouldn't write a code. As far as I remember, there were some errors with the 2d array version of it, 
    // and the fastest solution was just copy pasting it, but you should definitely change it.
    for(i=0; i<ROW; ++i) 
    {
        scanf(" %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &coordinates[i][0], &coordinates[i][1], &coordinates[i][2], &coordinates[i][3], &coordinates[i][4], &coordinates[i][5], &coordinates[i][6], &coordinates[i][7], &coordinates[i][8], &coordinates[i][9], &coordinates[i][10], &coordinates[i][11], &coordinates[i][12], &coordinates[i][13], &coordinates[i][14], &coordinates[i][15], &coordinates[i][16], &coordinates[i][17], &coordinates[i][18], &coordinates[i][19], &coordinates[i][20], &coordinates[i][21], &coordinates[i][22], &coordinates[i][23], &coordinates[i][24]);
    }

    // for(a; a < ROW; ++a) // I recommend you to try it and fix its errors, if there are any.
    // {
    //     for(b; b < COLUMN; ++b)
    //     {
    //         scanf(" %d", &coordinates[a][b]);
    //     }
    // }

    scanf(" %c", &operation);

    // This part executes the operation, for the clarifications about the operations, you can check THE pdf 
    switch (operation)
    {
    case 'F':
        scanf(" %d %d", &selectedColorX, &selectedColorY);
        scanf(" %d %d", &initialPixelX, &initialPixelY);

        oldColor = coordinates[initialPixelX][initialPixelY];

        // This selects a new color according to the given coordinates.
        if((selectedColorX < ROW) && (selectedColorX > -1) && (selectedColorY < COLUMN) && (selectedColorY > -1))
        {
            newColor = coordinates[selectedColorX][selectedColorY];
        }
        else
        { 
            if(selectedColorX<0 && selectedColorY<0){newColor=0;}
            else if(selectedColorX<0 && selectedColorY<COLUMN && selectedColorY>-1){newColor=1;}
            else if(selectedColorX<0 && selectedColorY>=COLUMN){newColor=2;}
            else if(selectedColorY>=COLUMN && selectedColorX<ROW && selectedColorX>-1){newColor=3;}
            else if(selectedColorX>=ROW && selectedColorY>=COLUMN){newColor=4;}
            else if(selectedColorX>=ROW && selectedColorY<COLUMN && selectedColorY>-1){newColor=5;}
            else if(selectedColorY<0 && selectedColorX>=ROW){newColor=6;}
            else{newColor=7;}
        }

        neighbourFinder(initialPixelX, initialPixelY);
        break;

    // Paste operation
    case 'P':
        scanf(" %d %d %d %d", &c1PointX, &c1PointY, &c2PointX, &c2PointY);  // Taking area to copy
        scanf(" %d %d %d %d", &p1PointX, &p1PointY, &p2PointX, &p2PointY);  // To paste

        // Finding the places of the areas relatively.
        smallC1X = c1PointX < c2PointX ? c1PointX : c2PointX;
        smallC1Y = c1PointY < c2PointY ? c1PointY : c2PointY;
        smallP1X = p1PointX < p2PointX ? p1PointX : p2PointX;
        smallP1Y = p1PointY < p2PointY ? p1PointY : p2PointY;
        
        differenceX = c1PointX - c2PointX > 0 ? c1PointX - c2PointX : c2PointX - c1PointX;
        differenceY = c1PointY - c2PointY > 0 ? c1PointY - c2PointY : c2PointY - c1PointY;

        for(a=0; a<=differenceX; a++)
        {
            for(b=0; b<=differenceY; b++)
            {
                if(coordinates[smallP1X+a][smallP1Y+b] == coordinates[smallC1X+a][smallC1Y+b]){continue;}
                counter++;
                coordinates[smallP1X+a][smallP1Y+b] = coordinates[smallC1X+a][smallC1Y+b];
            }
        }
        break;
    
    // This rotates the given area
    case 'R':
        scanf(" %c %d", &rotation, &degree);
        scanf(" %d %d %d %d", &c1PointX, &c1PointY, &c2PointX, &c2PointY);
        scanf(" %d %d %d %d", &p1PointX, &p1PointY, &p2PointX, &p2PointY);

        differenceX = c2PointX-c1PointX;

        for(q=0; q<=differenceX; ++q)
        {
            for(w = 0; w <= differenceX; ++w)
            {
                will_be_copied[q][w] = coordinates[c1PointX+q][c1PointY+w];
            }
        }
    
        if(rotation == 'L'){degree = (360-degree)%360;} // To make everything with the right rotations.

        if(!degree)
        {
            for(a=0; a<=differenceX; ++a)
            {
                for(b=0; b<=differenceX; ++b)
                {
                    if(coordinates[p1PointX+a][p1PointY+b] == coordinates[c1PointX+a][c1PointY+b]){continue;}
                    counter++;
                    coordinates[p1PointX+a][p1PointY+b] = coordinates[c1PointX+a][c1PointY+b];
                }
            }
        }
        else
        {
            for(i=0; i<=differenceX; ++i)
            {
                for(j=0; j<=differenceX; ++j)
                {
                    Transpose_will_be_copied[i][j] = will_be_copied[j][i];
                }
            }

            for(z=0; z<=differenceX; ++z)
            {
                for(y=0; y<=differenceX; ++y)
                {
                    reversed_Transpose_will_be_copied[z][y] = Transpose_will_be_copied[z][differenceX-y];
                }
            }

            if(degree==180)
            {
                for(i=0; i<=differenceX; ++i)
                {
                    for(j=0; j<=differenceX; ++j)
                    {
                        Transpose_will_be_copied[i][j] = reversed_Transpose_will_be_copied[j][i];
                    }
                }
                for(z=0; z<=differenceX; ++z)
                {
                    for(y=0; y<=differenceX; ++y)
                    {
                        reversed_Transpose_will_be_copied[z][y] = Transpose_will_be_copied[z][differenceX-y];
                    }
                }
            }
            else if(degree==270)
            {
                for(z=0; z<=differenceX; ++z++)
                {
                    for(y=0; y<=differenceX; ++y)
                    {
                        reversed_Transpose_will_be_copied[z][y] = Transpose_will_be_copied[differenceX-z][y];
                    }
                }
            }
            
            for(u=0; u<=differenceX; ++u)
            {
                for(v=0; v<=differenceX; ++v)
                {
                    if(coordinates[p1PointX+u][p1PointY+v] == reversed_Transpose_will_be_copied[u][v]){continue;}
                    counter++;
                    coordinates[p1PointX+u][p1PointY+v] = reversed_Transpose_will_be_copied[u][v];
                }
            }
        }
        break;
    }

    for(m=0; m < ROW; ++m) // Prints the final version.
    {
        for(n=0; n < COLUMN; ++n)
        {
            printf("%d ", coordinates[m][n]);
        }
        printf("\n");
    }  

    if(operation == 'P' || operation == 'R'){printf("%d\n", counter);}
    return 0;
}