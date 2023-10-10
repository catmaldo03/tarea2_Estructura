#include <stdio.h>
#include <stdlib.h>
//cambiar algunos int a bool - Equals - Unequals
typedef int elementType;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node {
    elementType element;
    Position Next;
    Position Prev;
};

typedef List Set;

Set MakeEmpty(Set A) {
    A = malloc(sizeof(struct Node));
    if (A == NULL) {
        printf("Out of memory");
    }
    A->Next = A;
    A->Prev = A;
    return A;
}

int IsEmpty(Set A) {
    if ((A->Next == A) && (A->Prev == A))
        return 1;
    else
        return 0;
}
void First (Set A, Position P){
    P->Prev = A;
    P->Next = A;
}
void AddSet(elementType x, Set L) {
    Position P = L->Prev; 
    Position TmpCell;

    TmpCell = malloc(sizeof(struct Node));
    if (TmpCell == NULL) {
        printf("Out of memory");
        return;
    }

    TmpCell->element = x;
    TmpCell->Next = L; 
    TmpCell->Prev = P; 
    L->Prev = TmpCell; 
    P->Next = TmpCell; 
}
void Delset(elementType x, Set A){
    Position P, TmpCell;
    P=A->Next;
    while (P!=A && P->element != x)
        P=P->Next;
    TmpCell = P;
    P= TmpCell->Prev;
    P->Next = TmpCell->Next;

    free(TmpCell);
}
int Min(Set A)
{// Falta poner IsEmpty
    int minimun;
    Position P;
    P=A->Next;
    minimun= P->element;
    while (P!=A){
        if(P->element<minimun)
            minimun = P->element;
        P=P->Next;
    }
    return minimun;
}
int Max(Set A)
{// Falta poner IsEmpty
    int maxinum;
    Position P;
    P=A->Next;
    maxinum= P->element;
    while (P!=A){
        if(P->element>maxinum)
            maxinum = P->element;
        P=P->Next;
    }
    return maxinum;
}
int GetElem(int Pos, Set A){
    //falta condicional en caso de que el elemento no este en la lista
    int i;
    Pos=Pos-1;
    Position P;
    P=A->Next;
    for(i=0; i<Pos&& P!=A;i++){
        P=P->Next;
    }
    return P->element;
}
int Cardinality(Set A){
    //condicional de lista vacia
    int cuantity=0;
    Position P;
    P=A->Next;
    while (P!=A){
        P=P->Next;
        cuantity++;
    }
    return cuantity;
}
int Membership(elementType x, Set A){
    Position P;
    P=A->Next;
    while (P!=A){
        if(P->element==x)
            return 1;
        P=P->Next;
        
    }
    return 0;
}
int Equals(Set A, Set B){
    if (Cardinality(A) != Cardinality(B)){
        return 0;
    }
    Position P = A->Next;
    while(P!=A)
    {
        int found;
        found =0;
        Position Q;
        Q = B->Next;
        while(Q!=B){
            if(Q->element==P->element){
                found = 1;
                break;
            }
            Q=Q->Next;
        }
        if(!found)
            return 0;
        P=P->Next;
    }
    return 1;
}
int Unequals(Set A, Set B){
    if(Equals(A,B)==0)
        return 1;
    else if(Equals(A,B)==1)
        return 0;
}
int Subset(Set A, Set B){
    if (Cardinality(A) > Cardinality(B)){
        return 0;
    }
    Position P = A->Next;
    while(P!=A)
    {
        int found;
        found =0;
        Position Q;
        Q = B->Next;
        while(Q!=B){
            if(Q->element==P->element){
                found = 1;
                break;
            }
            Q=Q->Next;
        }
        if(!found)
            return 0;
        P=P->Next;
    }
    return 1;
}
Set Union(Set A, Set B){
    Set NewSet = MakeEmpty(NULL);
    Position P=A->Next;
    while(P!=A){
        int found = 0; 
        Position Q = B->Next;
        while (Q != B) {
            if (P->element == Q->element) {
                found = 1;
                break;
            }
            else{
                AddSet(Q->element, NewSet);
            }
            Q = Q->Next;
        }

        if (found) {
            AddSet(P->element, NewSet);
        }
        else{
            AddSet(P->element, NewSet);
        }

        P = P->Next;
    }
    return NewSet;
}//Set A + Set B - Intersectiction (A,B)
Set Intersection(Set A, Set B) {
    Set NewSet = MakeEmpty(NULL);
    Position P = A->Next;
    while (P != A) {
        int found = 0; 
        Position Q = B->Next;
        while (Q != B) {
            if (P->element == Q->element) {
                found = 1;
                break;
            }
            Q = Q->Next;
        }

        if (found) {
            AddSet(P->element, NewSet);
        }
        P = P->Next;
    }

    return NewSet; 
} //Set A + Set B - Union(A,B)s
Set Complement(Set A, Set B){
    Set NewSet = MakeEmpty(NULL);
    Position P=B->Next;
    while(P!=B){
        int found = 0; 
        Position Q = A->Next;
        while (Q != A) {
            if (P->element == Q->element) {
                found = 1;
                break;
            }
            Q = Q->Next;
        }

        if (!found) {
            AddSet(P->element, NewSet);
        }
        P = P->Next;
    }
    return NewSet;
} //Set B complemento = Set A - Intersection (A,B)
int main() {
    Set A, B, C, D;
    int i;
    A = MakeEmpty(A);
    B = MakeEmpty(B);
    C = MakeEmpty(C);
    if (IsEmpty(C))
        printf("C esta vacio");
    AddSet(10,A);
    AddSet(11,A);
    AddSet(9,A);
    AddSet(12,B);
    AddSet(11,B); //debemos comprobar que el numero no se asigne dos veces
    AddSet(9,B);
    //printf("\n%d", A->Next->element);
    //printf("\n%d", A->Next->Next->element);
    //printf("\n%d", A->Next->Next->Next->element);
    //Delset(9,A);
    //printf("\n%d", A->Next->element);
    //printf("\n%d", A->Next->Next->element);
    //printf("\nMinimo: %d", Min(A));
    //printf("\nMaximo: %d", Max(A));
    //i=2;
    //printf("\nEn la posicion:%d, esta el elemento: %d",i,GetElem(i,A));
    //D = Union(A,B);
    //printf("\n%d",Cardinality(A));
    //printf("\n%d",Membership(9,A));
    //printf("\n%d",Equals(A,B));
    //printf("\n%d",Unequals(A,B));
    //printf("\n%d",Subset(A,B));
   // D = Intersection(A, B);
    //printf("\n%d", D->Next->element);
    //printf("\n%d", D->Next->Next->element);
    D= Complement(A,B);
    Position P= D->Next;
    printf("A\n");
    for(i=0;i<4;i++){
        printf("%d\n", P->element);
        P=P->Next;
    }
    return 0;
}
