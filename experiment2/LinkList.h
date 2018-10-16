//数据结构
typedef struct LNode {
	double coef; //多项式的系数 
	double expn; //多项式的指数 
	struct LNode *next; //指向下一个多项式结点的指针 
} Link;

//链表
typedef struct {
	Link* head;
	Link* tail;
	int len;
}LinkList;

//添加节点
void AddNode(LinkList* L, double coef, double expn) {
	Link *p = NULL;
	p = new Link;
	p->next = NULL;
	L->tail->coef = coef;
	L->tail->expn = expn;
	L->tail = L->tail->next = p;
	L->len++;
}

//基本操作
//初始化链表
void InitList(LinkList& L) {
	L.head = L.tail = new Link;
	L.len = 0;
};
//删除链表
void DestroyList(LinkList& L) {
	delete &L;
};
//交换节点
void swapLink(Link* L1, Link* L2) {
	double tempCoef = L1->coef;
	double tenpExpnv = L1->expn;

	L1->coef = L2->coef;
	L1->expn = L2->expn;

	L2->coef = tempCoef;
	L2->expn = tenpExpnv;
}
//删除节点
void deleteLink(Link* L, LinkList& linklist) {
	L->next = L->next->next;
	linklist.len--;
};

//冒泡排序(由大到小）
void LinkListBubbleSort(LinkList& L) {
	Link* index;
	for (int i = 0; i < L.len - 1; ++i) {
		index = L.head;
		for (int j = 0; j < L.len - i - 1; ++j) {
			if (index->next->coef == 0) {
				deleteLink(index, L);
			}
			if (index->expn == index->next->expn) {
				index->coef += index->next->coef;
				deleteLink(index, L);
			}
			if (index->expn < index->next->expn) {
				swapLink(index, index->next);
			}
			index = index->next;
		}
	}
}

//加法
LinkList AddPolyn(LinkList L1, LinkList L2) {
	LinkListBubbleSort(L1);
	LinkListBubbleSort(L2);
	LinkList result;
	InitList(result);

	while (L1.head->next != NULL || L2.head->next != NULL) {
		if (L1.head->expn > L2.head->expn) {
			AddNode(&result, L1.head->coef, L1.head->expn);
			L1.head = L1.head->next;
		}
		else if (L1.head->expn < L2.head->expn) {
			AddNode(&result, L2.head->coef, L2.head->expn);
			L2.head = L2.head->next;
		}
		else {
			AddNode(&result, L1.head->coef + L2.head->coef, L2.head->expn);
			L1.head = L1.head->next;
			L2.head = L2.head->next;
		}
	}
	while (L1.head->next != NULL) {
		AddNode(&result, L1.head->coef, L1.head->expn);
		L1.head = L1.head->next;
	}
	while (L1.head->next != NULL) {
		AddNode(&result, L2.head->coef, L2.head->expn);
		L2.head = L2.head->next;
	}
	return result;
}

//减法 L1-L2
LinkList SubPolyn(LinkList L1, LinkList L2) {
	LinkListBubbleSort(L1);
	LinkListBubbleSort(L2);
	LinkList result;
	InitList(result);
	while (L1.head->next != NULL || L2.head->next != NULL) {
		if (L1.head->expn > L2.head->expn) {
			AddNode(&result, L1.head->coef, L1.head->expn);
			L1.head = L1.head->next;
		}
		else if (L1.head->expn < L2.head->expn) {
			AddNode(&result, L2.head->coef*-1, L2.head->expn);
			L2.head = L2.head->next;
		}
		else {
			if (L1.head->coef - L2.head->coef != 0) {
				AddNode(&result, L1.head->coef - L2.head->coef, L2.head->expn);
			}
			L1.head = L1.head->next;
			L2.head = L2.head->next;
		}
	}
	while (L1.head->next != NULL) {
		AddNode(&result, L1.head->coef, L1.head->expn);
		L1.head = L1.head->next;
	}
	while (L1.head->next != NULL) {
		AddNode(&result, L2.head->coef*-1, L2.head->expn);
		L2.head = L2.head->next;
	}
	return result;
}

//乘法
LinkList MultiplyPolyn(LinkList L1, LinkList L2) {
	LinkListBubbleSort(L1);
	LinkListBubbleSort(L2);
	Link* index;
	LinkList result;
	InitList(result);
	while (L1.head->next != NULL)
	{
		index = L2.head;
		while (index->next != NULL) {
			if (L1.head->coef != 0 && index->coef != 0)
				AddNode(&result, L1.head->coef* index->coef, L1.head->expn + index->expn);
			index = index->next;
		}
		L1.head = L1.head->next;
	}
	return result;
}

//求导
LinkList Derivation(LinkList L) {
	LinkList result;
	InitList(result);
	while (L.head->next != NULL)
	{
		if (L.head->expn != 0)
			AddNode(&result, L.head->coef*L.head->expn, L.head->expn - 1);
		L.head = L.head->next;
	}
	return result;
}

