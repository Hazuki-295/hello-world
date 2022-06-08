import java.util.Scanner;

public class isNumericString {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (true) {
            System.out.print("Enter a numeric number: ");
            String line = input.nextLine();
            System.out.println("Is it matches the token? : " + isNumeric(line));
        }
    }

    /** Match a number with optional '-' and decimal. */
    public static boolean isNumeric(String str) {
        return str.matches("-?\\d+(\\.\\d+)?");
    }
}