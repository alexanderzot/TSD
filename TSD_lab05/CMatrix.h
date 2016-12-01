#ifndef LABA5_CMATRIX_H
#define LABA5_CMATRIX_H

#include "CList.h"
#include <assert.h>
#include <vector>
#include <time.h>

class CMatrix
{
private:
    int N = 0;
    int M = 0;
    int NA = 0;
    vector<int> A;
    vector<int> JA;
    node_t *IA = NULL;
public:
    CMatrix();
    CMatrix(int n_arr, int m_arr, int **arr);
    ~CMatrix();
    CMatrix(const CMatrix &obj);
    CMatrix &operator =(const CMatrix &obj);
    CMatrix operator *(CMatrix &obj);
    void trans(void);
    void matrix_info(void);
    int mem_info(void);
    int **to_array(void);
};

#endif
