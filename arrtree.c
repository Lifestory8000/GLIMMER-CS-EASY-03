#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE_SIZE 100
/*
 * 顺序存储二叉树结点
 * - data：结点数据
 * - used：当前位置是否有结点
 */
typedef struct {
    int data;
    bool used;
} SeqTreeNode;

/*
 * 顺序存储二叉树
 * - nodes：结点数组
 * - size：数组最大容量
 */
typedef struct {
    SeqTreeNode nodes[MAX_TREE_SIZE];
    int size;
} SeqBiTree;
/*
void init_tree(SeqBiTree *tree)
 实现初始化二叉树函数，
 让二叉树的大小为MAX_TREE_SIZE，
 并将其全部节点设置为空，大小为0。
 */
 void init_tree(SeqBiTree *tree){
    tree->size=0;
    for(int i=0;MAX_TREE_SIZE>i;i++ ){
        tree->nodes[i].data=0;
        tree->nodes[i].used=false;
    }
 }
 /*bool set_root(SeqBiTree *tree, int value) 
 创建根节点，在节点数组1处设置根节点，
 函数需要传入根节点的data
 */
 bool set_root(SeqBiTree *tree, int value) {
    if(tree==NULL){
        return false;
    }
    if(tree->nodes[1].used!=false){
        return false;
    }
    tree->nodes[1].data= value ;
    tree->nodes[1].used= true  ;
    tree->size=1;
    return true;
 }

/*
bool set_left_child(SeqBiTree *tree, int parent_node, int value) 
 创建左孩子，parent_node为对应父节点下标
 */
bool set_left_child(SeqBiTree *tree, int parent_node, int value)
{   if(tree==NULL){
    printf("tree is not exist.\n");
    return false;
}
    int i= parent_node;
    if(2*i>=MAX_TREE_SIZE){
        printf("out of MAX_TREE_SIZE.\n");
        return false;
    }
    if(tree->nodes[i].used!=true){
        printf("no such father node.\n");
        return false;
    }
    tree->nodes[2*i].data=value;
    tree->nodes[2*i].used=true;
    tree->size++;
    return true;

} 
 /*
 bool
  set_right_child(SeqBiTree *tree, int parent_node, int value) 
  创建右孩子。
 */
 bool set_right_child(SeqBiTree *tree, int parent_node, int value)
{   if(tree==NULL){
    printf("tree is not exist.\n");
    return false;
}
    int i= parent_node;
    if(2*i+1>=MAX_TREE_SIZE){
        printf("out of MAX_TREE_SIZE.\n");
        return false;
    }
    if(tree->nodes[i].used!=true){
        printf("no such father node.\n");
        return false;
    }
    tree->nodes[2*i+1].data=value;
    tree->nodes[2*i+1].used=true;
    tree->size++;
    return true;

} 
 /*
 void level_order(SeqBiTree *tree) 实现层序遍历，
 按数组下标顺序打印整棵树，节点为空则打印-1，
 每打印完一层之后换行。
 */
void level_order(SeqBiTree *tree){
    if(tree==NULL){
        return;
    }
    int a=1;
    int b=2;
    while(a<=MAX_TREE_SIZE-1){
        if(a==b){
            printf("\n");
            b=b*2;
        }
        int c=tree->nodes[a].data;
        if(tree->nodes[a].used==false){
            c=-1;
        }
        printf("%d ", c);
        a++;
    }
    return;
}
int main(void){
    SeqBiTree *tree=(SeqBiTree *)malloc(sizeof(SeqBiTree));
    init_tree(tree);
    set_root(tree, 1);
    set_left_child(tree, 1, 2);
    set_right_child(tree, 1, 3);
    level_order(tree);
    free(tree);
    return 0;
}