package programmingTest2;

import java.util.Scanner;

public class ProblemC_FutureInvestmentValue {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (input.hasNext()) {
            double investmentAmount = input.nextDouble();
            double annualInterestRate = input.nextDouble() * 0.01;
            double monthlyInterestRate = annualInterestRate / 12;
            int numberOfYears = input.nextInt();

            double futureInvestmentValue = investmentAmount * Math.pow(1 + monthlyInterestRate, numberOfYears * 12);
            System.out.printf("%.2f\n", futureInvestmentValue);
        }
    }
}
