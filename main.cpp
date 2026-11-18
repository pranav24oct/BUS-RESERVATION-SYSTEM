#include <iostream>
#include <string>
#include <limits>
#include <exception>

#include "Passenger.h"
#include "Route.h"
#include "Schedule.h"
#include "Payment.h"
#include "Refund.h"
#include "BusOperator.h"
#include "Trip.h"
#include "Bus.h"
#include "Seat.h"
#include "Reservation.h"

using namespace std;

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& message) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value) {
            clearInput();
            return value;
        }

        cout << "Invalid input. Enter an integer.\n";
        cin.clear();
        clearInput();
    }
}

double readDouble(const string& message) {
    double value;

    while (true) {
        cout << message;

        if (cin >> value) {
            clearInput();

            if (value > 0) {
                return value;
            }
        } else {
            cin.clear();
            clearInput();
        }

        cout << "Enter a valid positive amount.\n";
    }
}

string readLine(const string& message) {
    string value;

    cout << message;
    getline(cin, value);

    return value;
}

int main() {

    Passenger passenger;
    Route route;
    Schedule schedule;
    Payment payment;
    Refund refund;
    BusOperator busOperator;
    Trip trip;
    Bus bus;
    Seat seat;
    Reservation reservation;

    bool passengerAdded = false;
    bool routeAdded = false;
    bool scheduleAdded = false;
    bool operatorAdded = false;
    bool tripAdded = false;
    bool busAdded = false;
    bool seatReserved = false;
    bool reservationAdded = false;
    bool paymentMade = false;
    bool refundAvailable = false;

    int bookingId = 1001;
    int selectedSeat = 0;

    double ticketPrice = 1200.0;

    int choice;

    do {
        cout << "\n========================================\n";
        cout << "       BUS RESERVATION SYSTEM\n";
        cout << "========================================\n";

        cout << "\n--- Passenger Management ---\n";
        cout << "1. Register Passenger\n";
        cout << "2. View Passenger\n";

        cout << "\n--- Route Management ---\n";
        cout << "3. Add Route\n";
        cout << "4. View Route\n";

        cout << "\n--- Schedule Management ---\n";
        cout << "5. Add Schedule\n";
        cout << "6. View Schedule\n";

        cout << "\n--- Bus Operator Management ---\n";
        cout << "7. Register Bus Operator\n";
        cout << "8. View Bus Operator\n";

        cout << "\n--- Trip Management ---\n";
        cout << "9. Create Trip\n";
        cout << "10. View Trip\n";

        cout << "\n--- Bus Management ---\n";
        cout << "11. Register Bus\n";
        cout << "12. View Bus\n";

        cout << "\n--- Seat Management ---\n";
        cout << "13. Check Seat Availability\n";
        cout << "14. View Seat Details\n";

        cout << "\n--- Reservation Management ---\n";
        cout << "15. Book Ticket / Create Reservation\n";
        cout << "16. View Reservation\n";
        cout << "17. Cancel Reservation\n";

        cout << "\n--- Payment and Refund ---\n";
        cout << "18. Make Payment\n";
        cout << "19. Process Refund\n";
        cout << "20. View Payment Details\n";
        cout << "21. View Refund Details\n";

        cout << "\n--- Administration ---\n";
        cout << "22. Bus Operator Admin Details\n";
        cout << "23. Trip Admin Details\n";
        cout << "24. Bus Admin Details\n";
        cout << "25. Seat Admin Details\n";
        cout << "26. Reservation Admin Details\n";

        cout << "\n--- OOP Concepts ---\n";
        cout << "27. Demonstrate OOP Concepts and Templates\n";
        cout << "28. Demonstrate Multithreading\n";

        cout << "\n0. Exit\n";

        cout << "\n========================================\n";

        choice = readInt("Enter your choice: ");

        try {

            switch (choice) {

                case 1: {
                    int id = readInt("Enter Passenger ID: ");

                    string name = readLine("Enter Passenger Name: ");
                    string phone = readLine("Enter Phone Number: ");
                    string email = readLine("Enter Email: ");

                    passenger = Passenger(id, name, phone, email);

                    passengerAdded = true;

                    cout << "\nPassenger registered successfully!\n";
                    break;
                }

                case 2: {
                    if (!passengerAdded) {
                        cout << "Register passenger first.\n";
                        break;
                    }

                    passenger.displayPassenger();
                    break;
                }

                case 3: {
                    int id = readInt("Enter Route ID: ");

                    string source = readLine("Enter Source: ");
                    string destination = readLine("Enter Destination: ");

                    double distance = readDouble("Enter Distance in KM: ");

                    route = Route(id, source, destination, distance);

                    routeAdded = true;

                    cout << "\nRoute added successfully!\n";
                    break;
                }

                case 4: {
                    if (!routeAdded) {
                        cout << "Add route first.\n";
                        break;
                    }

                    route.displayRoute();
                    break;
                }

                case 5: {
                    int id = readInt("Enter Schedule ID: ");

                    string departure = readLine("Enter Departure Time: ");
                    string arrival = readLine("Enter Arrival Time: ");
                    string date = readLine("Enter Date: ");

                    schedule = Schedule(id, departure, arrival, date);

                    scheduleAdded = true;

                    cout << "\nSchedule added successfully!\n";
                    break;
                }

                case 6: {
                    if (!scheduleAdded) {
                        cout << "Add schedule first.\n";
                        break;
                    }

                    schedule.displaySchedule();
                    break;
                }

                case 7: {
                    int id = readInt("Enter Operator ID: ");

                    string name = readLine("Enter Operator Name: ");
                    string company = readLine("Enter Company Name: ");
                    string phone = readLine("Enter Phone Number: ");

                    busOperator = BusOperator(id, name, company, phone);

                    operatorAdded = true;

                    cout << "\nBus Operator registered successfully!\n";
                    break;
                }

                case 8: {
                    if (!operatorAdded) {
                        cout << "Register bus operator first.\n";
                        break;
                    }

                    busOperator.displayOperator();
                    break;
                }

                case 9: {
                    if (!routeAdded || !scheduleAdded || !operatorAdded) {
                        cout << "Add Route, Schedule and Operator first.\n";
                        break;
                    }

                    int tripId = readInt("Enter Trip ID: ");
                    int busId = readInt("Enter Bus ID: ");
                    int totalSeats = readInt("Enter Total Seats: ");

                    trip = Trip(
                        tripId,
                        busId,
                        route.getRouteId(),
                        schedule.getScheduleId(),
                        busOperator.getOperatorId(),
                        totalSeats
                    );

                    tripAdded = true;

                    cout << "\nTrip created successfully!\n";
                    break;
                }

                case 10: {
                    if (!tripAdded) {
                        cout << "Create trip first.\n";
                        break;
                    }

                    trip.displayTrip();
                    trip.displayAvailableSeats();
                    break;
                }

                case 11: {
                    if (!tripAdded) {
                        cout << "Create trip first.\n";
                        break;
                    }

                    int id = readInt("Enter Bus ID: ");

                    if (id != trip.getBusId()) {
                        cout << "Bus ID must match the Trip Bus ID.\n";
                        break;
                    }

                    string registration = readLine("Enter Registration Number: ");
                    string type = readLine("Enter Bus Type: ");

                    int capacity = readInt("Enter Bus Capacity: ");

                    if (capacity != trip.getTotalSeats()) {
                        cout << "Bus capacity must match the trip seat capacity.\n";
                        break;
                    }

                    bus = Bus(id, registration, type, capacity);

                    busAdded = true;

                    cout << "\nBus registered successfully!\n";
                    cout << "Seats created: " << bus.getCapacity() << '\n';

                    break;
                }

                case 12: {
                    if (!busAdded) {
                        cout << "Register bus first.\n";
                        break;
                    }

                    bus.displayBus();
                    break;
                }

                case 13: {
                    if (!busAdded) {
                        cout << "Register bus first.\n";
                        break;
                    }

                    int seatNumber = readInt("Enter Seat Number: ");

                    if (seatNumber <= 0 || seatNumber > bus.getCapacity()) {
                        cout << "Invalid seat number.\n";
                        break;
                    }

                    if (bus.checkAvailability(seatNumber)) {
                        cout << "Seat " << seatNumber << " is Available.\n";
                    } else {
                        cout << "Seat " << seatNumber << " is Not Available.\n";
                    }

                    cout << "Total Available Seats: "
                         << bus.getAvailableSeats() << '\n';

                    break;
                }

                case 14: {
                    if (!busAdded) {
                        cout << "Register bus first.\n";
                        break;
                    }

                    int seatNumber = readInt("Enter Seat Number: ");

                    if (seatNumber <= 0 || seatNumber > bus.getCapacity()) {
                        cout << "Invalid seat number.\n";
                        break;
                    }

                    seat = Seat(bus.getBusId() * 1000 + seatNumber, seatNumber);

                    seat.displaySeat();

                    break;
                }

                case 15: {
                    if (!passengerAdded || !tripAdded || !busAdded) {
                        cout << "Register Passenger, create Trip and register Bus first.\n";
                        break;
                    }

                    if (reservationAdded && !refundAvailable) {
                        cout << "An active reservation already exists.\n";
                        break;
                    }

                    int seatNumber = readInt("Enter Seat Number to Book: ");

                    if (seatNumber <= 0 || seatNumber > bus.getCapacity()) {
                        cout << "Invalid seat number.\n";
                        break;
                    }

                    if (!bus.checkAvailability(seatNumber)) {
                        cout << "This seat is already reserved.\n";
                        break;
                    }

                    if (!trip.bookSeats(1)) {
                        cout << "No seats available in this trip.\n";
                        break;
                    }

                    bus.reserveSeat(seatNumber);

                    selectedSeat = seatNumber;

                    int seatId = bus.getBusId() * 1000 + seatNumber;

                    string bookingDate = readLine("Enter Booking Date: ");

                    reservation = Reservation(
                        bookingId,
                        passenger.getUserId(),
                        trip.getTripId(),
                        seatId,
                        bookingDate,
                        ticketPrice
                    );

                    reservationAdded = true;
                    seatReserved = true;
                    paymentMade = false;
                    refundAvailable = false;

                    cout << "\nReservation created successfully!\n";
                    cout << "Reservation Status: "
                         << reservation.getStatus() << '\n';

                    cout << "Booking Reference: "
                         << reservation.getBookingReference() << '\n';

                    cout << "Seat Number: " << selectedSeat << '\n';
                    cout << "Fare: Rs. " << ticketPrice << '\n';

                    cout << "\nPlease make payment to confirm your reservation.\n";

                    break;
                }

                case 16: {
                    if (!reservationAdded) {
                        cout << "Create a reservation first.\n";
                        break;
                    }

                    reservation.displayReservation();
                    break;
                }

                case 17: {
                    if (!reservationAdded || !seatReserved) {
                        cout << "No active reservation found.\n";
                        break;
                    }

                    if (reservation.getStatus() == "Cancelled") {
                        cout << "Reservation is already cancelled.\n";
                        break;
                    }

                    reservation.cancel();

                    bus.releaseSeat(selectedSeat);
                    trip.cancelSeats(1);

                    seatReserved = false;

                    if (paymentMade) {
                        refund.setRefund(ticketPrice, "Pending");
                        refundAvailable = true;
                    }

                    paymentMade = false;

                    cout << "\nReservation cancelled successfully!\n";

                    if (refundAvailable) {
                        cout << "You can now process the refund.\n";
                    }

                    break;
                }

                case 18: {
                    if (!reservationAdded || !seatReserved) {
                        cout << "Create an active reservation first.\n";
                        break;
                    }

                    if (paymentMade) {
                        cout << "Payment has already been completed.\n";
                        break;
                    }

                    string method = readLine(
                        "Enter Payment Method (UPI/Card/Net Banking): "
                    );

                    payment = Payment(bookingId, ticketPrice, method);

                    payment.makePayment();

                    paymentMade = true;

                    reservation.setPaymentId(payment.getPaymentId());
                    reservation.confirm();

                    cout << "\nPayment successful!\n";
                    cout << "Reservation confirmed successfully!\n";

                    break;
                }

                case 19: {
                    RefundFinally finallyGuard;

                    if (!refundAvailable) {
                        cout << "No refund is currently available.\n";
                        break;
                    }

                    refund = Refund(bookingId, ticketPrice, "Pending");

                    RefundRunnableTask task(&refund);

                    RefundRunnableExecutor executor;

                    cout << "\nStarting refund processing...\n";

                    executor.start(task);
                    executor.join();

                    if (refund.getStatus() == "Processed") {
                        cout << "\nRefund processed successfully!\n";

                        refundAvailable = false;
                    } else {
                        cout << "\nRefund processing was not successful.\n";
                    }

                    break;
                }

                case 20: {
                    if (!paymentMade) {
                        cout << "No successful payment found.\n";
                        break;
                    }

                    payment.displayPayment();
                    break;
                }

                case 21: {
                    if (!refundAvailable && refund.getRefundId() == 0) {
                        cout << "No refund details available.\n";
                        break;
                    }

                    refund.displayRefund();
                    break;
                }

                case 22: {
                    if (!operatorAdded) {
                        cout << "Register operator first.\n";
                        break;
                    }

                    BusOperatorAdmin::displayOperatorDetails(busOperator);
                    break;
                }

                case 23: {
                    if (!tripAdded) {
                        cout << "Create trip first.\n";
                        break;
                    }

                    TripAdmin::displayTripInfo(trip);
                    break;
                }

                case 24: {
                    if (!busAdded) {
                        cout << "Register bus first.\n";
                        break;
                    }

                    BusAdmin::displayBusDetails(bus);
                    break;
                }

                case 25: {
                    if (!busAdded || selectedSeat <= 0) {
                        cout << "Book or select a seat first.\n";
                        break;
                    }

                    SeatAdmin::displaySeatDetails(seat);
                    break;
                }

                case 26: {
                    if (!reservationAdded) {
                        cout << "Create reservation first.\n";
                        break;
                    }

                    ReservationAdmin::displayReservationDetails(reservation);
                    break;
                }

                case 27: {
                    cout << "\n========== OOP CONCEPT DEMONSTRATION ==========\n";

                    if (passengerAdded) {
                        User* userPointer = &passenger;

                        cout << "\nRuntime Polymorphism - Passenger:\n";
                        userPointer->displayRole();

                        int passengerId = static_cast<int>(passenger);
                        PassengerSummary passengerSummary =
                            static_cast<PassengerSummary>(passenger);

                        cout << "Passenger ID using conversion: "
                             << passengerId << '\n';

                        cout << "Passenger Summary: "
                             << passengerSummary.name << '\n';
                    }

                    if (routeAdded) {
                        RouteInterface* routePointer = &route;

                        cout << "\nRuntime Polymorphism - Route:\n";
                        routePointer->displayRoute();

                        RouteSummary routeSummary =
                            static_cast<RouteSummary>(route);

                        cout << "Route Summary ID: "
                             << routeSummary.routeId << '\n';
                    }

                    if (scheduleAdded) {
                        ScheduleInterface* schedulePointer = &schedule;

                        cout << "\nRuntime Polymorphism - Schedule:\n";
                        schedulePointer->displaySchedule();

                        ScheduleSummary scheduleSummary =
                            static_cast<ScheduleSummary>(schedule);

                        cout << "Schedule Summary ID: "
                             << scheduleSummary.scheduleId << '\n';
                    }

                    if (tripAdded) {
                        TripInterface* tripPointer = &trip;

                        cout << "\nRuntime Polymorphism - Trip:\n";
                        tripPointer->displayTrip();

                        TripSummary tripSummary =
                            static_cast<TripSummary>(trip);

                        cout << "Trip Summary ID: "
                             << tripSummary.tripId << '\n';
                    }

                    if (busAdded) {
                        BusInterface* busPointer = &bus;

                        cout << "\nRuntime Polymorphism - Bus:\n";
                        busPointer->displayBus();

                        BusSummary busSummary =
                            static_cast<BusSummary>(bus);

                        cout << "Bus Summary ID: "
                             << busSummary.busId << '\n';
                    }

                    if (reservationAdded) {
                        ReservationInterface* reservationPointer = &reservation;

                        cout << "\nRuntime Polymorphism - Reservation:\n";
                        reservationPointer->displayReservation();

                        ReservationSummary reservationSummary =
                            static_cast<ReservationSummary>(reservation);

                        cout << "Reservation Summary ID: "
                             << reservationSummary.reservationId << '\n';
                    }

                    if (paymentMade) {
                        PaymentInterface* paymentPointer = &payment;

                        cout << "\nRuntime Polymorphism - Payment:\n";
                        paymentPointer->displayPayment();

                        PaymentSummary paymentSummary =
                            static_cast<PaymentSummary>(payment);

                        cout << "Payment Amount: "
                             << paymentSummary.amount << '\n';
                    }

                    cout << "\n--- Function Templates ---\n";

                    cout << "Larger Passenger Value: "
                         << getLargerPassenger(10, 20) << '\n';

                    cout << "Larger Route Value: "
                         << getLargerRoute(10, 20) << '\n';

                    cout << "Larger Schedule Value: "
                         << getLargerSchedule(10, 20) << '\n';

                    cout << "Larger Trip Value: "
                         << getLargerTrip(10, 20) << '\n';

                    cout << "Larger Bus Value: "
                         << getLargerBus(10, 20) << '\n';

                    cout << "Larger Seat Value: "
                         << getLargerSeat(10, 20) << '\n';

                    cout << "Larger Reservation Value: "
                         << getLargerReservation(10, 20) << '\n';

                    cout << "Larger Payment Value: "
                         << getLargerPayment(10, 20) << '\n';

                    cout << "Larger Refund Value: "
                         << getLargerRefund(10, 20) << '\n';

                    cout << "Larger Operator Value: "
                         << getLargerOperator(10, 20) << '\n';

                    cout << "\n--- Class Templates ---\n";

                    PassengerStorage<int> passengerStorage(101);
                    RouteStorage<int> routeStorage(201);
                    ScheduleStorage<int> scheduleStorage(301);
                    TripStorage<int> tripStorage(401);
                    BusStorage<int> busStorage(501);
                    SeatStorage<int> seatStorage(5);
                    ReservationStorage<int> reservationStorage(1001);
                    PaymentStorage<int> paymentStorage(601);
                    RefundStorage<int> refundStorage(701);
                    OperatorStorage<int> operatorStorage(801);

                    passengerStorage.displayData();
                    routeStorage.displayData();
                    scheduleStorage.displayData();
                    tripStorage.displayData();
                    busStorage.displayData();
                    seatStorage.displayData();
                    reservationStorage.displayData();
                    paymentStorage.displayData();
                    refundStorage.displayData();
                    operatorStorage.displayData();

                    cout << "\n--- Static Members ---\n";

                    cout << "Passenger Count: "
                         << Passenger::getPassengerCount() << '\n';

                    cout << "Route Count: "
                         << Route::getRouteCount() << '\n';

                    cout << "Schedule Count: "
                         << Schedule::getScheduleCount() << '\n';

                    cout << "Trip Count: "
                         << Trip::getTripCount() << '\n';

                    cout << "Bus Count: "
                         << Bus::getBusCount() << '\n';

                    cout << "Seat Count: "
                         << Seat::getSeatCount() << '\n';

                    cout << "Reservation Count: "
                         << Reservation::getReservationCount() << '\n';

                    cout << "Payment Count: "
                         << Payment::getPaymentCount() << '\n';

                    cout << "Refund Count: "
                         << Refund::getRefundCount() << '\n';

                    cout << "Operator Count: "
                         << BusOperator::getOperatorCount() << '\n';

                    cout << "\n--- Operator Overloading ---\n";

                    if (passengerAdded) {
                        cout << passenger << '\n';
                    }

                    if (routeAdded) {
                        cout << route << '\n';
                    }

                    if (busAdded) {
                        cout << bus << '\n';
                    }

                    if (reservationAdded) {
                        cout << reservation << '\n';
                    }

                    cout << "\nOOP demonstration completed.\n";

                    break;
                }

                case 28: {
                    cout << "\n========== MULTITHREADING DEMONSTRATION ==========\n";

                    if (passengerAdded) {
                        cout << "\nPassenger Threads:\n";
                        demonstratePassengerThreads(passenger);
                    }

                    if (routeAdded) {
                        cout << "\nRoute Threads:\n";
                        demonstrateRouteThreads(route);
                    }

                    if (scheduleAdded) {
                        cout << "\nSchedule Threads:\n";
                        demonstrateScheduleThreads(schedule);
                    }

                    if (operatorAdded) {
                        cout << "\nOperator Threads:\n";
                        demonstrateOperatorThreads(busOperator);
                    }

                    if (tripAdded) {
                        cout << "\nTrip Threads:\n";
                        demonstrateTripThreads(trip);
                    }

                    if (busAdded) {
                        cout << "\nBus Threads:\n";
                        demonstrateBusThreads(bus);
                    }

                    if (busAdded && selectedSeat > 0) {
                        cout << "\nSeat Threads:\n";
                        demonstrateSeatThreads(seat);
                    }

                    if (reservationAdded) {
                        cout << "\nReservation Threads:\n";
                        demonstrateReservationThreads(reservation);
                    }

                    if (paymentMade) {
                        cout << "\nPayment Threads:\n";
                        demonstratePaymentThreads(payment);
                    }

                    cout << "\nMultithreading demonstration completed.\n";

                    break;
                }

                case 0:
                    cout << "\nThank you for using Bus Reservation System!\n";
                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        }
        catch (const PassengerException& e) {
            cout << "\nPassenger Error: " << e.what() << '\n';
        }
        catch (const RouteException& e) {
            cout << "\nRoute Error: " << e.what() << '\n';
        }
        catch (const ScheduleException& e) {
            cout << "\nSchedule Error: " << e.what() << '\n';
        }
        catch (const BusOperatorException& e) {
            cout << "\nBus Operator Error: " << e.what() << '\n';
        }
        catch (const TripException& e) {
            cout << "\nTrip Error: " << e.what() << '\n';
        }
        catch (const BusException& e) {
            cout << "\nBus Error: " << e.what() << '\n';
        }
        catch (const SeatException& e) {
            cout << "\nSeat Error: " << e.what() << '\n';
        }
        catch (const ReservationException& e) {
            cout << "\nReservation Error: " << e.what() << '\n';
        }
        catch (const PaymentException& e) {
            cout << "\nPayment Error: " << e.what() << '\n';
        }
        catch (const RefundException& e) {
            cout << "\nRefund Error: " << e.what() << '\n';
        }
        catch (const exception& e) {
            cout << "\nGeneral Error: " << e.what() << '\n';
        }

    } while (choice != 0);

    return 0;
}
