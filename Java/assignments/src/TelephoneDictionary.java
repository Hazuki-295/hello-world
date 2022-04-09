import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class TelephoneDictionary {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        // Get test cases.
        String str = input.nextLine();
        int t = Integer.parseInt(str);

        Map<String, Integer> treeMap = new TreeMap<>();
        while (t-- > 0) {
            String originalForm = input.nextLine();
            StringBuilder buffer = new StringBuilder();

            for (char c : originalForm.toCharArray()) {
                switch (c) {
                    case 'A': case 'B': case 'C': buffer.append('2'); break;
                    case 'D': case 'E': case 'F': buffer.append('3'); break;
                    case 'G': case 'H': case 'I': buffer.append('4'); break;
                    case 'J': case 'K': case 'L': buffer.append('5'); break;
                    case 'M': case 'N': case 'O': buffer.append('6'); break;
                    case 'P': case 'R': case 'S': buffer.append('7'); break;
                    case 'T': case 'U': case 'V': buffer.append('8'); break;
                    case 'W': case 'X': case 'Y': buffer.append('9'); break;
                    case '-': break;
                    default: buffer.append(c);
                }
            }
            buffer.insert(3, '-');
            String standardForm = buffer.toString();
            treeMap.put(standardForm, treeMap.getOrDefault(standardForm, 0) + 1);
        }

        treeMap.forEach((telephone, count) -> { if (count > 1) System.out.println(telephone + " " + count); });
    }
}
