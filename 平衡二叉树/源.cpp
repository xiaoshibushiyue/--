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
//发现左边最小节点
struct node_st* find_min(struct node_st*root) {
	if (root->l==NULL)
	{
		return  root;
	}
	return find_min(root->l);
}
//左旋
void turn_left(struct node_st **root) {
	struct node_st* cur = *root;
	*root = cur->r;
	cur->r = NULL;
	find_min((*root))->l=cur;
}
//发现右边最大的节点
struct node_st* find_max(struct node_st* root) {
	if (root->r==NULL)
	{
		return root;
	}
	return find_max(root->r);
}
//右旋
void true_right(struct node_st** root) {
	struct node_st* cur = *root;
	*root = cur->l;
	cur->l = NULL;
	find_max(*root)->r=cur;
}
//生成平衡树
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
//根据值发现节点
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
//删除节点
void delete_node(struct node_st **root,int id) {
	//左边或者右边顶上来
	//采用左边顶上来
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
//遍历-先序
void travel(struct node_st*root) {
	if (root==NULL)
	{
		return;
	}
	//printf(&root->data);
	travel(root->l);
	travel(root->r);
	//中序
	travel(root->l);
	//printf(&root->data);
	travel(root->r);
	//后序
	travel(root->l);
	travel(root->r);
	//printf(&root->data);
}
//按照层遍历-采用队列
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

	//删除节点
	int tmpid = 5;
	delete_node(&tree,tmpid);
	//balance(&tree);应该不需要
	travel(tree);
}
