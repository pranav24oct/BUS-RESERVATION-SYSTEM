public class BusOperator {
    private int operatorId;
    private String name;
    private String phone;

    public BusOperator(int operatorId, String name, String phone) {
        this.operatorId = operatorId;
        this.name = name;
        this.phone = phone;
    }

    public void displayOperator() {
        System.out.println("\nBus Operator");
        System.out.println("ID    : " + operatorId);
        System.out.println("Name  : " + name);
        System.out.println("Phone : " + phone);
    }

    public void manageBus() {
        System.out.println("Bus management selected.");
    }

    public void manageSchedule() {
        System.out.println("Schedule management selected.");
    }

    public void manageRoute() {
        System.out.println("Route management selected.");
    }
}