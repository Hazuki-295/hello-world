package programmingTest3;

import java.util.Scanner;

public class ProblemA_DayOfTheWeek {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (input.hasNext()) {
            int year = input.nextInt();
            int month = input.nextInt();
            int day = input.nextInt();

            int q = day; // the day of the month
            int m = month; // the month
            if (month == 1 || month == 2) {
                m += 12;
                year--;
            }
            int j = year / 100; // integer division
            int k = year % 100; // the year of the century

            int h = (q + 26 * (m + 1) / 10 + k + k / 4 + j / 4 + 5 * j) % 7;
            String[] dayOfWeek = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
            System.out.println(dayOfWeek[h]);
        }
    }
}
