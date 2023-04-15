public class OutsidePrintJob extends PrintJob {
    private int cost_in_cents;

    // Constructor
    public OutsidePrintJob(String name, int user_priority, int num_pages) {
        super(name, user_priority, num_pages);
    }

    // Getters
    public int getCostInCents() {
        return cost_in_cents;
    }

    // Setters
    public void setCostInCents(int cost_in_cents) {
        this.cost_in_cents = cost_in_cents;
    }

    // Returns cost of print job
    public int getJobCost() {
        return 10 * getNumPages();
    }

    // Returns string representation of print job
    public String toString() {
        return super.toString() + "\tCost: " + getJobCost() + " cents";
    }

}
