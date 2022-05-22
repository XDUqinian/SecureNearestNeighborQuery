#include <cstdio>
#include <algorithm>
#include<fstream>
#include<iostream>
using namespace std;
#define MAXD 2      //空间维度
#define MAXN 123594
#define EPS 0.5     //判断重点的阈值
struct KD_P     //空间点结构
{
    int x[MAXD];    //坐标
    int id;     //初始编号
    bool operator < (const KD_P& b)
    {
        int i;
        for (i = 0; i < MAXD; i++)
            if (x[i] != b.x[i])
                return x[i] < b.x[i];
        return false;
    }
};
KD_P point[MAXN];   //原始点
KD_P node[MAXN];    //KD树划分用排序节点
KD_P point_1[MAXN];
int split_now;      //当前排序的维度
bool KD_cmp(const KD_P a, const KD_P b)
{
    return a.x[split_now] < b.x[split_now];
}
void KD_build(int l, int r, int d)
{
    if (l >= r)
        return;
    int mid = l + r >> 1, dem, i;
    split_now = d & 1;
    nth_element(node + l, node + mid, node + r + 1, KD_cmp);    //粗略排序找中位数,放好第mid大的点
    KD_build(l, mid - 1, d + 1);
    KD_build(mid + 1, r, d + 1);
}

KD_P dest;  //要询问最近点的点,本题中是KD中的点,所以要用eps判断是否是同一个点
long long ans;  //当前查询的最近距离
int ansid;  //最近点编号

long long get_dis(int* a, int* b)   //得到距离的平方
{
    int i;
    long long dis = 0;
    for (i = 0; i < MAXD; i++)
        dis += (long long)(a[i] - b[i]) * (long long)(a[i] - b[i]);
    return dis;
}

void KD_query(int l, int r, int d)
{
    if (l > r)
        return;
    int mid = l + r >> 1;
    long long dis = get_dis(point_1[node[mid].id].x, dest.x);   //询问点到当前根的距离方
    if (dis && (dis < ans || dis == ans && node[mid] < point[ansid]))
    {
        ans = dis;
        ansid = node[mid].id;
    }
    split_now = d & 1;
    long long radius = (long long)(dest.x[split_now] - node[mid].x[split_now])*(dest.x[split_now] - node[mid].x[split_now]);    //询问点到分裂面的距离方
    if (dest.x[split_now] < node[mid].x[split_now])
    {
        KD_query(l, mid - 1, d + 1);
        if (radius <= ans)
            KD_query(mid + 1, r, d + 1);
    }
    else
    {
        KD_query(mid + 1, r, d + 1);
        if (radius <= ans)
            KD_query(l, mid - 1, d + 1);
    }
}

int main()
{
    int n=123593;
	ifstream myfile("NE_encrypto.txt");
    ifstream myans("NE.txt");
	if (!myfile.is_open())
	{
		cout << "can not open this file" << endl;
		return 0;
	}
	if (!myans.is_open())
	{
		cout << "can not open this file1" << endl;
		return 0;
	}
	for(int i=1;i<=123593;i++)
	{
		myfile>>point[i].x[0]>>point[i].x[1];
		point[i].id = i;
        node[i] = point[i];
        float xx,yy;
        myans>>xx>>yy;
        point_1[i].id=i;
        point_1[i].x[0]=(int)(xx*1000000);
        point_1[i].x[1]=(int)(yy*1000000);
	}
	KD_build(1, n, 0);
	KD_P pt;
	float xx,yy;
	cout<<"输入待查询的x y坐标："<<endl; 
	cin>>xx>>yy;
	pt.x[0]=xx*1000000;
	pt.x[1]=yy*1000000;
	dest=pt;
    ans = (long long)1 << 62;
    KD_query(1, n, 0);
    cout<<"最近邻:"<<endl;
    cout<<(0.000001*point[ansid].x[0])<<" "<<(0.000001*point[ansid].x[1])<<" "<<ans<<endl;
    return 0;
}
