#include<stdio.h>
#include<stdlib.h>
 
typedef struct term//���������Ŷ���ʽ�ڵ� 
{
    float coef;
    int expn;
    struct term *next;
}term,*LinkList;
 
typedef LinkList polynomial;
 
int cmp(LinkList pa,LinkList pb)//�Ƚ�ָ����С 
{
    if(pa->expn > pb->expn)
        return 1;
    else if(pa->expn == pb->expn)
        return 0;
    else 
        return -1;
}
 
int LocateElem(LinkList L,LinkList t,LinkList *q)//��λָ����ʹ����ʽ����ڤ���� //���������Ⱑ��ָͬ����û�ܹ���ȥ�������� 
{
    LinkList p1=L->next;
    LinkList p2=L;
    while(p1)
    {
        if(t->expn > p1->expn)
        {
            p1=p1->next;
            p2=p2->next;
        }
        else if(t->expn == p1->expn)
        {
            *q=p1;
            return 1;
        }
        else 
        {
            *q=p2;
            return 0;
        }
    }
 
    *q=p2;
    return 0;
}
 
void CreatePolyn(polynomial P)//��������ʽ 
{
    LinkList t;
    LinkList q;
    P->coef=0.0;
    P->expn=-1;
    P->next=NULL;
    printf("����ʾ����һ������ʽ\n");
 
    t=(LinkList)malloc(sizeof(term));
    t->next=NULL;
    scanf("%f,%d",&t->coef,&t->expn);
    while(t->coef||t->expn)
    {
        if(!LocateElem(P,t,&q))
            {
                t->next=q->next;
                q->next=t;
            }
 
        t=(LinkList)malloc(sizeof(term));
        t->next=NULL;
        scanf("%f,%d",&t->coef,&t->expn);
    }
}
 
 
 
void printPolyn(polynomial P)//�������ʽ 
{
    LinkList q;
    q=P->next;
 
    if(!q)
    {
        printf("0\n");
    }
 
    while(q)
    {
        if(q->coef==0)
        {
            printf("");
            q=q->next;
 
        }
 
        if(q->expn==0)
        {
            printf("%.2f",q->coef);
            q=q->next;
        }
        else if(q->expn>0)
        {
            printf("%.2f*x^%d",q->coef,q->expn);
            q=q->next;
        }
        else 
        {
            printf("%.2f*x^(%d)",q->coef,q->expn);
            q=q->next;
        }
 
 
 
        if(q)
        {
            if(q->coef>0)
                printf("+");
            else
                printf("");
        }
        else
            printf("\n");
    }
    printf("\n");
}

void SubPolyn(polynomial Pa,polynomial Pb,polynomial Pc)//����ʽ��� 
{
    LinkList qa=Pa->next;
    LinkList qb=Pb->next;
    LinkList qc=Pc;
    LinkList head=qc;
    LinkList s;
    float differ;
 
    Pc->coef=0.0;
    Pc->expn=-1;
    Pc->next=NULL;
 
    while(qb)
    {
        qb->coef=0-(qb->coef);
        qb=qb->next;
    }
 
    qb=Pb->next;
 
    while(qa&&qb)
    {
        switch(cmp(qa,qb))
        {
            case -1:
                s=(LinkList)malloc(sizeof(term));
                *s=*qa;
                qc->next=s;
                qc=s;
                qa=qa->next;
                break;
            case 0:
                differ=qa->coef+qb->coef;
                if(differ!=0.0)
                {
                    s=(LinkList)malloc(sizeof(term));
                    *s=*qa;
                    s->coef=differ;
                    qc->next=s;
                    qc=s;
                    qa=qa->next;
                    qb=qb->next;
                }
                else
                {
                    qc->next=qa->next;
                    qa=qa->next;
                    qb=qb->next;
 
                }
                break;
            case 1:
                s=(LinkList)malloc(sizeof(term));
                *s=*qb;
                qc->next=s;
                qc=s;
                qb=qb->next;
                break;
        }
    }
    qc->next=qa?qa:qb;
    Pc=head;
}
 
int main()
{
    polynomial Pa;
    polynomial Pb;
    polynomial Pc;

    Pa=(LinkList)malloc(sizeof(term));
    Pb=(LinkList)malloc(sizeof(term));
    Pc=(LinkList)malloc(sizeof(term));
 

 
    printf("���������ʽ��ϵ����ָ��������һ������ʽ���������£�\n����ʽa=2x^2+x�������������һ����ϵ��Ϊ2��ָ��Ϊ2���ڶ���ϵ��Ϊ1��ָ��Ϊ1\n�������2,2�س���1,1�س�����0,0Ϊ�������\n2,2\n1,1\n0,0\n\n");
    CreatePolyn(Pa);
    printf("    F(a) = ");
    printPolyn(Pa);
    CreatePolyn(Pb);
    printf("    F(b) = ");
    printPolyn(Pb);
    printf("��������ʽ���\n"); 
    printf("    F(a)-F(b) = ");
    SubPolyn(Pa,Pb,Pc);
    printPolyn(Pc);
 
    return 0;
}
