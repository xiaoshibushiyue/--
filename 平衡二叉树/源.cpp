#include<stdio.h>
#include<stdlib.h>
#define NAMESIZE 100
struct node_st
{
	node_st* l;
	node_st* r;
	struct score_st* data;
};
struct score_st
{
	int id;
	char* name;
	int math;
	int chinese;
};
void draw(struct node_st *root) {
	draw_(root,0);
}
int get_num(struct node_st *root) {
	if (root==NULL)
	{
		return 0;
	}
	return	get_num(root->l)+1+get_num(root->r);
}
//���������С�ڵ�
struct node_st* find_min(struct node_st*root) {
	if (root->l==NULL)
	{
		return  root;
	}
	return find_min(root->l);
}
//����
void turn_left(struct node_st **root) {
	struct node_st* cur = *root;
	*root = cur->r;
	cur->r = NULL;
	find_min((*root))->l=cur;
}
//�����ұ����Ľڵ�
struct node_st* find_max(struct node_st* root) {
	if (root->r==NULL)
	{
		return root;
	}
	return find_max(root->r);
}
//����
void true_right(struct node_st** root) {
	struct node_st* cur = *root;
	*root = cur->l;
	cur->l = NULL;
	find_max(*root)->r=cur;
}
//����ƽ����
void balance(struct node_st** root) {
	if (*root==NULL)
	{
		return;
	}
	while (1)
	{
		int sub = get_num((*root)->l) - get_num((*root)->r);
		if (sub >= -1 && sub <= 1)
		{
			break;
		}
		if (sub < -1)
		{
			turn_left(root);
		}
		else {
			true_right(root);
		}
	}
	balance(&(*root)->l);
	balance(&(*root)->r);
}
//����ֵ���ֽڵ�
struct score_st* find(struct node_st*root,int id) {
	if (root==NULL)
	{
		return NULL;
	}
	if (id==root->data->id)
	{
		return root->data;
	}
	if (id<root->data->id)
	{
		return find(root->l,id);
	}
	else {
		return find(root->r,id);
	}
}
//ɾ���ڵ�
void delete_node(struct node_st **root,int id) {
	//��߻����ұ߶�����
	//������߶�����
	struct node_st** node = root;
	while (*node!=NULL&&(*node)->data->id!=id)
	{
		if (id < (*node)->data->id)
		{
			node = &(*node)->l;
		}
		else {
			node = &(*node)->r;

		}
	}
	if (*node==NULL)
	{
		return;
	}
	struct node_st*	cur = *node;
	if (cur->l=NULL)
	{
		*node = cur->r;
	}
	else {
		*node = cur->l;
		find_max(cur->l)->r = cur->r;
	}
	free(cur);
	
}
//����-����
void travel(struct node_st*root) {
	if (root==NULL)
	{
		return;
	}
	//printf(&root->data);
	travel(root->l);
	travel(root->r);
	//����
	travel(root->l);
	//printf(&root->data);
	travel(root->r);
	//����
	travel(root->l);
	travel(root->r);
	//printf(&root->data);
}
//���ղ����-���ö���
void travel_(struct node_st* root) {

}
int main() {
	int arr[] = { 1,2,3,7,6,5,9,8,4 };
	int i;
	struct node_st* tree = NULL;
	struct score_st tmp, *datap;
	for ( i = 0; i < sizeof(arr); i++)
	{
		tmp.id = arr[i];
		snprintf(tmp.name,NAMESIZE,"stu%d",arr[i]);
		tmp.math = rand() % 100;
		tmp.chinese = rand() % 100;
		insert(&tree,&tmp);
	}
	balance(&tree);

	//ɾ���ڵ�
	int tmpid = 5;
	delete_node(&tree,tmpid);
	//balance(&tree);Ӧ�ò���Ҫ
	travel(tree);
}
