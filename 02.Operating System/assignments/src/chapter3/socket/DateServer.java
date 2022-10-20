import java.net.*;
import java.io.*;

/* Time-of-day server listening to port 6013. (Figure 3.27) */
public class DateServer {
    public static void main(String[] args) {
        try {
            ServerSocket socket = new ServerSocket(6013);

            /* now listen for connections */
            while (true) {
                Socket client = socket.accept();
                /* we have a connection */

                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

                /* write the Date to the socket */
                pout.println(new java.util.Date());

                /* close the socket and resume listening for more connections */
                client.close();
            }
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}