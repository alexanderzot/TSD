#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#define NAME_LEN 20
#define STREET_LEN 30

typedef unsigned char byte_t;

typedef enum {HOUSE, HOSTEL} digs_t;
typedef enum {MALE, FEMALE} sex_t;

typedef struct
{
    char street[STREET_LEN];
    byte_t num_house;
    byte_t num_apart;
} house_t;

typedef struct
{
    byte_t num_room;
    byte_t num_hostel;
} hostel_t;

typedef union
{
    house_t house;
    hostel_t hotel;
} address_t;

// 68 byte
typedef struct
{
    char name[NAME_LEN];
    sex_t sex;
    byte_t height;
    float point;
    digs_t digs;
    address_t address;
} student_t;

#endif // TYPES_H_INCLUDED
