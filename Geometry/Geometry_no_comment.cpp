using dd = double;
const dd pi = acosl(-1.0);
const dd eps = 1e-9;
const dd DINF = 1e18;
#define rad(x) ((x)*pi/180)
#define sq(x) ((x)*(x))
namespace geo{
    using T = dd;

    bool eq(const T x,const T y){
        return fabs(x-y) < eps;
        // return x == y;
    }
    int sgn(T x){return (dd(x)>eps) - (dd(x)<-eps);}
    
    // pode representar um ponto, vetor ou numero complexo
    struct pt{
        T x,y;
        pt(T x_=0, T y_=0) : x(x_),y(y_){}
        bool operator<(const pt &ot)const{
            if(!eq(x,ot.x)) return x < ot.x; // ordena por x primeiro
            if(!eq(y,ot.y)) return y < ot.y;
            return false;
        }
        bool operator==(const pt &ot)const{return eq(x,ot.x) && eq(y,ot.y);}
        bool operator!=(const pt &ot)const{return !eq(x,ot.x) || !eq(y,ot.y);}
        pt operator-(){return pt(-x,-y);}
    };
    const pt pt_off(DINF,DINF);
    ostream& operator<<(ostream& out, const pt p){
        return out << "(" << p.x << "," << p.y << ")";
    }

    // representa uma reta ou segmento
    struct line{
        pt p,q;
        line(pt p_={0,0},pt q_={0,0}) : p(p_),q(q_){}
        T get_y(T x){
            T m = (p.y - q.y)/(p.x - q.x);
            T b = p.y - m*p.x;
            return m*x+b;
        }
        T get_x(T y){
            T m = (p.y - q.y)/(p.x - q.x);
            T b = p.y - m*p.x;
            return (y-b)/m;
        }
    };
    ostream& operator<<(ostream& out, const line l){
        return out << "(" << l.p << ", " << l.q << ")";
    }

    pt& operator+=(pt& a, pt b){a.x+=b.x;a.y+=b.y; return a;}
    pt& operator-=(pt& a, pt b){a.x-=b.x;a.y-=b.y; return a;}
    pt& operator*=(pt& a, T r){a.x*=r;a.y*=r; return a;}
    pt& operator/=(pt& a, T r){a.x/=r;a.y/=r; return a;}
    pt operator+(pt a,pt b){return a+=b;}
    pt operator-(pt a,pt b){return a-=b;}
    pt operator*(pt a, T r){return a*=r;}
    pt operator/(pt a, T r){return a/=r;}
    // operacoes de vetores/complexos
    T abs2(pt p){return sq(p.x) + sq(p.y);}
    dd abs(pt p){return sqrtl(dd(abs2(p)));}
    pt unit(pt p){return p/abs(p);}
    dd arg(pt p){
        dd ang = atan2(dd(p.y),dd(p.x));
        return (ang < 0 ? ang + 2*pi : ang);
    }
    pt conj(pt p){return pt(p.x,-p.y);}
    pt perp(pt p){return pt(-p.y,p.x);}
    pt dir(dd ang){return pt(cosl(ang),sinl(ang));}
    
    // operacoes de complexos
    pt operator*(pt a, pt b){return pt(a.x*b.x-a.y*b.y,a.y*b.x+a.x*b.y);}
    pt operator/(pt a, pt b){return a*conj(b)/abs2(b);}
    
    T dot(pt p1, pt p2){
        return p1.x*p2.x+p1.y*p2.y;
    }
    T dot(pt p1, pt p2, pt p3){
        return dot(p2-p1,p3-p1);
    }
    T cross(pt p1, pt p2){
        return p1.x*p2.y-p1.y*p2.x;
    }
    T cross(pt p1, pt p2, pt p3){
        return cross(p2-p1,p3-p1);
    }
    T det(pt p1, pt p2, pt p3){return cross(p2-p1,p3-p2);}
    bool colinear(pt p1,pt p2,pt p3){return eq(det(p1,p2,p3),0);}
    bool ccw(pt p1, pt p2, pt p3){return det(p1,p2,p3) > eps;}
    
    pt reflect(const pt p, const line l){
        pt a = l.p, d = l.q-l.p;
        return a+conj((p-a)/d)*d;
    }
    pt proj(const pt p, const line l){
        return (p+reflect(p,l))/(T)2;
    }
    pt rotate90(pt a, pt c = pt(0,0)){
        a -= c;
        swap(a.x,a.y);
        a.x = -a.x;
        a += c;
        return a;
    }
    pt rotate(pt a, dd d, pt c = pt(0,0)){
        a -= c;
        pt b;
        b.x = a.x*cosl(d) - a.y*sinl(d);
        b.y = a.y*cosl(d) + a.x*sinl(d);
        b += c;
        return b;
    }

    bool onseg(pt p, line l){
        return sgn(cross(l.p,l.q,p)) == 0 && sgn(dot(p,l.p,l.q)) <= 0;
    }
    bool online(pt p, line l){return sgn(cross(l.p,l.q,p)) == 0;}
    bool interseg(line r, line s) { // se o seg de r intersecta o seg de s
        if (onseg(r.p, s) || onseg(r.q, s) || onseg(s.p, r) || onseg(s.q, r)) return true;
        return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) && ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
    }
    dd dist(pt p1, pt p2){return abs(p2-p1);}
    T dist2(pt p1, pt p2){return abs2(p2-p1);}
    dd ang(pt p1, pt p2, pt p3){
        pt v1 = p1-p2, v2 = p3-p2;
        dd angle = acosl(dd(dot(v1,v2))/abs(v1)/abs(v2));
        return angle + (angle < 0 ? 2*pi : 0);
    }
    dd linedist(const line l, const pt p){ // distancia reta ponto
        return abs(cross(p,l.p,l.q))/abs(l.p-l.q);
    }
    dd segdist(const line seg, const pt p){ // distancia segmento ponto
        if(dot(seg.p, p, seg.q) <= 0) return abs(p-seg.p);
        if(dot(seg.q, p, seg.p) <= 0) return abs(p-seg.q);
        return linedist(seg,p);    
    }
    dd segdist(line a, line b) { // distancia entre seg
        if(interseg(a, b)) return 0;
        dd ret = DINF;
        ret = min(ret, segdist(b, a.p));
        ret = min(ret, segdist(b, a.q));
        ret = min(ret, segdist(a, b.p));
        ret = min(ret, segdist(a, b.q));
        return ret;
    }

    //  Usage: vpt v; sort(all(v),angleCmp);
    // used to sort points int ccw around the origin
    int half(pt p){return !eq(p.y,0) ? sgn(p.y) : -sgn(p.x);}
    bool angleCmp(pt a, pt b){
        int A = half(a), B = half(b);
        return A == B ? cross(a,b) > 0 : A < B;
    }
    // equivalent to: sort(all(v),[](pt a, pt b) { 
    //    return atan2(a.sd,a.ft) < atan2(b.sd,b.ft); });

    using vpt = vector<pt>;
    // degenerate line (one point line) if it exists
    // line == b if input lines are the same
    // line(pt_off,pt_off) if lines do not intersect
    line lineIsect(const line a, const line b){
        T a0 = cross(a.p,a.q,b.p), a1 = cross(a.p,a.q,b.q);
        if(eq(a0,a1)) return eq(a0,0) ? b : line(pt_off,pt_off);
        pt p = (b.q*a0-b.p*a1)/(a0-a1);
        return line(p,p);
    }
    // point in interior of both segments a and b, if it exists
    line strictIsect(const line a, const line b){
        T a0 = cross(a.p,a.q,b.p), a1 = cross(a.p,a.q,b.q);
        T b0 = cross(b.p,b.q,a.p), b1 = cross(b.p,b.q,a.q);
        if(sgn(a0)*sgn(a1) < 0 && sgn(b0)*sgn(b1) < 0) {
            pt p = (b.q*a0-b.p*a1)/(a0-a1); 
            return line(p,p);
        }
        return line(pt_off,pt_off);
    }
    // intersection of segments, a and b may be degenerate (the points that define it are equal)
    // degenerate line (one point line if its only one point)
    // line(pt_off,pt_off) if dont intersect
    // line == a || line == b, if one segment is inside the other
    line segIsect(const line a, const line b){
        line l = strictIsect(a,b); if(l.p != pt_off) return l;
        #define i(x,y) if(onseg(x,y)) {l.q = l.p; l.p = x;}
        i(a.p,b); i(a.q,b); i(b.p,a); i(b.q,a);
        return l;
    }

    // O(log(n))
    bool inconvex(vpt& pol, pt p){
        if (pol.size() == 0) return false;
		if (pol.size() == 1) return p == pol[0];
		int l = 1, r = pol.size();
		while (l < r) {
			int m = (l+r)/2;
			if (ccw(p, pol[0], pol[m])) l = m+1;
			else r = m;
		}
		if (l == 1) return onseg(p, line(pol[0], pol[1]));
		if (l == pol.size()) return false;
		return !ccw(p, pol[l], pol[l-1]);
    }
    // se o ponto ta dentro do poligono: retorna 0 se ta fora,
    // 1 se ta no interior e 2 se ta na borda
    int inpol(vpt &v, pt p) { // O(n)
        int qt = 0;
        for (int i = 0; i < v.size(); i++) {
            if (p == v[i]) return 2;
            int j = (i+1)%v.size();
            if (eq(p.y, v[i].y) and eq(p.y, v[j].y)) {
                if (dot(p,v[i],v[j]) < eps) return 2;
                continue;
            }
            bool baixo = v[i].y+eps < p.y;
            if (baixo == (v[j].y+eps < p.y)) continue;
            auto t = cross(v[i],p,v[j]);
            if (eq(t, 0)) return 2;
            if (baixo == (t > eps)) qt += baixo ? 1 : -1;
        }
        return qt != 0;
    }
    dd polarea(vpt &v){
        ld ret = 0;
        for (int i = 0; i < v.size(); i++)
            ret += det(pt(0, 0), v[i], v[(i + 1) % v.size()])/2;
        return abs(ret);
    }
    bool interpol(vpt &v1, vpt &v2) { // se dois poligonos se intersectam - O(n*m)
        int n = v1.size(), m = v2.size();
        for(int i = 0; i < n; i++) if (inpol(v2, v1[i])) return true;
        for(int i = 0; i < m; i++) if (inpol(v1, v2[i])) return true;
        for(int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            if (interseg(line(v1[i], v1[(i+1)%n]), line(v2[j], v2[(j+1)%m]))) return true;
        return false;
    }
    dd distpol(vpt &v1, vpt &v2) { // distancia entre poligonos
        if (interpol(v1, v2)) return 0;
        dd ret = DINF;
        for (int i = 0; i < v1.size(); i++) for (int j = 0; j < v2.size(); j++)
            ret = min(ret, segdist(line(v1[i], v1[(i + 1) % v1.size()]),
                        line(v2[j], v2[(j + 1) % v2.size()])));
        return ret;
    }
}
using namespace geo;
