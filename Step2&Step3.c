#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;                       // 节点存储的数据
    struct TreeNode *left;          // 左子树指针
    struct TreeNode *right;         // 右子树指针
} TreeNode;
TreeNode* create_node(int value){
    TreeNode *treenode=(TreeNode *)malloc(sizeof(TreeNode));
    treenode->data=value;
    treenode->left=NULL;
    treenode->right=NULL;
    return treenode;
}
void doubleadd(int a, int b, TreeNode *node){
            if(node==NULL){
                return;
            }
            if(node->left==NULL){
                node->left=create_node(a);
            }else if(node->left!=NULL){
                node->left->data=a;
            }   
            if(node->right==NULL){
                node->right=create_node(b);
            }else if(node->right!=NULL){
                node->right->data=b;
            }        
            return;
}
void preorder(TreeNode *node){
    if(node==NULL){
        return;
    }
    printf("%d | ", node->data);
    preorder(node->left);
    preorder(node->right);
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
typedef struct Stack {
    TreeNode **arr;//二重指针,arr指示TreeNode类型变量
    int top;
    int capacity;//栈的最大容量
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
    
int main(void)
{
    TreeNode *root=create_node(1);
    doubleadd(2, 3, root);
    TreeNode *child1=root->left;
    TreeNode *child2=root->right;
    doubleadd(4, 5, child1);
    doubleadd(6, 7, child2);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    int dep=depth(root, 1, 1);
    printf("%d\n", dep);
    preorderTraversal(root);
    return 0;
}