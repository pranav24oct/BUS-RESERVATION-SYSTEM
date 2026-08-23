public class Seat {
    private int seatNumber;
    private String status;

    public Seat(int seatNumber) {
        this.seatNumber = seatNumber;
        this.status = "Available";
    }

    public boolean isAvailable() {
        return status.equals("Available");
    }

    public void reserveSeat() {
        status = "Reserved";
    }

    public void releaseSeat() {
        status = "Available";
    }

    public int getSeatNumber() {
        return seatNumber;
    }

    public String getStatus() {
        return status;
    }
}