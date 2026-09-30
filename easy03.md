# step1.什么是树
### 现在先了解什么是树，给树下一个定义。什么是二叉树？该如何定义一个二叉树？
- 树是一群有序连接的结构体，结构体内部含有数据，还有多个分支指针；二叉树就是每个树最多有两个分支指针（左指针右指针）的树；下面展示定义的代码：
````
typedef struct treenode{
    int data;
    struct treenode *left;
    struct treenode *right;
}tree;
````
### 在这一题中我们只讨论二叉树。请你思考，二叉树在c语言中应该如何存储？二叉树有哪些特点？
- 可以用数表存储(顺序存储？)也可以用结构体加指针存储。
-  每一个节点最多有两个孩子（？）（左子树，右子树），二叉树要么是NULL，要么由根节点和它的两个孩子构成。没有孩子的节点叫做叶子。

## 使用顺序表完成二叉树操作
#### 复制题目代码
````
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
````
- 1：（解释，思路都在每一行\\后面）
````
void init_tree(SeqBiTree *tree){
    tree->size=0;\\让size=0，意思就是“看起来一个节点也没有”
    for(int i=0;MAX_TREE_SIZE>i;i++ ){\\用循环来使得每一个元素的data和bool值都被定义
        tree->nodes[i].data=0;\\访问tree内部的nodes[i](这里问了deepseek)，再访问nodes[i]这个元素的data，让它=0
        tree->nodes[i].used=false;\\同理，让这个元素的布尔值等于false（意思这个节点实际上没有用？没有被占用？）
    }
 }
````
- 2(这里本来用的是nodes[0]，但是后面问过ai之后就明白了)
````
bool set_root(SeqBiTree *tree, int value) {
    if(tree==NULL){//先检查是不是空树（？）
        return false;
    }
    if(tree->nodes[1].used!=true){//检查是不是已经被占用了
        return false;
    }
    tree->nodes[1].data= value ;//把数据填写到对应的栏目里
    tree->nodes[1].used= true  ;//更改是否占用
    tree->size=1;//把树的大小设为1
    return true;
 }
````
- 3（添加了printf，帮助在运行时快速查找错误）
````
bool set_left_child(SeqBiTree *tree, int parent_node, int value)
{   if(tree==NULL){\\检测树是否存在
    printf("tree is not exist.\n")
    return false;
}
    int i= parent_node;\\把父节点下标赋值给i，之后赋值更方便；
    if(2*i>=MAX_TREE_SIZE){\\检测是否超过最大下标
        printf("out of MAX_TREE_SIZE.\n")
        return false;
    }
    if(tree->nodes[i].used!=true){\\检测父节点是否存在
        printf("no such father node.\n")
        return false;
    }
    tree->nodes[2*i].data=value;\\上述检测都通过之后，给子节点赋值
    tree->nodes[2*i].used=true;
    tree->size++;\\大小加一
    return true;

} 
````
- 4（同理，就是把2\*i换成2\*i+1）
````
bool set_right_child(SeqBiTree *tree, int parent_node, int value)
{   if(tree==NULL){
    printf("tree is not exist.\n")
    return false;
}
    int i= parent_node;
    if(2*i+1>=MAX_TREE_SIZE){
        printf("out of MAX_TREE_SIZE.\n")
        return false;
    }
    if(tree->nodes[i].used!=true){
        printf("no such father node.\n")
        return false;
    }
    tree->nodes[2*i+1].data=value;
    tree->nodes[2*i+1].used=true;
    tree->size++;
    return true;

} 
````
- 5（编完之后我有时候会发给AI。让他帮我看看有没有什么问题）
````
void level_order(SeqBiTree *tree){
    if(tree==NULL){\\检测是否为空树，但是AI建议加一个|| size==0
        return;
    }
    int a=1;
    int b=2;\\用b来检测是否需要换行
    while(a<=MAX_TREE_SIZE-1){\\限定下标的范围，避免输出乱七八糟的值
        if(a==b){
            printf("\n")；\\换行
            b=b*2;
        }
        int c=tree->nodes[a].data;
        if(tree->nodes[a].used==false){
            c=-1;\\如果遇到空节点，临时创建一个值c，并把-1储存进c，最后输出-1
        }
        printf("%d ", c);
        a++;
    }
    return;
}
````
- 6
````
最终运行截图已发送至github对应仓库。
````

# step2.链二叉树
### TreeNode* create_node(int value) 创建一个新的节点，新节点赋值为value，left和right指针都指向NULL。请你实现这个函数。
````
TreeNode* create_node(int value){
    TreeNode *treenode=(TreeNode *)malloc(sizeof(TreeNode));\\固有申请内存，流程和上一题保持一致
    treenode->data=value;
    treenode->left=NULL;
    treenode->right=NULL;
    return treenode;
}
````
### 创建树的过程写在代码的主函数里。
````
int main(void){\\注释：这里的doubleadd就是同时创建左右孩子并且插入值，因为只展示主函数故而省去
    TreeNode *root=create_node(1);
    doubleadd(2, 3, root);
    TreeNode *child1=root->left;
    TreeNode *child2=root->right;
    doubleadd(4, 5, child1);
    doubleadd(6, 7, child2);
    return 0;
}
````
### 完成树的创建以后，你会自然想到，该怎样验证这棵树是否创建正确。要想完成验证，最简单的办法就是打印这棵树。
### 请你思考，我们应该怎样打印一颗链二叉树呢？只使用简单的for循环无法实现这个打印函数。请你讲讲问什么无法实现。
- ①：我的想法：参数含有``root``，打印root内部的data后换行，接着打印它依次左孩子和右孩子的data再换行，接着将root变更为两个（即它的左右孩子？？）重复这个操作。
-  for含有初始条件，迭代，运行条件；每一个节点都可能一分为2，迭代没法通过简单的组数加一来解决其可能含有两个孩子的问题。（？）
# step3.递归
### 请你自行了解什么是二叉树的前序遍历，中序遍历，后序遍历。然后在上面的链二叉树代码文件中，实现这三个函数。并在主函数中调用这三个函数打印遍历结果。
- 展示这三个函数
````
void preorder(TreeNode *node){
    if(node==NULL){
        return;\\终止递归的条件
    }
    printf("%d | ", node->data);\\访问根
    preorder(node->left);\\访问左孩子（在内部开始递归，先访问根，再访问左孩子……直到根=NULL）
    preorder(node->right);\\访问右孩子
}
void inorder(TreeNode *node){
    if(node==NULL){
        return;
    }
    inorder(node->left);
    printf("%d | ", node->data);
    inorder(node->right);
}
void postorder(TreeNode *node){
    if(node==NULL){
        return;
    }
    postorder(node->left);
    postorder(node->right);
    printf("%d | ", node->data);
}
````
````
展示打印结果：1 | 2 | 4 | 5 | 3 | 6 | 7 | 

4 | 2 | 5 | 1 | 6 | 3 | 7 | 

4 | 5 | 2 | 6 | 7 | 3 | 1 |
````
### 请你思考上面递归的过程，讲讲为什么只改变printf函数出现的位置就可以实现这三种不同的递归。以前序遍历为例，讲讲二叉树中递归的过程。
- printf其实是该函数访问根的次序，举个例子，如果把printf放在最前面，那么会先输出当前的data，然后再去进入左孩子（新根），输出其data。如果把printf放在left后面，那么会先进入左孩子（新根），只要还有左孩子，就会持续地进入新根而不输出，直到``左孩子==NULL为止``，才会打印当前根的data，让后再访问右孩子。
- 前序遍历：根->左->右，先输出根的data，然后进入左孩子（新根）（开始递归），新根会优先输出其data，然后继续进入左孩子（新根），重复这个过程直到新根的左孩子=  =NULL，此时函数会回到上一步，并且进入右孩子（如果右孩子有左孩子，则依次类推），如果右孩子也==NULL，则再回到上一步，若右孩子仍为NULL，继续返回，直到右孩子!=NULL，输出右孩子，依次类推。
### int depth(TreeNode \*root, int current_depth, int max_depth) 通过这个函数实现对树的深度的统计。并讲讲为什么后面两个int不需要使用指针变量。
- 代码展示（刚开始疯狂报错，询问ds后得知没有终止条件，以及left和right没用到）
````
int depth(TreeNode *root, int current_depth, int max_depth){
    int a=max_depth;
    int b=max_depth;
    int c=current_depth;
    int d=current_depth;
    max_depth=a>b?a:b;
    if (root == NULL) {
    return max_depth;
}
    if(c>=a){
        a=c;
    }
    if(d>=b){
        b=d;
    }
    int left=depth(root->left, c+1, a);
    int right=depth(root->right, d+1, b);
    return(left>right?left:right);
}
````
- 为什么后面两个int不需要使用指针变量？因为后面两个值只需要输入，不需要通过指针更改其值，所以只提供一个虚构（副本）值就可以实现目的。
### 相信你在使用递归的过程中，一定感觉递归和循环有很多相似之处，请你讲讲你对这两种算法的感悟。
- 循环的感觉，就是不断地判定条件是否为真，如果为真就一直执行循环，最后输出结果（或者不输出）。递归比起循环，感觉就像是在循环内部再嵌套循环，直到无法嵌套循环为止（这样子说不严谨），可以说递归的过程本身就是循环。
---
 “我在这里帮你写出了栈操作的基本函数。请你阅读并理解上面的栈操作，并书写简单的注释。”
(下面为批注部分)
````
typedef struct Stack {
    TreeNode **arr;\\二重指针，arr指示TreeNode类型变量
    int top;
    int capacity;\\栈的最大容量
} Stack;
Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));//为栈申请大小为Stack字节的内存
    stack->arr = malloc(sizeof(TreeNode *) * capacity);//为arr申请capacity个TreeNode的字节的内存
    stack->top = -1;//设定为空栈
    stack->capacity = capacity;//把指定的容量导入栈的最大容量
    return stack;
}
int isEmpty(Stack *stack) {
    return stack->top == -1;
}//如果是个空栈（top==-1），则返回1，否则返回0
void push(Stack *stack, TreeNode *node) {//无返回值入栈
    if (stack->top == stack->capacity - 1) {//检测top是否达到容量上限
        return;
    }
    stack->arr[++stack->top] = node;//先自增top，再返回top+1的数值，向该位置填入node
}
TreeNode *pop(Stack *stack) {
    if (isEmpty(stack)) {//如果是栈顶空的，终止，输出NULL
        return NULL;
    }
    return stack->arr[stack->top--];//先去除栈顶部的元素，再将栈下移一个
}

void preorderTraversal(TreeNode *root) // 补全这个函数
````
- 新的函数展示
````
void preorderTraversal(TreeNode *root){
    if(root==NULL){
        return;
    }
    Stack *stack=createStack(114514);
    push(stack, root);
    while(isEmpty(stack)!=1){
        TreeNode *a=pop(stack);
        printf("%d | ", a->data);
        if(a->right!=NULL){
            push(stack, a->right);
        }
        if(a->left!=NULL){
            push(stack, a->left);
        }
    }

    return;
}
````
- 所有函数均移植入“step2&step3”




























