#pragma once 

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <assert.h>

#include <iostream>

typedef int DataType;

struct BinTreeNode
{
  DataType data_;
  struct BinTreeNode* left;
  struct BinTreeNode* right;
};


BinTreeNode* BuyNode(DataType data)
{
  BinTreeNode* newNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));

  if(NULL == newNode)
  {
    assert(0);
    return NULL;
  }
  newNode->data_= data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

BinTreeNode* Create()
{
  BinTreeNode* node1 = BuyNode(1);
  BinTreeNode* node2 = BuyNode(2);
  BinTreeNode* node3 = BuyNode(3);
  BinTreeNode* node4 = BuyNode(4);
  BinTreeNode* node5 = BuyNode(5);
  BinTreeNode* node6 = BuyNode(6);

  BinTreeNode* pRoot = node1;
  node1->left = node2;
  node1->right = node3;
  node2->left = node4;
  node2->right = node5;
  node3->left = node6;

  return pRoot;
}

// 前序遍历
void PreOrder(BinTreeNode* root)
{
  if(root)
  {
    printf("%d ", root->data_);
    PreOrder(root->left);
    PreOrder(root->right);
  }
}

// 中序遍历
void InOrder(BinTreeNode* root)
{
  if(root)
  {
    InOrder(root->left);
    printf("%d ", root->data_);
    InOrder(root->right);
  }
}

// 后序遍历
void PostOrder(BinTreeNode* root)
{
  if(root)
  {
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ", root->data_);
  }
}

// 获取节点的个数
int GetCount(BinTreeNode* root)
{
  assert(root);
  if(root->left == NULL && root->right == NULL)
    return 0;

  return 1 + GetCount(root->left) + GetCount(root->right);
}

// 获得叶子节点的个数
int GetleafCount(BinTreeNode* root)
{
  if(root == NULL)
    return 0;

  if(root->left == NULL && root->right == NULL)
    return 1;

  return GetleafCount(root->left) + GetleafCount(root->right);
}

// 返回二叉树的高度
int GetHeight(BinTreeNode* root)
{
  assert(root);
  if(NULL == root)
    return 0;

  int leftHeight = GetHeight(root->left);
  int rightHeight = GetHeight(root->right);

  return leftHeight > rightHeight ? leftHeight : rightHeight;
}

// 获取k层节点的个数
int GetKCount(BinTreeNode* root, int k)
{
  if(root == NULL)
    return 0;

  if(k == 1)
    return 1;

  return GetKCount(root->left, k - 1) + GetKCount(root->right, k - 1); 
}

// 返回x在二叉树中的节点
BinTreeNode* Find(BinTreeNode* root, DataType data)
{
  if(root == NULL)
    return NULL;

  BinTreeNode* pNode = NULL;

  if(root->data_ == data)
    return root;

  if((pNode = Find(root->left, data)) || (pNode = Find(root->right, data)))
    return pNode;

  return NULL;
}

// 获取节点的双亲
BinTreeNode* GetParent(BinTreeNode* root, BinTreeNode* node)
{
  if(root == NULL || node == NULL || root == node)
    return NULL;

  BinTreeNode* pParent = NULL;

  if(root->left == node || root->right == node)
    return root;

  if((pParent = GetParent(root->left, node)) || (pParent = GetParent(root->right, node)))
    return pParent;

  return NULL;
}

// 二叉树层序遍历

