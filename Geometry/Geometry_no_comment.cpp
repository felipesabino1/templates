/*
    Alteracoes:
    
    Se for usar inteiro nas contas, muda a funca eq e o TT
*/
using dd = long double;
const dd pi = acosl(-1.0);
const dd eps = 1e-9;
const dd inf = 1e10;
#define rad(x) ((x)*pi/180)
#define sq(x) ((x)*(x))
namespace geo{
    using TT = long double;

    bool eq(TT x, TT y){
        return fabs(x-y) <= eps;
    }
    inline int signal(TT x){return (((x)>eps) - ((x)<eps));}
    
    // pode representar um ponto, vetor ou numero complexo
    struct Point{
        TT x,y;    
        Point(TT x_ = 0, TT y_ = 0) : x(x_), y(y_){}
        bool operator < (const Point & ot) const {
            if(!eq(x,ot.x)) return x < ot.x; // ordena por x primeiro 
            if(!eq(y,ot.y)) return y < ot.y; // depois ordena por y
            return false;
        }
        bool operator == (const Point & ot) const {
            return eq(x, ot.x) && eq(y, ot.y);
        }
        void operator +=(const Point &ot){
            x += ot.x;
            y += ot.y;
        }
        void operator -=(const Point &ot){
            x -= ot.x;
            y -= ot.y;
        }
        void operator *=(TT r){
            x *= r;
            y *= r;
        }
        void operator /=(TT r){
            x /= r;
            y /= r;
        }
        // operacoes de vetores/complexos
        TT abs2()const{return sq(x) + sq(y);} 
        dd abs()const{return sqrtl(abs2());} 
        Point unit()const{return (*this)/abs();} 
        dd arg()const{
            dd ang = atan2(y,x);
            return (ang < 0 ? ang + 2*pi : ang);
        }
        Point perp()const{return Point(-y,x);}
        // operacoes de complexos (x,y) -> x + y*i
        Point conj()const{return Point(x,-y);} 
    };
    Point operator-(const Point &at){return Point(-at.x,-at.y);}
    Point operator +(const Point &p1,const Point &p2){
        return Point(p1.x + p2.x, p1.y + p2.y);
    }
    Point operator -(const Point &p1, const Point &p2){
        return Point(p1.x - p2.x, p1.y - p2.y);
    }
    Point operator *(const Point &at, TT r){
        return Point(at.x * r, at.y * r);
    }
    Point operator*(TT r, const Point& at){
        return Point(at.x * r, at.y * r);
    }
    Point operator /(const Point &at, TT r){
        return Point(at.x / r, at.y / r);
    }
    Point dir(TT ang){return Point(cosl(ang), sinl(ang));} 
    // operacoes de complexo
    Point operator*(const Point &p1, const Point &p2) {return Point(p1.x*p2.x - p1.y*p2.y, p1.y*p2.x + p1.x*p2.y);}
    Point operator/(const Point &p1, const Point &p2) {return p1*p2.conj()/p2.abs2();}
    TT dot(const Point &p1, const Point &p2){
        return p1.x*p2.x + p1.y*p2.y;
    }
    TT dot(const Point & origin, const Point &p1, const Point &p2){
        return dot(p1-origin,p2-origin);
    }
    TT cross(const Point &p1, const Point &p2){
        return p1.x*p2.y - p1.y*p2.x;
    }
    TT cross(const Point &origin, const Point &p1, const Point&p2){
        return cross(p1-origin,p2-origin);
    }
    Point rotate90(const Point &center, const Point &p){
        Point rotated = p - center;
        swap(rotated.x,rotated.y);
        rotated.x = -rotated.x;
        rotated += center;
        return rotated;
    }
    Point rotate(const Point &center, const Point &p, dd ang){
        Point rotated = p - center;
        rotated = Point(rotated.x*cos(ang) - rotated.y*sin(ang), rotated.y*cos(ang) + rotated.x*sin(ang));
        rotated += center;
        return rotated;
    }
    dd dist(const Point &p1, const Point &p2){
        return (p1-p2).abs();
    }
    TT dist2(const Point &p1, const Point &p2){
        return (p1-p2).abs2();
    }
    dd det_area(const Point &p1, const Point &p2, const Point &p3){
        return cross(p2-p1,p3-p2)/TT(2);
    }
    bool colinear(const Point &p1, const Point &p2, const Point &p3){
        return eq(det_area(p1,p2,p3),0);
    }
    dd angle(const Point &p1, const Point &p2, const Point &p3){
        Point v1 = p1 - p2, v2 = p3 - p2;
        dd ang = acosl(dot(v1,v2)/v1.abs()/v2.abs());
        return (ang < 0 ? ang + 2*pi : ang);
    }
    istream& operator >>(istream& in, Point& p) {
        return in >> p.x >> p.y;
    }
    ostream& operator <<(ostream& out, const Point & p){
        return out << "(" << p.x << "," << p.y << ")";
    }

    // representa uma reta ou segmento, se p == q da merda
    struct Line{
        Point p,q;
        Line(){}
        Line(const Point &p1, const Point &p2) : p(p1.x,p1.y), q(p2.x,p2.y){}
        TT get_y(TT x){
            TT m = (p.y - q.y)/(p.x - q.x);
            TT b = p.y - m*p.x;
            return m*x + b;
        }
        TT get_x(TT y){
            TT m = (p.y - q.y)/(p.x - q.x);
            TT b = p.y - m*p.x;
            return (y-b)/m;
        }
    };
    istream& operator >>(istream& in, Line& l) {
        return in >> l.p >> l.q;
    }
    ostream& operator <<(ostream& out, const Line & l){
        return out << "(" << l.p << ", " << l.q << ")";
    }
    Point reflect(const Point &p, const Line &l){
        Point aux1 = l.p, aux2 = l.q-l.p; // ponto p e vetor p->q
        return aux1 + ((p-aux1)/aux2).conj()*aux2;
    }
    Point proj(const Point &p, const Line &l){
        return (p+reflect(p,l))/TT(2);
    }
    bool onSeg(const Point &p, const Line &l){
        return signal(cross(l.p,l.q,p)) == 0 && signal(dot(p,l.p,l.q)) <= 0;
    }
    bool onLine(const Point &p, const Line &l){
        return signal(cross(l.p,l.q,p)) == 0;
    }
    dd line_dist(const Line &line, const Point &p){
        dd ans = abs(cross(p,line.p,line.q));
        ans /= (line.p-line.q).abs();
        return ans;
    }
    dd seg_dist(const Line &seg, const Point &p){
        if(dot(seg.p, p, seg.q) <= 0) return (p-seg.p).abs();
        if(dot(seg.q, p, seg.p) <= 0) return (p-seg.q).abs();
        return line_dist(seg,p);
    }
}
using namespace geo;
