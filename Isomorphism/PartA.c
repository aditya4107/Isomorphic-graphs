// Aditya Kumar Sharma 2021A7PS3112H
// Harshit Juneja 2021A7PS2946H
// Enter in the following manner: "./.exe ./<file name>.txt"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *ptr; // making a file pointer
    char ch;
    int size;
    ptr = fopen(argv[1], "r");

    if (ptr != NULL) // for an empty file
    {

        fseek(ptr, 0, SEEK_END);
        size = ftell(ptr);

        if (size == 0)
        {
            printf("The file is empty.\n");
        }
    }
    fseek(ptr, 0L, SEEK_SET);

    int numNodes, numEdges; // the number of nodes and edges, respectively

    fscanf(ptr, "%d", &numNodes);

    if (numNodes == 0) // case of 0 nodes
    {
        printf("Please enter atleast one node.\n");
        exit(0);
    }

    fscanf(ptr, "%d", &numEdges);

    void desc_sort(int a[], int n) // sorting algorithm (used for final output)
    {
        int i, j, temp;
        for (i = 0; i < n - 1; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (a[i] < a[j])
                {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
        }
    }

    int arrayDS[numNodes][numNodes]; // arrayDS is the nxn matrix
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            arrayDS[i][j] = 0; // initialising all elements to 0
        }
    }
    for (int i = 0; i < numEdges; i++)
    {
        int a, b;
        if (ch != EOF)
        {
            fscanf(ptr, "%d", &a);
            fscanf(ptr, "%d", &b);

            arrayDS[b - 1][a - 1] = 1; // setting (a,b) {(a-1,b-1) for indexing} as marked
            arrayDS[a - 1][b - 1] = 1; // to mantain symetricity
        }
    }

    int sumArr[numNodes]; // array which contains sum of connections at each node
    for (int i = 0; i < numNodes; i++)
    {
        sumArr[i] = 0; // 0 initialising
    }

    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            sumArr[i] += arrayDS[i][j]; // row-then-column sum
        }
    }
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            sumArr[i] += arrayDS[j][i]; // column-then-row sum
        }
    }

    desc_sort(sumArr, numNodes); // sorting
    printf("Degree sequence in non-increasing order: \n");

    for (int i = 0; i < numNodes; i++)
    {
        printf("%d \t", sumArr[i] / 2); // dividing by 2 to remove effect of symetricity
    }
    fclose(ptr); // closing the txt file
    return 0;
}