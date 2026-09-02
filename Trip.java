public class Trip {
    private int tripId;
    private String travelDate;

    private Bus bus;
    private Route route;

    public Trip(int tripId, String travelDate,
                Bus bus, Route route) {

        this.tripId = tripId;
        this.travelDate = travelDate;
        this.bus = bus;
        this.route = route;
    }

    public void displayTrip() {
        System.out.println("\n========== Trip ==========");
        System.out.println("Trip ID     : " + tripId);
        System.out.println("Travel Date : " + travelDate);

        System.out.println("Route       : "
                + route.getSource()
                + " -> "
                + route.getDestination());

        System.out.println("Bus         : "
                + bus.getBusName());

        System.out.println("===========================");
    }

    public Bus getBus() {
        return bus;
    }

    public Route getRoute() {
        return route;
    }
}