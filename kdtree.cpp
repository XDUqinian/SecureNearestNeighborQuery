#include <cstdio>
#include <algorithm>
#include<fstream>
#include<iostream>
using namespace std;
#define MAXD 2      //�ռ�ά��
#define MAXN 123594
#define EPS 0.5     //�ж��ص����ֵ
struct KD_P     //�ռ��ṹ
{
    int x[MAXD];    //����
    int id;     //��ʼ���
    bool operator < (const KD_P& b)
    {
        int i;
        for (i = 0; i < MAXD; i++)
            if (x[i] != b.x[i])
                return x[i] < b.x[i];
        return false;
    }
};
KD_P point[MAXN];   //ԭʼ��
KD_P node[MAXN];    //KD������������ڵ�
KD_P point_1[MAXN];
int split_now;      //��ǰ�����ά��
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
    nth_element(node + l, node + mid, node + r + 1, KD_cmp);    //������������λ��,�źõ�mid��ĵ�
    KD_build(l, mid - 1, d + 1);
    KD_build(mid + 1, r, d + 1);
}

KD_P dest;  //Ҫѯ�������ĵ�,��������KD�еĵ�,����Ҫ��eps�ж��Ƿ���ͬһ����
long long ans;  //��ǰ��ѯ���������
int ansid;  //�������

long long get_dis(int* a, int* b)   //�õ������ƽ��
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
    long long dis = get_dis(point_1[node[mid].id].x, dest.x);   //ѯ�ʵ㵽��ǰ���ľ��뷽
    if (dis && (dis < ans || dis == ans && node[mid] < point[ansid]))
    {
        ans = dis;
        ansid = node[mid].id;
    }
    split_now = d & 1;
    long long radius = (long long)(dest.x[split_now] - node[mid].x[split_now])*(dest.x[split_now] - node[mid].x[split_now]);    //ѯ�ʵ㵽������ľ��뷽
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
	cout<<"�������ѯ��x y���꣺"<<endl; 
	cin>>xx>>yy;
	pt.x[0]=xx*1000000;
	pt.x[1]=yy*1000000;
	dest=pt;
    ans = (long long)1 << 62;
    KD_query(1, n, 0);
    cout<<"�����:"<<endl;
    cout<<(0.000001*point[ansid].x[0])<<" "<<(0.000001*point[ansid].x[1])<<" "<<ans<<endl;
    return 0;
}
