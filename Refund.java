public class Refund {
    private int refundId;
    private double amount;
    private String status;

    public Refund(int refundId, double amount) {
        this.refundId = refundId;
        this.amount = amount;
        this.status = "Pending";
    }

    public void processRefund() {
        status = "Processed";

        System.out.println(
            "\nRefund of Rs. " + amount +
            " processed successfully."
        );
    }

    public void displayRefund() {
        System.out.println("\n========== Refund ==========");
        System.out.println("Refund ID : " + refundId);
        System.out.println("Amount    : Rs. " + amount);
        System.out.println("Status    : " + status);
        System.out.println("============================");
    }
}