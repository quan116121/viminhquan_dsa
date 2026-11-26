#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	char ten[30];
	int ma;
	float d1, d2, d3;
}Data;

typedef struct tagNode{
	Data infor;
	struct tagNode *link;
}Node;
typedef struct{
	Node *pHead;
	Node *pTail;
	int spt;
}LList;
void initList(LList *L){
	L->pHead = NULL;
	L->pTail = NULL;
    L->spt = 0;
}
int emptyList(LList L){
	return(L.spt == 0);
}
void insert_Head(LList *L, Data x){
	Node *pp;
	pp = (Node*) malloc(sizeof(Node));
	pp->infor = x;
	pp->link = NULL;
	if(emptyList(*L)){
		L->pHead = pp;
		L->pTail = pp;
	}
	else{
		pp->link = L->pHead;
		L->pHead = pp;
	}
	L->spt++;
}
void insert_Tail(LList *L, Data x){
	Node *pp;
	pp = (Node*) malloc(sizeof(Node));
	pp->infor = x;
	pp->link = NULL;
	if(emptyList(*L)){
		L->pHead = pp;
		L->pTail = pp;
	}
	else {
		L->pTail->link = pp;
		L->pTail = pp;
	}
	L->spt++;
}
void insert_After(LList *L, Node *q, Data x){
	Node *pp;
	if(NULL == q) return;
	else{
		pp = (Node*) malloc(sizeof(Node));
		pp->infor = x;
		pp->link = q->link;
		q->link = pp;
		if(q == L->pTail) L->pTail = pp;
		L->spt++;
	}
}
Node *search(LList L, char name[30]){
	Node *pp = L.pHead;
	while(pp != NULL && !strstr(pp->infor.ten, name))
	    pp = pp->link;
	return pp;
}
void del_Head(LList *L){
	Node *pp;
	if(emptyList(*L)) return;
	else{
		pp = L->pHead;
		L->pHead = pp->link;
		free(pp);
		L->spt--;
		if(L->pHead == NULL) L->pTail = NULL;
	}
}
void del_After(LList *L, Node *q){
	Node *pp;
	if(NULL == q) return;
	else {
		pp = q->link;
		if(q->link == L->pTail) L->pTail = q;
		q->link = pp->link;
		free(pp);
		L->spt--;
	}
}
void tach(LList L, LList *L1, LList *L2){
	initList(L1);
	initList(L2);
	Node *pp = L.pHead;
	while(pp != NULL){
		if(pp->infor.d1 < 5 || pp->infor.d2 < 5 || pp->infor.d3 < 5)
		    insert_Head(L1, pp->infor);
		else
		    insert_Head(L2, pp->infor);
		pp = pp->link;
	}
}
void ghep(LList L1, LList L2, LList *L){
	initList(L);
	Node *p1 = L1.pHead;
	Node *p2 = L2.pHead;
	if(L1.spt < L2.spt){
		while(p1 != NULL){
			insert_Head(L, p1->infor);
			insert_Head(L, p2->infor);
			p1 = p1->link;
			p2 = p2->link;
		}
		while(p2 != NULL){
			insert_Head(L, p2->infor);
			p2 = p2->link;
		}
	}
	else{
		while(p2 != NULL){
			insert_Head(L, p1->infor);
			insert_Head(L, p2->infor);
			p1 = p1->link;
			p2 = p2->link;
		}
		while(p1 != NULL){
			insert_Head(L, p1->infor);
			p1 = p1->link;
		}
	}
}
void nhap(Data *x){
	printf("Nhap ma sinh vien: ");
	scanf("%d", &(x->ma));
	if(x->ma > 0){
		printf("Nhap ho ten: ");
		scanf("%s", (x->ten));
		printf("Nhap diem 1: ");
		scanf("%f", &(x->d1));
		printf("Nhap diem 2: ");
		scanf("%f", &(x->d2));
		printf("Nhap diem 3: ");
		scanf("%f", &(x->d3));
	}
}
void in(Data x){
	printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 3: %.2f\n", x.ten, x.ma, x.d1, x.d2, x.d3);
}
void duyetList(LList L){
	Node *pp = L.pHead;
	while(pp != NULL){
		in(pp->infor);
		pp = pp->link;
	}
}
int main(){
	LList L;
	LList L1, L2;
	int kt = 0;
	Data x;
	initList(&L);
	initList(&L1);
	initList(&L2);
	do{
		printf("\n1.Them nut vao dau danh sach");
		printf("\n2.Them nut vao cuoi danh sach");
		printf("\n3.Them nut vao sau mot nut khac");
		printf("\n4.Xoa nut dau danh sach");
		printf("\n5.Xoa nut sau mot nut khac");
		printf("\n6.Tach danh sach theo diem");
		printf("\n7.Ghep danh sach");
		printf("\n8.Tim kiem theo ten");
		printf("\n9.Duyet danh sach");
		printf("\n0.Thoat");
		printf("\nMoi ban chon: ");
		int chon;
		scanf("%d", &chon);
		switch(chon){
			case 1:
				printf("Nhap thong tin sinh vien can them\n");
				nhap(&x);
				if(x.ma > 0) insert_Head(&L, x);
				break;
			case 2:
				printf("Nhap thong tin sinh vien can them\n");
				nhap(&x);
				if(x.ma > 0) insert_Tail(&L, x);
				break;
			case 3:{
				int ma;
				Node *q = L.pHead;
				printf("Nhap ma sinh vien can them sau: ");
				scanf("%d", &ma);
				while(q != NULL && q->infor.ma != ma)
				    q = q->link;
				if(NULL != q) insert_After(&L, q, x);
				break;
		    }
			case 4:
				del_Head(&L);
				break;
			case 5:{
				int ma;
				Node *q = L.pHead;
				printf("Nhap ma sinh vien can xoa sau: ");
				scanf("%d", &ma);
				while(q != NULL && q->infor.ma != ma)
				    q = q->link;
				if(q != NULL && q->link != NULL)
				    del_After(&L, q);
				break;
			}
			case 6:
				if(x.ma > 0){
					tach(L, &L1, &L2);
					printf("Danh sach sinh vien co diem < 5:\n");
					duyetList(L1);
					printf("Danh sach sinh vien co diem > 5:\n");
					duyetList(L2);
				}
				break;
			case 7:
				if(x.ma > 0){
					ghep(L1, L2, &L);
					printf("Danh sach sau khi ghep:\n");
					duyetList(L);
				}
				break;
			case 8:{
				char name[30];
			    printf("Nhap ten sinh vien can tim: ");
			    scanf("%s", name);
			    Node *q = search(L, name);
				if(q != NULL)
					in(q->infor);
				break;
		    }
			case 9:
				duyetList(L);
				break;
			case 0:
				printf("Chao tam biet.\n");
				kt = 1;	
		}
	}while(kt == 0);
}
