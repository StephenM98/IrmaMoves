//IrmaMoves.c
//Created by Stephen Miller (smiller5162)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IrmaMoves.h"

//Prototype for helper function
int columnToInt(char);

//Creates board
char **createMapBoard(void)
{
    int i; //Iterator
    char **map = malloc(8 * sizeof(char *)); //Dynamically allocate memory for the rows

    for (i = 0; i < 8; i++) //Dynamically allocate memory for each element in map
        map[i] = malloc(8 * sizeof(char));
    map[0][0] = 'F'; //Plotting out map
    map[0][1] = 'F';
    map[0][2] = ' ';
    map[0][3] = ' ';
    map[0][4] = ' ';
    map[0][5] = ' ';
    map[0][6] = ' ';
    map[0][7] = ' ';
    map[1][0] = ' ';
    map[1][1] = 'F';
    map[1][2] = ' ';
    map[1][3] = ' ';
    map[1][4] = ' ';
    map[1][5] = ' ';
    map[1][6] = ' ';
    map[1][7] = ' ';
    map[2][0] = ' ';
    map[2][1] = 'F';
    map[2][2] = 'F';
    map[2][3] = ' ';
    map[2][4] = ' ';
    map[2][5] = ' ';
    map[2][6] = ' ';
    map[2][7] = ' ';
    map[3][0] = ' ';
    map[3][1] = ' ';
    map[3][2] = 'F';
    map[3][3] = ' ';
    map[3][4] = ' ';
    map[3][5] = ' ';
    map[3][6] = ' ';
    map[3][7] = ' ';
    map[4][0] = ' ';
    map[4][1] = ' ';
    map[4][2] = 'K';
    map[4][3] = ' ';
    map[4][4] = ' ';
    map[4][5] = ' ';
    map[4][6] = ' ';
    map[4][7] = ' ';
    map[5][0] = 'C';
    map[5][1] = ' ';
    map[5][2] = ' ';
    map[5][3] = 'B';
    map[5][4] = ' ';
    map[5][5] = ' ';
    map[5][6] = ' ';
    map[5][7] = ' ';
    map[6][0] = ' ';
    map[6][1] = 'C';
    map[6][2] = 'C';
    map[6][3] = ' ';
    map[6][4] = 'D';
    map[6][5] = ' ';
    map[6][6] = ' ';
    map[6][7] = ' ';
    map[7][0] = ' ';
    map[7][1] = ' ';
    map[7][2] = 'C';
    map[7][3] = ' ';
    map[7][4] = ' ';
    map[7][5] = 'D';
    map[7][6] = 'D';
    map[7][7] = ' ';

    return map;
};

//Frees memory allocated to the board
char **destroyMapBoard(char **map)
{
    free(map);
    return NULL;
};

void printMapBoard(char **map)
{
    int i, j;
    printf("========\n");
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
            printf("%c", map[i][j]);    //Print each element of map
        printf("\n");
    }
    printf("========");
    printf("\n");
    printf("\n");
};
//Helper function to convert letters for columns into integers
int columnToInt(char charCol)
{
    if (charCol == 'a')
        return 0;
    if (charCol == 'b')
        return 1;
    if (charCol == 'c')
        return 2;
    if (charCol == 'd')
        return 3;
    if (charCol == 'e')
        return 4;
    if (charCol == 'f')
        return 5;
    if (charCol == 'g')
        return 6;
    if (charCol == 'h')
        return 7;
    else{
        printf("Error: Column is mislabeled!\n");
        return 0;
    }
}
//Predicting where Irma will go based on conditions and prints final position
char **predictIrmaChange(char* str, Move* irmamove)
{
    char **board;
    board = createMapBoard();
    parseNotationString(str, irmamove);
    //variables for columns from and to, and rows from and to
    int fromCol = columnToInt(irmamove->from_loc.col);
    int toCol = columnToInt(irmamove->to_loc.col);
    int fromRow = irmamove->from_loc.row;
    int toRow = irmamove->to_loc.row;
    //Printing board with initial Irma position
    board[fromRow][fromCol] = 'I';
    printMapBoard(board);

    //Determining whether the final destination is greater than or less than from the columns
    if (fromCol > toCol)
    {
        //if greater, start from toCol
        for (int i = toCol; i < fromCol; i++)
        {
            if (board[fromRow][i] == ' ')        //Wind speed and gusts based off whether Irma is above land or water
            {
                irmamove->irma.ws += 10;
                irmamove->irma.wg += 5;
            }
            else
            {
                irmamove->irma.ws -= 15;
                irmamove->irma.wg -= 10;
            }
        }
    }
    else
    {
        //if less than, start from "fromCol"
        for (int i = fromCol; i < toCol; i++)
        {
            if (board[fromRow][i] == ' ')        //Wind speed and gusts based on whether Irma is above land or water
            {
                irmamove->irma.ws += 10;
                irmamove->irma.wg += 5;
            }
            else
            {
                irmamove->irma.ws -= 15;
                irmamove->irma.wg -= 10;
            }
        }
    }
    //Determining rows
    if (fromRow > toRow)
    {
        //If greater than, start from "toRow"
         for (int i = toRow; i < fromRow; i++)
         {
            if (board[i][toCol] == ' ')
            {
                irmamove->irma.ws += 6;     //Wind speed and gust based on whether Irma is on land or water
                irmamove->irma.wg += 3;
            }
            else
            {
                irmamove->irma.ws -= 2;
                irmamove->irma.wg -= 1;
            }
         }
    }
    else
    {
        //If less than, start from "fromRow"
        for(int i = fromRow; i < toRow; i++){
            if(board[i][toCol] == ' ')
            {
                irmamove->irma.ws += 6;
                irmamove->irma.wg += 3;
            }
            else
            {
                irmamove->irma.ws -= 2;
                irmamove->irma.wg -= 1;
            }
        }
    }
    //Move Irma on board to new spot

    board[toRow][toCol] = 'I';
    //Change from row and col back to " "
    board[fromRow][fromCol] = ' ';

    printMapBoard(board);
    return board;
};

void parseNotationString(char* str, Move* irmamove)
{
    //Parsing the starting location
    irmamove->from_loc.col = str[0];
    irmamove->from_loc.row = atoi(&str[1]);

    char tempVar[3];

    //Parsing the wind speeds
    for (int i = 0; i < 3; i++)
        tempVar[i] = str[i+3];
    irmamove->irma.ws = atoi(tempVar);

    //Parsing the wind gusts
    for (int i = 0; i < 3; i++)
        tempVar[i] = str[i+7];
    irmamove->irma.wg = atoi(tempVar);

    //Parsing the final location
    irmamove->to_loc.col = str[11];
    irmamove->to_loc.row = atoi(&str[12]);
};

double difficultyRating(void)
{
    return 4;
};

double hoursSpent(void)
{
    return 5;
};
