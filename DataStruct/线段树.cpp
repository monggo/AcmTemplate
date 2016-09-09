// 线段树中的几个函数的参数比较多，为了方便常定义几个宏方便编写
#define lrt rt<<1       // 左儿子
#define rrt rt<<1|1     // 右儿子
#define lson l,m,lrt    // 左节点
#define rson m+1,r,rrt  // 右节点

// push_up函数用来维护rt的两个子节点到rt的信息
void push_up(int rt) // 父节点
{
    sum[rt]=sum[lrt]+sum[rrt]; // 维护和
    mx[rt]=max(mx[lrt],mx[rrt]); // 维护最大值
    mi[rt]=min(mi[lrt],mi[rrt]); // 维护最小值
}

// build函数是用来建造树的:
void build(l,r,rt) // 范围,节点编号
{
    if(l==r) // l==r时初始化节点
    {
        //初始化
        return ;
    }
    int m=(l+r)/2;
    build(lson); build(rson); // 递归子节点
    push_up(rt); // 统计并维护子节点的信息
}

// push_down函数用来进行lazy的操作,如果节点上有lazy的标记
就把lazy的标记传递下去,并更新对子节点的影响
void push_down(int l,int r,int rt)
{
    if(add[rt]) // rt上有一个add标记
    {
        add[lrt]=add[rrt]=add[rt]; // 标记先传递下去
        int m=(l+r)/2; // 标记对儿子节点的影响
        sum[lrt]+=(m-l+1)*add[rt];
        sum[rrt]+=(r-m)*add[rt];
        add[rt]=0; // 清除掉标记
    }
    if(set[rt]) // 有一个set标记
    {
        set[lrt]=set[rrt]=set[rt]; // 传递标记
        num[rrt]=num[lrt]=set[rt]; // 标记的影响
        set[rt]=0; // 清除标记
    }
}

// update 用来更新线段树
/*
参数: update(L,R,V,l,r,rt)
要更新L~R这一段的值为V, 目前在节点rt[l,r]
递归的时候前三个值不用变,变后面的就可以了.
每当要递归一个节点,一定要先把标记push_down下去,更新完了要记得push_up维护好信息
*/
void update(L,R,V,l,r,rt)
{
    if(L<=l&&r<=R)
    {
        // set V and lazy mark
        return ;
    }
    // 放下标记
    push_down(l,r,rt)
    int m=(l+r)/2;
    if(L<=m) update(L,R,V,lson);
    if(R>m) update(L,R,V,rson);
    // 维护新的信息
    push_up(rt);
}

// query 查询用的函数
int query(int L,int R,int l,int r,int rt)
{
    if(L<=l && r<=R)
    {
        //返回这节点的信息
        return xxxx;
    }
    // 放下标记
    push_down(l,r,rt);
    int m=(l+r)/2;
    // 递归查询
    if(R <= m) return query(L,R,lson);
    else if(L > m) return query(L,R,rson);
    else return query(L, m, lson) + query(m+1, R, rson);
}
