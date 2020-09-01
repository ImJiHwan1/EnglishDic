#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
// strcat() = 문자열 이어 붙이기 strcmp() = 두 문자열 비교(주소 값)
//strlen() = 문자열의 길이 알려줌 strcpy() = 문자열 복사

#define MAX_WORD_LENGTH 20
#define MAX_MEAN_LENGTH 200

typedef struct {
	char word[MAX_WORD_LENGTH];
	char mean[MAX_MEAN_LENGTH];
} element;

typedef struct treeNode { //트리 구조체 변수 설정
	element key;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

treeNode* searchBST(treeNode* root, element key) // 단어 검색 알고리즘
{
	treeNode* p;	int compare;
	p = root;
	printf("\n찾을 단어 : %s", key.word); 
	printf("\n현재단어 : %s", p->key.word); //트리에 구성된 단어
	while (p != NULL) {
		compare = strcmp(key.word, p->key.word); // key.word, p->key.word 문자열 비교
		if (compare < 0) {
			p = p->left;
			printf("\n검색 중 왼쪽단어 : %s", p->key.word);
		}
		else if (compare > 0) {
			p = p->right;
			printf("\n검색 중 오른쪽 단어 : %s", p->key.word);
		}
		else { // compare = 0
			printf("\n찾은 단어 : %s", p->key.word);
			return p;
		}
	}
	return p;
}

treeNode* insertKey(treeNode* p, element key)
{
	treeNode* newNode;
	int compare;
	if (p == NULL) {
		newNode = (treeNode*)malloc(sizeof(treeNode)); //트리에 생성되는 공백 노드 구성
		newNode->key = key; //p값이 공백이라서 링크에는 NULL값을 준다
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else {
		compare = strcmp(key.word, p->key.word); //현재 트리에 구성되어있는 문자열과 비교하여 	
		if (compare < 0) {	//왼쪽 트리						   //동일 문자가 없는지 확인
			p->left = insertKey(p->left, key);
			return p;
		}
		else if (compare > 0) { //오른쪽 트리
			p->right = insertKey(p->right, key);
			return p;
		}
		else {
			printf("\n 이미 같은 단어가 있습니다! \n");
			return p;
		}
	}
}

void insert(treeNode** root, element key) //treeNode -> insertKey 두번 거쳐 참조
{
	*root = insertKey(*root, key);
}

void deleteNode(treeNode* root, element key)
{
	treeNode* parent, * p, * succ, * succ_parent;
	treeNode* child;

	parent = NULL;
	p = root;
	while ((p != NULL) && (strcmp(p->key.word, key.word) != 0)) { //노드가 0이아니거나 strcmp값이 0이 아닐때 계속 탐색
		parent = p;
		if (strcmp(key.word, p->key.word) < 0)
			p = p->left;
		else p = p->right;
	}
	if (p == NULL) {
		printf("\n 찾는 키가 이진트리에 없습니다!!");
		return;
	}

	//단말 노드의 삭제
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else root = NULL;
	}
	// 자식 노드가 한 개인 노드의 삭제 
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL) child = p->left;
		else child = p->right;
		if (parent != NULL) {
			if (parent->left == p) parent->left = child;
			else parent->right = child;
		}
		else root = child;
	}

	else { // 자식 노드가 두 개인 노드의 삭제
		succ_parent = p;
		succ = p->right;
		while (succ->left != NULL) {
			succ_parent = succ;
			succ = succ->left;
		}
		if (succ_parent->left == succ)
			succ_parent->left = succ->right;
		else succ_parent->right = succ->right;
		p->key = succ->key;
		p = succ;
	}
	free(p);
}

void menu()
{
	printf("\n*-----------------------------*");
	printf("\n\t1 : 입력");
	printf("\n\t2 : 삭제");
	printf("\n\t3 : 검색");
	printf("\n\t4 : 출력");
	printf("\n\t5 : 종료");
	printf("\n*-----------------------------*");
}

void inorderDisplay(treeNode* root) //왼쪽 오른쪽 노드를 검색중 해당 단어가 있으면 출력
{
	if (root) {
		inorderDisplay(root->left);
		printf("\n%s : %s", root->key.word, root->key.mean);
		inorderDisplay(root->right);
	}
}

void main()
{
	char choice;
	element e;
	treeNode* root = NULL, * temp;

	do
	{
		menu();
		choice = getchar();	getchar();

		switch (choice-'0')
		{
		case 1 :
			printf("\n[단어 입력] 단어를 입력하세요 : "); gets_s(e.word); //printf 출력후 라인변경 후 띄어쓰기를
			printf("\n[단어 입력] 단어 뜻을 입력하세요 : "); gets_s(e.mean); // 그대로 받아오기 위해 gets_s사용
			insert(&root, e);
			break;
		case 2:																						//puts_s란
			printf("\n[단어 삭제] 삭제할 단어 : "); gets_s(e.word); //printf에 입력된 문자열 출력 후 라인변경후
			deleteNode(root, e);														 // puts_s인수 출력
			break;
		case 3:
			printf("\n[단어 검색] 검색할 단어 : "); gets_s(e.word);
			temp = searchBST(root, e);
			if (temp != NULL)
				printf("\n단어 뜻 : %s", temp->key.mean);
			else printf("\n사전에 없는 단어입니다");
			break;
		case 4:
			printf("\t[사전 출력] ");
			inorderDisplay(root); printf("\n\t[사전 끝]\n");
			break;
		}
	} while ((choice-'0') != 5);
}


