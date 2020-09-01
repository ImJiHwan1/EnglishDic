#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
// strcat() = ���ڿ� �̾� ���̱� strcmp() = �� ���ڿ� ��(�ּ� ��)
//strlen() = ���ڿ��� ���� �˷��� strcpy() = ���ڿ� ����

#define MAX_WORD_LENGTH 20
#define MAX_MEAN_LENGTH 200

typedef struct {
	char word[MAX_WORD_LENGTH];
	char mean[MAX_MEAN_LENGTH];
} element;

typedef struct treeNode { //Ʈ�� ����ü ���� ����
	element key;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

treeNode* searchBST(treeNode* root, element key) // �ܾ� �˻� �˰���
{
	treeNode* p;	int compare;
	p = root;
	printf("\nã�� �ܾ� : %s", key.word); 
	printf("\n����ܾ� : %s", p->key.word); //Ʈ���� ������ �ܾ�
	while (p != NULL) {
		compare = strcmp(key.word, p->key.word); // key.word, p->key.word ���ڿ� ��
		if (compare < 0) {
			p = p->left;
			printf("\n�˻� �� ���ʴܾ� : %s", p->key.word);
		}
		else if (compare > 0) {
			p = p->right;
			printf("\n�˻� �� ������ �ܾ� : %s", p->key.word);
		}
		else { // compare = 0
			printf("\nã�� �ܾ� : %s", p->key.word);
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
		newNode = (treeNode*)malloc(sizeof(treeNode)); //Ʈ���� �����Ǵ� ���� ��� ����
		newNode->key = key; //p���� �����̶� ��ũ���� NULL���� �ش�
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else {
		compare = strcmp(key.word, p->key.word); //���� Ʈ���� �����Ǿ��ִ� ���ڿ��� ���Ͽ� 	
		if (compare < 0) {	//���� Ʈ��						   //���� ���ڰ� ������ Ȯ��
			p->left = insertKey(p->left, key);
			return p;
		}
		else if (compare > 0) { //������ Ʈ��
			p->right = insertKey(p->right, key);
			return p;
		}
		else {
			printf("\n �̹� ���� �ܾ �ֽ��ϴ�! \n");
			return p;
		}
	}
}

void insert(treeNode** root, element key) //treeNode -> insertKey �ι� ���� ����
{
	*root = insertKey(*root, key);
}

void deleteNode(treeNode* root, element key)
{
	treeNode* parent, * p, * succ, * succ_parent;
	treeNode* child;

	parent = NULL;
	p = root;
	while ((p != NULL) && (strcmp(p->key.word, key.word) != 0)) { //��尡 0�̾ƴϰų� strcmp���� 0�� �ƴҶ� ��� Ž��
		parent = p;
		if (strcmp(key.word, p->key.word) < 0)
			p = p->left;
		else p = p->right;
	}
	if (p == NULL) {
		printf("\n ã�� Ű�� ����Ʈ���� �����ϴ�!!");
		return;
	}

	//�ܸ� ����� ����
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else root = NULL;
	}
	// �ڽ� ��尡 �� ���� ����� ���� 
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL) child = p->left;
		else child = p->right;
		if (parent != NULL) {
			if (parent->left == p) parent->left = child;
			else parent->right = child;
		}
		else root = child;
	}

	else { // �ڽ� ��尡 �� ���� ����� ����
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
	printf("\n\t1 : �Է�");
	printf("\n\t2 : ����");
	printf("\n\t3 : �˻�");
	printf("\n\t4 : ���");
	printf("\n\t5 : ����");
	printf("\n*-----------------------------*");
}

void inorderDisplay(treeNode* root) //���� ������ ��带 �˻��� �ش� �ܾ ������ ���
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
			printf("\n[�ܾ� �Է�] �ܾ �Է��ϼ��� : "); gets_s(e.word); //printf ����� ���κ��� �� ���⸦
			printf("\n[�ܾ� �Է�] �ܾ� ���� �Է��ϼ��� : "); gets_s(e.mean); // �״�� �޾ƿ��� ���� gets_s���
			insert(&root, e);
			break;
		case 2:																						//puts_s��
			printf("\n[�ܾ� ����] ������ �ܾ� : "); gets_s(e.word); //printf�� �Էµ� ���ڿ� ��� �� ���κ�����
			deleteNode(root, e);														 // puts_s�μ� ���
			break;
		case 3:
			printf("\n[�ܾ� �˻�] �˻��� �ܾ� : "); gets_s(e.word);
			temp = searchBST(root, e);
			if (temp != NULL)
				printf("\n�ܾ� �� : %s", temp->key.mean);
			else printf("\n������ ���� �ܾ��Դϴ�");
			break;
		case 4:
			printf("\t[���� ���] ");
			inorderDisplay(root); printf("\n\t[���� ��]\n");
			break;
		}
	} while ((choice-'0') != 5);
}


