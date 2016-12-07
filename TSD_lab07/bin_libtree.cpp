#include "bin_libtree.h"

CTreeBin::CTreeBin(void)
{
    this->cnt = 0;
    this->head = NULL;
}

void CTreeBin::free_tree(node_bin *p)
{
    if(p)
    {
        free_tree(p->left);
        free_tree(p->right);
        free(p);
    }
}

CTreeBin::~CTreeBin(void)
{
    this->cnt = 0;
    free_tree(this->head);
}

void CTreeBin::insert_tree(node_bin *p, const char *value)
{
    if (this->is_empty())
    {
        this->head = (node_bin *)malloc(sizeof(node_bin));
        this->head->left = NULL;
        this->head->right = NULL;
        this->head->count = 1;
        this->head->value = (char *)value;
        return;
    }
    int cmp = strcmp(p->value, value);
    if (cmp == 0)
    {
        p->count++;
    }
    else if (cmp > 0)
    {
        if (p->left == NULL)
        {
            p->left = (node_bin *)malloc(sizeof(node_bin));
            p->left->left = NULL;
            p->left->right = NULL;
            p->left->count = 1;
            p->left->value = (char *)value;
        }
        else
            insert_tree(p->left, value);
    }
    else if (cmp < 0)
    {
        if (p->right == NULL)
        {
            p->right = (node_bin *)malloc(sizeof(node_bin));
            p->right->left = NULL;
            p->right->right = NULL;
            p->right->count = 1;
            p->right->value = (char *)value;
        }
        else
            insert_tree(p->right, value);
    }
}

void CTreeBin::insert(const char *value)
{
    this->cnt++;
    insert_tree(this->head, value);
}

node_bin *CTreeBin::search_tree(node_bin *p, const char *value)
{
    this->cmp++;
    int cmp = strcmp(p->value, value);
    if (cmp == 0)
    {
        return p;

    }
    else if (cmp > 0)
    {
        if (p->left != NULL)
            return search_tree(p->left, value);
        else
            return NULL;
    }
    else if (cmp < 0)
    {
        if (p->right != NULL)
            return search_tree(p->right, value);
        else
            return NULL;
    }
}

node_bin *CTreeBin::search(const char *value)
{
    this->cmp = 0;
    return search_tree(this->head, value);
}

int CTreeBin::is_empty(void)
{
    return this->head == NULL ? 1 : 0;
}

unsigned CTreeBin::get_memory(void)
{
    return this->cnt * sizeof(node_bin);
}

unsigned CTreeBin::get_cmp(void)
{
    return this->cmp;
}

void print_line(char buf[], int pos, char last)
{
    if (pos == -1)
        return;
    print_line(buf, pos - 1, buf[pos]);
    if (last != 'r' && last != 'l')
    {
        if (buf[pos] == 'l')
            std::cout << LU_BORDER << HOR_BORDER << HOR_BORDER << HOR_BORDER;
        if (buf[pos] == 'r')
            std::cout << LD_BORDER << HOR_BORDER << HOR_BORDER << HOR_BORDER;
        return;
    }
    if (last == buf[pos])
        std::cout << "    ";
    else
    {
        std::cout << VER_BORDER << "   ";
    }

}

void CTreeBin::print_tree(node_bin *p, int num)
{
    static char buf[255] = {0}; // MAX_PATH
    static unsigned char pos = 0;
    if(p)
    {
        buf[pos++] = 'l';
        print_tree(p->left, num + 1);
        pos--;
        print_line(buf, pos - 1, '#');
        std::cout << p->value << "(" << p->count << ")" << std::endl;
        buf[pos++] = 'r';
        print_tree(p->right, num + 1);
        pos--;
    }
}

void CTreeBin::print(void)
{
    if (!this->head)
        std::cout << "Tree is empty!" << std::endl;
    else
        this->print_tree(this->head, 0);
}
