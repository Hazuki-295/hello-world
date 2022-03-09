import java.util.Scanner;

public class NextCharacter  {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        input.useDelimiter("");
        char ch = input.next().charAt(0);  // 读取一个字符，可以读入换行符'\n'
        input.reset();

        System.out.printf("ch = %c\n", ch);

        while (input.hasNext()) {
            String str = input.next();
            System.out.println(str);
        }
    }
}