---
layout: article
title:  "mod 性质"
date: 2022-12-27 23:31:48 +0300
---
设 $Z_{[n]} = \{[0], [1], \cdots, [n - 1]\}$ - 为某数对 n 取模后得到的集合

## 欧拉函数 $\varphi (n)$

**欧拉函数**是不大于 n 且与 n 互为质数的自然数的数量。

$$
\varphi (n) = \lvert\{ x \in N: x \le n, gcd(x,n) = 1 \}\rvert
$$

$$
\begin{aligned}
&\varphi(1)=1\quad(1)\\
&\varphi(2)=1\quad(1)\\
&\varphi(3)=2\quad(1,2)\\
&\varphi(4)=2\quad(1,2)\\
&\varphi(5)=4\quad(1,2,3,4)\\
&\varphi(6)=2\quad(1,5)\\
&\varphi(8)=4\quad(1,3,5,7)
\end{aligned}
$$

## 欧拉函数的性质

令 $a,b,p \in N$

1. 如果 p 是质数，则 $\varphi (р) = р - 1$
2. $\forall \alpha \in N, \varphi (р^\alpha) = р^{\alpha-1}(р-1)$
3. 欧拉函数乘法:

   $$
   gcd (a,b) =1 \Rightarrow \varphi (a \cdot b)= \varphi (a) \cdot \varphi (b)
   $$
4. 如果将 $n = p_1^{\alpha_1}\cdot p_2^{\alpha_2}\cdot \cdots \cdot p_k^{\alpha_k}$ 因式分解，则

   $$
   \varphi (n) = p_1^{\alpha_1 -1}\cdot p_2^{\alpha_2 -1}\cdot \cdots \cdot p_k^{\alpha_k -1} \cdot (p_1-1)\cdot (p_2-1)\cdot \cdots \cdot (p_k-1)\cdot
   $$
5. 当 $n > 1$

   $$
   \varphi (n) = n \Pi_{p \mid n}(1-\frac 1 p)
   $$

   其中$p\mid n$表示乘积 $\Pi$ 的乘数是取自 $n$ 的所有质因数。

   $$
   \varphi(18)=18\cdot(1-\frac 1 2)\cdot (1-\frac 1 3)=6
   $$
6. 高斯恒等式

$$
\sum_{d \mid n} \varphi(d) = n
$$

表示 $n$ 的所有正因数之和的欧拉函数相加。

$$
18 = 1,18,2,9,3,6 \Rightarrow 1+6+1+6+2+2=18
$$

7. 根据上述性质计算欧拉函数
<input id="mod_eular"><button onclick="calcEularEvent()">计算</button>
<div id="mod_answer"></div>
<script>
const calcEularEvent = ()=>{
    let num = document.getElementById("mod_eular").value;
    let str = `&${num} = `;
    let ans = calcEular(num);
    for(let i in ans){
        str += `${i}^{${ans[i]}}+`
    }
    str = str.slice(0,str.length-1);
    str += `\\\\`;
    str += `&\\varphi(${num}) = `;
    eul = 1;
    if(num!=1)
        for(let i in ans){
            str += `${i}^{${ans[i]}-1}\\cdot(${i}-1)+`;
            eul *= Math.pow(i,ans[i]-1) * (i-1);
        }
    else str += `1+`;
    str = str.slice(0,str.length-1);
    str += `=${eul}`;
    str = `&\\varphi(${num})=${eul}\\\\${str}`
    document.getElementById("mod_answer").innerHTML = `$$\\begin{aligned}${str}\\end{aligned}$$`;
    MathJax.typeset();
}
const calcEular = (number) => {
    if(number == 1) return {1:1};
    let t = 1;
    let ans = {};
    while(number != 1 && t++)
        while(number%t==0 && (number /= t)){
            if(!(t in ans)) ans[t]=0;
            ans[t]++;
        }
    return ans;
}
</script>

## 欧拉定理

对于任何模数 n 存在 $\forall а \ge 1$ 与 n 互质，满足

$$
a^{\varphi (n)} = 1 (mod\ n)
$$

根据欧拉定理求整数的大次幂的余数

<input id="TEular_A" placeholder="A">
<input id="TEular_N" placeHolder="N"><br>
<button onclick="TEular_calc(this)">计算</button>

<script>
let gcd = (a,b) => {
    return a%b==0?b:gcd(b,a%b);
}
const TEular_calc = (element)=>{
    A = document.getElementById("TEular_A").value
    N = document.getElementById("TEular_N").value
    element.innerHTML = `$$\\begin{aligned}&${A}^{\\varphi(${N})}=${pow_mod(A,calcEularNumber(N),N)}(mod\\ ${N})\\\\&gcd(${A},${N})=${gcd(A,N)}\\end{aligned}$$`;
    MathJax.typeset();
}
const calcEularNumber = (num)=>{
    let t = 1;
    let ans = {};
    eul = 1;
    let number = num;
    while(number != 1 && t++){
        while(number%t==0 && (number /= t)){
            if(!(t in ans)) ans[t]=0;
            ans[t]++;
        }
    }
    for(let i in ans){
        eul *= Math.pow(i,ans[i]-1) * (i-1);
    }
    return eul;
}
</script>


## 费马小定理

取模数 $p$ 为质数，对于质数 $p$ 满足：

$$
\varphi (p) = p - 1
$$

存在 $\forall а \ge 1, p \nmid а$（$a,p$ 互质），满足：

$$
a^{p - 1} = 1 (mod\ p)
$$

存在 $\forall а \in N$ 满足：

$$
a^p = a (mod\ p)
$$

另外，费马小定理只是 p 为质数的必要条件而非充分条件。通过费马小定理检验整数是否是质数，如果不满足上式则 p 一定不是质数，如果满足上式则不能说明 p 一定是质数。

费马小定理测试

<input id="Fermat_A" placeholder="a">
<input id="Fermat_P" placeholder="p">
<button onclick="calcFermat()">计算</button>
<div id="Fermat_ans"></div>
<script>
const pow_mod = (x, y, mod) => {
    ret = 1;
    while(y-->0){
        ret *= x
        ret %= mod
    }
    return ret;
}
const calcFermat = ()=>{
    a = document.getElementById("Fermat_A").value;
    p = document.getElementById("Fermat_P").value;
    apmp = pow_mod(a,p,p);
    amp  = a%p;
    let Fermat_ans = `&a=${a}, p=${p}\\\\&a^p=${a}^{${p}} = ${apmp} (mod\\ ${p}), a=${a} = ${amp}(mod\\ ${p}) \\Rightarrow \\\\ &${apmp}${apmp == amp ? `\\equiv` : `\\neq`}${amp}(mod\\ ${p})`;
    document.getElementById("Fermat_ans").innerHTML = `计算结果：${apmp == amp ? `${p} 可能是质数` : `${p} 一定不是质数`}$$\\begin{aligned}${Fermat_ans}\\end{aligned}$$`;
    MathJax.typeset();
}
</script>

## 模数运算

令 $х, у \in Z, n \in N$，如果 $x-y$ 可以被 $n$ 整除，则 $x,y$ 对于模 $n$ 相等。

$$
х \equiv у\ (mod\ n)\Leftrightarrow х - у = tn,\ где\ t \in Z
$$

基本定理

1. 自反性 $a \equiv a(mod\ n)$;
2. 对称性 $a \equiv b(mod\ n) \Rightarrow b \equiv a(mod\ n)$;
3. 传递性 $a \equiv b(mod\ n) , b \equiv с(mod\ n) \Rightarrow a \equiv с(mod\ n)$;
4. $a \equiv b(mod\ n), k \in Z \Rightarrow ka \equiv kb(mod\ n)$;
5. $ka \equiv kb(mod\ n), НОД (k,n )=1 \Rightarrow a \equiv b(mod\ n)$;
6. $a \equiv b(mod\ n), k \in N \Rightarrow ka \equiv kb(mod\ kn)$;
7. $ka \equiv kb(mod\ kn), k,n \in N \Rightarrow a \equiv b(mod\ n)$;
8. $a \equiv b(mod\ n) , c \equiv d(mod\ n) \Rightarrow a\pm c \equiv b\pm d(mod\ n)$,
9. $a \equiv b(mod\ n) , c \equiv d(mod\ n) \Rightarrow ac \equiv bd(mod\ n)$;
10. $a \equiv b(mod\ n) \Rightarrow \forall k \in Z, k \ge 0 a^k\equiv b^k(mod\ n)$;
11. $a \equiv b(mod\ n), f(x) = c_0+c_1x+ \cdots +c_nx^n$ 整数系数多项式 $\Rightarrow f(a) \equiv f(b)(mod\ n)$;
12. $$
    a+c \equiv b(mod\ n) \Rightarrow a \equiv b - с(mod\ n)
    $$
13. 增添被模数 n 整除的项
    $$
    a \equiv b(mod\ n), k \in Z \Rightarrow a \pm kn \equiv b(mod\ n)
    $$
14. $a \equiv b(mod\ n)$, $n$ 被 $d > 0$ 整除 $\Rightarrow$ $a \equiv b(mod\ d)$;
