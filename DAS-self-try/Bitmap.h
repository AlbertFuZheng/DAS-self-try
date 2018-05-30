#pragma once
class Bitmap
{
private:

   int* f;
   int* t;
   int top = 0;

public:

   Bitmap() = delete;
   Bitmap(int n)//��̬�������飬�䳤�����ⲿ����Ĳ���n�й�
   {
      f = new int[n];
      t = new int[n];
   }
   ~Bitmap()//�ͷ�����
   {
      delete[] f;
      delete[] t;
   }

   bool test(int k)//����k�Ƿ����
   {
      return ((0 <= f[k]) && (f[k] < top) && (k == t[f[k]]));
   }

   void reset()//����Ϊ����Ԫ�ض�������
   {
      top = 0;
   }

   void set(int k)//����һ��Ԫ��
   {
      if (!test(k))
      {
         t[top] = k;
         f[k] = top++;
      }
   }

   void clear(int k)//ɾ��һ��Ԫ��
   {
      if (test(k))
      {
         if (top--)
         {
            f[t[top]] = f[k];//��β��Ԫ�ص�����д��k��λ��
            t[f[k]] = t[top];
         }
      }
   }

   int num()//���ص�ǰԪ������
   {
      return top;
   }
};
