#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct node
{
    char bfunction[150];
    char order[20];
    char letter;

    struct node *zeroChild;
    struct node *oneChild;

} NODE;
NODE *root = NULL;


int nodeArrayIndex = 0;
int numberOfNodes = 1;
int numberOfDeletedNode = 0;

void printTree(NODE *currentNode);
void create_BDD(char *bfunction, char *order, NODE**nodeArray);
void createChildren(NODE *currentNode,char *newBfunction, NODE*nodeArray);
void createZeroChild(char **boolOperators, NODE *currentNode,char *order,char wantedLetter,int countInt, NODE*nodeArray);
void createOneChild(char **boolOperators, NODE *currentNode,char *order,char wantedLetter, int countInt, NODE*nodeArray);
void checkking(NODE *currentNode, char *str, NODE **newPointer);

void BDD_create_with_best_order(char *bfunction, char *order,NODE **nodeArray);

void BDD_use(NODE *currentNode,char *vstup);


void addToNodeArray(NODE *currentNode, NODE **nodeArray){
    nodeArray[nodeArrayIndex] = currentNode;
    nodeArrayIndex++;
}

void removeChar(char *str, char c) {
    int i, j;
    int len = strlen(str);
    for (i = j = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}
//!ABCF
void removeVykricnikBeforeLetter(char *str, char c){
    int i;
    int j = 0;
    int len = strlen(str);
    char buffer[20];
    for (i = 0; i < len; i++) {
        if (str[i] == '!' && str[i+1] == c){
        }
        else{
            buffer[j] = str[i];
            j++;
        }
    }
    buffer[j] = '\0';
    strcpy(str,buffer);
}

void removeLastChar(char *str){
    int len = strlen(str);
    str[len-1] = '\0';
}

void addToString(char *destStr, char *fromStr){
    int len = strlen(destStr);
    for (int i = 0; i < strlen(fromStr); ++i) {
        destStr[i+len] = fromStr[i];
        destStr[i+len+1] = '+';
    }
}

void duplicate3DcharArray(char **destStr, char **fromStr, int count){
    for (int i = 0; i < count; ++i) {
        strcpy(destStr[i],fromStr[i]);
    }
}

void createRandomOrder(char *order, char**randomOrder){
    int len = strlen(order);
    char buffer[20];
    strcpy(buffer,order);
    for (int i = 0; i < len; i++)
    {
        char tmp[20];
        strcpy(tmp,buffer);
        for (int j = 0; j < len-1; j++)
        {
            buffer[j+1] = tmp[j];
        }
        buffer[0] = tmp[len-1];
        buffer[len] = '\0';
        strcpy(randomOrder[i],buffer);
    }
}

void deAllocateWholeTree(NODE **nodeArray){
    for (int i = 0; i < nodeArrayIndex; ++i) {
        free(nodeArray[i]);
        nodeArray[i] = NULL;
    }
    nodeArrayIndex = 0;
}

int main(){
    NODE **nodeArray = (NODE**) malloc(3000* sizeof(NODE*));
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    //
    //
    //create_BDD("A!C+ABC+!AB+!BC", "ABC",nodeArray);
    //create_BDD("A!C+ABCF+!AB!F+!BC+AB!FCD+A!BC!D+BCFA+!ABC+ABCD+!A!B!C!D+!DAB!CF", "ABCDF",nodeArray);
    //create_BDD("A!C+ABCF+!EAB!F+!BC+AB!FCD+A!BCE!D+B!BCFA+!AE!ABC+ABCD+!A!B!CE!D+!DAB!CEF", "ABCDFE",nodeArray); //C C C C CC
    //create_BDD("A!C+ABC+!AB+!BC+ABCD+A!BC!D+B!BCA+!A!ABC+EA!BC+BC!FA", "ABCDEF", nodeArray);
    //create_BDD("AB+!AB+A!B", "AB");
    //create_BDD("KICEI!HGB+!MBDCH+E!HJLC+!AD!L!M+BAE+KMCD+CI!LD+!GI!H+L!GC+!J!K+H!DBK!F", "HFGLIMBAJKECD",nodeArray);
    //create_BDD("A!B+ABLK+A+AMBDCH+ABBBC+ACDE+!A!B!CA!DAB+BCEB+!KMCD!LF+G+H+P+A+M+N+A+J","ABCDEFGHIJKLMNOPRS",nodeArray);
    //create_BDD("KICEI!HGB+!MBDCH+E!HJLC+!AD!L!M+B+KMCD+CI!LD+!GI!H+L!GC+!J!K+H!DBK!F","HFGLIMBAJKECD",nodeArray);
    //printf("\n\n");
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    printTree(root);
    //deAllocateWholeTree(nodeArray);

    //BDD_create_with_best_order("A!C+ABC+!AB+!BC", "ABC",nodeArray);
    //create_BDD("A!C+ABCF+!AB!F+!BC+AB!FCD+A!BC!D+B!BCFA+!A!ABC+ABCD+!A!B!C!D+!DAB!CF", "CDFAB",nodeArray);
    //BDD_create_with_best_order("A!C+ABCF+!EAB!F+!BC+AB!FCD+A!BCE!D+B!BCFA+!AE!ABC+ABCD+!A!B!CE!D+!DAB!CEF", "ABCDFE",nodeArray);
    //BDD_use(root,"100");

    //create_BDD("A!C+ABCF+!AB!F+!BC+AB!FCD+A!BC!D+B!BCFA+!A!ABC+ABCD+!A!B!C!D+!DAB!CF", "ABCDF",nodeArray);
    //deAllocateWholeTree(nodeArray);
    printf("\n\n%d",numberOfNodes);printf("\n\n%d",numberOfDeletedNode);
    printf("\n\nTotal time taken by CPU: %f\n", total_t  );
    return 0;
}

void printTree(NODE *currentNode){
    if(currentNode != NULL){
        printf("%s      %s      memory: %p\n",currentNode->bfunction,currentNode->order, currentNode);
        if(currentNode->zeroChild != NULL){
            printf(" L bool: ");
            printTree(currentNode->zeroChild);
        }

        if(currentNode->oneChild != NULL){
            printf(" R bool: ");
            printTree(currentNode->oneChild);
        }
    }
}

void create_BDD(char *bfunction, char *order, NODE**nodeArray){
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    strcpy(newNode->bfunction,bfunction);
    strcpy(newNode->order, order);
    newNode->letter = order[0];
    newNode->zeroChild = NULL;
    newNode->oneChild = NULL;

    root = newNode;
    nodeArray[nodeArrayIndex] = root;
    nodeArrayIndex++;
    createChildren(root, root->bfunction, (NODE *) nodeArray);
}

void createChildren(NODE *currentNode,char *newBfunction, NODE*nodeArray){
    int count = 1;
    for (int i = 0; i < strlen(newBfunction); i++)
    {
        if (newBfunction[i] == '+')
        {
            count ++;
        }
    }
    char **booleanOpearots = (char**)malloc(count*sizeof(char*));
    for (int i = 0; i < count; i++)
    {
        *(booleanOpearots + i) = (char*)malloc(100*sizeof(char));
    }

    int k = 0;
    int I = 0;
    for (int i = 0; i < strlen(newBfunction); i++)
    {
        if (newBfunction[i] != '+')
        {
            booleanOpearots[I][k] = newBfunction[i];
            booleanOpearots[I][k+1] = '\0';
            k++;
        }
        if (newBfunction[i] == '+')
        {
            I++;
            k = 0;
        }
    }
    createZeroChild(booleanOpearots,currentNode, currentNode->order, currentNode->letter, count,nodeArray);
    createOneChild(booleanOpearots,currentNode, currentNode->order, currentNode->letter, count,nodeArray);
}

void createZeroChild(char **boolOperators, NODE *currentNode,char *order,char wantedLetter, int countInt, NODE*nodeArray){
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    NODE *newPointerNode = NULL;

    char **peso;
    peso = (char**) malloc(countInt* sizeof(char*));
    for (int i = 0; i < countInt; ++i) {
        peso[i]= (char*) malloc(150* sizeof(char ));
    }

    duplicate3DcharArray(peso,boolOperators,countInt);

    char buffer[150] = "";
    for (int i = 0; i < countInt; ++i) {
        int isThere = 0;
        for (int j = 0; j < strlen(peso[i]); ++j) {
            if(peso[i][j] == wantedLetter){
                isThere++;
            }
            if(peso[i][j] == wantedLetter && peso[i][j-1] == '!'){
                removeVykricnikBeforeLetter(peso[i], wantedLetter);
                removeChar(peso[i], wantedLetter);
                addToString(buffer,peso[i]);
            }
        }
        if(isThere == 0){
            //printf("YES %s      %c\n",peso[i], wantedLetter);
            addToString(buffer,peso[i]);
            isThere = 0;
        }
    }
    if(strcmp(buffer,"") == 0){
        newNode->zeroChild = NULL;
        newNode->oneChild = NULL;
        newNode->letter = '\0';
        strcpy(newNode->bfunction,"0");
        strcpy(newNode->order,"");

        newPointerNode = newNode;
        checkking(root,newNode->bfunction,&newPointerNode);
        if(newPointerNode != newNode){
            numberOfDeletedNode++;
            free(newNode);
            currentNode->zeroChild = newPointerNode;
        }else{
            numberOfNodes++;
            addToNodeArray(newPointerNode, (NODE **) nodeArray);
            currentNode->zeroChild = newPointerNode;
        }

    } else {
        removeLastChar(buffer);
        char newOrder[20];
        strcpy(newOrder, order);

        removeChar(newOrder, wantedLetter);

        strcpy(newNode->bfunction, buffer);
        strcpy(newNode->order, newOrder);
        newNode->letter = newOrder[0];
        newNode->zeroChild = NULL;
        newNode->oneChild = NULL;

        newPointerNode = newNode;
        checkking(root,newNode->bfunction,&newPointerNode);
        if(newPointerNode == newNode){
            currentNode->zeroChild = newPointerNode;
            addToNodeArray(newPointerNode, (NODE **) nodeArray);
            numberOfNodes++;
            createChildren(currentNode->zeroChild, currentNode->zeroChild->bfunction,nodeArray);
        } else{
            //currentNode->zeroChild = newPointerNode;
            numberOfDeletedNode++;
            free(newNode);
            newNode = NULL;
        }
    }

}

void createOneChild(char **boolOperators, NODE *currentNode,char *order,char wantedLetter, int countInt, NODE*nodeArray){
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    NODE *newPointerNode = NULL;

    char **peso = (char**) malloc(countInt* sizeof(char*));
    for (int i = 0; i < countInt; ++i) {
        peso[i]= (char*) malloc(10* sizeof(char ));
    }

    duplicate3DcharArray(peso,boolOperators,countInt);

    char buffer[150] = "";
    for (int i = 0; i < countInt; ++i) {
        int isThere = 0;
        for (int j = 0; j < strlen(peso[i]); ++j) {
            if(peso[i][j] == wantedLetter){
                isThere++;
            }
            if(peso[i][j] == wantedLetter && peso[i][j-1] != '!'){
                removeChar(peso[i],wantedLetter);
                addToString(buffer,peso[i]);
            }
        }
        if(isThere == 0){
            addToString(buffer,peso[i]);
            isThere = 0;
        }
    }

    if(strcmp(buffer,"") == 0){
        newNode->zeroChild = NULL;
        newNode->oneChild = NULL;
        newNode->letter = '\0';
        strcpy(newNode->bfunction,"1");
        strcpy(newNode->order,"");

        newPointerNode = newNode;
        checkking(root,newNode->bfunction,&newPointerNode);
        if(newPointerNode != newNode){
            numberOfDeletedNode++;
            free(newNode);
            currentNode->oneChild = newPointerNode;
        }else{
            numberOfNodes++;
            addToNodeArray(newPointerNode, (NODE **) nodeArray);
            currentNode->oneChild = newPointerNode;
        }
    }else{

        removeLastChar(buffer);


        char newOrder[20];
        strcpy(newOrder,order);

        removeChar(newOrder,wantedLetter);

        strcpy(newNode->bfunction,buffer);
        strcpy(newNode->order,newOrder);
        newNode->letter = newOrder[0];
        newNode->zeroChild = NULL;
        newNode->oneChild = NULL;

        newPointerNode = newNode;
        checkking(root,newNode->bfunction,&newPointerNode);
        if(newPointerNode == newNode){
            currentNode->oneChild = newPointerNode;
            addToNodeArray(newPointerNode, (NODE **) nodeArray);
            numberOfNodes++;
            createChildren(currentNode->oneChild,currentNode->oneChild->bfunction,nodeArray);
        }else{
            //ROBI PROBLEMI VELKY STRING
            //currentNode->oneChild = newPointerNode;
            numberOfDeletedNode++;
            free(newNode);
            newNode=NULL;
        }
    }

}

void checkking(NODE *currentNode, char *str, NODE **newPointer){
    if (strcmp(currentNode->bfunction,str) == 0){
        *newPointer = currentNode;
        return;
    }
    if (currentNode->zeroChild != NULL){
        checkking(currentNode->zeroChild,str,newPointer);
    }
    if (currentNode->oneChild != NULL){
        checkking(currentNode->oneChild,str,newPointer);
    }
}


void BDD_create_with_best_order(char *bfunction, char *order, NODE **nodeArray){
    int len = strlen(order);
    char **randomOrder = (char**) malloc(len* sizeof(char*));
    for (int i = 0; i < len; ++i) {
        randomOrder[i] = (char*) malloc(20* sizeof(char));
    }
    createRandomOrder(order,randomOrder);
    for (int i = 0; i < len; ++i) {
        create_BDD(bfunction,randomOrder[i],nodeArray);
        printf("Order: %s       Number of Nodes: %d\n", randomOrder[i], numberOfNodes);
        deAllocateWholeTree(nodeArray);
        numberOfNodes = 1;
        nodeArrayIndex = 0;
    }
}

void BDD_use(NODE *currentNode,char *vstup){
    int len = strlen(vstup);
    for (int i = 0; i < len; ++i){
        if(vstup[i] == '0'){
            currentNode = currentNode->zeroChild;
        }
        if(vstup[i] == '1'){
            currentNode = currentNode->oneChild;
        }
        if(currentNode == NULL){
            printf("Vysledkom BDD_use je: -1\n");
            return;
        }
    }
    printf("Vysledkom BDD_use je: %s    %c",currentNode->bfunction, currentNode->letter);
}
/*if(strcmp(buffer,"") == 0){ strcpy(buffer,"1");}
 *
 *
     if(strcmp(buffer,"") == 0){
        newNode->zeroChild = NULL;
        newNode->oneChild = NULL;
        newNode->letter = '\0';
        strcpy(newNode->bfunction,"0");
        strcpy(newNode->order,"");

        newPointerNode = newNode;
        checkking(root,newNode->bfunction,&newPointerNode);
        if(newPointerNode == newNode){numberOfNodes++;}
        addToNodeArray(newPointerNode, (NODE **) nodeArray);
        currentNode->zeroChild = newPointerNode;
    } else {
        removeLastChar(buffer);
        char newOrder[20];
        strcpy(newOrder, order);

        removeChar(newOrder, wantedLetter);

        strcpy(newNode->bfunction, buffer);
        strcpy(newNode->order, newOrder);
        newNode->zeroChild = NULL;
        newNode->oneChild = NULL;

        newPointerNode = newNode;
        checkking(root,newNode->bfunction,&newPointerNode);
        if(newPointerNode == newNode){
            currentNode->zeroChild = newPointerNode;
            addToNodeArray(newPointerNode, (NODE **) nodeArray);
            numberOfNodes++;
            createChildren(currentNode->zeroChild, currentNode->zeroChild->bfunction,nodeArray);
        } else{
            free(newNode);
            newNode = NULL;
        }
    }

 *
 *
 *
 *
 * if(strcmp(buffer,"") == 0){
        newNode->zeroChild = NULL;
        newNode->oneChild = NULL;
        newNode->letter = '\0';
        strcpy(newNode->bfunction,"1");
        strcpy(newNode->order,"");

        newPointerNode = newNode;
        checkking(root,newNode->bfunction,&newPointerNode);
        if(newPointerNode == newNode){numberOfNodes++;}
        addToNodeArray(newPointerNode, (NODE **) nodeArray);
        currentNode->oneChild = newPointerNode;
    }else{

    removeLastChar(buffer);


    char newOrder[20];
    strcpy(newOrder,order);

    removeChar(newOrder,wantedLetter);

    strcpy(newNode->bfunction,buffer);
    strcpy(newNode->order,newOrder);
    newNode->zeroChild = NULL;
    newNode->oneChild = NULL;

    newPointerNode = newNode;
    checkking(root,newNode->bfunction,&newPointerNode);
    if(newPointerNode == newNode){
        currentNode->oneChild = newPointerNode;
        addToNodeArray(newPointerNode, (NODE **) nodeArray);
        numberOfNodes++;
        createChildren(currentNode->oneChild,currentNode->oneChild->bfunction,nodeArray);
    }else{free(newNode); newNode=NULL;
        }
    }
 *
 *
 *
 *
 * */