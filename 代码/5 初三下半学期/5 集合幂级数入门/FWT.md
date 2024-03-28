# FWT 基础

## 位运算卷积

定义位运算卷积：第 $i$ 项和第 $j$ 项的乘积贡献到第 $i*j$ 项，其中，$*$ 代表某种位运算 (And,Or,Xor) 。

即 $S_k=\sum_{i\oplus j=k}A_iB_j$，记作 $S=A*B$

## 构造

现在有两个序列 $A$，$B$，我们要求 $A*B$。

我们期望把位运算卷积转化成点积。

设 $FWT(A)$ 是 $A$ 经过 $FWT$ 变换后得到的序列。

我们要求：$A*B=C\Longleftrightarrow FWT(A)\times FWT(B)=FWT(C)$（对应位置点乘）。

我们希望 $FWT$ 为线性的。

我们设 $c(i,j)$ 为变换系数，即 $A_j$ 对 $FWT(A)_i$ 的贡献系数。

那么 $FWT(A)_i=\sum\limits_{j=0}^{n-1}c(i,j)A_j$

根据 $FWT(A)·FWT(B)=FWT(C)$ ,得到 :

$$
\begin{aligned}
FWT(A)[i]FWT(B)[i]&=FWT(C)[i]\\
\sum\limits_{j=0}^{n-1}c(i,j)A[j]\sum\limits_{k=0}^{n-1}c(i,k)B[k]&=\sum\limits_{p=0}^{n-1}c(i,p)C[p]\\
\sum\limits_{j=0}^{n-1}\sum\limits_{k=0}^{n-1}c(i,j)c(i,k)A[j]B[k]&=\sum\limits_{p=0}^{n-1}c(i,p)C[p]
\end{aligned}
$$

根据 $A*B=C$，又能得到 :

$$ C[p]=\sum\limits_{t_1⊕t_2=p}A[t_1]B[t_2]$$

所以：

$$\sum\limits_{p=0}^{n-1}c(i,p)C[p]=\sum\limits_{p=0}^{n-1}c(i,p)\sum\limits_{t_1⊕t_2=p}A[t_1]B[t_2]=\sum\limits_{p=0}^{n-1}\sum\limits_{t_1⊕t_2=p}A[t_1]B[t_2]c(i,p)$$

那么：

$$\sum\limits_{j=0}^{n-1}\sum\limits_{k=0}^{n-1}c(i,j)c(i,k)A[j]B[k]=\sum\limits_{p=0}^{n-1}c(i,p)C[p]=\sum\limits_{p=0}^{n-1}\sum\limits_{t_1⊕t_2=p}A[t_1]B[t_2]c(i,p)$$

最后：

$$
\sum\limits_{j=0}^{n-1}\sum\limits_{k=0}^{n-1}c(i,j)c(i,k)A[j]B[k]=\sum\limits_{p=0}^{n-1}\sum\limits_{t_1⊕t_2=p}A[t_1]B[t_2]c(i,p)=\sum\limits_{t_1=0}^{n-1}\sum\limits_{t_2=0}^{n-1}A[t_1]B[t_2]c(i,t_1⊕t_2)
$$

两者相对比，我们发现，只要求 $c(i,j)c(i,k)=c(i,j⊕k)$ 即可。

由于位运算每位的独立性，我们可以分为考虑。

也就是说，对于二进制的第 $t$ 位，我们需要满足 $c(i_t,j_t)c(i_t,k_t)=c(i_t,j_t\oplus k_t)$

------------

由于不同的运算的 $c$ 不同，所以我们先放一放，看看如果我们知道了 $c$，怎么求 $FWT$。

已知：$FWT(A)_i=\sum\limits_{j=0}^{n-1}c(i,j)A_j$

如果直接暴力，为 $O(n^2)$

我们考虑**按位拆半**：

设 $i'$ 为 $i$ 去掉二进制首位剩下的数。

$$
\begin{aligned}
FWT(A)_i&=\sum\limits_{j=0}^{n-1}c(i,j)A[j]\\
&=\sum\limits_{j=0}^{(n/2)-1}c(i,j)A[j]+\sum\limits_{j=(n/2)}^{n-1}c(i,j)A[j]\\
&=\sum\limits_{j=0}^{(n/2)-1}c(i_0,j_0)c(i',j')A[j]+\sum\limits_{j=(n/2)}^{n-1}c(i_0,j_0)c(i',j')A[j]\\
&=c(i_0,0)\sum\limits_{j=0}^{(n/2)-1}c(i',j')A[j]+c(i_0,1)\sum\limits_{j=(n/2)}^{n-1}c(i',j')A[j]
\end{aligned}
$$

那么这样规模就减半了。

设序列前半为 $A_0$，后半段为 $A_1$。

若 $i_0=0$，则：

$FWT(A)[i]=c(0,0)FWT(A_0)[i]+c(0,1)FWT(A_1)[i]\quad \big(i\in[0,n/2)\big)$

若 $i_0=1$，则:

$FWT(A)[i+(n/2)]=c(1,0)FWT(A_0)[i]+c(1,1)FWT(A_1)[i]\quad \big(i\in[0,n/2)\big)$

可以使用 $O(n)$ 的代价合并。

若 $n=2^m$，则时间复杂度为 $O(m2^m)$

## 基础位运算卷积

由于不会推，所以直接给结论。

由于我们最后求的是 $FWT(A*B)$，但我们要求 $A*B$，因此还需要来一个函数 $IFWT(FWT(A*B))=A*B$。即 $IFWT$ 为 $FWT$ 的逆运算。

具体的算法只需要将 $c$ 求逆作为 $IFWT$ 的 $c$ 即可。

设位矩阵  $c=\begin{bmatrix}c(0,0)\quad c(0,1)\\c(1,0)\quad c(1,1)\end{bmatrix}$

### Or 卷积

$c=\begin{bmatrix}1\quad 0\\1\quad 1\end{bmatrix}$

逆矩阵 $c'=\begin{bmatrix}1&\quad 0\\-1&\quad 1\end{bmatrix}$

$FWT(A)[i]=FWT(A_0)[i]$

$FWT(A)[i+(n/2)]=FWT(A_0)[i]+FWT(A_1)[i]$

---------

$IFWT(A)[i]=IFWT(A_0)[i]$

$IFWT(A)[i+(n/2)]=IFWT(A_1)[i]-IFWT(A_0)[i]$

###  And 卷积

$c=\begin{bmatrix}1&\quad 1\\0&\quad 1\end{bmatrix}$

逆矩阵 $c'=\begin{bmatrix}1&\quad -1\\0&\quad 1\end{bmatrix}$

$FWT(A)[i]=FWT(A_0)[i]+FWT(A_1)[i]$

$FWT(A)[i+(n/2)]=FWT(A_1)[i]$

---------

$IFWT(A)[i]=IFWT(A_0)[i]-IFWT(A_1)[i]$

$IFWT(A)[i+(n/2)]=IFWT(A_1)[i]$

### Xor 卷积

$c=\begin{bmatrix}1&\quad 1\\1&\quad -1\end{bmatrix}$

逆矩阵 $c'=\begin{bmatrix}0.5&\quad 0.5\\0.5&\quad -0.5\end{bmatrix}$

$FWT(A)_i=FWT(A_0)_i+FWT(A_1)_i$

$FWT(A)_{i+(n/2)}=FWT(A_0)_i-FWT(A_1)_{i}$

---------

$IFWT(A)_i=\dfrac{IFWT(A_0)_i+IFWT(A_1)_i}{2}$

$IFWT(A)_{i+(n/2)}=\dfrac{IFWT(A_0)_i-IFWT(A_1)_i}{2}$