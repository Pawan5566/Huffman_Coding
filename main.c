#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main()
{
    CharFreq *Y;
    Y = GetFreq();
    Tree *A;
    init_tree(&A);
    insert_tree(&A);
    //postorder_traversal(A);
    BinConv(A, Y);
    encode *E;
    E = CreateBF();
    float f = bin(E);
    regenerate(A, f);
    return 0;
}




























/*#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main()
{
    CharFreq *Y;
    Y = GetFreq();
    Tree *A;
    init(&A);
    inserT(&A);
    //postorder_traversal(A);
    BinConv(A, Y);
    encode *E;
    E = CreateBF();
    bin(E);
    regenerate(A);
    return 0;
}
*/
