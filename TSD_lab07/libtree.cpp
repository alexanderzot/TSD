#include "libtree.h"

CTree::CTree(void)
{
    this->cnt = 0;
    this->head = NULL;
}

void CTree::free_tree(node *p)
{
    if (!p)
        return;
    this->free_tree(p->left);
    p->left = NULL;
    this->free_tree(p->right);
    p->right = NULL;
    p->height = 0;
    free((char *)p->value);
    delete p;
}

CTree::~CTree(void)
{
    this->free_tree(this->head);
}

unsigned char CTree::get_height(node *p)
{
	return p ? p->height : 0;
}

int CTree::calc_factor(node *p)
{
	return get_height(p->right) - get_height(p->left);
}

void CTree::calc_height(node *p)
{
	unsigned char height_l = get_height(p->left);
	unsigned char height_r = get_height(p->right);
	p->height = (height_l > height_r ? height_l : height_r) + 1;
}

node *CTree::right_rot(node *p)
{
	node *q = p->left;
	p->left = q->right;
	q->right = p;
    calc_height(p);
    calc_height(q);
	return q;
}

node *CTree::left_rot(node *q)
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
    calc_height(q);
    calc_height(p);
	return p;
}

node *CTree::balance(node *p)
{
    calc_height(p);
	if (calc_factor(p) == ROT_RIGHT)
	{
		if (calc_factor(p->right) < 0)
			p->right = right_rot(p->right);
		return left_rot(p);
	}
	if (calc_factor(p) == ROT_LEFT)
	{
		if (calc_factor(p->left) > 0)
			p->left = left_rot(p->left);
		return right_rot(p);
	}
	return p;
}

node *CTree::insert_tree(node *p, const char *value)
{
	if (!p)
        return new node(value);
	if (strcmp(value, p->value) > 0)
		p->left = insert_tree(p->left, value);
	else if (strcmp(value, p->value) < 0)
		p->right = insert_tree(p->right, value);
    else
        p->count++;
	return balance(p);
}

node *CTree::search_tree(node *p, const char *value)
{
	if (!p)
        return NULL;
    this->cmp++;
	if (strcmp(value, p->value) > 0)
		return search_tree(p->left, value);
	else if (strcmp(value, p->value) < 0)
		return search_tree(p->right, value);
    else
        return p;
}

node *CTree::find_min(node *p)
{
	return p->left ? find_min(p->left) : p;
}

node *CTree::remove_min(node *p)
{
	if (p->left == 0)
		return p->right;
	p->left = remove_min(p->left);
	return balance(p);
}

node *CTree::remove_tree(node *p, const char *value, int *status)
{
	if (!p)
        return 0;
	if (strcmp(value, p->value) > 0)
		p->left = remove_tree(p->left, value, status);
	else if(strcmp(value, p->value) < 0)
		p->right = remove_tree(p->right, value, status);
	else
	{
	    *status = 1;
		node *q = p->left;
		node *r = p->right;
		delete p;
		if(!r)
            return q;
		node *min = find_min(r);
		min->right = remove_min(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

static void print_line(char buf[], int pos, char last)
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

void CTree::print_tree(node *p, int num)
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

void CTree::print(void)
{
    if (!this->head)
        std::cout << "Tree is empty!" << std::endl;
    else
        this->print_tree(this->head, 0);
}

void CTree::insert(const char *value)
{
    this->cnt++;
    this->head = this->insert_tree(this->head, value);
}

int CTree::remove(const char *value)
{
    this->cnt--;
    int status = 0;
    this->head = this->remove_tree(this->head, value, &status);
    return status;
}

node *CTree::search(const char *value)
{
    this->cmp = 0;
	return search_tree(this->head, value);
}

int CTree::is_empty(void)
{
    return this->head == NULL ? 1 : 0;
}

void CTree::remove_tree_char(node *p,  char ch)
{
	if (!p)
        return;
    remove_tree_char(p->left, ch);
    remove_tree_char(p->right, ch);
    if (p->value[0] == ch)
        this->remove(p->value);
}

void CTree::remove_char(char ch)
{
    this->remove_tree_char(this->head, ch);
}

unsigned CTree::get_memory(void)
{
    return this->cnt * sizeof(struct node);
}

unsigned CTree::get_cmp(void)
{
    return this->cmp;
}
