package programmingTest3;

import java.util.Arrays;
import java.util.Scanner;

public class ProblemB_NumberPyramid {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (input.hasNext()) {
            int factor = input.nextInt();
            int numOfLines = input.nextInt();

            int[] numbers = new int[numOfLines];
            numbers[0] = 1;
            for (int i = 1; i < numOfLines; i++) { // numbers on the left, contains the middle number
                numbers[i] = numbers[i - 1] * factor;
            }

            System.out.println("1"); // 第一行特判
            for (int i = 2; i <= numOfLines; i++) {
                int numOfNumbers = 2 * i - 1;
                int numOfLeftNumbers = numOfNumbers / 2;
                int[] leftNumber = Arrays.copyOfRange(numbers, 0, numOfLeftNumbers); // not contain middle number
                int middleNumber = numbers[numOfLeftNumbers];

                StringBuilder buffer = new StringBuilder();
                for (int j = 0; j < numOfLeftNumbers; j++) { // print left
                    buffer.append(leftNumber[j]).append(' ');
                }
                buffer.append(middleNumber).append(' ');
                for (int j = 0; j < numOfLeftNumbers; j++) { // print right
                    buffer.append(leftNumber[numOfLeftNumbers - 1 - j]).append(' ');
                }
                System.out.println(buffer.toString().trim());
            }
        }
    }
}