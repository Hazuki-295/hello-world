package courseExercises;

import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

public class GiftGivers {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int numOfMember = input.nextInt();
        Map<String, Integer> map = new LinkedHashMap<>();
        for (int i = 0; i < numOfMember; i++) {
            map.put(input.next(), 0);
        }

        for (int i = 0; i < numOfMember; i++) {
            String givenName = input.next();
            int initialMoney = input.nextInt();
            int numOfFriends = input.nextInt();

            if (numOfFriends == 0) continue;
            int givenForEach = initialMoney / numOfFriends;
            int remainMoney = (-initialMoney) + initialMoney % numOfFriends;
            map.put(givenName, map.get(givenName) + remainMoney);
            for (int j = 0; j < numOfFriends; j++) {
                String receivedName = input.next();
                map.put(receivedName, map.get(receivedName) + givenForEach);
            }
        }

        // output
        map.forEach((name, money) -> System.out.println(name + ' ' + money));
    }
}
