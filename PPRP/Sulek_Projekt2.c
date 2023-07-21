#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct meno_autora
{
    int index;
    char meno[20];
    char priezvisko[20];
    char rola[2];
    struct meno_autora *next;
} MENO_AUTORA;


typedef struct node
{
    int index;
    char IDprispevku[20];
    char nazovPrispevku[150];
    int *datum;

    struct meno_autora *menaAutorovHead;

    struct node *next;
} NODE;

void openFile(FILE **fp);
int getLine(FILE *fp);
void structCount(NODE *head);
void printList(NODE *head);
void readFromFile(FILE **fp, int line, NODE **head);
void addNode(NODE **head,char *IDname, char *title, char *authors, char *date);
NODE *createArraysForNames(char *authors);
void addNameNode(MENO_AUTORA **head,char *name, char *surName, char *charName);

void p(NODE **head);
void addNodeAnyWhere(NODE **head, int c1, char *IDname, char *title, char *authors, char *date);
bool checkIfPositionExists(NODE *head,int c1);
bool checkIfAuthorsAreCorrect(char *authors);

void z(NODE **head);
void deleteNode(NODE **head, int indexNod);


void deleteFirstNode(NODE **head);
void sortIndex(NODE **head);
void a(NODE **head);

void r(NODE **head);
void exchangeNodes(NODE **head, int c1, int c2);

void freeLinkedList(NODE **head);


//
//Pouzivam STDIN na zbieranie garbagu. cize mozno to nepojde na linuxe
//Pri vyvatrani noveho nodu s p() z pdfka zadania projektu je za autorom jedna medzera. Ak sa objavi na vstupe
//tak sa to vyhodnoti ako zly vstup
int main()
{
    printf("Adrian Sulek Project 2 ZPPRP\n");
    printf("n: Vyvtvorenie LinkedListov\nv: Zobrazenie LinkedListov\n");
    printf("p: Pridanie noveho LinkedListu\nz: Zmazanie LinkedListu\n");
    printf("a: Aktualizacia LinkedListu\nr: prehodenie 2 zaznamov\nk: Ukoncenie programu\n\n");

    FILE *fp = NULL;
    NODE *headNode = NULL;

    
    int line = 0;
    char menu;

    while (scanf(" %c", &menu) == 1)
    {
        switch (menu)
        {
        case 'n':
            openFile(&fp);
            line = getLine(fp);
            readFromFile(&fp,line,&headNode);
            structCount(headNode);
            break;
        case 'v':
            printList(headNode);
            break;
        case 'p':
            p(&headNode);
            break;
        case 'z':
            z(&headNode);
            break;
        case 'a':
            a(&headNode);
            break;
        case 'r':
            r(&headNode);
            break;
        case 'k':
            freeLinkedList(&headNode);
            printf("Bye");
            exit(0);
            break;
        default:
            break;
        }
    }
    
    return 0;
}

//Funkcia na scitanie zaznamov
void structCount(NODE *head){
    if (head == NULL)
    {
        printf("Nacitalo sa 0 zaznamov\n");
        return;
    }
    NODE *currentNode = head;
    int count;
    while (currentNode != NULL)
    {
        count = currentNode->index; 
        currentNode = currentNode->next;
    }
    printf("Nacitalo sa <%d> zaznamov\n", count);
}

void openFile(FILE **fp){
    if (*fp == NULL)
    {
        *fp = fopen("KonferencnyZoznam2.txt", "r");
        if (*fp == NULL)
        {
            printf("“Zaznamy neboli nacitane!\n");
        }
    }
}

//Spocitanie kolko je riadkov v subore 
int getLine(FILE *fp){
    if(fp == NULL){return 0;}
    rewind(fp);
    char endLine;
    
    int lineInt = 1;
    for (endLine = getc(fp); endLine!=EOF; endLine = getc(fp))
    {
        if (endLine == '\n')
        {
            lineInt++;
        }
        
    }
    return lineInt/5;
}






//Vypisovanie hodnot z struktur
void printList(NODE *head){
    if (head == NULL)
    {
        printf("Prazdny zoznam zaznamov\n");
        return;
    }
    NODE *currentNode = head;
    while (currentNode != NULL)
    {
        MENO_AUTORA *oldNode = currentNode->menaAutorovHead;
        printf("%d.\n",currentNode->index);
        printf("ID prispevku: %s\n", currentNode->IDprispevku);
        printf("Nazov prispevku: %s\n", currentNode->nazovPrispevku);
        printf("Mena autorov: \n");
        while (currentNode->menaAutorovHead != NULL)
        {
            printf("    %d: %s %s (%s)\n", currentNode->menaAutorovHead->index,
            currentNode->menaAutorovHead->meno, currentNode->menaAutorovHead->priezvisko, currentNode->menaAutorovHead->rola);
            currentNode->menaAutorovHead = currentNode->menaAutorovHead->next;
        }
        currentNode->menaAutorovHead = oldNode;
        printf("Datum a cas: %d%d%d%d.", currentNode->datum[0], currentNode->datum[1], currentNode->datum[2], currentNode->datum[3]);
        printf("%d%d.%d%d ", currentNode->datum[4], currentNode->datum[5], currentNode->datum[6], currentNode->datum[7]);
        printf("%d%d:%d%d\n", currentNode->datum[8], currentNode->datum[9], currentNode->datum[10], currentNode->datum[11]);
        currentNode = currentNode->next;
    }
}

//Citanie poloziek z subora
void readFromFile(FILE **fp, int line, NODE **head){
    //Ak je subor neotvoreny alebo ak uz boli nacitane structy
    if(*fp==NULL){return;}
    if (*head != NULL)
    {
        freeLinkedList(*(&head));
    }

    rewind(*fp);
    //Pomocne polia
    char *dollars = (char*)malloc(5*sizeof(char));
    char *IDname = (char*)malloc(50*sizeof(char));
    char *title = (char*)malloc(150*sizeof(char));
    char *authors = (char*)malloc(300*sizeof(char));
    char *date = (char*)malloc(12*sizeof(char));



    //Krajanie zaznamov podla poctu riadkov
    char *token;
    char buffer[150];
    for (int i = 0; i < line; i++)
    {
        //Na zbavenie sa $$$
        fgets(buffer,300,*fp);
        token = strtok(buffer, "\n");
        strcpy(dollars, token);


        fgets(buffer,300,*fp);
        token = strtok(buffer, "\n");
        strcpy(IDname, token);

        fgets(buffer,300,*fp);
        token = strtok(buffer, "\n");
        strcpy(title, token);

        fgets(buffer,300,*fp);
        token = strtok(buffer, "\n");
        strcpy(authors, token);

        fgets(buffer,300,*fp);
        token = strtok(buffer, "\n");
        strcpy(date, token);

        //prejde vzdy 5 riadkov zo suboru a vytvori z nich novy Node
        addNode(*(&head),IDname,title,authors,date);
    }

    
    free(IDname);
    free(title);
    free(authors);
    free(date);
    

    IDname = NULL;
    title = NULL;
    authors = NULL;
    date = NULL;
    token = NULL;
    //Zatvarnie suboru kedze uz s nim nepotrebujem robit
    fclose(*fp);
    *fp = NULL;
}

//--------------------------Vlozenie Prvku na Koniec zoznamu---------------------------
void addNode(NODE **head,char *IDname, char *title, char *authors, char *date){
    NODE *newNode = NULL;
    NODE *currentNode = *head;

    //Node je najprv NULL lebo este musim vytvorit vnutro
    newNode = createArraysForNames(authors);

    
    newNode->datum = (int*)malloc(12*sizeof(int));

    int increment = 0;
    for (int i = 0; i < 12; i++)
    {
        int k = date[i] - '0';
        newNode->datum[i] = k;
    }


    strcpy(newNode->IDprispevku,IDname);
    strcpy(newNode->nazovPrispevku,title);
    newNode->index = 1;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
    sortIndex(*(&head));
}

void addNameNode(MENO_AUTORA **head,char *name, char *surName, char *charName){
    MENO_AUTORA *newNode = (MENO_AUTORA*)malloc(sizeof(MENO_AUTORA));
    MENO_AUTORA *currentNode = *head;

    strcpy(newNode->meno, name);
    strcpy(newNode->priezvisko, surName);
    strcpy(newNode->rola, charName);
    newNode->next = NULL;
    newNode->index = 1;


    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }
    newNode->index = currentNode->index+1;
    currentNode->next = newNode;
    
    
}
//--------------------------------------------------------------------


//--------------------Vytvaranie vnutra hlavne linkedlistu---------
NODE *createArraysForNames(char *authors){
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    MENO_AUTORA *authorsHead = NULL;
    
    char *name = (char*)malloc(30*sizeof(char));
    char *surName = (char*)malloc(30*sizeof(char));
    char *charName = (char*)malloc(3*sizeof(char));
    
    char c,k;
    int increment = 0;
    int incrementAuthors = 0;


    //Z celeho stringu autorov mi to rozdeli na meno priezvisko a znak
    while (k != '\n')
    {
        while (k != ' ')
        {
            name[increment] = authors[incrementAuthors];
            k = name[increment];
            if (k == ' ')
            {
                name[increment] = '\0';
            }
            incrementAuthors++;
            increment++;
        }
        increment = 0;
        while (k != '#')
        {
            surName[increment] = authors[incrementAuthors];
            k = surName[increment];
            if (k == '#')
            {
                surName[increment] = '\0';
            }
        
            incrementAuthors++;
            increment++;
        }
        increment = 0;
        do
        {
            charName[increment] = authors[incrementAuthors];
            k = charName[increment];
            if (k == '#')
            {
                charName[increment] = '\0';
            }
        
            increment++;
            incrementAuthors++;
        } while (k != '#');
        k = authors[incrementAuthors];
        if (k < 65 || k > 90)
        {
            k = '\n';
        }
        increment = 0;

        addNameNode(&authorsHead, name,surName,charName);
    }

    newNode->menaAutorovHead = authorsHead;

    //Vnutorni Node uz ma spravene hodnoty. tak teraz sa ten vonkajsi rovna tomuto
    return newNode;
}
//----------------------------------------------------------------


//Pridavanie noveho nodu
void p(NODE **head){
    char *IDname = (char*)malloc(15*sizeof(char));
    char *title = (char*)malloc(150*sizeof(char));
    char *authors = (char*)malloc(50*sizeof(char));
    char *date = (char*)malloc(12*sizeof(char));
    int c1;
    int increment = 0;
    char c,IDindex[9];
    scanf("%d", &c1);
    c = getc(stdin); //Na zbavenie sa '\n'

    bool correctInput = false;

    //Zistovanie ci input je korektny
    //!!!! 
    //ID musi byt PD UD PP UP, a 8 cifier za
    //titul moze byt hocijaky
    //Mena musia byt meno -> medzera -> priezvisko -> # ->Znak -># a znak konca riadku! inak to vyhodnoti ako nespravny vstup
    //date musi byt 12 cifier cislo
    while (!correctInput)
    {
        correctInput = true;
        gets(IDname);
        gets(title);
        gets(authors);
        gets(date);
        for (int i = 2; i < 11; i++)
        {
            IDindex[i-2] = IDname[i];
        }
        if ((IDname[0] != 'U' && IDname[0] != 'P') || (IDname[1] != 'D' && IDname[1] != 'P'))
        {
            correctInput = false;
        }
        if (strlen(IDindex) != 8)
        {
            correctInput = false;
        }
        
        if(!checkIfAuthorsAreCorrect(authors)){
            correctInput = false;
        }
        if (strlen(date) != 12)
        {
            correctInput = false;
        }


        if (!correctInput)
        {
            printf("Zadali ste neplatne hodnoty. Prosim zadajte nove spravne hodnoty\n");
        }
        
    }

    //Ak je hlava null tak proste prida na koniec. Ak pozicia neexistuje tak tiez prida na koniec
    if (*head == NULL || checkIfPositionExists(*head,c1) == false)
    {
        addNode(*(&head),IDname,title,authors,date);
        free(IDname);
        free(title);
        free(authors);
        free(date);
        IDname = NULL;
        title = NULL;
        authors = NULL;
        date = NULL;
        return;
    }

    //Pridanie na lubovolne miesto
    addNodeAnyWhere(*(&head), c1, IDname,title,authors,date);


    free(IDname);
    free(title);
    free(authors);
    free(date);

    IDname = NULL;
    title = NULL;
    authors = NULL;
    date = NULL;
}

//Vyhodnocovanie inputu pre Authora
bool checkIfAuthorsAreCorrect(char *authors){

    int increment = 0;
    for (int i = 0; i < strlen(authors); i++)
    {
        if (authors[i] == ' ' || authors[i] == '#')
        {
            increment++;
        }
        
    }
    if (increment%3 == 0)
    {
        return true;
    }else
        return false;
}

//Fukncia ktora vracia TRUE ak existuje index Nodu, a FALSE ak nie
bool checkIfPositionExists(NODE *head ,int c1){
    while (head != NULL)
    {
        if (head->index == c1)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

//Pridavanie Nodu na lubovolne miesto
void addNodeAnyWhere(NODE **head, int c1, char *IDname, char *title, char *authors, char *date){
    NODE *newNode = NULL;
    NODE *currentNode = *head;

    newNode = createArraysForNames(authors);

    newNode->datum = (int*)malloc(12*sizeof(int));

    int increment = 0;
    for (int i = 0; i < 12; i++)
    {
        int k = date[i] - '0';
        newNode->datum[i] = k;
    }

    strcpy(newNode->IDprispevku,IDname);
    strcpy(newNode->nazovPrispevku,title);
    newNode->index = c1;
    newNode->next = NULL;
    
    //Ak chceme pridat zaznam na prve miesto
    if (newNode->index == 1)
    {
        newNode->next = currentNode;
        *head = newNode;
        sortIndex(*(&head));
        return;
    }

    //Inak posuvam takto
    while (currentNode->next->index != newNode->index)
    {
        currentNode = currentNode->next;
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    while (currentNode->next != NULL)
    {
        currentNode->next->index = currentNode->index+1;
        currentNode = currentNode->next;
    }
}


//vymazanie Nodu
void z(NODE **head){
    if(*head == NULL){
        printf("Prazdny zoznam\n"); 
        return;
    }
    NODE *currentNode = *head;

    char *name = (char*)malloc(25*sizeof(char));
    char *surName = (char*)malloc(25*sizeof(char));

    scanf("%s %s", name, surName);

    //Premena inputu nech je jedno ci velke alebo male pismena
    for (int i = 1; i < strlen(name); i++)
    {  
        if (i == 1){
            name[0] = toupper(name[0]);
        } 
        name[i] = tolower(name[i]);
    }
    
    for (int i = 1; i < strlen(surName); i++)
    {
        if (i == 1){
            surName[0] = toupper(surName[0]);
        }
        
        surName[i] = tolower(surName[i]);
    }


    
    //Prechadzanie cez linkedList a hladanie mena a priezviska
    while (currentNode != NULL)
    {
        MENO_AUTORA *oldNode = currentNode->menaAutorovHead;
        while (currentNode->menaAutorovHead != NULL)
        {
            //Porovnavanie inputu a mena
            if (strcmp(currentNode->menaAutorovHead->meno,name) == 0  && strcmp(currentNode->menaAutorovHead->priezvisko,surName) == 0 
                && strcmp(currentNode->menaAutorovHead->rola, "A") == 0 ){
                //Ak chceme vymazat hlavu
                if (currentNode->index == 1)
                {
                    deleteFirstNode(*(&head));
                    break;
                }
                deleteNode(*(&head), currentNode->index);
            }
            currentNode->menaAutorovHead = currentNode->menaAutorovHead->next;
        }
        currentNode->menaAutorovHead = oldNode;
        if (currentNode->next == NULL)
        {
            return;
        }
        currentNode = currentNode->next;
    }
}

//Samotne presuvanie Nodov pre zmazanie
void deleteNode(NODE **head, int indexNode){
    NODE *currentNode = *head, *prev;
    while (currentNode != NULL && currentNode->index != indexNode)
    {
        prev = currentNode;
        currentNode = currentNode->next;
    }
    printf("Prispevok s nazvom %s bol vymazany\n", currentNode->nazovPrispevku);
    prev->next = currentNode->next;
    
    free(currentNode->menaAutorovHead);
    free(currentNode->datum);
    free(currentNode);
    sortIndex(*(&head));
}

//Proste len dame ze pointer na hlavu je druhy node a nasledne free prvy blok
void deleteFirstNode(NODE **head){
    NODE *current;
    MENO_AUTORA *currentNameNode = NULL;
    current = *head;
    printf("Prispevok s nazvom %s bol vymazany\n", current->nazovPrispevku);
    while ( (*head)->menaAutorovHead != NULL)
    {
        currentNameNode = (*head)->menaAutorovHead;
        (*head)->menaAutorovHead =  (*head)->menaAutorovHead->next;
        free(currentNameNode);
    }
    *head = (*head)->next;
    free(current->datum);
    free(current);
    sortIndex(*(&head));
    
}

//Fukncia ktora zoradi indexi 
//Priradi hlave index 1 a iteraju a kazdemu .next da =+ 1
void sortIndex(NODE **head){
    NODE *currentNode = *head;
    currentNode->index = 1;
    while (currentNode->next != NULL)
    {
        currentNode->next->index = currentNode->index+1;
        currentNode = currentNode->next;
    }
}


//Prehodenie typu prezentacie
void a(NODE **head){
    if (*head == NULL)
    {
        printf("Prazdny zoznam\n");
        return;
    }
    
    char typ[3];
    long typInt;
    bool correctNumber = false;

    //Nacitavanie vstupu. zle pismena a pocet cifier sa neberie
    while (!correctNumber){
        scanf("%ld %s",&typInt,typ );
        char length[9];
        sprintf(length, "%ld", typInt);
        
        if (typInt%15==0 && (strcmp(typ, "PD") == 0 || strcmp(typ, "UD") == 0 ||
            strcmp(typ, "PP") == 0 || strcmp(typ, "UP") == 0) && strlen(length) == 8)
        {
            correctNumber = true;
        }else{
            printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
        }
    }

    char oldType[3];
    NODE *currentNode = *head;
    char currentIndex[9];
    char wantedIndex[9];
    
    sprintf(wantedIndex, "%ld", typInt);

    //iterovanie cez list hladanie rovnakeho ID cisla
    while (currentNode != NULL)
    {
        for (int i = 2; i < 11; i++)
        {
            currentIndex[i-2] = currentNode->IDprispevku[i];
        }
        //ak sa najde rovnae ID cislo, zmeni sa v Node ID znak
        if (strcmp(currentIndex, wantedIndex) == 0)
        {
            for (int i = 0; i < 2; i++){
                oldType[i] = currentNode->IDprispevku[i];
                oldType[i+1] = '\0';
            }
            for (int i = 0; i < 2; i++){
                currentNode->IDprispevku[i] = typ[i];
            }
            printf("Prispevok s nazvom %s sa bude prezentovat %c%c [%s].\n", currentNode->nazovPrispevku, currentNode->IDprispevku[0],currentNode->IDprispevku[1], oldType);
        }
        currentNode = currentNode->next;
    }
    
}


//Prehodenie 2 Nodov
void r(NODE **head){
    if(*head == NULL){
        printf("Prazdny zoznam\n");
        return;
    }
    int c1,c2;
    bool positiveNumber = false;

    while (!positiveNumber)
    {
        scanf("%d %d", &c1, &c2);
        if (c1 > 0 && c2 > 0)
        {
            positiveNumber = true;
        }
        else{
            printf("Napisali ste zly input. obe cisla musia byt > 0. Skuste este raz: ");
        }
    }

    //Rovnake cislo = Nody su uz "prehodene"
    if (c1 == c2)
    {
        return;
    }
    //inak prehadzujeme len nody ktorych index existuje
    if (checkIfPositionExists(*head, c1) == true && checkIfPositionExists(*head, c2) == true)
    {
        exchangeNodes(*(&head), c1,c2);
    }
    else{
        printf("Pozicie neexistuju\n");
    }
}


//Funkcia na prehodenie nodov
void exchangeNodes(NODE **head, int c1, int c2){
    NODE *currentNodeC1 = *head, *currentNodeC2 = *head;
    NODE *previouseNodec1 = NULL, *previouseNodec2 = NULL;

    while (currentNodeC1->index != c1)
    {
        previouseNodec1 = currentNodeC1;
        currentNodeC1 = currentNodeC1->next;
    }
    while (currentNodeC2->index != c2)
    {
        previouseNodec2 = currentNodeC2;
        currentNodeC2 = currentNodeC2->next;
    }

    if (previouseNodec1 != NULL)
    {
        previouseNodec1->next = currentNodeC2;
    }else{
        *head = currentNodeC2;
    }

    if (previouseNodec2 != NULL)
    {
        previouseNodec2->next = currentNodeC1;
    }else{
        *head = currentNodeC1;
    }
    
    NODE *currentNode = currentNodeC2->next;
    currentNode = currentNodeC2->next;
    currentNodeC2->next = currentNodeC1->next;
    currentNodeC1->next = currentNode;

    sortIndex(*(&head));
}


//Uvolnenie pamety pre alokovane zlozky
void freeLinkedList(NODE **head){
    NODE *currentNode;
    MENO_AUTORA *currentNameNode;

    while (*head != NULL)
    {
        currentNode = *head;
        while ((*head)->menaAutorovHead != NULL)
        {
            currentNameNode = (*head)->menaAutorovHead;
            (*head)->menaAutorovHead =  (*head)->menaAutorovHead->next;
            free(currentNameNode);
        }
        *head = (*head)->next;
        free(currentNode->datum);
        free(currentNode);
    }
}