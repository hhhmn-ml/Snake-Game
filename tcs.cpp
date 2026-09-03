#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
struct Snakenode{
	int x;
	int y;
	struct Snakenode *next;
};
struct Food{
	int x1;
	int y1;
};
struct Snakenode *head=NULL;
struct Food food;
int score=0;
int flag=0;

int right,left,down,up;
int tailx,taily;

void Draw();
void GotoXY(int x,int y);
void Createfood();
void keycontrol();
void Movesnake();


void Initsnake(){
	struct Snakenode *node3=(struct Snakenode*)malloc(sizeof(struct Snakenode));
	node3->x=10;
	node3->y=10;
	node3->next=NULL;
	
	struct Snakenode *node2=(struct Snakenode*)malloc(sizeof(struct Snakenode));
	node2->x=11;
	node2->y=10;
	node2->next=node3;
	
	struct Snakenode *node1=(struct Snakenode*)malloc(sizeof(struct Snakenode));
	node1->x=12;
	node1->y=10;
	node1->next=node2;
	
	head=node1;
}
int main(){
	SetConsoleOutputCP(65001);
	right = 1;
	left=0;
	down=0;
	up=0;
	srand((unsigned)time(NULL));
	Initsnake();
	Createfood();
	while(1){
		Draw();
		keycontrol();
		Movesnake();
		Sleep(80);
		if(flag==1){
			break;
		}
	}
	return 0;
}
void Createfood(){
	int flag;
	do{
		flag=0;
		food.x1=rand()%36+2;
		food.y1=rand()%20+2;
		struct Snakenode *p=head;
		while(p!=NULL){
			if(p->x==food.x1&&p->y==food.y1){
				flag=1;
				break;
			}
			p=p->next;
		}
		
	}while(flag==1);
}
void Draw(){
	GotoXY(0,0);
	for(int i=0; i<40; i++){
		printf("#");
	}
	printf("\n");
	for(int y=1; y<22; y++){
		GotoXY(0,y);
		printf("#");
		GotoXY(39,y);
		printf("#");
	}
	GotoXY(0,22);
	for(int i=0; i<40; i++){
		printf("#");
	}
	printf("\n");
	
	struct Snakenode *p=head;
	while(p!=NULL){
		GotoXY(p->x,p->y);
		printf("o");
		p=p->next;
	}
	
	GotoXY(food.x1,food.y1);
	printf("F");
	
	GotoXY(tailx,taily);
	printf(" ");
	
	GotoXY(0,25);
}
void GotoXY(int x,int y){
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void Movesnake(){
	struct Snakenode *newhead=(struct Snakenode*)malloc(sizeof(struct Snakenode));
	if(right){
		newhead->x=head->x+1;
		newhead->y=head->y;
	}else if(left){
		newhead->x=head->x-1;
		newhead->y=head->y;
	}else if(up){
		newhead->x=head->x;
		newhead->y=head->y-1;
	}else if(down){
		newhead->x=head->x;
		newhead->y=head->y+1;
	}
	
	newhead->next=head;
	head=newhead;
	
	struct Snakenode *p=head;
	p=p->next;
	while(p!=NULL){
		if(p->x==head->x&&p->y==head->y){
			printf("游戏结束\n");
			printf("分数为%d分\n",score);
			flag=1;
			return;
		}
		p=p->next;
	}
	if(head->x<=0||head->x>=39||head->y<=0||head->y>=22){
		printf("游戏结束\n");
		printf("分数为%d分\n",score);
		flag=1;
		return;
	}
	
	if(head->x==food.x1&&head->y==food.y1){
		Createfood();
		score++;
		return;
	}
	
	struct Snakenode *pp=head;
	while(pp->next->next!=NULL){
		pp=pp->next;
	}
	tailx=pp->next->x;
	taily=pp->next->y;
	free(pp->next);
	pp->next=NULL;
	GotoXY(0,25);

	
	                                                                                                                                                                      
}
void keycontrol(){
	if(_kbhit()){
		switch(_getch()){
			case 'w':
				if(down==0){up=1;down=0;left=0;right=0;}
				break;
			case 's':
				if(up==0){up=0;down=1;left=0;right=0;}
				break;
			case 'd':
				if(left==0){up=0;down=0;left=0;right=1;}
				break;
			case 'a':
				if(right==0){up=0;down=0;left=1;right=0;}
				break;
			
		}
	}
}