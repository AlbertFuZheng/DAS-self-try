#define _CRT_SECURE_NO_WARNINGS

#define max(x, y) ((x) > (y) ? (x) : (y))
#define stature(p) ( (p) ? (p)->height : -1)//��ʾ�������ĸ߶ȣ����ݿսڵ㣬�սڵ�߶�Ϊ-1
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
//�ֵܵ�ָ��
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
//���Ը��׵�ָ��
#define FromParentTo(x) ( IsRoot(x) ? this->_root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )
//�����������this->�Ļ����ڼ̳�����ʹ�������ͻ����δ������ʶ��������
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool test = 0;

template <typename T> struct BinNode {
public:
   BinNode<T> *parent = 0, *lc = 0, *rc = 0;
   T data = 0;
   int height = 0;
   int count = 0;//�������ڱ�����޸ģ�������
   BinNode(T const &e, BinNode<T>* p) //:data(e), parent(p) {}
   {
      //�������ڱ�����޸ģ������ַ���

      //assert(0);
      data = new char[16];
      //assert(0);

      strcpy(data, e);
      
      parent = p;
   }
   ~BinNode() {
      delete[] data;
   }
   int size() { //��������Ϊ���ڵ�ĺ�����������Ӷ�ΪO(n)
      int s = 1;
      if (lc)
         s += lc->size();
      if (rc)
         s += rc->size();
      return s;
   }
   BinNode<T>* insertAsLC(T const &e) {
      return lc = new BinNode(e, this);
   }
   BinNode<T>* insertAsRC(T const &e) {
      return rc = new BinNode(e, this);
   }
   //����������������µ�ֱ�Ӻ��
   BinNode<T>* succ() {
      BinNode<T>* s = this;
      if (rc) {
         s = rc;
         while (s->lc)
            s = s->lc;
      }
      else {
         while (s->parent->rc == s)
            s = s->parent;
         s = s->parent;
      }
      return s;
   }
};

template <typename T> class BinTree {

public:

   int _size = 0;
   BinNode<T>* _root = nullptr;
   BinNode<T>* bestStudent = nullptr;//�������ڱ�����޸ģ���¼�������ѧ��

   virtual int updateHeight(BinNode<T>* x) {
      return x->height = 1 + max(stature(x->lc), stature(x->rc));
   }
   void updateHeightAbove(BinNode<T>* x) {
      while (x) {
         int temp = x->height;
         updateHeight(x);
         if (x->height == temp)
            break;//һ���߶�û�б仯���Ϳ�����ֹ������Դ
         x = x->parent;
      }
   }

   int size() const {
      return _size;
   }
   bool empty() const {
      return !_root;
   }
   BinNode<T>* rood() const {
      return _root;
   }

   //�����ӽڵ�
   BinNode<T>* insertAsLC(BinNode<T>* x, T const &e) {
      _size++;
      x->insertAsLC(e);
      updateHeightAbove(x);
      return x->lc;
   }
   BinNode<T>* insertAsRC(BinNode<T>* x, T const &e) {
      _size++;
      x->insertAsRC(e);
      updateHeightAbove(x);
      return x->rc;
   }

   //��������
   BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &S) {
      if (x->lc = S->_root)//��ֵ��ͬʱ�ж�����S�ǿ�
         x->lc->parent = x;
      _size += S->_size;
      updateHeightAbove(x);
      //�ͷ�S
      S->_root = NULL;
      S->_size = 0;
      release(S);
      S = NULL;
      return x;
   }
   BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &S) {
      if (x->rc = S->_root)//��ֵ��ͬʱ�ж�����S�ǿ�
         x->rc->parent = x;
      _size += S->_size;
      updateHeightAbove(x);
      //�ͷ�S
      S->_root = NULL;
      S->_size = 0;
      release(S);
      S = NULL;
      return x;
   }

   //ɾ������
   int remove(BinNode<T>* x) {
      //�ж����Ը��ڵ��ָ��
      FromParentTo(*x) = NULL;
      updateHeightAbove(x->parent);
      int n = removeAt(x);
      _size -= n;
      return n;
   }
   static int removeAt(BinNode<T>* x) {
      if (!x)
         return 0;
      int n = 1 + removeAt(x->lc) + removeAt(x->rc);
      release(x->data);
      release(x);
      return n;
   }
};






template <typename T> class BST : public BinTree<T> {

public:

   //���ң�����hotָ�����нڵ�ĸ���
   virtual BinNode<T>*& search(const T &e) {
      return searchIn(this->_root, e, _hot = NULL);
   }
   static BinNode<T>*& searchIn(BinNode<T>* &v, const T &e, BinNode<T>* & hot) {
      //if (!v || (e == v->data))
      //�������ڱ�����޸ģ��ַ�����Ƚϴ�С
      if (!v)
      {
         cout << "NULL!" << endl;
         return v;
      }
      if (strcmp(e, v->data) == 0)
      {
         cout << "here!" << endl;
         return v;
      }
      cout << "go down" << endl;
      hot = v;
      //return searchIn(e < v->data ? v->lc : v->rc, e, hot); 
      //�������ڱ�����޸ģ��ַ�����Ƚϴ�С
      return searchIn(strcmp(e, v->data) < 0 ? v->lc : v->rc, e, hot);
   }

   //����
   virtual BinNode<T>* insert(const T &e) {
      BinNode<T>* &x = search(e);
      if (!x) {//ֻ���ڲ���ͬ������²Ž��в���
         x = new BinNode<T>(e, _hot);
         this->_size++;
         this->updateHeightAbove(x);
      }
      else
         cout << "got it +1" << endl;
      //�������ڱ�����޸ģ�����ظ����������+1
      if (++(x->count) > (this->bestStudent ? this->bestStudent->count : 0))
      {
         this->bestStudent = x;

      }

      cout << x->data << x->count << endl;
      return x;
   }

   //ɾ��
   virtual bool remove(const T &e) {
      BinNode<T>* &x = search(e);
      if (!x)
         return false;
      removeAt(x, _hot);
      this->_size--;
      this->updateHeightAbove(_hot);
      return true;
   }
   //ɾ������������д����
   BinNode<T>* removeAt(BinNode<T>* &x, BinNode<T>* &hot) {
      BinNode<T>* w = x;
      BinNode<T>* succ = NULL;
      //����֧
      if (!x->lc)
         succ = x = x->rc;
      else
         if (!x->rc)
            succ = x = x->lc;
      //���֧
         else {
            w = w->succ();
            T temp(x->data);
            x->data = w->data;
            w->data = temp;
            //release(temp);
            BinNode<T>* u = w->parent;
            (u == x ? u->rc : u->lc) = succ = w->rc;
         }
         hot = w->parent;
         if (succ)
            succ->parent = hot;
         //release(w->data);
         //release(w);
         return succ;
   }

protected:

   BinNode<T>* _hot = 0;

   //3+4�ع�
   BinNode<T>* connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c, BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3) {
      a->lc = T0;
      if (T0) T0->parent = a;
      a->rc = T1;
      if (T1) T1->parent = a;
      c->lc = T2;
      if (T2) T2->parent = c;
      c->rc = T3;
      if (T3) T3->parent = c;
      b->lc = a;
      a->parent = b;
      b->rc = c;
      c->parent = b;
      cout << "3+4: " << a->data << "  " << b->data << "  " << c->data << endl;
      //this->updateHeight(a);
      //this->updateHeight(c);
      //this->updateHeight(b);
      return b;
   }

   BinNode<T>* rotateAt(BinNode<T>* v) {
      BinNode<T>* p = v->parent, *g = p->parent;
      if (IsLChild(*p))//zig
         if (IsLChild(*v)) {//zig-zig
            cout << "zig-zig" << endl;
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
         }
         else {//zig-zag
            cout << "zig-zag" << endl;
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
         }
      else//zag
         if (IsRChild(*v)) {//zag-zag
            cout << "zag-zag" << endl;
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
         }
         else {//zag-zig
            v->parent = g->parent;
            cout << "zag-zig" << endl;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
         }
   }
};





#define Balanced(x) ( stature((x).lc) == stature((x).rc) )
#define BalFac(x) ( stature((x).lc) - stature((x).rc) )
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))
#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*���*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*�Ҹ�*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*�ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������*/ \
   ) \
   ) \
)
using namespace std;

template <typename T> class AVL : public BST<T> {

public:

   //������д����
   BinNode<T>* insert(const T &e) {
      

      cout << "insert!!!" << endl;
      BinNode<T>* &x = this->search(e);

      if (!x) {
         cout << "x is nullptr, everything's fine, until now..." << endl;
      }
         //assert(0);
      if(x){
         cout << "i got it +1: " << x->data << x->count << endl;
         //�������ڱ�����޸ģ�����ظ����������+1
         if (++(x->count) > (this->bestStudent ? this->bestStudent->count : 0))
            this->bestStudent = x;

         cout << x->data << x->count << endl;
         cout << "parent: ";
         if (x->parent)
            cout << x->parent->data << endl;
         else
            cout << endl;
         cout << "lc: ";
         if (x->lc)
            cout << x->lc->data << endl;
         else
            cout << endl;
         cout << "rc: ";
         if (x->rc)
            cout << x->rc->data << endl;
         else
            cout << endl;

         return x;
      }

      
      BinNode<T>* xx = x = new BinNode<T>(e, this->_hot);//���������⣡����
      //assert(0);
      this->_size++;
      for (BinNode<T>* g = this->_hot; g; g = g->parent)
      {

         if (!AvlBalanced(*g)) {

            //��֪��Ϊʲô������������ò���
            //FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));//�ҵ���ɲ�ƽ����ӽڵ㣬����3+4�ع�
            if (!g->parent)
               this->_root = this->rotateAt(tallerChild(tallerChild(g)));
            else
               (IsLChild(*g) ? g->parent->lc : g->parent->rc) = this->rotateAt(tallerChild(tallerChild(g)));


            break;
         }
         else
         {

            this->updateHeight(g);

         }

      }

      //�������ڱ�����޸ģ��״μ���ڵ㣬������+1
      if (++(xx->count) > (this->bestStudent ? this->bestStudent->count : 0))
         this->bestStudent = xx;
      cout << xx->data << xx->count << endl;
      cout << "parent: ";
      if (x->parent)
         cout << x->parent->data << endl;
      else
         cout << endl;
      cout << "lc: ";
      if (x->lc)
         cout << x->lc->data << endl;
      else
         cout << endl;
      cout << "rc: ";
      if (x->rc)
         cout << x->rc->data << endl;
      else
         cout << endl;
      return xx;
   }

   //ɾ����д����
   bool remove(const T &e) {
      BinNode<T>* &x = this->search(e);
      if (!x)
         return false;
      this->removeAt(x, this->_hot);
      this->_size--;
      for (BinNode<T>* g = this->_hot; g; g = g->parent) {
         if (!AvlBalanced(*g))
            FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
         this->updateHeight(g);
      }
      return true;
   }
};




int main() {

   /*

   int n;
   cin >> n;
   BST<string> tree;
   string name;
   for (int i = 0; i < n; i++) {
   cin >> name;
   //tree.insert(name);
   }
   //cout << tree.bestStudent->data << ' ' << tree.bestStudent->count << endl;

   */

#ifndef _OJ_
   freopen("input.txt", "r", stdin);
   //freopen("output.txt", "w", stdout);
#endif

   //assert(1);

   cout << "started" << endl;
   cout << "------------------" << endl;

  
  
   int n;
   scanf("%d", &n);
   BST<char*> tree;
   char name[16];
   const int m = 0;
   for (int i = 0; i < m; i++) {
      scanf("%s", name);
      tree.insert(name);
   }
   
   
   /*
   char str[16]="a";

   BinNode<char*>* t=tree.search(str);
   // assert(0);
   int k=t->count;
   cout<<k;
   */
   
   test = 1;
   for (int i = m; i < n; i++) {
      
      scanf("%s", name);

      tree.insert(name); 
      
      cout << "-----------" << endl;
   }

   printf("%s %d", tree.bestStudent->data, tree.bestStudent->count);

   

   return 0;
}