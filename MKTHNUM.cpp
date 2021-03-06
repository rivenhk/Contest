#include <iostream>
#include <map>

using namespace std;

struct T {
	int l, r, w;
};

typedef map<int, int> MI;

int root[100005];
T t[2000005];
int a[100005];
int n, m;

MI mp;
MI rmp;

int tn = 0;

void build(int i, int l, int r) {
	t[i].w = 0;
	
	if(l == r) return;
	
	int mid = (l + r) >> 1;
	
	t[i].l = ++tn;
	t[i].r = ++tn;
	build(t[i].l, l, mid);
	build(t[i].r, mid + 1, r);
}

void clone(int i) {
	t[++tn] = t[root[i - 1]];
	root[i] = tn;
}

void insert(int v, int i, int ip, int l, int r) {
	if(l == r) {
		t[i].w += 1;
		return;
	}
	
	int mid = (l + r) >> 1;
	t[i] = t[ip];
	if(v <= mid) t[i].l = ++tn, insert(v,t[i].l, t[ip].l, l, mid);
	else t[i].r = ++tn, insert(v, t[i].r, t[ip].r, mid + 1, r);
	
	t[i].w = t[t[i].l].w + t[t[i].r].w;
}

int query(int c1, int c2, int l, int r, int k) {
	if(l == r) return l;
	
	int f = t[t[c2].l].w - t[t[c1].l].w;
	int mid = (l + r) >> 1;
	if(k <= f) return query(t[c1].l, t[c2].l, l, mid, k);
	else return query(t[c1].r, t[c2].r, mid + 1, r, k - f);
}

int main() {
	scanf("%d %d", &n, &m);
	
	for(int i = 0; i < n; ++i) scanf("%d", a + i), mp[a[i]] = 0;
	
	int cnt = 0;
	for(auto& it: mp) ++cnt, mp[it.first] = cnt, rmp[cnt] = it.first;
	
	build(0, 1, n);
	
	for(int i = 1; i <= n; ++i) {
		clone(i);
		insert(mp[a[i - 1]], root[i], root[i - 1], 1, n);
	}
	
	for(int i = 0; i < m; ++i) {
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		
		printf("%d\n", rmp[query(root[l - 1], root[r], 1, n, k)]);
	}

	return 0;
}
