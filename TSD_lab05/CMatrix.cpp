#include "CMatrix.h"

CMatrix::CMatrix()
{
    this->IA = NULL;
    this->NA = 0;
    this->N = 0;
    this->M = 0;
}

CMatrix::CMatrix(int n_arr, int m_arr, int **arr)
{
    this->N = n_arr;
    this->M = m_arr;
    this->NA = 0;
    this->IA = NULL;
    node_t *IA_tail = NULL;
    int flag = 0;

    for (register int i = 0; i < this->N; ++i)
    {
        node_t* tmp = node_create(NA);
        if (!this->IA)
            this->IA = IA_tail = tmp;
        else
        {
            IA_tail->next = tmp;
            IA_tail = IA_tail->next;
        }
        for (register int j = 0; j < this->M; ++j)
        {
            if (arr[i][j])
            {
                this->A.push_back(arr[i][j]);
                this->JA.push_back(j);
                this->NA++;
                flag = 1;
            }
        }
        if (flag == 0)
            tmp->value = INFINITY;
    }
    IA_tail->next = node_create(this->NA);
}

CMatrix::~CMatrix()
{
    list_free(this->IA);
}

CMatrix::CMatrix(const CMatrix &obj)
{
    *this = obj;
}

CMatrix &CMatrix::operator =(const CMatrix &obj)
{
    if (this == &obj)
    {
        return *this;
    }
    if (this->IA)
        list_free(this->IA);
    this->NA = obj.NA;

    if (!this->JA.empty())
        this->JA.erase(this->JA.begin(), this->JA.end());
    if (!this->A.empty())
        this->A.erase(this->A.begin(), this->A.end());

    for (register int i = 0; i < this->NA; i++)
    {
        this->JA.push_back(obj.JA[i]);
        this->A.push_back(obj.A[i]);
    }

    this->N = obj.N;
    this->M = obj.M;
    this->IA = list_copy(obj.IA);
    return *this;
}

CMatrix CMatrix::operator *(CMatrix &obj)
{
    CMatrix res = CMatrix();
    CMatrix copy = obj;
    copy.trans();
    res.IA = NULL;
    node_t *IA_tail = NULL;
    node_t *tmp1_i = this->IA;
    int flag = 0;
    for (register int i = 0; i < this->N; ++i)
    {
        node_t* tmp = node_create((int) res.A.size());
        if (!res.IA)
            res.IA = IA_tail = tmp;
        else
        {
            IA_tail->next = tmp;
            IA_tail = IA_tail->next;
        }

        int A1_begin = tmp1_i->value;
        int A1_end = tmp1_i->next->value;
        node_t *tmp2_i = copy.IA;
        for (register int j = 0; j < copy.N; ++j)
        {
            int mult = 0;
            int A2_begin = tmp2_i->value;
            int A2_end = tmp2_i->next->value;
            for (register int k1 = A1_begin, k2 = A2_begin; k1 < A1_end && k2 < A2_end; )
            {
                if (this->JA[k1] == copy.JA[k2])
                    mult += this->A[k1++] * copy.A[k2++];
                else if (this->JA[k1] < copy.JA[k2])
                    k1++;
                else
                    k2++;
            }
            if (mult)
            {
                res.A.push_back(mult);
                res.JA.push_back(j);
                flag = 1;
            }
            tmp2_i = tmp2_i->next;
        }
        if(flag == 0)
            tmp->value = INFINITY;
        tmp1_i = tmp1_i->next;
    }
    res.NA = (int)res.A.size();
    if (IA_tail)
        IA_tail->next = node_create(res.NA);
    else
        IA_tail = node_create(res.NA);
    res.N = this->N;
    res.M = obj.M;
    return res;
}

void CMatrix::trans(void)
{
    vector <vector <int> > new_A (M);
    vector <vector <int> > new_JA (M);

    node_t *tmp_i = this->IA;
    for (register int i = 0; i < this->N; ++i)
    {
        int tmp_b = tmp_i->value;
        int tmp_e = tmp_i->next->value;
        for (register int k = tmp_b; k < tmp_e; ++k)
        {
            new_A[JA[k]].push_back(A[k]);
            new_JA[JA[k]].push_back(i);
        }
        tmp_i = tmp_i->next;
    }
    this->A.erase(this->A.begin(), this->A.end());
    this->JA.erase(this->JA.begin(), this->JA.end());
    list_free(IA);

    this->IA = NULL;
    node_t* IA_tail = NULL;
    int flag = 0;

    for (register int i = 0; i < this->M; ++i)
    {
        node_t* tmp = node_create((int) A.size());
        if (!this->IA)
            this->IA = IA_tail = tmp;
        else
        {
            IA_tail->next = tmp;
            IA_tail = IA_tail->next;
        }

        for (register int j = 0; j < new_A[i].size(); ++j)
        {
            this->A.push_back(new_A[i][j]);
            this->JA.push_back(new_JA[i][j]);
            flag = 1;
        }
        if(flag == 0)
            tmp->value = INFINITY;
    }
    this->NA = this->A.size();
    IA_tail->next = node_create(this->NA);
    swap(this->N, this->M);
}

void CMatrix::matrix_info(void)
{
    cout << "N = " << this->N << endl;
    cout << "M = " << this->M << endl;
    cout << "A: ";
    for (register int i = 0; i < this->NA; ++i)
        cout << A[i] << " ";
    cout << endl;
    cout << "JA: ";
    for (register int i = 0; i < this->NA; ++i)
        cout << JA[i] << " ";

    cout << endl;
    cout << "IA_list: ";
    list_print(IA);
    cout << endl;
}

int CMatrix::mem_info(void)
{
    return (this->NA * 2 + this->M) * sizeof(int) + sizeof(node *) * this->NA;
}

int **CMatrix::to_array(void)
{
    int **res = new int *[N];
    for (register int i = 0; i < this->N; ++i)
        res[i] = new int [M];

    node_t *tmp = IA;
    for (register int i = 0; i < this->N; ++i)
    {
        for(register int j = 0; j < this->M; ++j)
            res[i][j] = 0;
        int tmp_b = tmp->value;
        int tmp_e = tmp->next->value;
        for (register int k = tmp_b; k < tmp_e; ++k)
            res[i][JA[k]] = A[k];
        tmp = tmp->next;
    }
    return res;
}
