#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_LEN  100
int main(int argc ,const char ** argv){
    char tmp_buf[BUF_LEN];
    //char read_form_file[BUF_LEN];
    char * filename = "1.txt" ;
    FILE * fp =  fopen(filename,"w+");
    if(!fp){
        perror("fopen is error\n");
    }
    else {
        puts("fopen is success!!\n");
    }
    //输入要写入的数据 
    if(!fgets(tmp_buf,BUF_LEN, stdin)){
        perror("获取字符串错误 \n");
    } 
    //将获取数据写入  FILE
    if( fputs(tmp_buf,fp) == EOF ){
        perror("向文件写入数据错误\n");
    }
    if( !memset(tmp_buf,0,BUF_LEN)){
        perror("memset is error!\n");
    } 
    //usleep(10000000);
    fseek(fp, 0, SEEK_SET);  // 将文件指针移到文件的开头
    //从文件中读取数据
    if(!fgets(tmp_buf,BUF_LEN,fp)){
        perror("读取文件内数据错误");
    } 
    printf("从文件中读取到的字符串：%s\n",tmp_buf);
    //关闭文件
    if(fclose(fp)){
        perror("fclose is error!\n");
    }else {
        puts("fclose is success!\n");
    }
    return 0;
}