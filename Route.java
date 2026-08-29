public class Route {
    private int routeId;
    private String source;
    private String destination;
    private boolean active;

    public Route(int routeId, String source, String destination) {
        this.routeId = routeId;
        this.source = source;
        this.destination = destination;
        this.active = true;
    }

    public void displayRoute() {
        System.out.println("\n========== Route ==========");
        System.out.println("Route ID    : " + routeId);
        System.out.println("Source      : " + source);
        System.out.println("Destination : " + destination);
        System.out.println("Status      : "
                + (active ? "Active" : "Inactive"));
        System.out.println("============================");
    }

    public boolean validateRoute() {
        return active && !source.equals(destination);
    }

    public String getSource() {
        return source;
    }

    public String getDestination() {
        return destination;
    }

    public int getRouteId() {
        return routeId;
    }
}