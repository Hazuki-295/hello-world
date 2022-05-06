import java.util.Scanner;

public class ProblemC_Pyramid {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (input.hasNext()) {
            int pyramidSize = input.nextInt();
            for (int i = pyramidSize; i >= 1; i--) {
                printLine(i);
            }
        }
    }

    static void printLine(int num) {
        StringBuilder buffer = new StringBuilder();
        for (int i = num; i > 1; i--) { // left
            buffer.append(i).append(" ");
        }
        buffer.append(1).append(" ");
        for (int i = 2; i <= num; i++) { // right
            buffer.append(i).append(" ");
        }
        String result = buffer.toString().trim();
        System.out.println(result);
    }
}
