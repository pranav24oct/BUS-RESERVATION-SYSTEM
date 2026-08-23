public class Passenger {
    private int passengerId;
    private String name;
    private String phone;
    private String email;

    public Passenger() {
    }

    public Passenger(int passengerId, String name, String phone, String email) {
        this.passengerId = passengerId;
        this.name = name;
        this.phone = phone;
        this.email = email;
    }

    public void displayPassenger() {
        System.out.println("\n========== Passenger ==========");
        System.out.println("Passenger ID : " + passengerId);
        System.out.println("Name         : " + name);
        System.out.println("Phone        : " + phone);
        System.out.println("Email        : " + email);
        System.out.println("===============================");
    }

    public String getName() {
        return name;
    }
}