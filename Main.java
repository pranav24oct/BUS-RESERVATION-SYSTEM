import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.println(
            "===================================="
        );

        System.out.println(
            "       BUS RESERVATION SYSTEM"
        );

        System.out.println(
            "===================================="
        );

        // Passenger
        Passenger passenger = new Passenger(
            101,
            "Rahul",
            "9876543210",
            "rahul@gmail.com"
        );

        // Bus
        Bus bus = new Bus(
            501,
            "MH12AB1234",
            "Maharashtra Express",
            "AC",
            10
        );

        // Route
        Route route = new Route(
            301,
            "Mumbai",
            "Pune"
        );

        // Schedule
        Schedule schedule = new Schedule(
            701,
            "08:00 AM",
            "11:30 AM"
        );

        // Trip
        Trip trip = new Trip(
            801,
            "20-08-2026",
            bus,
            route
        );

        // Display information

        passenger.displayPassenger();

        bus.displayBus();

        route.displayRoute();

        schedule.displaySchedule();

        trip.displayTrip();

        // Display seats

        bus.displaySeats();

        // Reservation

        Reservation reservation =
                new Reservation();

        System.out.print(
            "\nEnter seat number to book: "
        );

        int seatNumber = sc.nextInt();

        boolean booked =
            reservation.createReservation(
                passenger,
                trip,
                seatNumber
            );

        if (booked) {

            reservation.displayReservation();

            System.out.println(
                "\nSeats after booking:"
            );

            bus.displaySeats();

            System.out.print(
                "\nDo you want to cancel booking? (y/n): "
            );

            char choice = sc.next().charAt(0);

            if (choice == 'y' || choice == 'Y') {

                reservation.cancelBooking();

                reservation.displayReservation();

                System.out.println(
                    "\nSeats after cancellation:"
                );

                bus.displaySeats();
            }
        }

        System.out.println(
            "\nThank you for using Bus Reservation System!"
        );

        sc.close();
    }
}