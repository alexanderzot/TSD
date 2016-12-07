#include "libio.h"

char *read_line(FILE *f, int *err_code)
{
    size_t pos = 0;
    size_t max_pos = BEGIN_BUFF_SIZE;
    char *buf = (char *)malloc( sizeof(char) * max_pos );
    if (!buf)
    {
        *err_code = ERROR_ALLOC_MEM;
        return NULL;
    }
    ///buf[0] = '\0';

    char str[BUFF_SIZE] = "";
    while (fgets(str, BUFF_SIZE, f) != NULL)
    {
        size_t j = 0;
        // if first char in line is new line
        if (str[0] == '\n' && !pos)
            buf[pos++] = '\0';
        while ( str[j] != '\n' && str[j] != '\0')
        {
            // allocated memory
            if (pos >= max_pos)
            {
                max_pos <<= 1;
                char *new_buf = (char *)malloc( sizeof(char) * max_pos );
                if (!new_buf)
                {
                    free(buf);
                    *err_code = ERROR_ALLOC_MEM;
                    return NULL;
                }
                // copy
                strncpy(new_buf, buf, pos);
                // free old memory
                free(buf);
                buf = new_buf;
            }
            buf[pos++] = str[j++];
        }
        if (str[strlen(str) - 1] == '\0' || str[strlen(str) - 1] == '\n')
            break;
    }
    // create buffer result for string
    char *res = NULL;
    if (pos > 0)
    {
        // allocated mmory for result
        res = (char *)malloc( sizeof(char) * (pos + 1) );
        if (!res)
        {
            free(buf);
            *err_code = ERROR_ALLOC_MEM;
            return NULL;
        }
        // copy string to new buffer
        strncpy(res, buf, pos);
        // write string end
        res[pos] = 0;
    }
    // free memory and return buffer
    //free(buf);
    if (pos == 0)
        *err_code = ERROR_EOF;
    else
        *err_code = ERROR_NO;
    //return res;
    return res;
}

int is_simple(unsigned num)
{
    for (register unsigned i = 2; i * i <= num; ++i)
        if (num % i == 0)
            return 0;
    return 1;
}

unsigned get_pred_simple(unsigned num)
{
    unsigned tmp = 1;
    unsigned i = 2;
    while(i < num)
    {
        if (is_simple(i))
            tmp = i;
        i++;
    }
    return tmp;
}

int menu_value(void)
{
    int value = 0;
    int flag = 0;
    do
    {
        flag = 0;
        cout << "Input: ";
        flag = scanf("%1d", &value);
        // read all chars
        char ch;
        while( scanf("%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    return value;
}

unsigned get_next_simple(unsigned num)
{
    unsigned tmp = get_pred_simple(num) + 1;
    for(tmp; !is_simple(tmp); ++tmp);
    return tmp;
}
