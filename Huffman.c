#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "huffman.h"

void init_tree(Tree **S){
    *S = NULL;
    return;
}

void init_store(Store **H){
    *H = NULL;
    return;
}

void init_stack(Stack **T)
{
    *T = NULL;
    return;
}


void insert_store(Store **Q, Tree *W){
    //this is used for storing sorted tree in increasing order
    Store *R, *T;
    R = NULL;
    T = NULL;
    T = *Q;
    R = (Store *)malloc(sizeof(Store));
    R -> A = W;
    if(T == NULL){
        R -> next = NULL;
        *Q = R;
        T = *Q;
        return;
    }
    if(T -> A -> freq > W -> freq){
        R -> next = T;
        *Q = R;
        T = R;
        return;
    }
    while(T -> next != NULL && T -> next -> A -> freq < W -> freq){
        T = T -> next;
    }
    R -> next = T -> next;
    T -> next = R;
    return;
}

void insert_tree(Tree **S){
    FILE *F;
    Store *G;
    init_store(&G);
    char W[50];
    F = fopen("Freq.txt", "r");
    Tree *X, *Y, *Z, *Combn;
    char x, *B;
    int y = 0, *U, v = 0, i;
    U = (int *)malloc(sizeof(int)*200);
    B = (char *)malloc(sizeof(char)*200);
    while(fgets(W, 50, F) != NULL){
        x = W[0];
        i = 0;
        y = 0;
        if(x == '\n'){
            fgets(W, 50, F);
        }
        fgets(W, 50, F);
        while(W[i+1] != '\0'){
            y = y*10+(W[i]-'0');
            i++;
        }
        //y = W[0] - '0';
        U[v] = y;
        B[v] = x;
        v++;
    }
    fclose(F);
    //till now, data and frequency is read from file and stored into U & V
    for(int y = 0;y < v;y++){
        X = (Tree *)malloc(sizeof(Tree));
        X -> c = B[y];
        X -> freq = U[y];
        X -> left = NULL;
        X -> right = NULL;
        X -> parent = NULL;
        insert_store(&G, X);
    }
    while(G != NULL){
        Y = G -> A;
        Z = G -> next -> A;
        Combn = (Tree *)malloc(sizeof(Tree));
        Combn -> left = Y;
        Combn -> right = Z;
        Combn -> parent = NULL;
        Y -> parent = Combn;
        Z -> parent = Combn;
        Combn -> c = '\0';
        Combn -> freq = Y -> freq + Z -> freq;
        if(G -> next -> next == NULL){
            *S = Combn;
            return;
        }
        G = G -> next -> next;
        insert_store(&G, Combn);
    }
    return;
}

void postorder_traversal(Tree *Y)
{
     Tree *L;
     L = Y;
     if(L == NULL){
        return;
     }
     postorder_traversal(L -> left);
     postorder_traversal(L -> right);
     printf("%d ", L -> freq);
     printf("%c,", L -> c);
     return;
}

int Get(CharFreq *M, char e){
    CharFreq *E;
    E = M;
    while(E -> a != e){
        E = E -> next;
    }
    return E -> freq;
}

void push_stack(Stack **W, Tree *A)
{
    Stack *D;
    D = (Stack *)malloc(sizeof(Stack));
    D -> ptr = A;
    if(*W == NULL){
        *W = D;
        D -> next = NULL;
    }
    else{
        D -> next = *W;
        *W = D;
    }
    return;
}

char *Convert(Tree *T, char *ch, int Freq)
{
    Stack *A;
    init_stack(&A);
    Tree *R;//, *Y;
    R = T;
    char *X = (char *)malloc(sizeof(char)*100); //previously 20
    if(R != NULL){
        push_stack(&A, R);
    }
    while(A != NULL){
        Tree *Y, *Z;
        Y = A -> ptr;
        A = A -> next;
        //above two lines are doing a job of pop operation on Stack
        if(Y -> c == ch[0] && Y -> freq == Freq){
            Z = Y;
            int i = 0;
            while(Z -> parent != NULL){
                if(Z -> parent -> left == Z){
                    X[i] = '0';
                }
                else if(Z -> parent -> right == Z){
                    X[i] = '1';
                }
                i++;
                Z = Z -> parent;
            }
            X[i] = '\0';
            free(A);
            A = NULL;
            return strrev(X);
        }
        if(Y -> right != NULL){
            push_stack(&A, Y -> right);
        }
        if(Y -> left != NULL){
            push_stack(&A, Y -> left);
        }
    }
    return '\0';
}


void BinConv(Tree *T, CharFreq *N)
{
     CharFreq *L;
     L = N;
     FILE *fptr;
     //printf("\n\nBinary file error : ");
     fptr = fopen("bin.txt", "w");
     char *C;
     int b;
     C = (char *)malloc(sizeof(char)*20);
     while(L != NULL){
        b = L -> freq;
        C = Convert(T, &L -> a, b);
        //printf("%c %s\n", L -> a, C);
        fprintf(fptr, "%c\n", L -> a);
        fprintf(fptr, "%s\n", C);
        L = L -> next;
     }
     fclose(fptr);
}

void init_charfreq(CharFreq **T){
    *T = NULL;
    return;
}

void insert_charfreq(CharFreq **Q, int data, int t){
    CharFreq *I, *J;
    char x = (char)t;
    I = *Q;
    J = (CharFreq *)malloc(sizeof(CharFreq));
    J -> a = x;
    J -> freq = data;
    if(I == NULL){
        I = J;
        I -> next = NULL;
        *Q = I;
        return;
    }
    J -> next = I;
    I = J;
    *Q = I;
    return;
}

//read data from Data.txt file and store into Freq.txt CharFreq Linked List
CharFreq *GetFreq(){
    CharFreq *B;
    init_charfreq(&B);
    FILE *fptr, *Wfptr;
    char W[400];
    fptr = fopen("Data.txt", "r");
    Wfptr = fopen("Freq.txt", "w");
    int E[256] = {0};
    int i;
    while(fgets(W, 400, fptr) != NULL){
        i = 0;
        while(W[i] != '\0'){                                //this is because ascii value of \0 is zero
            E[W[i] - '\0'] = E[W[i] - '\0'] + 1;
            i++;
        }
    }
    for(i = 0;i < 256;i++){
        if(E[i] != 0){
            fprintf(Wfptr, "%c\n", i);                      //prints character
            fprintf(Wfptr, "%d\n", E[i]);                   //prints frequency
            insert_charfreq(&B, E[i], i);                            //stores ascii value and freq in CharFreq linked list
        }
    }
    fclose(fptr);
    fclose(Wfptr);
    return B;
}

void init_encode(encode **S){
    *S= NULL;
    return;
}

void insertEncode(encode **S, char U[5], char T[100]){
    encode *Y;
    Y = (encode *)malloc(sizeof(encode));
    int o = 0;
    while(U[o] != '\0'){
        Y -> chr[o] = U[o];
        o++;
    }
    Y -> chr[o] = '\0';
    //Y -> chr[0] = U[0];
    int i = 0;
    while(T[i] != '\0'){
        Y -> freq[i] = T[i];
        i++;
    }
    Y -> freq[i] = '\0';
    if(*S == NULL){
        Y -> next = NULL;
        *S = Y;
        return;
    }
    Y -> next = *S;
    *S = Y;
    return;
}

encode *CreateBF(){
    FILE *ab;
    ab = fopen("bin.txt", "r");
    encode *A;
    init_encode(&A);
    char W[100];
    int i;
    while(fgets(W, 100, ab) != NULL){
        i = 0;
        char Character[5], binary[100];
        while(W[i] != '\0'){
            Character[i] = W[i];
            i++;
        }
        Character[i] = '\0';
        i = 0;
        fgets(W, 100, ab);
        while(W[i] != '\0'){
            binary[i] = W[i];
            i++;
        }
        binary[i] = '\0';
        insertEncode(&A, Character, binary);
    }
    return A;
}

int calculate(char C[20]){
    int i = 0, sum = 0;
    while(i < 8){
        if(C[i] == '1'){
            sum += pow(2, 7-i);
        }
        i++;
    }
    return sum;
}

float bin(encode *S){
    FILE *fptr, *Wfptr;
    fptr = fopen("Data.txt", "r");
    Wfptr = fopen("encoded.bin", "w");
    encode *T;
    //printf("\n\n\nError : ");
    int i, j, k = 0, l;
    float a = 0.0, b = 0.0;
    char W[400], Buffer[20];
    while(fgets(W, 400, fptr) != NULL){
        i = 0;
        while(W[i] != '\0'){
            T = S;
            while(T -> chr[0] != W[i]){
                T = T -> next;
            }
            j = 0;
            while(T -> freq[j] != '\0'){
                if(T -> freq[j] == '\n'){
                    j++;
                }
                else{
                    Buffer[k++] = T -> freq[j];
                    if(k == 8){
                        Buffer[k] = '\0';
                        k = 0;
                        l = calculate(Buffer);
                        //printf(" %d\n", l);
                        fprintf(Wfptr, "%c", l);
                        a = a + 1.0;
                    }
                    j++;
                }
            }
            i++;
        }
    }
    if(k != 0){
        l = 0;
        while(k < 8){
            Buffer[k++] = '0';
            b = b + 0.1;
        }
        l = calculate(Buffer);
        //printf(" %d ", l);
        fprintf(Wfptr, "%c", l);
    }
    fclose(fptr);
    fclose(Wfptr);
    return a+b;
}

void regenerate(Tree *S, float f){
    FILE *fptr, *Decode;
    Tree *T;
    int g = (int)f;
    //int b = (f-g)*10 + 1;
    int b = round((b - (int)b)*10);
    char W[100], a, A[10];
    printf("\n  Decoded Data :       ");
    T = S;
    fptr = fopen("encoded.bin", "r");
    Decode = fopen("Decoded.txt", "w");
    while(fgets(W, 100, fptr)!= NULL){
        int i = 0;
        while(W[i] != '\0'){
            a = W[i];
            //this for loop will convert readen data into binary format.
            for(int k = 0;k < 8;k++){
                if(a & 1){
                    A[7-k] = '1';
                }
                else{
                    A[7-k] = '0';
                }
                a >>= 1;
            }
            g--;
            int k = 0;
            while(k < 8){
                if(T -> left == NULL && T -> right == NULL){
                    printf("%c", T -> c);
                    fprintf(Decode, "%c", T -> c);
                    T = S;
                }
                if(A[k] == '1'){
                    T = T -> right;
                }
                else{
                    T = T -> left;
                }
                k++;
                if(g < 0){
                    b++;
                    if(b > 8){
                        return;
                    }
                }
            }
            i++;
        }
    }
    fclose(fptr);
    fclose(Decode);
    printf("\n\nDecoded Data Successfully and Saved in \"Decoded.txt\" File..!");
    return;
}
