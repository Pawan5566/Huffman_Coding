//this structure is for Huffman tree
typedef struct node{
    char c;
    int freq;
    struct node *left, *right, *parent;
}Tree;

//This is helping linked list for huffman tree
typedef struct Node{
    Tree *A;
    struct Node *next;
}Store;

//linked list of char and freq
typedef struct NODE{
    int freq;
    char a;
    struct NODE *next;
}CharFreq;

//initializes Tree
void init_tree(Tree **S);

//initializes Store
void init_store(Store **H);

//insert into store
void insert_store(Store **Q, Tree *W);

//insert into tree
void insert_tree(Tree **S);

//postorder traversal of tree
void postorder_traversal(Tree *Y);

void BinConv(Tree *O, CharFreq *L);

CharFreq *GetFreq();

void init_charfreq(CharFreq **T);

void insert_charfreq(CharFreq **Q, int data, int t);

char *Convert(Tree *T, char *ch, int Freq);

typedef struct noDE
{
    Tree *ptr;
    struct noDE *next;
} Stack;

void push_stack(Stack **W, Tree *A);

typedef struct Encode{
    char chr[5], freq[100];
    struct Encode *next;
} encode;

encode *CreateBF();

void init_encode(encode **S);

void insertEncode(encode **S, char U[5], char T[20]);

float bin(encode *S);

int calculate(char C[20]);

void regenerate(Tree *S, float f);
