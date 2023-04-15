import java.util.Scanner;
import java.io.File;

public class Printer {
    public static void main(String[] args) {
        Scanner scanner;
        try {
            scanner = new Scanner(new File("input.txt"));
        } catch (Exception e) {
            System.out.println(e);
            return;
        }
        BinaryHeap<PrintJob> queue = new BinaryHeap<PrintJob>();

        // read line by line from input.txt
        while (scanner.hasNext()) {

            // read name, user_priority, num_pages, and inside/outside in order
            String name = scanner.next();
            int user_priority = scanner.nextInt();
            int num_pages = scanner.nextInt();
            String outside = scanner.next();
            boolean outside_bool = outside.equals("O") ? true : false;

            // create print job based on inside/outside
            PrintJob print_job = outside_bool ? new OutsidePrintJob(name, user_priority, num_pages)
                    : new PrintJob(name, user_priority, num_pages);

            // Add print job to queue
            queue.insert(print_job);

        }
        scanner.close();

        // Now deleteMin each object while printing it
        while (!queue.isEmpty()) {
            PrintJob print_job = queue.deleteMin();
            if (print_job instanceof OutsidePrintJob) {
                OutsidePrintJob outside_print_job = (OutsidePrintJob) print_job;
                System.out.println(outside_print_job);
            } else {
                System.out.println(print_job);
            }
        }
    }
}
