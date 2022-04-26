import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Thimbles {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        // Get test cases.
        String str = input.nextLine();
        int t = Integer.parseInt(str);

        while (t-- > 0) {
            Map<Integer, Boolean> hashMap = new HashMap<>();
            hashMap.put(1, true);
            hashMap.put(2, false);
            hashMap.put(3, false);

            int swapsCount = input.nextInt();
            while (swapsCount-- > 0) {
                String swap = input.next();
                int thimble1 = swap.charAt(0) - '0';
                int thimble2 = swap.charAt(2) - '0';

                boolean temp = hashMap.get(thimble1);
                hashMap.put(thimble1, hashMap.get(thimble2));
                hashMap.put(thimble2, temp);
            }

            hashMap.forEach((key, value) -> {
                if (value) System.out.println(key);
            });
        }
    }
}
