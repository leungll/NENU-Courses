> 题目：编写一个成绩排名程序。首先从一个文件中读入一组学生的姓名、学号和成绩，其中，姓名为一个字符串，学号为一个整数，成绩为一个实数，每位学生的信息占用一行，如“Yueying 20050923 95.5”。然后对这些学生的成绩进行排序，并将排序后的结果保存在另一个文件中。在该文件中，除了原有的姓名、学号和成绩以外，再增加排名信息。

```
import java.io.*;
import java.util.*;
 
public class Test5 {
    
    static int num = 0;
    
    public static void main(String[] args) throws FileNotFoundException{
        //读入"student.txt"文件
        Scanner input = new Scanner(new File("student.txt"));
        double []arr = new double[100];
        while(input.hasNext()){
            if(input.hasNextDouble()){
                //将文件内容存入数组中
                arr[num++] = input.nextDouble();
            }
            else input.next();
        }
        System.out.print("学生成绩分别为");
        //打印学生为排名成绩
        for(int i = 0;i < num;i++){
            System.out.print(" " + arr[i]);
        }
        try{
            //复制"student.txt"内容并粘贴到新文件"newDemo.txt"中
            FileReader fr = new FileReader("student.txt");
            FileWriter fw = new FileWriter("newDemo.txt");
            int ch;
            while((ch = fr.read()) != -1){
                fw.write(ch);
            }
            fr.close();
            fw.close();
            //保证在"newDemo.txt"新添加的内容不覆盖原来的内容
            FileOutputStream fos = new FileOutputStream("newDemo.txt",true);
            fos.write(sort(arr).getBytes());
            fos.close();//关闭文件流
        }catch(IOException ex){
            System.out.println("无法打开文件!");
        }
    }
    
    //将学生成绩进行排序
    public static String sort(double score[]){
        int i;
        String str = "\r\n成绩排名为: ";
        for(i = num - 2;i >= 0;i--){
            for(int j = 0;j <= i;j++){
                if(score[j] < score[j+1]){
                    double temp;
                    temp = score[j];
                    score[j] = score[j+1];
                    score[j+1] = temp;
                }
            }
        }
        for(int n = 0;n < num;n++){
            str += score[n] + " ";
        }
        return str;
    }
}
```