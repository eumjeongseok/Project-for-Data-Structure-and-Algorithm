/*
p(x)=10x100+6과 같이 최고차항의 차수가 매우 크고 대부분 항의 계수가 0인 다항식을 희소 다항식이라 한다.
이러한 다항식을 구현하기 위해 배열을 사용하면 메모리의 낭비가 심하다.
따라서 희소 다항식은 연결 리스트를 이용하여 구현하는 것이 좋다.
다음과 같이 처리되도록 프로그램 2.7을 참고하여 연결 리스트를 이용한 희소 다항식 프로그램을 구현하라.

(고쳐야 하는 것: 출력 형식, 마지막 항의 '+' 삭제, 그리고 계수를 실수형 그대로 출력하기)

*/

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;


class Node

{
private:
    float coef; //계수
    int exp; //지수
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

    //자신의 다음에 새로운 노드 n을 삽입하는 함수
    void insertNext(Node* n) {
        if (n != NULL) {
            n->link = link;
            link = n;
        }
    }

    //자신의 다음 노드를 리스트에서 삭제하는 함수
    Node* removeNext()
    {
        Node* removed = link;
        if (removed != NULL)
            link = removed->link;
        return removed;
    }
    friend class polyList;
};

//다항식 링크 리스트
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

    //pos번째 항목을 반환함
    Node* getEntry(int pos) {
        Node* n = &org;
        for (int i = -1; i < pos; i++, n = n->getLink())
            if (n == NULL)
                break;
        return n;
    }

    //리스트의 어떤 위치에 항목 삽입
    void insert(int pos, Node* n)
    {
        Node* prev = getEntry(pos - 1);
        if (prev != NULL)
            prev->insertNext(n);
    }

    //리스트의 어떤 위치의 항목 삭제
    Node* remove(int pos) {
        Node* prev = getEntry(pos - 1);
        return prev->removeNext();
    }

    //리스트의 항목 개수 반환
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

        //cout << "A+B =(" << temp.size() << "항)= ";
        cout << "(" << temp.size() << ") = ";

        temp.display();

    }

    void input() {
        int count, e;
        float c;
        //cout << "희소 다항식의 항의 개수를 입력하세요: ";
        cin >> count;

        //cout << "각 항의 계수와 지수 입력(최고차항부터 "  << count << "개)" << endl;
        for (int i = 0; i < count; i++) {
            //cout << i + 1 << "번째 항 : 계수 지수 = ";
            cin >> c >> e;
            insert(i, new Node(c, e));
        }
    }

    //출력
    void display() {
        int count = 1;
        if (size() == 0) {
            cout << "다항식이 존재하지 않습니다" << endl;
            return;
        }
        else {
            for (Node* p = getHead(); p != NULL; p = p->getLink()) {
                p->display();
                if (p->getLink() != NULL) {
                    cout << " + ";
                } //이에 따라 마지막 항은 '+'이 출력되지 않는다!
            }
            cout << endl;
        }
    }
};

int main(void)

{
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL); cout.tie(NULL);
    //실행 속도 증가

    polyList A, B, C;
    A.input();
    B.input();

    //cout << "A=(" << A.size() << "항) = ";
    cout << "(" << A.size() << ") = ";
    A.display();

    //cout << "B=(" << B.size() << "항) = ";
    cout << "(" << B.size() << ") = ";
    B.display();

    A.Add(&B);
    return 0;

}