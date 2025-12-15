#include <iostream>
#include <cmath>
using namespace std;

template <class T> class Polynomial;
template <class T>
class Node {
    friend class Polynomial<T>;
public:
    int exp;
    T coef;
    Node<T>* link;
    Node(T c = 0, int e = 0, Node<T>* p = nullptr)
        : coef(c), exp(e), link(p) {}
};

////////////////////////////////////////////////////////////////

template <class T>
class Polynomial {
private:
    Node<T>* head;

public:
    Polynomial();
    Polynomial(const Polynomial<T>& a);
    Polynomial<T>& operator=(const Polynomial<T>& a);
    Polynomial<T> operator+(const Polynomial<T>& b) const;
    Polynomial<T> operator-(const Polynomial<T>& b) const;
    Polynomial<T> operator*(const Polynomial<T>& b) const;
    Polynomial<T> operator/(const Polynomial<T>& b) const;
    Polynomial<T> R(const Polynomial<T>& b) const;
    void Newnode(T coef, int exp);
    void del();
    ~Polynomial();

    friend istream& operator>>(istream& in, Polynomial<T>& x) {
        int n;
        in >> n;
        for (int i = 0; i < n; i++) {
            T coef;
            int exp;
            in >> coef >> exp;
            x.Newnode(coef, exp);
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Polynomial<T>& x) {
        Node<T>* p = x.head->link;
        bool first = true;

        while (p != x.head) {
            T c = p->coef;
            int e = p->exp;
            if (!first) {
                if (c > 0) out << " + ";
                else       out << " - ";
            }
            else {
                if (c < 0) out << "-";
            }

            T absCoef = (c < 0) ? -c : c;
            if (e == 0) {
                out << absCoef;
            }
            else {
                if (absCoef != 1)
                    out << absCoef;

                out << "x";

                if (e != 1)
                    out << "^" << e;
            }

            first = false;
            p = p->link;
        }
        if (first)
            out << "0";

        return out;
    }
};

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T>::Polynomial() {
    head = new Node<T>();
    head->link = head;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T>::Polynomial(const Polynomial<T>& a) {
    head = new Node<T>();
    head->link = head;
    Node<T>* p = a.head->link;
    while (p != a.head) {
        Newnode(p->coef, p->exp);
        p = p->link;
    }
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& a) {
    if (this == &a) return *this;
    del();
    Node<T>* p = a.head->link;
    while (p != a.head) {
        Newnode(p->coef, p->exp);
        p = p->link;
    }
    return *this;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T>::~Polynomial() {
    del();
    delete head;
}

////////////////////////////////////////////////////////////////
template <class T>
void Polynomial<T>::del() {
    Node<T>* p = head->link;
    while (p != head) {
        Node<T>* t = p;
        p = p->link;
        delete t;
    }
    head->link = head;
}

////////////////////////////////////////////////////////////////
template <class T>
void Polynomial<T>::Newnode(T coef, int exp) {
    if (coef == 0) return;

    Node<T>* p = head;
    Node<T>* q = head->link;

    while (q != head && q->exp > exp) {
        p = q;
        q = q->link;
    }

    if (q != head && q->exp == exp) {
        q->coef += coef;
        if (q->coef == 0) {
            p->link = q->link;
            delete q;
        }
        return;
    }

    p->link = new Node<T>(coef, exp, q);
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& b) const {
    Polynomial<T> c;
    Node<T>* p = head->link;
    Node<T>* q = b.head->link;

    while (p != head && q != b.head) {
        if (p->exp == q->exp) {
            c.Newnode(p->coef + q->coef, p->exp);
            p = p->link;
            q = q->link;
        }
        else if (p->exp > q->exp) {
            c.Newnode(p->coef, p->exp);
            p = p->link;
        }
        else {
            c.Newnode(q->coef, q->exp);
            q = q->link;
        }
    }

    while (p != head) {
        c.Newnode(p->coef, p->exp);
        p = p->link;
    }
    while (q != b.head) {
        c.Newnode(q->coef, q->exp);
        q = q->link;
    }

    return c;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& b) const {
    Polynomial<T> c;
    Node<T>* p = head->link;
    Node<T>* q = b.head->link;

    while (p != head && q != b.head) {
        if (p->exp == q->exp) {
            c.Newnode(p->coef - q->coef, p->exp);
            p = p->link;
            q = q->link;
        }
        else if (p->exp > q->exp) {
            c.Newnode(p->coef, p->exp);
            p = p->link;
        }
        else {
            c.Newnode(-q->coef, q->exp);
            q = q->link;
        }
    }

    while (p != head) {
        c.Newnode(p->coef, p->exp);
        p = p->link;
    }
    while (q != b.head) {
        c.Newnode(-q->coef, q->exp);
        q = q->link;
    }

    return c;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T>& b) const {
    Polynomial<T> c;
    for (Node<T>* p = head->link; p != head; p = p->link) {
        for (Node<T>* q = b.head->link; q != b.head; q = q->link) {
            c.Newnode(p->coef * q->coef, p->exp + q->exp);
        }
    }
    return c;
}
////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::operator/(const Polynomial<T>& b) const {
    Polynomial<T> D, S(*this);

    if (b.head->link == b.head) {
        return D;
    }

    Node<T>* bLead = b.head->link;

    while (S.head->link != S.head &&
        S.head->link->exp >= bLead->exp) {

        T coef = S.head->link->coef / bLead->coef;
        int exp = S.head->link->exp - bLead->exp;

        Polynomial<T> term;
        term.Newnode(coef, exp);

        D = D + term;
        S = S - (term * b);
    }

    return D;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::R(const Polynomial<T>& b) const {
    Polynomial<T> S(*this);

    if (b.head->link == b.head)
        return S;

    Node<T>* bLead = b.head->link;

    while (S.head->link != S.head &&
        S.head->link->exp >= bLead->exp) {

        T coef = S.head->link->coef / bLead->coef;
        int exp = S.head->link->exp - bLead->exp;

        Polynomial<T> term;
        term.Newnode(coef, exp);

        S = S - (term * b);
    }

    return S;
}

////////////////////////////////////////////////////////////////
int main() {
    Polynomial<int> A, B;

    cin >> A;
    cin >> B;

    cout << "A: " << A << endl;
    cout << "B: " << B << endl;

    cout << "A + B: " << (A + B) << endl;
    cout << "A - B: " << (A - B) << endl;
    cout << "A * B: " << (A * B) << endl;
    Polynomial<int> D = A / B;
    Polynomial<int> S = A.R(B);

    cout << "A / B = " << D << endl;
    cout << "A % B = " << S << endl;

    cout << "41343124.洋芋";//此乃防委標記

    return 0;
}