import java.util.*;

public class UniqueDigits {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int caseCount = input.nextInt();
        input.nextLine();

        for (int i = 0; i < caseCount; i++) {
            String line = input.nextLine();
            if (line.charAt(0) == '-') {
                line = line.substring(1, line.length());
            }
            Set<Character> set = new LinkedHashSet<>();
            for (char c : line.toCharArray()) {
                set.add(c);
            }
            for (char c : set) {
                System.out.print(c);
            }
            System.out.println();
        }
    }
}