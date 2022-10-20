import java.net.*;
import java.io.*;

/* Client program requesting current date from server. (Figure 3.28) */
public class DateClient {
    public static void main(String[] args) {
        try {
            /* make connection to server socket */
            /* this could be changed to an IP name or address other than the localhost */
            Socket socket = new Socket("localhost", 6013);

            InputStream in = socket.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));

            /* read the date from the socket */
            String line;
            while ((line = bin.readLine()) != null) {
                System.out.println(line);
            }

            /* close the socket connection*/
            socket.close();
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}