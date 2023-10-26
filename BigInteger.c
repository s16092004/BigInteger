//Final
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000000

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

struct BigInteger initialize(char *str)
{
    struct BigInteger l;
    l.length = 0;
    l.sign = 0;
    l.n = NULL;
    int size = strlen(str);
    l.length = size;
    int i=0;
    if (str[0] == '-')
    {
        l.sign = 1;
        size--;
        i++;
    }
    while(str[i]!='\0')
    {
        int digit = str[i] - 48;
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        temp->data = digit;
        temp->next = l.n;
        l.n = temp;
        i++;
    }
    return l;
}

struct BigInteger reverse(struct BigInteger p)
{
    struct node *cur = p.n, *next = NULL, *prev = NULL;
    if (p.n == NULL)
    {
        printf("empty");
        return p;
    }
    while (cur != NULL)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    p.n = prev;
    return p;
}

int length(struct BigInteger h)
{
    int count = 0;
    struct node *head = h.n;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

struct node *newnode(int val)
{
    struct node *tp = (struct node *)malloc(sizeof(struct node));
    tp->data = val;
    tp->next = NULL;
    return tp;
}

struct BigInteger add(struct BigInteger p1, struct BigInteger p2)
{
int l1=length(p1),l2=length(p2);
if(l1<l2)
{
struct node * temp=p1.n;
p1.n=p2.n;
p2.n=temp;
int temp1=l1;
l1=l2;
l2=temp1;
}
    struct BigInteger res;
    res.n = NULL;
    if (p1.n == NULL && p2.n == NULL)
    {
        printf("empty lists");
        return res;
    }
    int n = l1 - l2, i = 0;
    int sum, carry = 0, var;
    struct node *n1 = p1.n;
    struct node *n2 = p2.n;
    struct node *temp = NULL;
    struct node *new_node = NULL;
    while (n2 != NULL)
    {
        sum = n1->data + n2->data + carry;
        var = sum % 10;
        carry = sum / 10;
        new_node = newnode(var);
        if (res.n == NULL)
        {
            res.n = new_node;
            temp = res.n;
            n1 = n1->next;
            n2 = n2->next;
        }
        else
        {
            temp->next = new_node;
            temp = temp->next;
            n1 = n1->next;
            n2 = n2->next;
        }
    }

    if (n == 0 && carry != 0)
    {
        new_node = newnode(carry);
        temp->next = new_node;
    }

    while (i < n)
    {
        sum = n1->data + carry;
        var = sum % 10;
        carry = sum / 10;
        new_node = newnode(var);
        if (res.n == NULL)
        {
            res.n = new_node;
            temp = res.n;
            n1 = n1->next;
        }
        else
        {
            temp->next = new_node;
            temp = temp->next;
            n1 = n1->next;
        }
        i++;
    }
    if (carry != 0)
    {
        new_node = newnode(carry);
        temp->next = new_node;
    }
    return res;
}


int compare(struct BigInteger p1, struct BigInteger p2)
{
    
    int l1 = length(p1), l2 = length(p2);
    int b=-1;
    if(l1>l2)
    {
        return 0;
    }
    else if(l1<l2)
    {

        return 1;
    }
    
    struct BigInteger rp1=reverse(p1);
    struct BigInteger rp2=reverse(p2);
    struct node *n1=rp1.n;
    struct node *n2=rp2.n;
    while(n1!=NULL&&n2!=NULL)
    {
        if(n1->data>n2->data)
        {
            b=0;
            break;
        }
        else if(n1->data<n2->data)
        {
            b=1;
            break;
        }
        else{
        n1=n1->next;
        n2=n2->next;
        }
    }
    p1=reverse(rp1);
    p2=reverse(rp2);
    return b;
}

struct BigInteger sub(struct BigInteger p1, struct BigInteger p2)
{
    int l1 = length(p1), l2 = length(p2);
    if(l1<l2)
    {
    struct node * temp=p1.n;
    p1.n=p2.n;
    p2.n=temp;
    int temp1=l1;
    l1=l2;
    l2=temp1;
    }
   if(l1==l2)
    {
        int n=compare(p1,p2);
        if(n==1)
        {
            struct node* temp=p1.n;
            p1.n=p2.n;
            p2.n=temp;
            int temp1=l1;
            l1=l2;
            l2=temp1;
        }
    }
    struct BigInteger res;
    res.n = NULL;
    if (p1.n == NULL && p2.n == NULL)
    {
        printf("empty lists");
        return res;
    }

    int n = l1 - l2, i = 0;
    int borrow = 0;
    struct node *n1 = p1.n;
    struct node *n2 = p2.n;
    struct node *temp = NULL;
    struct node *new_node = NULL;
   
    while(n1!=NULL)
    {
        int val1=n1->data;
        int val2=(n2!=NULL)?n2->data:0;
        int diff =val1-val2-borrow;
        if(diff<0)
        {
            diff+=10;
            borrow=1;
        }
        else{
            borrow=0;
        }
        new_node=newnode(diff);
        if(res.n==NULL)
        {
            res.n=new_node;
            temp=res.n;
        }
        else{
            temp->next=new_node;
            temp=temp->next;
        }
        if(n2!=NULL)
        {
            n2=n2->next;
        }
        n1=n1->next;
    }
   
    return res;
}
struct BigInteger mul(struct BigInteger p1, struct BigInteger p2) {
    struct BigInteger result;
    result.n = NULL;

    if (p1.n == NULL || p2.n == NULL) {
        printf("empty lists");
        return result;
    }

    int l1 = length(p1);
    int l2 = length(p2);

    int* prod = (int*)malloc(sizeof(int) * (l1 + l2));
    for (int i = 0; i < l1 + l2; i++) {
        prod[i] = 0;
    }

    struct node* n1 = p1.n;
    struct node* n2 = p2.n;

    for (int i = 0; i < l1; i++) {
        int carry = 0;
        n2 = p2.n;

        for (int j = 0; j < l2; j++) {
            int val1 = n1->data;
            int val2 = n2->data;
            int product = val1 * val2 + prod[i + j] + carry;
            carry = product / 10;
            prod[i + j] = product % 10;
            n2 = n2->next;
        }

        int k = l2;
        while (carry > 0) {
            int product = prod[i + k] + carry;
            carry = product / 10;
            prod[i + k] = product % 10;
            k++;
        }

        n1 = n1->next;
    }

    for (int i = l1 + l2 - 1; i >= 0; i--) {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        new_node->data = prod[i];
        new_node->next = result.n;
        result.n = new_node;
        result.length++;
    }

    if (result.n == NULL) {
        result.n = (struct node*)malloc(sizeof(struct node));
        result.n->data = 0;
        result.n->next = NULL;
        result.length = 1;
    }

    free(prod);
   
    return result;
}

void display(struct BigInteger m)
{
    m = reverse(m);
    struct node *itr = m.n;
    while (itr != NULL &&itr->data == 0)
    {
        itr = itr->next;
    }
    m.n=itr;
    struct node *current = m.n;

    if (current == NULL)
    {
        printf("0\n");
        return;
    }

    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}



struct BigInteger div1(struct BigInteger p1,struct BigInteger p2)
{
    struct BigInteger res;
    res=initialize("0");
    if (p1.n == NULL || p2.n == NULL) 
    {
        printf("empty lists");
        return res;
    }
    struct BigInteger divi;
    divi=p2;
    struct BigInteger quo;
    quo=initialize("1");
    while(compare(divi,p1)!=0)
    {
        divi=add(divi,p2);
        res=add(res,quo);
    }
    return res;
}

struct BigInteger mod(struct BigInteger p1,struct BigInteger p2)
{
    struct BigInteger res;
    res=initialize("0");
    if (p1.n == NULL || p2.n == NULL) 
    {
        printf("empty lists");
        return res;
    }
    struct BigInteger divi;
    divi=p2;
    struct BigInteger quo;
    quo=initialize("1");
    while(compare(divi,p1)!=0)
    {
        divi=add(divi,p2);
        res=add(res,quo);
    }
    struct BigInteger rem;
    rem=sub(divi,p1);
    struct BigInteger rom;
    rom=sub(p2,rem);
    return rom;
}


