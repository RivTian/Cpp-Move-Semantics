![](https://u98yad7iy.oss-cn-shanghai.aliyuncs.com/imgsbed/2022/09/13/22-09-03-move_str-min.png)

> “*Move semantics allows us to optimize the copying of objects, where we no longer need the value. It can be used implicitly (for unnamed temporary objects or local return values) or explicitly (with std::move())*”



移动语义（Move semantics）是 C++11 后引入的一个非常重要的概念，对提升系统性能有着非常明显的效果。移动语义的基本思想可以参考[这里](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html) ，更多细节可以参考 [《深入理解C++11》](https://book.douban.com/subject/24738301/) / [《C++ Move Semantics》](https://book.douban.com/subject/35374444/) / [《Effective Modern C++》](https://book.douban.com/subject/26793803/) /

***本文混杂了 C++11 ~ C++20 中移动语义的相关特性***

## 移动语义基石

### 右值引用

> rvalue references can refer only to a temporary object that does not have a name or to an object marked with std::move()

右值引用是给类或者函数引入移动语义的基础。编译器通过参数的类型实现重载函数决断，对于右值入参，优先调用形参为右值引用的函数。形参为右值引用类型的接口实现方式一般和传统接口（例如拷贝构造、拷贝赋值）实现方式不同，简单来说[前者为浅拷贝，后者为深拷贝](https://stackoverflow.com/questions/184710/what-is-the-difference-between-a-deep-copy-and-a-shallow-copy)，即前者为“窃取”后者为副本复制，形如本文开篇那张图片所示（class string）

```c++
template<typename T>
class vector {
public:
    ...
    // insert a copy of elem:
    void push_back (const T& elem);
    // insert elem when the value of elem is no longer needed:
    void push_back (T&& elem);
    ...
};
```

#### Fallback / const &&

> if there is no optimized version of a function for move semantics, then the usual copying is used as a fallback

在可以调用移动函数的场景下，如果类没有对应的移动方法，那么编译器将调用可用的拷贝方法

形参类型为右值的函数，其形参不能使用 const 进行修饰。右值操作伴随着入参变量的修改，const 禁止了这种行为。这种情况下编译器将调用可用的拷贝方法

### std::move()

除临时变量外，有些变量可能是“一次性”的，使用过后就不会再使用（xvalue，将亡值，解释见下文）。为了减少[深拷贝](https://www.cnblogs.com/GouQ/p/13667647.html)的开销，可以使用 std::move() 标记变量的属性，告知编译器这个变量可以当作右值进行处理

```c++
void foo(std::string&& rv);
std::string s{"hello"};
foo(std::move(s));
```

因为 std::move 只是告知编译器变量可以当作右值处理，所以 std::move 可以等价于下面的语句。当然真实的实现方式要复杂一些，细节可以参考 [cppref](https://yearn.xyz/docs/c++/170.-cpp-move-semantics/static_cast(obj))

```c++
static_cast<decltype(obj)&&>(obj)
```

#### Valid & Unspecified

> The C++ standard library guarantees that moved-from objects are in a valid but unspecified state. The value of an object is not specified except that the object’s invariants are met and operations on the object behave as specified for its type
>
> For all objects and types you use in the C++ standard library you should ensure that moved-from objects also support all requirements of the functions called

被移动的变量，其内部资源被“窃取”，处于 Unspecified 状态（Do not know its value），**不能简单的认为其值为默认构造后的值**，但可以**赋予新值**。因为历史原因，部分标准库实现中，std::string 有 [SSO](https://gaomf.cn/2017/07/26/Cpp_string_COW_SSO/) 优化，移动操作并不一定会影响被移动对象的值（规范的操作是在移动的时候手动清空数据，但这不是强制性的）

```c++
std::vector<std::string> allRows;
std::string row;
while (std::getline(myStream, row)) { // read next line into row
	allRows.push_back(std::move(row)); // and move it to somewhere
}
```

swap 操作以本节约定为基础：

1. 被移动对象是可正常析构的
2. 除特殊情况外，被移动对象可以被重新赋予新值，无论是使用拷贝还是移动操作
3. ***应该保证与当前被移动对象相关的函数都可以正常运行（成员函数或者 free funcs）***

C++ 标准库中大部分类没有提供检测当前类是否被移动的接口，这是是为了避免性能损耗。部分类有移动检查函数，例如 std::future

#### 自赋值移动

> The rule that moved-from objects are in a valid but unspecified state usually also applies to objects after a direct or indirect self-move

使用 swap 操作和移动构造可以很好的避免[自赋值问题](https://www.cnblogs.com/BlueBlueSea/p/14018994.html)，所以拷贝/移动赋值最好使用 swap 形式实现。其他比较经典的字符值检查方式就是判断地址

```c++
Customer &operator=(Customer &&cust) { // noexcept declaration missing
  if (this != &cust) { // move assignment to myself?
    name = std::move(cust.name);
    values = std::move(cust.values);
  }
  return *this;
}
```

#### 值传递

使用传值（passing by value）的形式也可以利用移动语义来提升系统的性能：

```c++
void foo(std::string str); // takes the object by value
...
std::string s{"hello"};
...
foo(s); // calls foo(), str becomes a copy of s
foo(std::move(s)); // calls foo(), s is moved to str
```

右值引用形参是更高效的一种手段，但其有缺陷：**对具名变量不友好**。如何选择需要权衡，如果 move 操作很耗时，还是多写几行代码比较好，否则值传递简洁且高效，应优先使用

```c++
class Person {
  Person(std::string &&f, std::string &&l)
      : first{std::move(f)}, last{std::move(l)} {}
};
```

#### 移动语义截断

> Move semantics is not passed through

以下面的代码片段为例，在调用 insertTwice 函数的位置，入参 str 的生命周期我们是知道的，然而进入 insertTwice 函数内部，str 的生命周期需要另作处理。函数内外作用域不同，需要做不同的考虑

```c++
void insertTwice(std::vector<std::string> &coll, std::string &&str) {
  coll.push_back(str);            // copy str into coll
  coll.push_back(std::move(str)); // move str into coll
}
```

### Be Careful

编译器自动生成的移动函数可能会造成一些问题，例如：

1. 成员变量是引用语义，例如引用、指针。这种情况使用智能指针可以解决部分问题。任何指针操作最好都先判空
2. 相互关联的成员变量在移动之后未保持一致，例如字面值一致的整型和 string 变量在移动之后前者不变，后者为空
3. 其他

移动语义不是万能的，一些场景下 pass by const ref 可能比 move 更高效。以下面两个函数为例

1. 如果入参 s 本身就是常量，则第一个函数并不需要创建一个额外的变量，而第二个函数需要在栈上创建一个临时变量
2. 第二个函数可能减小了 first 的容量，下一次赋值可能会促使新的内存分配

```c++
void setFirstname(const std::string &s) { // take by lvalue reference
  first = s;                              // and assign
}
void setFirstname(std::string &&s) { // take by rvalue reference
  first = std::move(s);              // and move assign
}
```

### Benefit From Move

> If compilers automatically detect that a value is used from an object that is at the end of its lifetime, they will automatically switch to move semantics

移动语义可以发生在不同场景下，例如：

1. 传递了一个临时变量。使用不具名的临时变量，就可以触发当前场景
2. 返回局部变量。函数返回其局部变量将自动触发当前场景，给返回值套上一个 std::move 会禁止编译器的返回值优化从而降低性能，这是因为 move 改变了返回值的类型（&&），造成类型不匹配
3. 调用 std::move 标记变量的生命周期

为了避免一些不必要的 move，可以开启一些编译选项，例如 gcc 支持 -Wpessimizing-move 和 -Wredundant-move 或者 -Wextra

### noexcept & static_assert

> When move semantics was almost complete for C++11, we detected a problem: vector reallocations could not use move semantics. As a consequence, the new keyword noexcept was introduced

C++ `push_back` 操作有强[异常安全](https://www.cnblogs.com/qinfengxiaoyue/p/3713762.html)保证：either it succeeds or it has no effect。为了保证强异常安全，vector 在重新分配内存与拷贝已有数据时元素的拷贝抛出异常后，旧的堆数组依旧完整，所以拷贝操作对 vector 而言强异常安全；如果重新分配内存后使用的是移动操作来迁移旧数据，那么移动函数就不能抛异常，否则异常出现后异常安全的保证就被破坏了

编写移动语义函数时尽量保证函数不会抛出异常，并使用 noexcept 关键字限制相关函数，避免一些场景下移动语义的退化。由编译器生成的默认移动函数，编译器会尝试添加 noexcept 限制，可以使用下面的断言来确保 noexcept 的存在

使用 noexcept 标记的方法如果出现了异常，程序将直接调用 std::terminate() 方法中断程序。为了兼顾效率与安全性，可以使用编译时断言（`static_assert`）来确定对象的可移动性，示例如下：

```c++
static_assert(std::is_nothrow_move_constructible_v<Person>); // C++ 20
static_assert(std::is_nothrow_move_constructible<Person>::value, ""); // C++ 17
```

C++11标准规定下面几种函数会默认带有 noexcept 声明：

1. 默认构造函数、默认复制构造函数、默认赋值函数、默认移动构造函数和默认移动赋值函数。有一个额外要求，对应的函数在类型的基类和成员中也具有noexcept 声明，否则其对应函数将不再默认带有noexcept声明。自定义实现的函数默认也不会带有 noexcept 声明
2. 类型的析构函数以及delete运算符默认带有noexcept声明，请注意即使自定义实现的析构函数也会默认带有 noexcept 声明

## Rule of Five

![img](https://u98yad7iy.oss-cn-shanghai.aliyuncs.com/imgsbed/2022/09/14/20-02-10-rules-min.png)

当类满足一定要求时，编译器将自动为类生成移动构造和移动赋值函数。基本原则是编译器没有发现用户有***自己管理资源***的倾向，如果发现类中有任何用户定义的部分（Copy constructor / Copy assignment operator / Another move operation / Destructor），编译器都将不会自动生成移动语义函数，即使定义了一个空的析构函数（或者`dtor = default`），也是如此。当然你可以实现自己的移动语义部分。相关概念也常被称为 [Big5](https://en.cppreference.com/w/cpp/language/rule_of_three) ，或者 rule of five

> Since C++11, the rule has become the Rule of Five, which is usually formulated as The guideline is to either declare all five (copy constructor, move constructor, copy assignment operator, move assignment operator, and destructor) or none of them

为了保证最佳兼容性，最好按照 big5 的原则来实现类

### Declare/Del & Disable

> When declaring a copying/moving special member function (or the destructor), we have the automatic generation of the moving/copying special member functions disabled

只要用户显示声明了拷贝构造函数，编译器就不会自动帮我们生成移动构造函数，反之亦然。即使使用 `=default` 或者 `=delete` 也是如此，如下代码片段所示

```c++
class Person {
public:
  Person(const Person &) = default;
  Person &operator=(const Person &) = default;

  // NO move constructor/assignment declared
};
```

尽量不要对移动方法使用 `=delete`，不然可能类连**退化为拷贝**方法的机会都没有。如果想禁用移动方法，直接声明拷贝方法即可

当类中包含多个成员变量且部分没有移动方法时，编译器将移动可移动的成员，不可移动的成员将直接拷贝

### 继承体系下的移动

对于定义了虚析构函数的基类，其默认移动构造可能不会被自动生成（依赖编译器实现），为了保证存在移动操作，需要手动声明移动和构造函数（使用 `=default`）。子类的移动性跟普通类的定义是一致的，例如子类在进行移动操作时，父类相关变量由其自身属性决定

## 成员函数的引用签名

返回类内属性时我们经常使用 pass by const ref 的方式，这个方式的一个缺点是我们可能调用一个临时变量的相关方法，从而造成不可预测的结果。为了解决这类问题，可以考虑新增 && 成员函数，代码片段如下

```c++
class Person {
private:
  std::string name;

public:
  std::string getName() && { // when we no longer need the value
    return std::move(name);  // we steal and return by value
  }
    
  const std::string &getName() const & { // in all other cases
    return name;                         // we give access to the member
  }
};
```

合理的使用 && 函数可以提升性能：`coll.push_back(std::move(p).getName())`。右值的引入也为函数的签名提供了更多的复杂性：

```c++
class C {
public:
  void foo() const & { std::cout << "foo() const&\n"; }
  void foo() && { std::cout << "foo() &&\n"; }
  void foo() & { std::cout << "foo() &\n"; }
  void foo() const && { std::cout << "foo() const&&\n"; }
};
```

成员函数的引用签名（Reference Qualifiers）还有其他功能，例如使用引用签名禁用临时变量赋值可以避免一些错误：

```c++
std::optional<int> getVal();

// 使用引用签名（如 operator=(...)&;）可以禁止对 optional 临时变量赋值，从而避免下面的错误
if(getVal() = 0) {...} 
```

## Value Categories

![img](https://u98yad7iy.oss-cn-shanghai.aliyuncs.com/imgsbed/2022/09/17/16-21-19-cpp_vals-min.png)

1. primary categories: lvalue (“locator value”) / prvalue (“pure readable value”) / xvalue (“eXpiring value”)
2. The composite categories are:
   1. glvalue (“generalized lvalue”) as a common term for “lvalue or xvalue”
   2. rvalue as a common term for “xvalue or prvalue”

C++11 之后因为移动语义的引入，左值和右值概念被扩充，新引入了将亡值（eXpiring value）、prvalue 等。细节请参考其他资料，例如[《C++ Move Semantics》](https://book.douban.com/subject/35374444/) 第 8 章

搞清楚将亡值（xvalue）就差不多理解了上图，C++17 后将亡值的形式有两种，示例如下。细节请参考 [《现代C++语言核心特性解析》](https://book.douban.com/subject/35602582/) 第 6.6 节

```c++
static_cast<BigMemoryPool&&>(my_pool)

// 临时变量实质化
struct X{int a;};
int main () {int b = X().a;} 
```

### Materialization

> C++17 then introduces a new term, called materialization (of an unnamed temporary), for the moment a prvalue becomes a temporary object. Thus, a temporary materialization conversion is a (usually implicit) prvalue-to-xvalue conversion

C++17 引入 materialization 后，我们可以返回没有拷贝和移动相关方法的对象

### Special Rules

数值类型不仅仅适用于常规变量，也可用于函数和类成员变量：

1. 左值（这里借左值表示 lvalues，而不仅仅是 left value）对象的成员函数是左值
2. 右值的静态变量和引用类型变量是左值
3. 右值的普通成员变量是将亡值（xvalues）

示例代码如下：

```c++
std::pair<std::string, std::string&> foo(); // note: member second is reference
std::vector<std::string> coll;
...
coll.push_back(foo().first); // moves because first is an xvalue here
coll.push_back(foo().second); // copies because second is an lvalue here
```

下面两种方式的效果是一样的，member 需要是普通变量（plain，非 static 或 ref）：

```c++
std::move(obj).member
std::move(obj.member)
```

### decltype

> The primary goal of this keyword is to get the exact type of a declared object

```cpp
void rvFunc(std::string &&str) {
  std::cout << std::is_same<decltype(str), std::string>::value;    // false
  std::cout << std::is_same<decltype(str), std::string &>::value;  // false
  std::cout << std::is_same<decltype(str), std::string &&>::value; // true
  std::cout << std::is_reference<decltype(str)>::value;            // true
  std::cout << std::is_lvalue_reference<decltype(str)>::value;     // false
  std::cout << std::is_rvalue_reference<decltype(str)>::value;     // true
}
```

## 泛型中的移动语义

### 完美转发

> We have already learned that move semantics is not automatically passed through. This has consequences for generic code

完美转发（Perfect Forwarding）用于解决泛型中移动语义截断的问题。如果没有完美转发，引入右值后 C++ 的重载机制会变得非常臃肿与复杂。C++ 中实现完美转发需要结合通用引用和 std::forward

#### 通用引用

> An rvalue reference (not qualified with const or volatile) of a function template parameter does not follow the rules of ordinary rvalue references. It is a different thing

***通用引用的形式和右值引用形式类似，但功能完全不同***。通用引用可以绑定所有类型的变量，所以通用引用也称为万能引用，重载函数决断时，***通用引用的优先级要低于精确匹配***。尽量不要在构造函数中使用通用引用

```c++
template<typename T>
void callFoo(T&& arg); // arg is a universal/forwarding reference
```

#### std::forward

> Just like for std::move(), the semantic meaning of std::forward<>() is I no longer need this value here, with the additional benefit that we preserve the type (including constness) and the value category of the object the passed universal reference binds to

```c++
void foo(const X &); // for constant values (read-only access)
void foo(X &);       // for variable values (out parameters)
void foo(X &&);      // for values that are no longer used (move semantics)

void callFoo(const X &arg) { // arg binds to all const objects
  foo(arg);                  // calls foo(const X&)
}
void callFoo(X &arg) { // arg binds to lvalues
  foo(arg);            // calls foo(X&)
}
void callFoo(X &&arg) { // arg binds to rvalues
  foo(std::move(arg));  // needs std::move() to call foo(X&&)
}

template <typename T> void callFoo(T &&arg) {
  foo(std::forward<T>(arg)); // equivalent to foo(std::move(arg)) for passed rvalues
}

template <typename... Ts> void callFoo(Ts &&...args) {
  foo(std::forward<Ts>(args)...);
}
```

#### 引用折叠

引用折叠（reference collapsing）是通用引用绑定和完美转发的细节，这里不展开，细节可以参考[《C++ Move Semantics》](https://book.douban.com/subject/35374444/) 第 10 章

#### auto &&

> in generic code, how can you program passing a return value later but still keeping its type and value category?

```c++
auto callFoo = [](auto&& arg) { // arg is a universal/forwarding reference
	foo(std::forward<decltype(arg)>(arg)); // perfectly forward arg
};

void callFoo(auto&& val) { // C++ 20
	foo(std::forward<decltype(arg)>(arg));
}
```

#### decltype(auto)

略

## Moving Algs

引入移动语义后标准库提供了一些以移动为基础的算法函数，例如：std::move()（注意与上面的 move 做区别）、`std::move_backward()`，这两个函数对应着 `std::copy()` 和 `std::copy_backward()`

### Move Iters

> By using move iterators (also introduced with C++11), you can use move semantics even in other algorithms and in general wherever input ranges are taken
>
> Using move iterators in algorithms usually only makes sense when the algorithm guarantees to use each element only once

在算法函数中使用移动迭代器可以提升性能，但使用移动迭代器有一定的约束，比如算法函数**只能使用被移动的对象一次**

```cpp
std::for_each(std::make_move_iterator(coll.begin()),
              std::make_move_iterator(coll.end()), [](auto &&elem) {
                if (elem.size() != 4) {
                  process(std::move(elem));
                }
              });

std::vector<std::string> vec{std::make_move_iterator(src.begin()),
                             std::make_move_iterator(src.end())};
```

## 标准库

### std::array

> std::array<> is the only container that does not allocate memory on the heap. In fact, it is implemented as a templified C data structure with an array member

std::array 是标准库中唯一不支持移动语义的容器，因为其在堆中没有分配任何内存空间
