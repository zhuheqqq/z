//爬楼梯,本质是斐波那契数列
int climbStairs(int n){
    int num0,num1,num2;
    num0=1,num1=2;
    if(n<=2){
        return n;
    }
    for(int i=3;i<=n;i++){
        num2=num0+num1;
        num0=num1;
        num1=num2;
    }
    return num2;
}
