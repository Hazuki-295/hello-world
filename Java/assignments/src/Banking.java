/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

import java.util.Scanner;

public class Banking {
    public static void main(String[] args) {
        Bank bank = new Bank();

        Scanner s = new Scanner(System.in);
        int t = s.nextInt();
        s.nextLine();
        while (t-- > 0) {
            String f = s.next();
            String l = s.next();
            s.nextLine();
            bank.addCustomer(f, l);
        }
        for (int i = 0; i < bank.getNumOfCustomers(); i++) {
            Customer customer = bank.getCustomer(i);
            System.out.println("Customer [" + (i + 1) + "] is "
                    + customer.getLastName() + ", " + customer.getFirstName());
        }
    }
}
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

class Bank {
    private Customer[] customers;
    private int numberOfCustomers;

    private final int maximumSize = 16;

    public Bank() {
        customers = new Customer[maximumSize];
    }

    public boolean addCustomer(String f, String l) {
        if (numberOfCustomers <= maximumSize) {
            customers[numberOfCustomers] = new Customer(f, l);
            numberOfCustomers++;
            return true;
        } else {
            return false;
        }
    }

    public int getNumOfCustomers() {
        return numberOfCustomers;
    }

    public Customer getCustomer(int index) {
        if (index < numberOfCustomers) {
            return customers[index];
        } else {
            return null;
        }
    }
}

class Account {
    private double balance;

    public Account(double init_balance) {
        balance = init_balance;
    }

    public double getBalance() {
        return balance;
    }

    public boolean deposit(double amt) {
        balance += amt;
        return true;
    }

    public boolean withdraw(double amt) {
        if (amt < balance) {
            balance -= amt;
            return true;
        } else {
            return false;
        }
    }
}

class Customer {
    private final String firstName;
    private final String lastName;

    private Account account;

    Customer(String f, String l) {
        firstName = f;
        lastName = l;
        account = new Account(0);
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public Account getAccount() {
        return account;
    }

    public void setAccount(Account acct) {
        account = acct;
    }
}