#include <iostream>//���D�ج��B�Φh����(Polynomial)�Ӷi��|���B�⤤���[�k�H�έ��k�C
#include <algorithm>//�o�Ӽ��Y�ɴ��� �j�q�`�Ϊ��t��k�禡�A���b�o���D�ؤ��u�|�Ψ�sort()�ƧǡC
#include <cmath>//�o�Ӽ��Y�ɬO C++ �ƾǨ禡�w�A�]�t�U�ؼƾǹB��禡�A�D�ؤ��Ω�h������ Eval() �禡�A�p�� pow(x, exp)�C
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Term {// Term ���O
    friend class Polynomial;//�NPolynomial�[�J�ͽ����O�N��ϥ�Polynomial���O���p�������e�F
public:
    float coef;//�`�ƶ��ܼ�
    int exp;//���ƶ��ܼ�
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}//����Polynomial���`�ƤΫ���
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Polynomial {// Polynomial ���O
private:
    Term* termArray;//�O���I�O����
    int capacity;//�O���骺�Ŷ��p�O���I
    int terms;//�x�s�D�s���ܼ�

    // �p�G�ݭn�A�X�W�e�q
    void NewArray(int n1) {
        if (n1 <= capacity) return;//�P�_�O����Ŷ��O�_����
        int n2 = capacity;//�����ɱN�{�b���Ŷ��j�p�s�_��
        while (n2 < n1) n2 *= 2;//�å[�⭿���Ŷ��A����2��N���譿�W�[
        Term* n3 = new Term[n2];//�إ߷s���O����Ŷ�
        for (int i = 0; i < terms; ++i) n3[i] = termArray[i];//�ñN�{�b���Ŷ����e�ಾ
        delete[] termArray;//�R���쥻���O����
        termArray = n3;/////////////////////////////////�`�N!! ���ɤw�R���쥻���ж����O����A�ݭn���s�����s���O����Ŷ�
        capacity = n2;//�ǤJ�s���Ŷ��j�p
    }

    void addTerm(const Term& t) {//�PSTerm�j�P�ۦP�����禡�O�M���P�_Term��ƫ��A���ӫD��l��Jcoef��exp�A�Ω� Mult �H�� add
        if (t.coef == 0) return;
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].exp == t.exp) {
                termArray[i].coef += t.coef;
                return;
            }
        }
        NewArray(terms + 1);
        termArray[terms++] = t;
    }

    void Sort() { // �̦���Ѥj��p�ƧǡA�ò����Y�Ƭ� 0 �����A�X�֥i�୫�ƪ�����]²�氵�k�G���ƧǦA�X�֡^
        sort(termArray, termArray + terms, [](const Term& a, const Term& b) {//sort(�_�l��m, ������m, ����禡)�A�o�O�@�� lambda ��F��
            return a.exp > b.exp; // �q������C��
            });
        int c = 0;//�O���I
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].coef == 0) continue;//�G���Y�Ƭ� 0 ����
            if (c > 0 && termArray[c - 1].exp == termArray[i].exp) {//�P�_���ƶ��O�_�ۦP
                termArray[c - 1].coef += termArray[i].coef; // �ۦP���ܦX��
            }
            else {
                termArray[c++] = termArray[i];//���ۦP���ܴN��������c+1
            }
        }
        terms = c;//��s�O���I
        c = 0;//���s�����`�ƫD�s��
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].coef != 0) termArray[c++] = termArray[i];//�u�����`�ƫD�s��
        }
        terms = c;//��s�O���I
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    Polynomial(int n = 2) {//�p�G�ϥΪ̶ǤJ���e�q�Ӥp�]�p�� 2�^�A�t�Τ��|�T�O�ܤ֦� 2 ���w�]�j�p
        capacity = max(2, n);//���u2�v�M�un�v�������j�����ӧ@���e�q
        termArray = new Term[capacity];// �إ߰O����
        terms = 0;// �M���즳���e�H�K���ݭ�
    }

    Polynomial(const Polynomial& n) {//�ƻs�@���h�����H�����
        capacity = n.capacity;
        terms = n.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) termArray[i] = n.termArray[i];
    }

    Polynomial& operator=(const Polynomial& n) {//�o�Ө禡�|��쥻�����n����ƻs�A���ѩ󦳫��Ц����]termArray�^�A����ϥΪ��������_�h��Ӫ���|�@�ΦP�@���O����A�|�y���O������~
        if (this == &n) return *this;
        delete[] termArray;
        capacity = n.capacity;
        terms = n.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) termArray[i] = n.termArray[i];
        return *this;
    }

    ~Polynomial() {//Polynomial�Ѻc�l
        delete[] termArray;//�{�����槹���̫�Ѱ��O����ʺA�t�m�H�K���`
    }

    void STerm(float coef, int exp) {// �N�ϥΪ̿�J�����[�J�]�|�X�֬ۦP����^
        if (coef == 0) return; // �`�ƶ�����"0"�������� 
        for (int i = 0; i < terms; ++i) {//�P�_�O����}�C(termArray)���O�_���ۦP�����ƶ�
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef;//�����ܪ����X��
                return;//�õ���
            }
        }
        NewArray(terms + 1);//�S�������ˬd�O����Ŷ��A�ǤJ�ثe�Ŷ��[�@���j�p�[�H�P�_
        termArray[terms++] = Term(coef, exp);//�ñN�`�Ƹ���ƥ[�J�O����
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Polynomial Add(const Polynomial& n) const {//�h�����[�k
        Polynomial a;// ����䪺�����J a�]addTerm �|�X�֬ۦP����^
        for (int i = 0; i < terms; ++i) a.addTerm(termArray[i]);//�h�����@�X��
        for (int j = 0; j < n.terms; ++j) a.addTerm(n.termArray[j]);//�h�����G�X��
        a.Sort();//�Ƨ�
        return a;
    }

    Polynomial Mult(const Polynomial& n) const {//�h�������k
        Polynomial p;// ���h�����C�@���`�ƶ��H�Ϋ��ƶ��ۭ��öǤJ�s�h�����Ŷ� t�]addTerm �|�X�֬ۦP����^
        for (int i = 0; i < terms; ++i) {//�h�����@�Ĥ@���}�l
            for (int j = 0; j < n.terms; ++j) {//�h�����G�Y�����
                Term t(termArray[i].coef * n.termArray[j].coef, termArray[i].exp + n.termArray[j].exp);
                p.addTerm(t);//�s�h�����X��
            }
        }
        p.Sort();//�Ƨ�
        return p;
    }

    float Eval(float f) const {
        float sum = 0;
        for (int i = 0; i < terms; ++i) {
            sum += termArray[i].coef * powf(f, termArray[i].exp);
        }
        return sum;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       //������n�Ψ��J��X�B��l�h���O?
       //�o��ӹB��l�쥻�u�{�o���ث��O�A�i�O�p�G�A�Q�n������u�ۭq���O�v��J�ο�X�]Polynomial�^�N�����D�n���L�A�ҥH�ϥιB��l�h���ӧi���sĶ��

    friend istream& operator>>(istream& a, Polynomial& pin) {// ��J�ާ@�O�B��l�h���Gcin >> p;
        pin.terms = 0;// �M���즳���e�H�K���ݭ�
        cout << "�п�J�h�����Ӽ�: ";
        int n;
        a >> n;
        cout << "�п�J�h��������, EX. 3 2  ��X: 3x^2\n";
        for (int i = 0; i < n; ++i) {
            float c; int e;//�`�ƥH�Ϋ��ƶ�
            a >> c >> e;
            pin.STerm(c, e); // STerm �|�N�ۦP�����ƶ��i��`�ƶ��X��
        }
        pin.Sort();//Sort�|�NtermArray�O���餺�e�Ƨ�
        return a;
    }

    friend ostream& operator<<(ostream& t, const Polynomial& pin) {// ��X�ާ@�O�B��l�h���Gcout << t;
        if (pin.terms == 0) {//�h�����u���s�u�ݿ�X�s
            t << "0";
            return t;
        }
        for (int i = 0; i < pin.terms; ++i) {
            float c = pin.termArray[i].coef;//�����g�L�Ƨǫ᪺�`�ƶ�
            int e = pin.termArray[i].exp;//�ҹ��������ƶ�
            if (i == 0) {//�P�_�Ĥ@���A�Y�Y�Ƭ� -1 �B���� !=0�A��� "-" ����� 1
                if (c == -1 && e != 0) t << "-";
                else if (c != 1 || e == 0) t << c;
            }
            else {
                if (c < 0) {//�Y�Y�Ƭ� -1 �B���� !=0�A��� "-" ����� 1
                    if (c == -1 && e != 0) t << " - ";
                    else t << " - " << fabs(c);//�H�~����� "-" �H�ε���ȫ᪺�`�ƶ�
                }
                else {
                    if (c == 1 && e != 0) t << " + ";//�Y�Y�Ƭ� + �B���� !=0�A��� "+" �H�α`�ƶ�
                    else t << " + " << c;
                }
            }
            if (e != 0) {// �P�_����O�_���s
                if (!(i == 0 && (c == -1))) t << "x";//�`�ƶ�������-1�B���O�Ĥ@���N��X�@�ӥ�����"x"
                if (e != 1) t << "^" << e;//���趵������1�N��X�@��"^"��ܦ����
            }
        }
        return t;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    Polynomial p1, p2;//�ŧi��Ӧh����
    cout << "��J�Ĥ@�Ӧh����\n";
    cin >> p1;//�I�s istream
    cout << "��J�ĤG�Ӧh����\n";
    cin >> p2;//�I�s istream

    // ��ܨ�Ӧh����
    cout << "\nP1(x) = " << p1 << "\n";//�Ĥ@��
    cout << "P2(x) = " << p2 << "\n";//�ĤG��

    // �ۥ[�P�ۭ����G�ҹ��������G
    Polynomial s = p1.Add(p2);
    cout << "\nP1 + P2 = " << s << "\n";//�[�k�h����
    Polynomial p = p1.Mult(p2);
    cout << "P1 * P2 = " << p << "\n";//���k�h����

    float x; // �N�J x �p��h�����|���B��᪺�`���G
    cout << "\n�п�J�n�N�J�� x �ȡG";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;//�[�k�h���� P1(X)
    cout << "P2(" << x << ") = " << p2.Eval(x) << endl;//���k�h���� P2(X)

    return 0;//���浲���^��0
}
