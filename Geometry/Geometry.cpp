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
    // friend are non-member functions
    // you use const as a return in member functions
    using TT = dd;

    bool eq(TT x, TT y){
        return x == y; // se for usar inteiro
        // return fabs(x-y) <= eps;
    }
    inline int signal(TT x){return (((x)>eps) - ((x)<eps));}
    
    // pode representar um ponto, vetor ou numero complexo
    struct Point{
        TT x,y;    
        
        // construtor
        Point(TT, TT); // passar as coordenadas
        
        // operadores de pontos/vetores/complexos
        bool operator <(const Point &ot)const; 
        bool operator ==(const Point &ot)const;
        void operator +=(const Point &ot);
        void operator -=(const Point &);
        void operator *=(TT r);
        void operator /=(TT r);
        /*
            void operator -(const Point &at); 
        */

        // operacoes de vetores/complexos
        TT abs2()const; // faz a conta do modulo do vetor (x)^2 + (y)^2 sem a raiz
        dd abs()const; // retorna o modulo/absoluto de um vetor
        Point unit()const; // Retorna o vetor unitario
        dd arg()const; // calcula o argumento de um complexo, angulo em radianos (que nem no ciclo trigonometrico)
        Point perp()const; // retorna um ponto perpendicular
        /*
            Point dir(TT ang); // retorna um ponto no ciclo trigonometrico com angulo x (em radianos)
        */

        // operacoes de complexos (x,y) -> x + y*i
        Point conj()const; // retorna o conjugado do complexo, eh util pra problemas de simetria e calculos como modulo |(x,y)| = sqrt(x^2 + y^2) = sqrt((x,y)*conj())
        /*
            Point operator*(const Point &p1, const Point &p2); // faz o produto de dois complexos, (x1+y1*i)*(x2+y2*i) = (x1*x2 + x1*y2*i + x2*y1*i + y1*y2*i*i) = (x1*x2-y1*y2 + (x1*y2 + x2*y1)*i)
            Point operator/(const Point &p1, const Point &p2); // faz a divisao de dois complexos, multiplica o conjugado do numerador e denominador que ai a divisao vai ser por um real
        */

        // operacoes de vetores
        /*
            TT dot(const Point &p1, const Point &p2); // produto escalar
            TT dot(const Point &origin, const Point &p1,const Point &p2) // produto escalar considerando os vetores origin->p1 e origin->p2
            TT cross(const Point &p1, const Point &p2); // componente Z do produto vetorial (bom pra saber como dois vetores estao orientados)
            TT cross(const Point &origin, const Point &p1, const Point &p2); // componente Z do produto vetorial considerando os vetores origin->p1 e origin->p2
        */

        // transformacoes geometricas de pontos
        /*
            Point rotate90(const Point &center, const Point &p); // rotacao de 90 graus em torno de center
            Point rotate(const Point &center, const Point &p, dd ang); // rotacao de ang graus em torno de center
        */

        // calculos com pontos
        /*
            dd dist(const Point &p1, const Point &p2); // distancia entre dois pontos
            TT dist2(const Point &p1, const Point &p2); // quadrado da distancia entre dois pontos, nao precisa fazer raiz quadrada
            dd det_area(const Point &p1, const Point &p2, const Point &p3); // area calculada entre os 3 pontos usando determinante (retorno sem tirar o modulo)
            bool colinear(const Point &p1, const Point &p2, const Point &p3); // os 3 pontos sao colineares?
            dd angle(const Point &p1, const Point &p2, const Point &p3); // calcula o angulo do angulo no p2, considerando o triangulo (p1,p2,p3)
        */

        // I/O
        /*
            istream& operator >>(istream &in, Point &p);
            ostream& operator <<(ostream &out, const Point &p);
        */
    };
    // --------------CODIGO--------------
        Point::Point(TT x_ = 0,TT y_ = 0) : x(x_), y(y_){}
        bool Point::operator < (const Point & ot) const {
            if(!eq(x,ot.x)) return x < ot.x; // ordena por x primeiro 
            if(!eq(y,ot.y)) return y < ot.y; // depois ordena por y
            return false;
        }
        bool Point::operator == (const Point & ot) const {
            return eq(x, ot.x) && eq(y, ot.y);
        }
        Point operator-(const Point &at){return Point(-at.x,-at.y);}
        void Point::operator +=(const Point &ot){
            x += ot.x;
            y += ot.y;
        }
        void Point::operator -=(const Point &ot){
            x -= ot.x;
            y -= ot.y;
        }
        void Point::operator *=(TT r){
            x *= r;
            y *= r;
        }
        void Point::operator /=(TT r){
            x /= r;
            y /= r;
        }
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
        TT Point::abs2()const{return sq(x) + sq(y);} 
        dd Point::abs()const{return sqrtl(abs2());} 
        Point Point::unit()const{return (*this)/abs();} 
        dd Point::arg()const{
            dd ang = atan2(y,x);
            return (ang < 0 ? ang + 2*pi : ang);
        }
        Point Point::perp()const{return Point(-y,x);}
        Point dir(TT ang){return Point(cosl(ang), sinl(ang));} 
        Point Point::conj()const{return Point(x,-y);} 
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
    // --------------FIM--------------

    // representa uma reta ou segmento, se p == q da merda
    struct Line{
        Point p,q;

        // construtor
        Line();
        Line(const Point &, const Point &); // passar dois pontos
    
        TT get_y(TT x); // retorna o y pra essa funcao de reta
        TT get_x(TT y); // retorna o x pra essa funcao de reta

        // I/O
        /*
            istream& operator >>(istream& in, Line& l);
            ostream& operator <<(ostream& out, const Line & l);
        */
    };
    // --------------CODIGO--------------
        Line::Line(){}
        Line::Line(const Point &p1, const Point &p2) : p(p1.x,p1.y), q(p2.x,p2.y){}
        TT Line::get_y(TT x){
            // seja m = (p.y - q.y)/(p.x - q.x)
            // y = m*x + b
            // p.y = m*p.x + b -> b = p.y - m*p.x
            TT m = (p.y - q.y)/(p.x - q.x);
            TT b = p.y - m*p.x;
            return m*x + b;
        }
        TT Line::get_x(TT y){
            // seja m = (p.y - q.y)/(p.x - q.x)
            // y = m*x + b
            // p.y = m*p.x + b -> b = p.y - m*p.x
            TT m = (p.y - q.y)/(p.x - q.x);
            TT b = p.y - m*p.x;
            // y = m*x + b -> y-b = m*x -> (y-b)/m = x
            return (y-b)/m;
        }
        istream& operator >>(istream& in, Line& l) {
            return in >> l.p >> l.q;
        }
        ostream& operator <<(ostream& out, const Line & l){
            return out << "(" << l.p << ", " << l.q << ")";
        }
    // --------------FIM--------------

    // operacoes entre pontos e retas
    // --------------HEADER--------------
        Point reflect(const Point &p, const Line &l); // reflexao do ponto em torno da reta
        Point reflect(const Line &l, const Point &p); // reflexao do ponto em torno da reta
        Point proj(const Point &p, const Line &l); // projecao do ponto na reta
        Point proj(const Line &l, const Point &p); // projecao do ponto na reta
        bool onSeg(const Point &p, const Line &l); // verifica se o ponto esta no segmento
        bool onSeg(const Line &l, const Point &p); // verifica se o ponto esta no segmento
        bool onLine(const Point &p, const Line &l); // verifica se o ponto esta na reta
        bool onLine(const Line &l, const Point &p); // verifica se o ponto esta na reta
        dd line_dist(const Line &line, const Point &p); // distancia entre um ponto e reta
        dd line_dist(const Point &p, const Line &line); // distancia entre um ponto e reta
        dd seg_dist(const Line &seg, const Point &p); // distancia entre um ponto e um segmento
        dd seg_dist(const Point &p, const Line &seg); // distancia entre um ponto e um segmento
        // a distancia entre dois segmentos, vai ser a distancia de um dos pontos das extremidades pra outro segmento 
    // --------------FIM--------------

    // --------------CODIGO--------------
        Point reflect(const Point &p, const Line &l){
            Point aux1 = l.p, aux2 = l.q-l.p; // ponto p e vetor p->q
            return aux1 + ((p-aux1)/aux2).conj()*aux2;
        }
        Point reflect(const Line &l, const Point &p){
            return reflect(p,l);
        }
        Point proj(const Point &p, const Line &l){
            return (p+reflect(p,l))/TT(2);
        }
        Point proj(const Line &l, const Point &p){
            return proj(p,l);
        }
        bool onSeg(const Point &p, const Line &l){
            // verifica se o deslocamento do vetor l.p->p pro l.p->q eh zero, ou seja, losango nulo, mesma direcao
            // verifica se p esta entre l.p e l.q
            return signal(cross(l.p,l.q,p)) == 0 && signal(dot(p,l.p,l.q)) <= 0;
        }
        bool onSeg(const Line &l, const Point &p){
            return onSeg(p,l);
        }
        bool onLine(const Point &p, const Line &l){
            return signal(cross(l.p,l.q,p)) == 0;
        }
        bool onLine(const Line &l, const Point &p){
            return onLine(p,l);
        }
        dd line_dist(const Line &line, const Point &p){
            dd ans = abs(cross(p,line.p,line.q));
            ans /= (line.p-line.q).abs();
            return ans;
        }
        dd line_dist(const Point &p, const Line &line){
            return line_dist(line,p);
        }
        dd seg_dist(const Line &seg, const Point &p){
            if(dot(seg.p, p, seg.q) <= 0) return (p-seg.p).abs();
            if(dot(seg.q, p, seg.p) <= 0) return (p-seg.q).abs();
            return line_dist(seg,p);
        }
        dd seg_dist(const Point &p, const Line &seg){
            return seg_dist(seg,p);
        }
    // --------------FIM--------------
}
using namespace geo;
