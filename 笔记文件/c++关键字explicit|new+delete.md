## c++关键字explicit

explicit关键字的作用:防止利用隐式类型转换方式来构造你的对象

```c++
class MyString
{
public:
    MyString(char * str)
    {
        
    }
    explicit MyString(int len)//没有加explicit默认函数为隐式声明
    {
        
    }
}

int main()
{
    MyString str("abcd");
    MyString str="abcd";
    MyString str(10);
    MyString str=10;//10的含义不明确,可能为长度也可能为字符,此时出现歧义,但是如果不加explicit关键字这条语句是可以的!编译不会报错,原因是在C++中, 如果的构造函数只有一个参数时, 那么在编译的时候就会有一个缺省的转换操作:将该构造函数对应数据类型的数据转换为该类对象
    //为了防止这种情况的出现,可以在函数前加上关键字explicit
}
```

**注意事项:**

**explicit关键字只对有一个参数的类构造函数有效**

**但是, 也有一个例外, 就是当除了第一个参数以外的其他参数都有默认值的时候, explicit关键字依然有效, 此时, 当调用构造函数时只传入一个参数, 等效于只有一个参数的类构造函数**

------

## new和delete

new的用法

```c++
Person *p=new Person[10];//表示在堆区分配了十个自定义类型Person的空间
```

```
由此看出,在堆区开辟数组,一定会调用默认构造函数,所以!当写了有参构造函数,编译器不会提供默认构造函数,此时若没有写默认构造函数,则无法在堆区开辟空间
如果在栈上开辟内存,可以没有默认构造函数
```



------

new在堆区开辟一块内存,并返回一个指针来接收这个内存,堆区开辟的内存手动开辟手动释放,自动初始化并调用构造函数

```c++
Person *person=new Person;
//相当于c语言中
Person *person=(Person)malloc(sizeof(Person));
if(person==NULL)
{
    return 0;
}
person->Init();构造函数
//想要释放内存直接
    delete person;//自动调用析构函数
```

### new和malloc的区别

本质区别:malloc和free属于库函数,new和delete属于运算符

malloc不会调用构造函数,new会调用构造函数

malloc返回void *,C++需要强转;new返回创建的对象的指针

### 注意事项

不要用void *去接收new出来的对象,利用void *无法调用析构函数

### delete

用delete释放数组时

```c++
delete [] p;//多加一个[]表示p是一个数组,需要被释放的是一个数组,不加指挥释放一个,其余全部泄漏
```

