> **Code Hub**
>
> * https://www.cppmove.com/code/code.html
> * [Download](./cppmove-code.tar)
> * [Online Code](https://www.cppmove.com/code/toc.html)

本文将完整的介绍 C++ Move Semantics(移动语义), 请配合《C++ Move Semantics》阅读

## PartI: 移动语义的基本特征

* 移动语义允许对对象的复制进行优化，它可以隐式使用 (用于未命名的临时对象或局部返回
  值)，也可以显式使用 (通过 $std::move()$)。
* $std::move()$ 表示不再需要这个值，它将对象标记为可移动的。标记为 $std::move()$ 的对象不
  会 (部分地) 销毁 (析构函数仍然会调用)。
*   通过使用非 $const$ 右值引用 (例如 `std::string&&`) 声明函数，可以定义一个接口，调用者在接
    口中从语义上声明不再需要传递的值。函数可以通过“窃取”这个信息来进行优化，或者对
    传递的参数做任何修改。通常，实现者还必须确保传递的参数在调用后处于有效状态。
* 移动的 C++ 标准库的对象仍然是有效的对象，但其值为未定义。
* 拷贝语义用作移动语义的备选 (如果拷贝语义支持的话)。如果没有采用右值引用的实现，则使用任何采用普通 $const$ 左值引用的实现 (如：`const std::string&`)。即使对象被显式地标记为 `std::move()`，也会使用备选方式。
*  对 $const$ 对象调用 `std::move()` 通常没有效果。
*  如果按值 (而不是按引用) 返回，不要将返回值声明为 $const$。



![](https://github.com/RivTian/Cpp-Move-Semantics/blob/main/asserts/image-20231122151034186.png?raw=true)
