#include "CMatrix.h"

#define MAX_RANGE 10
#define MIN_RANGE 1

/*
 * Create random int
 */
static int rand(const int n)
{
    return (int)((rand() / (double)RAND_MAX) * (double)n);
}

/*
 * Standart mul 2 matrix array
 */
static int **mul_matrix_array(int **arr1, const int rows1, const int cols1,
                              int **arr2, const int rows2, const int cols2)
{
    assert(cols1 == rows2);
    int **res = new int *[rows1];
    for (register int i = 0; i < rows1; ++i)
        res[i] = new int [cols2];
    for (register int i = 0; i < rows1; ++i)
    {
        for (register int j = 0; j < cols2; ++j)
        {
            res[i][j] = 0;
            for (register int k = 0; k < cols1; ++k)
                res[i][j] += arr1[i][k] * arr2[k][j];
        }
    }
    return res;
}

/*
 * Create matrix with auto value [min_val, max_val]
 */
static int **create_matrix_array(const int rows, const int cols, const double perc,
                                 const int min_val, const int max_val)
{
    int col = (int)(rows * cols * perc / 100);
    int **matr = new int *[rows];
    for (register int i = 0; i < rows; i++)
    {
        matr[i] = new int[cols];
        for (register int j = 0; j < cols; j++)
            matr[i][j] = 0;
    }
    for (register int i = 0; i < col; i++)
    {
        int i_tmp = rand(rows - 1);
        int j_tmp = rand(cols - 1);
        matr[i_tmp][j_tmp] = rand(max_val - min_val) + min_val;
    }
    return matr;
}

/*
 * Free memory for matrix array
 */
static void free_matr(int **arr, const int rows)
{
    for (register int i = 0; i < rows; ++i)
        delete[] arr[i];
    delete arr;
}

/*
 * Print matrix array
 */
static void print_matr(int **a, const int rows, const int cols)
{
    for (register int i = 0; i < rows; ++i)
    {
        for (register int j = 0; j < cols; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

/*
 * Input matrix array
 */
static int **input_matrix(int *rows, int *cols)
{
    int **arr_tmp = new int* [*rows];
    for (register int i = 0; i < *rows; i++)
    {
        arr_tmp[i] = new int [*cols];
        for (register int j = 0; j < *cols; j++)
            arr_tmp[i][j] = 0;
    }
    cout << "Input 3 number(col row value)" << endl;
    while(1)
    {
        while (1)
        {
            int i = *rows + 1, j = *cols + 1, k = 0;
            if (scanf("%d %d %d", &i, &j, &k))
            {
                if ((i >= 0) && (i < *rows) && (j >= 0) && (j < *cols))
                {
                    arr_tmp[i][j] = k;
                    break;
                }
            }
            cout << "error, please repeat:  ";
        }
        cout << "Exit [Yes:1]: ";
        int num;
        cin >> num;
        if (num == 1)
            break;
    }
    return arr_tmp;
}

/*
 * Auto input matrix array
 */
static int **input_matrix_auto(int *rows, int *cols)
{
    double perc = -1;
    do
    {
        cout << "Enter the percentage of filling [0, 100]: ";
    }
    while(!(scanf("%lf", &perc) && (perc >= 0) && (perc <= 100)));

    return create_matrix_array(*rows + 1, *cols + 1, perc, MIN_RANGE, MAX_RANGE);
}

/*
 * Input matrix menu
 */
static int **input_matrix_menu(int *rows, int *cols)
{
    int tmp = 0;
    *cols = 0;
    cout << "Matrix" << endl;
    do
    {
        cout << "Input rows count [1, " << MATRIX_MAX_SIZE << "]: ";
    }
    while(!(scanf("%d", cols) && (*cols >= 1) && (*cols <= MATRIX_MAX_SIZE)));

    do
    {
        cout << "Taking method of input matrix:" << endl;
        cout << " [1]: Inputing" << endl;
        cout << " [2]: Auto" << endl;
        cout << "Input: ";
        cin >> tmp;
    }
    while(tmp != 1 && tmp != 2);

    if(tmp == 1)
        return input_matrix(rows, cols);
    else
        return input_matrix_auto(rows, cols);
}

static int **input_vector(int *rows, int *cols)
{
    int tmp = 0;
    *rows = 1;
    *cols = 0;
    do
    {
        cout << "Input cols count [1, " << MATRIX_MAX_SIZE << "]: ";
    }
    while(!(scanf("%d", cols) && (*cols >= 1) && (*cols <= MATRIX_MAX_SIZE)));

    do
    {
        cout << "Taking method of input vector:" << endl;
        cout << " [1]: Inputing" << endl;
        cout << " [2]: Auto" << endl;
        cout << "Input: ";
        cin >> tmp;
    }
    while(tmp != 1 && tmp != 2);

    if(tmp == 1)
        return input_matrix(rows, cols);
    else
        return input_matrix_auto(rows, cols);
}

static void menu_mul_vm(void)
{
    int **matr1 = NULL;
    int **matr2 = NULL;
    int matr1_rows = 0;
    int matr1_cols = 0;
    int matr2_rows = 0;
    int metr2_cols = 0;

    matr1 = input_vector(&matr1_rows, &matr1_cols);
    matr2_rows = matr1_cols;
    matr2 = input_matrix_menu(&matr2_rows, &metr2_cols);
    CMatrix matrix1(matr1_rows, matr1_cols, matr1);
    CMatrix matrix2(matr2_rows, metr2_cols, matr2);
    CMatrix matrix_mul = matrix1 * matrix2;
    int num = 0;
    int **matr_tmp;
    do
    {
        cout << "Matrix-work menu:" << endl;
        cout << " [1]: Show matrix 1[R]" << endl;
        cout << " [2]: Show matrix 1[S]" << endl;
        cout << " [3]: Show matrix 2[R]" << endl;
        cout << " [4]: Show matrix 2[S]" << endl;
        cout << " [5]: Show mul result alg-R[R]" << endl;
        cout << " [6]: Show mul result alg-R[S]" << endl;
        cout << " [7]: Show mul result alg-S[S]" << endl;
        cout << " [8]: Exit" << endl;
        cout << "Input: ";
        cin >> num;
        switch(num)
        {
            case 1:
                matrix1.matrix_info();
                break;
            case 2:
                print_matr(matr1, matr1_rows, matr1_cols);
                break;
            case 3:
                matrix2.matrix_info();
                break;
            case 4:
                print_matr(matr2, matr2_rows, metr2_cols);
                break;
            case 5:
                matrix_mul.matrix_info();
                break;
            case 6:
                matr_tmp = matrix_mul.to_array();
                print_matr(matr_tmp, matr1_rows, metr2_cols);
                free_matr(matr_tmp, matr1_rows);
                break;
            case 7:
                matr_tmp = mul_matrix_array(matr1, matr1_rows, matr1_cols, matr2, matr2_rows, metr2_cols);
                print_matr(matr_tmp, matr1_rows, metr2_cols);
                free_matr(matr_tmp, matr1_rows);
                break;
        }
    }
    while (num != 8);
    free_matr(matr1, matr1_rows);
    free_matr(matr2, matr2_rows);
}

static int menu_test(void)
{
    // input i
    int i = 0;
    do
    {
        cout << "Input rows matrix1 [1, " << MATRIX_MAX_SIZE << "]: ";
        cin >> i;
    }
    while ((i < 1) || (i > MATRIX_MAX_SIZE));
    // input j
    int j = 0;
    do
    {
        cout << "Input cols matrix1 [1, " << MATRIX_MAX_SIZE << "]: ";
        cin >> j;
    }
    while ((j < 1) || (i > MATRIX_MAX_SIZE));
    // input k
    int k = 0;
    do
    {
        cout << "Input rows matrix2 [1, " << MATRIX_MAX_SIZE << "]: ";
        cin >> k;
    }
    while ((k < 1) || (k > MATRIX_MAX_SIZE));


    double perc = -1;
    do
    {
        cout << "Enter the percentage of filling [0, 100]: ";
    }
    while(!(scanf("%lf", &perc) && (perc >= 0) && (perc <= 100)));

    int **matr1 = create_matrix_array(i, j, perc, -RANGE_ABS_MAX, RANGE_ABS_MAX);
    int **matr2 = create_matrix_array(j, k, perc, -RANGE_ABS_MAX, RANGE_ABS_MAX);
    int **matr_tmp = NULL;
    CMatrix matrix1(i, j, matr1);
    CMatrix matrix2(j, k, matr2);

    // time 1
    time_t tick1 = clock();
    CMatrix matrix_mul = matrix1 * matrix2;
    cout << "Time mulling [R]: "  << clock() - tick1 << endl;

    // time 2
    time_t tick2 = clock();
    matr_tmp = mul_matrix_array(matr1, i, j, matr2, j, k);
    cout << "Time mulling [S]: "  << clock() - tick2 << endl;

    // print memory info
    cout << "Memory [R]: " << matrix1.mem_info() << endl;
    cout << "Memory [S]: " << i * j * sizeof(int) << endl;

    // free memory
    free_matr(matr1, i);
    free_matr(matr2, j);
    free_matr(matr_tmp, i);
}

int main()
{
    srand(time(NULL));
    int num = 0;
    while (num != 3)
    {
        cout << endl;
        cout << "Menu:" << endl;
        cout << " [1]: Mul vector on Matrix" << endl;
        cout << " [2]: Speed test" << endl;
        cout << " [3]: Exit" << endl;
        cout << "Input: ";
        cin >> num;
        switch(num)
        {
            case 1:
                menu_mul_vm();
                break;
            case 2:
                menu_test();
        }
    }
    return EXIT_SUCCESS;
}