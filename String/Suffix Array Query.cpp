// Suffix Array indexado em 0
// suporta query de LCP entre sufixos
// get_lcp(i,j) = LCP entre s[i...n-1] e s[j...n-1]
// sa - Suffix Array, pos - posicao no Suffix Array
// build - O(n)
// get_lcp - O(1)
template<typename T> struct RMQ{
	vector<T> v;
	int n; static const int b = 30;
	vector<int> mask, t;
 
	int op(int x, int y) { return v[x] < v[y] ? x : y; }
	int msb(int x) { return __builtin_clz(1)-__builtin_clz(x); }
	int small(int r, int sz = b) { return r-msb(mask[r]&((1<<sz)-1)); }
	RMQ() {}
	RMQ(const vector<T>& v_) : v(v_), n(v.size()), mask(n), t(n) {
		for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
			at = (at<<1)&((1<<b)-1);
			while (at and op(i, i-msb(at&-at)) == i) at ^= at&-at;
		}
		for (int i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
		for (int j = 1; (1<<j) <= n/b; j++) for (int i = 0; i+(1<<j) <= n/b; i++)
			t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
	}
	T query(int l, int r) {
		if (r-l+1 <= b) return v[small(r, r-l+1)];
		int ans = op(small(l+b-1), small(r));
		int x = l/b+1, y = r/b-1;
		if (x <= y) {
			int j = msb(y-x+1);
			ans = op(ans, op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
		}
		return v[ans];
	}
};
struct SA {
	string s;
	int n;
	vector<int> sa, cnt, pos, lcp;
	RMQ<int> rmq;
	bool cmp(int a1, int b1, int a2, int b2, int a3=0, int b3=0) {
		return a1 != b1 ? a1 < b1 : (a2 != b2 ? a2 < b2 : a3 < b3);
	}
	template<typename T> void radix(int* fr, int* to, T* r, int N, int k) {
		cnt = vector<int>(k+1, 0);
		for (int i = 0; i < N; i++) cnt[r[fr[i]]]++;
		for (int i = 1; i <= k; i++) cnt[i] += cnt[i-1];
		for (int i = N-1; i+1; i--) to[--cnt[r[fr[i]]]] = fr[i];
	}
	void rec(vector<int>& v, int k) {
		auto &tmp = pos, &m0 = lcp;
		int N = v.size()-3, sz = (N+2)/3, sz2 = sz+N/3;
		vector<int> R(sz2+3);
		for (int i = 1, j = 0; j < sz2; i += i%3) R[j++] = i;
 
		radix(&R[0], &tmp[0], &v[0]+2, sz2, k);
		radix(&tmp[0], &R[0], &v[0]+1, sz2, k);
		radix(&R[0], &tmp[0], &v[0]+0, sz2, k);
 
		int dif = 0;
		int l0 = -1, l1 = -1, l2 = -1;
		for (int i = 0; i < sz2; i++) {
			if (v[tmp[i]] != l0 or v[tmp[i]+1] != l1 or v[tmp[i]+2] != l2)
				l0 = v[tmp[i]], l1 = v[tmp[i]+1], l2 = v[tmp[i]+2], dif++;
			if (tmp[i]%3 == 1) R[tmp[i]/3] = dif;
			else R[tmp[i]/3+sz] = dif;
		}
 
		if (dif < sz2) {
			rec(R, dif);
			for (int i = 0; i < sz2; i++) R[sa[i]] = i+1;
		} else for (int i = 0; i < sz2; i++) sa[R[i]-1] = i;
 
		for (int i = 0, j = 0; j < sz2; i++) if (sa[i] < sz) tmp[j++] = 3*sa[i];
		radix(&tmp[0], &m0[0], &v[0], sz, k);
		for (int i = 0; i < sz2; i++)
			sa[i] = sa[i] < sz ? 3*sa[i]+1 : 3*(sa[i]-sz)+2;
 
		int at = sz2+sz-1, p = sz-1, p2 = sz2-1;
		while (p >= 0 and p2 >= 0) {
			if ((sa[p2]%3==1 and cmp(v[m0[p]], v[sa[p2]], R[m0[p]/3],
				R[sa[p2]/3+sz])) or (sa[p2]%3==2 and cmp(v[m0[p]], v[sa[p2]],
				v[m0[p]+1], v[sa[p2]+1], R[m0[p]/3+sz], R[sa[p2]/3+1])))
				sa[at--] = sa[p2--];
			else sa[at--] = m0[p--];
		}
		while (p >= 0) sa[at--] = m0[p--];
		if (N%3==1) for (int i = 0; i < N; i++) sa[i] = sa[i+1];
	}
	SA(string& ss) : s(ss), n(s.size()), sa(n+3), cnt(n+1), pos(n), lcp(n-1) {
		vector<int> v(n+3);
		for (int i = 0; i < n; i++) v[i] = i;
		radix(&v[0], &pos[0], &s[0], n, 256);
		int dif = 1;
		for (int i = 0; i < n; i++)
			v[pos[i]] = dif += (i and s[pos[i]] != s[pos[i-1]]);
		if (n >= 2) rec(v, dif);
		sa.resize(n);
 
		for (int i = 0; i < n; i++) pos[sa[i]] = i;
		for (int i = 0, k = 0; i < n; i++, k -= !!k) {
			if (pos[i] == n-1) {
				k = 0;
				continue;
			}
			int j = sa[pos[i]+1];
			while (i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
			lcp[pos[i]] = k;
		}
		rmq = RMQ<int>(lcp);
	}
	int get_lcp(int i, int j) {
		if(min(i,j) < 0 || max(i,j) >= n) return 0;
        return i == j ? n-i : rmq.query(min(pos[i],pos[j]), max(pos[i],pos[j])-1);
	}
};
