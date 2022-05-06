import java.util.Scanner;

public class ProblemA_PhoneKeyPads {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (input.hasNext()) {
            String originalString = input.nextLine().toLowerCase();
            StringBuilder buffer = new StringBuilder();

            outer:
            for (char c : originalString.toCharArray()) {
                switch (c) {
                    case 'a': case 'b': case 'c': buffer.append('2'); break;
                    case 'd': case 'e': case 'f': buffer.append('3'); break;
                    case 'g': case 'h': case 'i': buffer.append('4'); break;
                    case 'j': case 'k': case 'l': buffer.append('5'); break;
                    case 'm': case 'n': case 'o': buffer.append('6'); break;
                    case 'p': case 'q': case 'r': case 's': buffer.append('7'); break;
                    case 't': case 'u': case 'v': buffer.append('8'); break;
                    case 'w': case 'x': case 'y': case 'z': buffer.append('9'); break;
                    case ' ':
                        buffer.append('0');
                        break;
                    default: {
                        if (Character.isDigit(c)) {
                            buffer.append(c);
                        } else {
                            System.out.println("Invalid input");
                            break outer;
                        }
                    }
                }

                if (buffer.length() == originalString.length()) {
                    System.out.println(buffer);
                }
            }
        }
    }
}
