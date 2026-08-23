import java.util.ArrayList;

public class Bus {
    private int busId;
    private String busNumber;
    private String busName;
    private String busType;
    private int totalSeats;

    private ArrayList<Seat> seats;

    public Bus(int busId, String busNumber, String busName,
               String busType, int totalSeats) {

        this.busId = busId;
        this.busNumber = busNumber;
        this.busName = busName;
        this.busType = busType;
        this.totalSeats = totalSeats;

        seats = new ArrayList<>();

        for (int i = 1; i <= totalSeats; i++) {
            seats.add(new Seat(i));
        }
    }

    public void displayBus() {
        System.out.println("\n========== Bus Details ==========");
        System.out.println("Bus ID      : " + busId);
        System.out.println("Bus Number  : " + busNumber);
        System.out.println("Bus Name    : " + busName);
        System.out.println("Bus Type    : " + busType);
        System.out.println("Total Seats : " + totalSeats);
        System.out.println("=================================");
    }

    public void displaySeats() {
        System.out.println("\nSeat Status:");

        for (Seat seat : seats) {
            System.out.println(
                "Seat " + seat.getSeatNumber()
                + " : " + seat.getStatus()
            );
        }
    }

    public Seat getSeat(int seatNumber) {
        if (seatNumber >= 1 && seatNumber <= totalSeats) {
            return seats.get(seatNumber - 1);
        }

        return null;
    }

    public String getBusName() {
        return busName;
    }

    public int getBusId() {
        return busId;
    }
}