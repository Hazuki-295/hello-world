package courseExercises;

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */
import java.util.*;

public class IsItASubstring {
    public static void main(String[] args) {
        IsSubString iss = new IsSubString();
        Scanner scanner = new Scanner(System.in);
        // Get test cases.
        String str = scanner.nextLine();
        int t = Integer.parseInt(str);
        while (t-- > 0) {
            String sub = scanner.nextLine();
            String mother = scanner.nextLine();
            System.out.println(iss.isSubString(sub, mother));
        }
    }
}
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

class IsSubString {
    public boolean isSubString(String sub, String Mother) {
        int subLength = sub.length();
        int matchLength = 0;
        for (int i = 0; i < Mother.length(); i++) {
            if (Mother.charAt(i) == sub.charAt(matchLength)) { // 匹配
                matchLength++;
                if (matchLength == subLength) {
                    return true;
                }
            } else { // 失配
                matchLength = 0;
            }
        }
        return false;
    }
}