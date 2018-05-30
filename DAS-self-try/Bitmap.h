#pragma once
class Bitmap
{
private:

   int* f;
   int* t;
   int top = 0;

public:

   Bitmap() = delete;
   Bitmap(int n)//动态申请数组，其长度与外部传入的参数n有关
   {
      f = new int[n];
      t = new int[n];
   }
   ~Bitmap()//释放数组
   {
      delete[] f;
      delete[] t;
   }

   bool test(int k)//检验k是否存在
   {
      return ((0 <= f[k]) && (f[k] < top) && (k == t[f[k]]));
   }

   void reset()//重置为所有元素都不存在
   {
      top = 0;
   }

   void set(int k)//加入一个元素
   {
      if (!test(k))
      {
         t[top] = k;
         f[k] = top++;
      }
   }

   void clear(int k)//删除一个元素
   {
      if (test(k))
      {
         if (top--)
         {
            f[t[top]] = f[k];//将尾部元素的内容写入k的位置
            t[f[k]] = t[top];
         }
      }
   }

   int num()//返回当前元素总数
   {
      return top;
   }
};
