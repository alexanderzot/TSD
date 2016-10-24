#include "libio.h"

void input_name(student_t *st, FILE *f)
{
    int flag = 0;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("Name: ");

        int pos = 0;
        int first = 1;
        while ( pos < NAME_LEN && fscanf(f, "%c", &(st->name[pos])) && st->name[pos] != '\n')
        {
            if ( !(isspace(st->name[pos]) && first) )
            {
                first = 0;
                pos++;
            }
        }
        if (st->name[pos] == '\n')
        {
            st->name[pos] = '\0';
            flag = 1;
        }
        else
        {
            char ch;
            while( fscanf(f, "%c", &ch) && ch != '\n' )
                flag = 0;
        }
    }
    while( flag == 0 );
}

void input_sex(student_t *st, FILE *f)
{
    int flag = 0;
    char sex;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("Sex (M or F): ");
        flag = fscanf(f, "%c", &sex);
        if ( sex != 'm' && sex != 'M' && sex != 'f' && sex != 'F' )
            flag = 0;
        // read all chars
        char ch;
        while( fscanf(f, "%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    if (sex == 'm' || sex == 'M')
        st->sex = MALE;
    else
        st->sex = FEMALE;
}

void input_height(student_t *st, FILE *f)
{
    int flag = 0;
    byte_t h;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("Height (140..200): ");
        flag = fscanf(f, "%uc", &h);
        if (h < 140 || h > 200)
            flag = 0;
        // read all chars
        char ch;
        while( fscanf(f, "%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    st->height = h;
}

void input_point(student_t *st, FILE *f)
{
    int flag = 0;
    float ball;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("Avarage point: ");
        flag = fscanf(f, "%f", &ball);
        // read all chars
        char ch;
        while( fscanf(f, "%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    st->point = ball;
}

void input_type(student_t *st, FILE *f)
{
    int flag = 0;
    int num_type;
    do
    {
        flag = 0;
        if (f == stdin)
        {
            printf("[1] House\n");
            printf("[2] Hostel\n");
            printf("Type: ");
        }
        flag = fscanf(f, "%2d", &num_type);
        if (num_type != 1 && num_type != 2)
            flag = 0;
        // read all chars
        char ch;
        while( fscanf(f, "%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    if (num_type == 1)
        st->digs = HOUSE;
    else if (num_type == 2)
        st->digs = HOSTEL;
}
void input_street(student_t *st, FILE *f)
{
    int flag = 0;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("Street: ");

        int pos = 0;
        int first = 1;
        while ( pos < STREET_LEN && fscanf(f, "%c", &(st->address.house.street[pos])) && st->address.house.street[pos] != '\n')
        {
            if ( !(isspace(st->address.house.street[pos]) && first) )
            {
                first = 0;
                pos++;
            }
        }
        if (st->address.house.street[pos] == '\n')
        {
            st->address.house.street[pos] = '\0';
            flag = 1;
        }
        else
        {
            char ch;
            while( fscanf(f, "%c", &ch) && ch != '\n' )
                flag = 0;
        }
    }
    while( flag == 0 );
}

void input_house_num(student_t *st, FILE *f)
{
    int flag = 0;
    int num;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("House num: ");
        flag = fscanf(f, "%3d", &num);
        if (num < 0 || num > 255)
            flag = 0;
        // read all chars
        char ch;
        while( fscanf(f, "%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    st->address.house.num_house = num;
}

void input_apart_num(student_t *st, FILE *f)
{
    int flag = 0;
    int num = 0;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("Appartment num: ");
        flag = fscanf(f, "%3d", &num);
        if (num < 0 || num > 255)
            flag = 0;
        // read all chars
        char ch;
        while( fscanf(f, "%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    st->address.house.num_apart = num;
}

void input_hostel_num(student_t *st, FILE *f)
{
    int flag = 0;
    int num;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("Hostel num: ");
        flag = fscanf(f, "%3d", &num);
        if (num < 0 || num > 255)
            flag = 0;
        // read all chars
        char ch;
        while( fscanf(f, "%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    st->address.hotel.num_hostel = num;
}

void input_room_num(student_t *st, FILE *f)
{
    int flag = 0;
    int num = 0;
    do
    {
        flag = 0;
        if (f == stdin)
            printf("Root num: ");
        flag = fscanf(f, "%3d", &num);
        if (num < 0 || num > 255)
            flag = 0;
        // read all chars
        char ch;
        while( fscanf(f, "%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    st->address.hotel.num_room = num;
}

void input_student(student_t *st, FILE *f)
{
    input_name(st, f);
    input_sex(st, f);
    input_height(st, f);
    input_point(st, f);
    input_type(st, f);

    if (st->digs == HOUSE)
    {
        input_street(st, f);
        input_house_num(st, f);
        input_apart_num(st, f);
    }
    else if (st->digs == HOSTEL)
    {
        input_hostel_num(st, f);
        input_room_num(st, f);
    }
}

void print_student(student_t *st)
{
    printf("Name: %s\n", st->name);
    printf("Sex: %s\n", st->sex == MALE ? "Male" : "Female" );
    printf("Height: %u\n", st->height);
    printf("Avarage point: %f\n", st->point);

    if (st->digs == HOUSE)
    {
        printf("Type: house\n");
        printf("Street: %s\n", st->address.house.street);
        printf("House num: %d\n", st->address.house.num_house);
        printf("Apartment num: %d\n", st->address.house.num_apart);
    }
    else if (st->digs == HOSTEL)
    {
        printf("Type: hostel\n");
        printf("Hostel num: %d\n", st->address.hotel.num_hostel);
        printf("Room num: %d\n", st->address.hotel.num_room);\
    }
}
