
#include<iostream>
using namespace std;
#define dline cout<<"\n\n"
#define sline cout<<"\n"

int i, j;

float powerof1(int exp)
{
    if ((exp & 1) == 1)
        return -1;
    else
        return 1;
}

float** createArray(int n)
{
    float** array = new float* [n];
    for (i = 0; i < n; i++)
        array[i] = new float[n];
    return array;
}

void DelArray(float** addressOfTable, int n)
{
    for (i = 0; i < n; i++)
        delete[] addressOfTable[i];

    delete[] addressOfTable;
}

void printArray(float** table, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout <<"\n";
        for (int j = 0; j < n; j++)
            cout << table[i][j] << "  ";
    }
    cout << "\n\n";
}

float det22(float** array)
{
    return (array[0][0] * array[1][1] - array[0][1] * array[1][0]);
}

float** subMatrix(float** table, int n, int l, int k)
{
        // This fuction returns a Sub - matrix of size n-1 of the passed element Index.......
        // my logic starts here .....
        // l is Index Of Row and k is Index Of Column
        int f = 0;
        int a = 0, b = 0;
        float** submatrix = createArray(n - 1);
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (i != l && j != k)
                {
                    submatrix[a][b] = table[i][j];
                    b++;
                    if (b == n - 1)
                    {
                        f = 1;
                        b = 0;
                    }
                }

            }
            if (f == 1)
                a++;
            f = 0;
        }

       /* cout << "this is a sub matrix of : " << table[l][k] << endl;
        printArray(submatrix, n - 1);*/

        return submatrix;
        DelArray(submatrix, n - 1);
        submatrix = nullptr;
    
}

float DetDriver(float** array, int n)
{
    float ans = 0;
    if (n == 2)
        ans = det22(array);
    else
        for (int h = 0; h < n; h++)
        {
            float** workingArray = createArray(n - 1);
            workingArray = subMatrix(array, n, 0, h);
            if (n - 1 == 2)
                ans = ans + powerof1(h) * array[0][h] * det22(workingArray);
            else
                ans = ans + powerof1(h) * array[0][h] * DetDriver(workingArray, n - 1);
            DelArray(workingArray, n - 1);
            workingArray = nullptr;
        }
    return ans;
}

void transpose(float** array, int n)
{
    float change = 0;
    for (int x = 0; x < n; x++)
        for (int y = x + 1; y < n; y++)
        {
            change = array[x][y];
            array[x][y] = array[y][x];
            array[y][x] = change;
        }
}

float** inverse(float** array, int n, float det)
{
    transpose(array, n);
    float** inverseOfA = createArray(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inverseOfA[i][j] = powerof1(i + j) * (DetDriver(subMatrix(array, n, i, j), n - 1)) / det;
 
    return inverseOfA;
    DelArray(inverseOfA, n);
    inverseOfA = nullptr;
}

void FindSolution(float** table, int n)
{
    float** parameters = new float* [n];
    for (int z = 0; z < n; z++)
        parameters[z] = new float[1];

    float** solution = new float* [n];
    for (int v = 0; v < n; v++)
        solution[v] = new float[1];

    cout << "ENTER THE EQUATION PARAMETERS  ";
    dline;
    for (int zx = 0; zx < n; zx++)
    {
        cout << "Parameter of equation No. " << zx + 1 << " : ";
        cin >> parameters[zx][0];
        sline;
    }

    for (int i = 0; i < n; i++)
    {
        solution[i][0] = 0;
        for (int j = 0; j < n; j++)
        {
            solution[i][0] = solution[i][0] + table[i][j] * parameters[j][0];
        }
    }


    cout << endl << endl << "******** ANSWERS ARE *************" << endl << endl;
    for (int rt = 0; rt < n; rt++)
    {
        cout << "Answer No. " << rt + 1 << " unknown : ";
        cout << solution[rt][0] << endl;
    }
    dline;
    sline;

    DelArray(parameters, n);
    parameters = nullptr;
    DelArray(solution, n);
    solution = nullptr;
}

int main()
{
    cout << "\n\n***** THIS IS A OPEN SOURCE CODE TO SOLVE SYSTEM OF EQUATIONS (NxN) USING MATRIX INVERSION ROUTINE ********\n\n";
    int n;
    cout << "enter order of ( matrix or ) system of equations : ";
    cin >> n;
    if (n <= 1)
    {
        cout << "venam philips ehh !!!........\n\n";
        return 0;
    }

    float** table = createArray(n);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            cin >> table[i][j];

    dline;
    float det = 0, temp = 0;

    if (n == 2)
    {
        det = det22(table);
        if (det != 0)
        {
            cout << "the determinant of \n";
            printArray(table, n);
            cout <<"\n is : " << det << "   ************\n";
            temp = table[0][0];
            table[0][0] = table[1][1];
            table[1][1] = temp;
            temp = 0;
            temp = table[0][1];
            table[0][1] = table[1][0];
            table[1][0] = temp;
            table[0][0] = (-1) * table[0][0];
            table[1][1] = (-1) * table[1][1];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    table[i][j] = table[i][j] / det;

            dline;
            cout << "**********  Inverse of the matrix ***********" << endl;
            printArray(table, n);
            cout << endl << "***************************************" << endl << endl;

            FindSolution(table, n);
        }
        else
            cout << "adhu seri unga vaai unga uruttu" << endl << endl << endl;
    }

    else if (n > 2)
    {
        det = DetDriver(table, n);
        if (det != 0)
        {
            cout << "the determinant of " << endl;
            printArray(table, n);
            cout << endl << " is : " << det << "   ************" << endl;

            table = inverse(table, n, det);

            dline;
            cout <<"\n**********  Inverse of the matrix ***********\n";
            printArray(table, n);
            cout <<"\n***************************************\n\n";

            FindSolution(table, n);

        }
        else
            cout << "adhu seri unga vaai unga uruttu\n\n\n";
    }

    else
        cout << "3 ah thotadhu yaaru xD...........\n\n\n";

    dline;

    DelArray(table, n);
    table = nullptr;
    return 0;
}
