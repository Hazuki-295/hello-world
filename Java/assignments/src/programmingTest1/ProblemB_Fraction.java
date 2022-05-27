package programmingTest1;

import java.util.Scanner;

class InvalidParamException extends Exception {
    private Fraction model;

    InvalidParamException(Fraction model) {
        this.model = model;
    }

    public void printMessage() {
        System.out.println(model + ": Invalid Arguments");
    }
}

class Fraction {
    private int a, b;

    Fraction(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public int getA() {
        return a;
    }

    public int getB() {
        return b;
    }

    public String toString() {
        return "[" + a + "/" + b + "]";
    }

    public int[] solve() throws InvalidParamException {
        if (b == 0) {
            throw new InvalidParamException(this);
        }

        int[] result = new int[2];

        result[0] = Math.abs(a % b);
        result[1] = Math.abs(b);

        int gcd = 1;

        for (int i = 2; i <= result[0]; i++) {
            if (result[0] % i == 0 && result[1] % i == 0) {
                gcd = i; // update
            }
        }

        result[0] /= gcd;
        result[1] /= gcd;

        if ((double) a / b < 0) result[0] = -result[0];

        return result;
    }
}

public class ProblemB_Fraction {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (input.hasNext()) {
            String line = input.nextLine();
            int pos = line.indexOf("/");
            int a = Integer.parseInt(line.substring(0, pos));
            int b = Integer.parseInt(line.substring(pos + 1));

            Fraction test = new Fraction(a, b);
            try {
                int[] result = test.solve();
                if (result[0] == 0) {
                    System.out.println(0);
                } else {
                    System.out.println(result[0] + "/" + result[1]);
                }
            } catch (InvalidParamException ex) {
                ex.printMessage();
            }
        }
    }
}
