#include <cstdio>

class Singleton{
  private:
    static int data;
  public:
    static int* GetInstance(){
      return &data;
    }
};

int Singleton::data = 10;

int main()
{
  Singleton a,b;
  printf("a : %d\n", *a.GetInstance());
  printf("b : %d\n", *nclude <cstdio>
        2 
        3 class Singleton{
          4   private:
            5     static int data;
              6   public:
              7     static int* GetInstance(){
                8       return &data;
                  9     
              }
               10 
        };
         11 
          12 int Singleton::data = 10;
           13 
            14 int main()
            15 {
             16   Singleton a,b;
              17   printf("a : %d\n", *a.GetInstance());
               18   printf("b : %d\n", *b.GetInstance());
                19 
                   20   *b.GetInstance() = 20;                                                                                                                                 
                 21   printf("a : %d\n", *a.GetInstance());
                  22   printf("b : %d\n", *b.GetInstance());
                   23 
                      24 
            }
  b.GetInstance());

  *b.GetInstance() = 20;
  printf("a : %d\n", *a.GetInstance());
  printf("b : %d\n", *b.GetInstance());

}
