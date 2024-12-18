#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_LEN  100
/**
 * 《fscanf 与  fprintf  返回值不同》
 * fprintf  返回值  是 字节数
 * fscanf 正确执行 返回值是数组个数
 * 错误时 返回-1 EOF
*/
int main(int argc ,const char ** argv){
    char tmp_buf[BUF_LEN];
    //char read_form_file[BUF_LEN];
    char * filename = "1.txt" ;
    int fun_ret_data = 0;   // 用于暂时存储函数返回值
    FILE * fp =  fopen(filename,"w+");
    if(!fp){
        perror("fopen is error\n");
        return 1;
    }
    else {
        puts("fopen is success!!\n");
    }
    //输入要写入的数据 
    fun_ret_data = fscanf(stdin,"%s", tmp_buf);
    if(1 != fun_ret_data ){
        perror("获取字符串错误 \n");
    } 
    printf("fscanf  返回值 是 %d\n",fun_ret_data);
    //tmp_buf[strlen(tmp_buf)-1] = 0; 
    //将获取数据写入  FILE
    fun_ret_data = fprintf(fp,"%s",tmp_buf);
    if(1 != fun_ret_data ){
        perror("向文件写入数据错误\n");
    }
    printf("fprintf 返回值 是 %d\n",fun_ret_data);
    if( !memset(tmp_buf,0,BUF_LEN)){
        perror("memset is error!\n");
    } 
    //usleep(10000000);
    fseek(fp, 0, SEEK_SET);  // 将文件指针移到文件的开头
    //从文件中读取数据
    if(!fscanf(fp,"%s", tmp_buf)){
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