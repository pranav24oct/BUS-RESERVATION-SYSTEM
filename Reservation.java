public class Reservation {

    private int reservationId;
    private String bookingReference;

    private Passenger passenger;
    private Trip trip;
    private Seat seat;

    private double fare;
    private String status;

    public Reservation() {
        status = "Pending";
    }

    public boolean createReservation(
            Passenger passenger,
            Trip trip,
            int seatNumber) {

        this.passenger = passenger;
        this.trip = trip;

        seat = trip.getBus().getSeat(seatNumber);

        if (seat == null) {
            System.out.println("Invalid seat number.");
            return false;
        }

        if (!seat.isAvailable()) {
            System.out.println("Seat is already reserved.");
            return false;
        }

        // Reserve seat
        seat.reserveSeat();

        reservationId = 1001;

        bookingReference = "BUS" + reservationId;

        calculateFare();

        // Payment
        Payment payment = new Payment(5001, fare);

        if (payment.processPayment()) {

            status = "Confirmed";

            System.out.println("\nBooking successful!");
            System.out.println(
                "Booking Reference : "
                + bookingReference
            );

            return true;
        }

        // If payment fails
        seat.releaseSeat();

        return false;
    }

    public void calculateFare() {
        fare = 500;
    }

    public void cancelBooking() {

        if (!status.equals("Confirmed")) {
            System.out.println(
                "Booking cannot be cancelled."
            );
            return;
        }

        // Release seat
        seat.releaseSeat();

        status = "Cancelled";

        // Refund
        Refund refund = new Refund(7001, fare);

        refund.processRefund();

        System.out.println(
            "\nBooking cancelled successfully."
        );
    }

    public void displayReservation() {

        System.out.println(
            "\n========== Reservation =========="
        );

        System.out.println(
            "Booking Reference : "
            + bookingReference
        );

        System.out.println(
            "Passenger         : "
            + passenger.getName()
        );

        System.out.println(
            "Fare              : Rs. "
            + fare
        );

        System.out.println(
            "Status            : "
            + status
        );

        if (seat != null) {
            System.out.println(
                "Seat Number       : "
                + seat.getSeatNumber()
            );
        }

        System.out.println(
            "================================="
        );
    }
}