#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

typedef struct
{
    char *studentID;
    char *studentName;
} ElementType;
struct Node
{
    ElementType element;
    PtrToNode next;
};

void Insert(ElementType X, List *L);
void Delete(ElementType X, List *L);
PtrToNode CreateNode(ElementType X);
Position Find(ElementType X, List *L);
Position FindPrevNode(Position N, List *L);
void PrintList(List *L);
void PrintCurrentList(List *L);
int IsEmpty(List *L);
int IsLast(Position P, List *L);
void DeleteList(List *L);

int main()
{

    char input;
    List L = NULL;
    while (1)
    {
        scanf(" %c", &input);

        if (input == 'i')
        {
            // Data 입력
            ElementType E;
            E.studentID = malloc(sizeof(char) * 15);
            E.studentName = malloc(sizeof(char) * 15);
            scanf("%s %s", E.studentID, E.studentName);
            scanf("%s", E.studentName + strlen(E.studentName) + 1);
            E.studentName[strlen(E.studentName)] = ' ';

            // 만약 E가 L에 없다면 Insert함수를 호출하고 성공메세지를 출력한다.
            if (Find(E, &L) == NULL)
            {
                Insert(E, &L);
                printf("Insertion Success : %s\n", E.studentID);
            }
            // 아니라면 실패메세지를 출력한다.
            else
                printf("Insertion Failed. ID %s is already exist\n", E.studentID);

            free(E.studentID);
            free(E.studentName);
        }

        else if (input == 'd')
        {
            ElementType E;
            E.studentID = malloc(sizeof(char) * 15);
            scanf("%s", E.studentID);

            Delete(E, &L);
            free(E.studentID);
        }

        else if (input == 'f')
        {
            ElementType E;
            E.studentID = malloc(sizeof(char) * 15);
            scanf("%s", E.studentID);

            PtrToNode P = Find(E, &L);
            // 만약
            if (P == NULL)
                printf("Find %s Faild. There is No such student id.\n", E.studentID);
            else
                printf("Find Success : %s %s\n", P->element.studentID, P->element.studentName);

            free(E.studentID);
        }

        else if (input == 'p')
        {
            PrintList(&L);
            DeleteList(&L);
            break;
        }

        PrintCurrentList(&L);
    }

    return 0;
}

// 오름차순으로 정렬된 리스트에 올바른 위치를 찾아 노드를 삽입하는 함수
void Insert(ElementType X, List *L)
{
    // 리스트가 비어있는 경우 바로 추가해준다.
    if (IsEmpty(L))
    {
        *L = CreateNode(X);
    }
    else
    {

        PtrToNode P = *L;

        // X의 studentID보다 큰 노드를 찾는다.
        while (P != NULL)
        {
            if (atoi(P->element.studentID) >= atoi(X.studentID))
                break;
            P = P->next;
        }

        // FindPrevNode를 통해 P의 이전노드를 PrevN에 저장한다.
        PtrToNode PrevN = FindPrevNode(P, L);
        PtrToNode newNode = CreateNode(X);

        // 만약 P가 리스트의 첫번째 노드일 경우
        if (PrevN == NULL)
            *L = newNode;
        // P가 리스트의 중간에 존재할 경우
        else
            PrevN->next = newNode;

        newNode->next = P;
    }
}

// 새로운 노드를 만들어주는 함수
PtrToNode CreateNode(ElementType X)
{
    PtrToNode Node = (PtrToNode)malloc(sizeof(struct Node));
    Node->element.studentID = (char *)malloc(sizeof(char) * 15);
    Node->element.studentName = (char *)malloc(sizeof(char) * 15);
    strcpy(Node->element.studentID, X.studentID);
    strcpy(Node->element.studentName, X.studentName);

    Node->next = NULL;
    return Node;
}

// X의 studentID와 동일한 노드
void Delete(ElementType X, List *L)
{
    // 만약 List가 비어있다면 오류메세지를 출력한다.
    if (IsEmpty(L))
    {
        printf("Deletion Failed : Student ID %s is not in the list\n", X.studentID);
    }
    else
    {

        PtrToNode DeleteNode = Find(X, L);
        PtrToNode P = FindPrevNode(DeleteNode, L);

        // 만약 List에서 X를 찾지 못한다면 오류메세지를 출력한다.
        if (DeleteNode == NULL)
            printf("Deletion Failed : Student ID %s is not in the list\n", X.studentID);
        else
        {

            // 만약 DeleteNode가 리스트의 첫 노드라면
            if (P == NULL)
                *L = DeleteNode->next;

            else
                P->next = DeleteNode->next;

            free(DeleteNode->element.studentID);
            free(DeleteNode->element.studentName);
            free(DeleteNode);
            printf("Deletion Success : Student ID %s\n", X.studentID);
        }
    }
}

// 파라미터로 넘겨받은 X의 studentID와 같은 Data를 가진 노드를 리턴한다.
// 만약 찾지 못하면 NULL을 반환한다.
Position Find(ElementType X, List *L)
{
    Position P = *L;
    while (P != NULL && strcmp(P->element.studentID, X.studentID))
    {
        P = (P)->next;
    }
    return P;
}

// 파라미터로 넘겨받은 노드의 직전 노드를 리턴하는 함수
// 만약 파라미터 노드가 리스트의 첫 노드라면 NULL을 리턴해준다.
Position FindPrevNode(Position N, List *L)
{
    Position P = *L;

    if (P == N)
        return NULL;

    while (P->next != N)
    {
        P = P->next;
    }

    return P;
}

// 문제의 입력 p의 출력형태의 맞게 출력해주는 함수.
void PrintList(List *L)
{

    printf("-----LIST-----\n");
    Position P = *L;
    while (P != NULL)
    {
        printf("%s %s\n", P->element.studentID, P->element.studentName);
        P = P->next;
    }
    printf("--------------\n");
}

// 문제의 Current List의 출력형태에 맞게 출력해주는 함수
void PrintCurrentList(List *L)
{
    printf("Current List > ");
    Position P = *L;
    if (*L == NULL)
        return;

    printf("%s %s", P->element.studentID, P->element.studentName);
    while (P->next != NULL)
    {
        P = P->next;
        printf("-%s %s", P->element.studentID, P->element.studentName);
    }
    printf("\n");
}

// 리스트가 비어있는지 확인하는 함수
int IsEmpty(List *L)
{
    if (*L == NULL)
        return 1;
    return 0;
}

// P가 리스트의 마지막 노드인지 확인하는 함수
int IsLast(Position P, List *L)
{
    if (*L != NULL && P->next == NULL)
        return 1;
    return 0;
}

// 리스트 전체의 메모리를 해제하고 리스트를 비우는 함수
void DeleteList(List *L)
{
    Position P = *L;
    while (P != NULL)
    {
        Position temp = P->next;

        free(P->element.studentID);
        free(P->element.studentName);
        free(P);

        P = P->next;
    }
    *L = NULL;
}
