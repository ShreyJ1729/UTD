public class PrintJob implements Comparable<PrintJob> {
    private String name;
    private int user_priority;
    private int num_pages;

    // Constructor
    public PrintJob(String name, int user_priority, int num_pages) {
        this.name = name;
        this.user_priority = user_priority;
        this.num_pages = num_pages;
    }

    // Getters
    public String getName() {
        return name;
    }

    public int getUserPriority() {
        return user_priority;
    }

    public int getNumPages() {
        return num_pages;
    }

    // Setters
    public void setUserPriority(int user_priority) {
        this.user_priority = user_priority;
    }

    public void setNumPages(int num_pages) {
        this.num_pages = num_pages;
    }

    // Returns the job priority
    public int getJobPriority() {
        return user_priority * num_pages;
    }

    // Compares two print jobs
    public int compareTo(PrintJob other) {
        if (this.getJobPriority() > other.getJobPriority()) {
            return 1;
        } else if (this.getJobPriority() < other.getJobPriority()) {
            return -1;
        } else {
            return 0;
        }
    }

    // Returns string representation of print job
    public String toString() {
        return "Name: " + getName() + "\tUser Priority: " + getUserPriority() + "\tNumber of Pages: "
                + getNumPages();
    }
}
