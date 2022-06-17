package programmingTest3;

import java.util.Scanner;

public class ProblemC_ISBN13 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        outer:
        while (input.hasNext()) {
            String line = input.nextLine();
            if (line.length() != 12) {
                System.out.println("Invalid");
                continue;
            }
            StringBuilder buffer = new StringBuilder();
            int[] factor = {1, 3};
            int indexOfFactor = 0;
            int item = 0; // 12 位数字的加权和
            for (int i = 0; i < line.length(); i++) {
                if (!Character.isDigit(line.charAt(i))) {
                    System.out.println("Invalid");
                    continue outer;
                } else {
                    buffer.append(line.charAt(i));
                }
                item += factor[indexOfFactor] * (line.charAt(i) - '0');
                indexOfFactor = (indexOfFactor + 1) % 2;
            }
            int d13 = 10 - item % 10;
            buffer.append(d13 == 10 ? 0 : d13);
            System.out.println(buffer);
        }
    }
}