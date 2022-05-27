package programmingTest2;

import java.util.Arrays;
import java.util.Scanner;

public class ProblemA_Taxes {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        double[] marginalTaxRate = {0.10, 0.15, 0.25, 0.28, 0.33, 0.35};
        int[][] threshold = new int[4][6];

        threshold[0] = new int[]{0, 8350, 33950, 82250, 171550, 372950};
        threshold[1] = new int[]{0, 16700, 67900, 137050, 208850, 372950};
        threshold[2] = new int[]{0, 8350, 33950, 68525, 104425, 186475};
        threshold[3] = new int[]{0, 11950, 45500, 117450, 190200, 372950};

        while (input.hasNext()) {
            int status = input.nextInt();
            int taxableIncome = input.nextInt();

            if (Arrays.binarySearch(new int[]{0, 1, 2, 3}, status) >= 0) {
                double sum = 0;
                for (int i = 5; i >= 0; i--) {  // i: index of max threshold
                    if (threshold[status][i] < taxableIncome) {
                        sum += (taxableIncome - threshold[status][i]) * marginalTaxRate[i];
                        for (int j = i; j >= 1; j--) {
                            sum += (threshold[status][j] - threshold[status][j - 1]) * marginalTaxRate[j - 1];
                        }
                        break;
                    }
                }
                System.out.printf("Tax is %.2f%n", sum);
            } else {
                System.out.printf("Error: invalid status%n");
            }
        }
    }
}
