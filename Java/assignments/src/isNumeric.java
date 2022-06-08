import java.util.Scanner;

public class isNumeric {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (true) {
            System.out.print("Enter a floating point number: ");
            String line = input.nextLine();
            System.out.println("Is it matches the token? : " + isNumeric(line));
        }
    }

    public static boolean isNumeric(String str) {
        return str.matches("-?\\d+(\\.\\d+)?");
    }
}