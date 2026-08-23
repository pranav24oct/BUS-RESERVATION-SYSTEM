public class Schedule {
    private int scheduleId;
    private String departureTime;
    private String arrivalTime;

    public Schedule(int scheduleId,
                    String departureTime,
                    String arrivalTime) {

        this.scheduleId = scheduleId;
        this.departureTime = departureTime;
        this.arrivalTime = arrivalTime;
    }

    public void displaySchedule() {
        System.out.println("\n========== Schedule ==========");
        System.out.println("Schedule ID : " + scheduleId);
        System.out.println("Departure   : " + departureTime);
        System.out.println("Arrival     : " + arrivalTime);
        System.out.println("==============================");
    }

    public void updateSchedule(String departure, String arrival) {
        this.departureTime = departure;
        this.arrivalTime = arrival;
    }
}