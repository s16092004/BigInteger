#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *n;
    int length;
    int sign;
};

struct BigInteger initialize(char *);
struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct BigInteger mul(struct BigInteger,struct BigInteger);
struct BigInteger div1(struct BigInteger,struct BigInteger);
void display(struct BigInteger);

#endif