/*
p(x)=10x100+6�� ���� �ְ������� ������ �ſ� ũ�� ��κ� ���� ����� 0�� ���׽��� ��� ���׽��̶� �Ѵ�.
�̷��� ���׽��� �����ϱ� ���� �迭�� ����ϸ� �޸��� ���� ���ϴ�.
���� ��� ���׽��� ���� ����Ʈ�� �̿��Ͽ� �����ϴ� ���� ����.
������ ���� ó���ǵ��� ���α׷� 2.7�� �����Ͽ� ���� ����Ʈ�� �̿��� ��� ���׽� ���α׷��� �����϶�.

(���ľ� �ϴ� ��: ��� ����, ������ ���� '+' ����, �׸��� ����� �Ǽ��� �״�� ����ϱ�)

*/

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;


class Node

{
private:
    float coef; //���
    int exp; //����
    Node* link;

public:
    Node(float c = 0, int e = 0) :coef(c), exp(e), link(NULL) { }

    Node* getLink() {
        return link;
    }

    void setLink(Node* next) {
        link = next;
    }

    void display() {
        printf("%.1f x^%d", coef, exp);
    }

    //�ڽ��� ������ ���ο� ��� n�� �����ϴ� �Լ�
    void insertNext(Node* n) {
        if (n != NULL) {
            n->link = link;
            link = n;
        }
    }

    //�ڽ��� ���� ��带 ����Ʈ���� �����ϴ� �Լ�
    Node* removeNext()
    {
        Node* removed = link;
        if (removed != NULL)
            link = removed->link;
        return removed;
    }
    friend class polyList;
};

//���׽� ��ũ ����Ʈ
class polyList {

private:
    Node org;

public:
    polyList() : org(0) { }

    ~polyList() { clear(); }

    void clear() {
        while (!isEmpty())
            delete remove(0);
    }

    Node* getHead() {
        return org.getLink();
    }

    bool isEmpty() {
        return getHead() == NULL;
    }

    //pos��° �׸��� ��ȯ��
    Node* getEntry(int pos) {
        Node* n = &org;
        for (int i = -1; i < pos; i++, n = n->getLink())
            if (n == NULL)
                break;
        return n;
    }

    //����Ʈ�� � ��ġ�� �׸� ����
    void insert(int pos, Node* n)
    {
        Node* prev = getEntry(pos - 1);
        if (prev != NULL)
            prev->insertNext(n);
    }

    //����Ʈ�� � ��ġ�� �׸� ����
    Node* remove(int pos) {
        Node* prev = getEntry(pos - 1);
        return prev->removeNext();
    }

    //����Ʈ�� �׸� ���� ��ȯ
    int size() {
        int count = 0;
        for (Node* p = getHead(); p != NULL; p = p->getLink())
            count++;
        return count;
    }

    void Add(polyList* that) {
        polyList temp;
        int count = 0;
        Node* p = getHead();
        Node* t = that->getHead();
        while (p != NULL && t != NULL) {
            if (p->exp == t->exp) {
                temp.insert(count++, new Node(p->coef + t->coef, p->exp));
                p = p->getLink();
                t = t->getLink();
            }
            else if (p->exp > t->exp) {
                temp.insert(count++, new Node(p->coef, p->exp));
                p = p->getLink();
            }
            else {
                temp.insert(count++, new Node(t->coef, t->exp));
                t = t->getLink();
            }
        }

        for (; p != NULL; p = p->getLink())
            temp.insert(count++, new Node(p->coef, p->exp));

        for (; t != NULL; t = t->getLink())
            temp.insert(count++, new Node(t->coef, t->exp));

        //cout << "A+B =(" << temp.size() << "��)= ";
        cout << "(" << temp.size() << ") = ";

        temp.display();

    }

    void input() {
        int count, e;
        float c;
        //cout << "��� ���׽��� ���� ������ �Է��ϼ���: ";
        cin >> count;

        //cout << "�� ���� ����� ���� �Է�(�ְ����׺��� "  << count << "��)" << endl;
        for (int i = 0; i < count; i++) {
            //cout << i + 1 << "��° �� : ��� ���� = ";
            cin >> c >> e;
            insert(i, new Node(c, e));
        }
    }

    //���
    void display() {
        int count = 1;
        if (size() == 0) {
            cout << "���׽��� �������� �ʽ��ϴ�" << endl;
            return;
        }
        else {
            for (Node* p = getHead(); p != NULL; p = p->getLink()) {
                p->display();
                if (p->getLink() != NULL) {
                    cout << " + ";
                } //�̿� ���� ������ ���� '+'�� ��µ��� �ʴ´�!
            }
            cout << endl;
        }
    }
};

int main(void)

{
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL); cout.tie(NULL);
    //���� �ӵ� ����

    polyList A, B, C;
    A.input();
    B.input();

    //cout << "A=(" << A.size() << "��) = ";
    cout << "(" << A.size() << ") = ";
    A.display();

    //cout << "B=(" << B.size() << "��) = ";
    cout << "(" << B.size() << ") = ";
    B.display();

    A.Add(&B);
    return 0;

}