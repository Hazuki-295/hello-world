import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.MalformedURLException;
import java.net.Proxy;
import java.net.URL;
import java.util.Scanner;

public class ReadFileFromURL {
    public static void main(String[] args) {
        System.out.print("Enter a URL: ");
        String URLString = new Scanner(System.in).next();

        try {
            URL url = new URL(URLString);
            // Scanner input = new Scanner(url.openStream());
            Scanner input = new Scanner(url.openConnection(new Proxy(Proxy.Type.HTTP,
                    new InetSocketAddress("127.0.0.1", 11000))).getInputStream());

            StringBuffer buffer = new StringBuffer();
            while (input.hasNext()) {
                buffer.append(input.nextLine()).append('\n');
            }

            System.out.println("The file size is " + buffer.length() + " characters.");
            System.out.println("Print the content:");
            System.out.println();
            System.out.println(buffer);
        } catch (MalformedURLException ex) {
            System.out.println("Invalid URL.");
        } catch (IOException ex) {
            System.out.println("IO Errors.");
        }
    }
}
