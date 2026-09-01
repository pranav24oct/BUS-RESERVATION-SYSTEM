public class Payment {
    private int paymentId;
    private double amount;
    private String status;

    public Payment(int paymentId, double amount) {
        this.paymentId = paymentId;
        this.amount = amount;
        this.status = "Pending";
    }

    public boolean processPayment() {

        System.out.println("\nProcessing payment of Rs. "
                + amount + "...");

        status = "Successful";

        System.out.println("Payment successful!");

        return true;
    }

    public void displayPayment() {
        System.out.println("\n========== Payment ==========");
        System.out.println("Payment ID : " + paymentId);
        System.out.println("Amount     : Rs. " + amount);
        System.out.println("Status     : " + status);
        System.out.println("=============================");
    }

    public String getStatus() {
        return status;
    }
}