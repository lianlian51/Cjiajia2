#pragma once 

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

typedef int DataType;

typedef struct QNode{
  struct QNode* next_;
  DataType data_;
}QNode;


typedef struct Queue{
  struct QNode* head;  // 这里的一定写的是QNode，因为是以QNode为底层建立的队列
  struct QNode* rear;
  DataType size_;
}Queue;

struct QNode* BuyNode(int val)
{
  struct QNode* Node = (struct QNode*)malloc(sizeof(struct QNode));
  if(Node == NULL)
  {
    assert(0);
    return NULL;
  }
  Node->next_ = NULL;
  Node->data_ = val;

  return Node;
}

// 队列是否为空
int QueueEmpty(struct Queue* q)
{
  assert(q);
  return 0 == q->size_;
}

// 队列初始化
void QueueInit(struct Queue* q)
{
  assert(q);
  q->head = BuyNode(0);
  q->rear = q->head;
  q->size_ = 0;
}

// 入队
void QueuePush(struct Queue* q, DataType val)
{
  assert(q);
  QNode* NewNode = BuyNode(val);
  q->rear->next_ = NewNode;
  q->rear = NewNode;
  q->size_++;
}

// 出队
void QueuePop(struct Queue* q)
{
  QNode* delNode = NULL;

  assert(q);
  if(QueueEmpty(q))
    return;

  delNode = q->head->next_;
  q->head->next_ = delNode->next_;
  free(delNode);
  q->size_--;
}

// 获取有效元素
DataType QueueSize(struct Queue* q)
{
  assert(q);
  return q->size_;
}


// 获取队头元素
struct QNode* QueueFront(struct Queue* q)
{
  assert(q);
  return q->head->next_;
}

// 获取队尾元素
DataType QueueBack(struct Queue* q)
{
  assert(q);
  return q->rear->data_;
}

