1. static 全局变量与普通的全局变量有什么区别： static 全局变量只初使化一次，防止在其他文件单元中被引用;    
static 局部变量和普通局部变量有什么区别： 	static 局部变量只被初始化一次，下一次依据上一次结果值；  
static 函数与普通函数有什么区别： 			static 函数在内存中只有一份，普通函数在每个被调用中维持一份拷贝

2. 程序的局部变量存在于（堆栈）中，全局变量存在于（静态区 ）中，动态申请数据存在于（ 堆）中
union 与struct, see https://stackoverflow.com/questions/22844542/sizeofstruct-and-sizeofunion

3. sizeof vs strlen
sizeof()

Sizeof operator is a compile time unary operator which can be used to compute the size of its operand.

The result of sizeof is of unsigned integral type which is usually denoted by size_t.
sizeof can be applied to any data-type, including primitive types such as integer and floating-point types, pointer types, or compound datatypes such as Structure, union etc.
strlen()

strlen() is a predefined function in C whose definition is contained in the header file “string.h”.
4. 对于一个频繁使用的短小函数,在 C 语言中应用什么实现,在 C++中应用什么实现?
 c 用宏定义，c++用 inline 
5. 请问下面程序有什么错误?
int a[60][250][1000],i,j,k;
for(k=0;k<=1000;k++)
for(j=0;j<250;j++)
for(i=0;i<60;i++)
a[i][j][k]=0;
答: 把循环语句内外换一下
