import java.io.File;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class TextIODemo {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner input = new Scanner(System.in);

        String directory = "./out/testIO/";
        File dir = new File(directory);
        if (dir.mkdirs()) {
            System.out.println("Creat directory: " + dir.getAbsolutePath());
        }
        String filename = "output.txt";
        File file = new File(dir, filename);

        try (PrintWriter output = new PrintWriter(file)) {
            // Write formatted output to the file
            System.out.println("Enter the contents of the file:");
            int numOfLines = 0;
            while (true) {
                try {
                    System.out.printf("[%d]: ", ++numOfLines);
                    String line = input.nextLine();
                    output.printf("[%d]: ", numOfLines);
                    output.println(line);
                } catch (NoSuchElementException ignored) {
                    break;
                }
            }
        }
        System.out.println("Success.");
        System.out.println();

        try (Scanner reader = new Scanner(file)) {
            // Read data from the file
            System.out.println("Contents read from the file:");
            while (reader.hasNextLine()) {
                System.out.println(reader.nextLine());
            }
        }
        System.out.println("Success.");
    }
}
