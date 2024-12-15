#include "ceshi.h"


int fun_add(int a ,int b){
    return (a+b);

}
int fun_sub(int a, int b){
    return ((a>=b) ? (a-b):(b-a));
}
int   chose_fun(int a, int b,int (*fun)(int ,int) ){
    return fun(a,b);
}
int  main(int argc, const char ** argv){
    char buf[100] = {0};
    int a = 0;
    int b = 0;
    int ret =0 ;
    scanf("%d %d",&a, &b);
    printf("get a = %d ,b= %d\n",a,b);
    if(strcmp(argv[0] ,"+")){
       ret  = chose_fun(a,b,fun_add);
        sprintf(buf,"the add =  %d",ret);
    }else if (strcmp(argv[0],"-")){
        ret = chose_fun(a,b,fun_sub);
         sprintf(buf,"the sub =  %d",ret );
    }

    puts(buf);
    return 0;
}
