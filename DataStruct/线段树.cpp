// �߶����еļ��������Ĳ����Ƚ϶࣬Ϊ�˷��㳣���弸���귽���д
#define lrt rt<<1       // �����
#define rrt rt<<1|1     // �Ҷ���
#define lson l,m,lrt    // ��ڵ�
#define rson m+1,r,rrt  // �ҽڵ�

// push_up��������ά��rt�������ӽڵ㵽rt����Ϣ
void push_up(int rt) // ���ڵ�
{
    sum[rt]=sum[lrt]+sum[rrt]; // ά����
    mx[rt]=max(mx[lrt],mx[rrt]); // ά�����ֵ
    mi[rt]=min(mi[lrt],mi[rrt]); // ά����Сֵ
}

// build������������������:
void build(l,r,rt) // ��Χ,�ڵ���
{
    if(l==r) // l==rʱ��ʼ���ڵ�
    {
        //��ʼ��
        return ;
    }
    int m=(l+r)/2;
    build(lson); build(rson); // �ݹ��ӽڵ�
    push_up(rt); // ͳ�Ʋ�ά���ӽڵ����Ϣ
}

// push_down������������lazy�Ĳ���,����ڵ�����lazy�ı��
�Ͱ�lazy�ı�Ǵ�����ȥ,�����¶��ӽڵ��Ӱ��
void push_down(int l,int r,int rt)
{
    if(add[rt]) // rt����һ��add���
    {
        add[lrt]=add[rrt]=add[rt]; // ����ȴ�����ȥ
        int m=(l+r)/2; // ��ǶԶ��ӽڵ��Ӱ��
        sum[lrt]+=(m-l+1)*add[rt];
        sum[rrt]+=(r-m)*add[rt];
        add[rt]=0; // ��������
    }
    if(set[rt]) // ��һ��set���
    {
        set[lrt]=set[rrt]=set[rt]; // ���ݱ��
        num[rrt]=num[lrt]=set[rt]; // ��ǵ�Ӱ��
        set[rt]=0; // ������
    }
}

// update ���������߶���
/*
����: update(L,R,V,l,r,rt)
Ҫ����L~R��һ�ε�ֵΪV, Ŀǰ�ڽڵ�rt[l,r]
�ݹ��ʱ��ǰ����ֵ���ñ�,�����ľͿ�����.
ÿ��Ҫ�ݹ�һ���ڵ�,һ��Ҫ�Ȱѱ��push_down��ȥ,��������Ҫ�ǵ�push_upά������Ϣ
*/
void update(L,R,V,l,r,rt)
{
    if(L<=l&&r<=R)
    {
        // set V and lazy mark
        return ;
    }
    // ���±��
    push_down(l,r,rt)
    int m=(l+r)/2;
    if(L<=m) update(L,R,V,lson);
    if(R>m) update(L,R,V,rson);
    // ά���µ���Ϣ
    push_up(rt);
}

// query ��ѯ�õĺ���
int query(int L,int R,int l,int r,int rt)
{
    if(L<=l && r<=R)
    {
        //������ڵ����Ϣ
        return xxxx;
    }
    // ���±��
    push_down(l,r,rt);
    int m=(l+r)/2;
    // �ݹ��ѯ
    if(R <= m) return query(L,R,lson);
    else if(L > m) return query(L,R,rson);
    else return query(L, m, lson) + query(m+1, R, rson);
}
