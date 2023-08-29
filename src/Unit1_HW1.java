import java.util.Scanner;
public class Unit1_HW1 {
    public static void main(String[] args) {
        Scanner myScan = new Scanner (System.in);

        String studentId;
        String studentFullName;
        String firstClass;
        String secondClass;
        String[] courseCreds;
        int firstClassCrn, firstClassCredit, secondClassCrn, secondClassCredit;

        //Scan for user ID and name
        System.out.printf("Enter the Student's Id: ");
        studentId = myScan.nextLine();

        System.out.printf("Enter the Student's full name: ");
        studentFullName = myScan.nextLine();

        //Gather class information
        System.out.println(" ");
        System.out.printf("Enter crn/credit hours for the first class (like 5665/3): ");
        firstClass = myScan.nextLine();
        courseCreds = firstClass.split("/");
        firstClassCrn = Integer.parseInt(courseCreds[0]);
        firstClassCredit = Integer.parseInt(courseCreds[1]);

        System.out.printf("Enter crn/credit hours for the second class (like 5665/3): ");
        secondClass = myScan.nextLine();
        courseCreds = secondClass.split("/");
        secondClassCrn = Integer.parseInt(courseCreds[0]);
        secondClassCredit = Integer.parseInt(courseCreds[1]);

        //Fee Invoice
        double firstClassTotal = firstClassCredit * 120.25;
        double secondClassTotal = secondClassCredit * 120.25;
        double total = firstClassTotal + secondClassTotal + 35.00;
        {
            //Fee invoice header
            System.out.println(" ");
            System.out.println("Thank you!\n\nUNIVERSITY OF EXAMPLE TOWN\nEXAMPLE FL 10101");
            System.out.println("*************************\n");
            System.out.println("Fee invoice prepared for:\n" + "[" + studentFullName + "][" + studentId + "]\n");
            System.out.println("1 Credit Hour = $120.25\n");
            System.out.println("CRN\t\tCREDIT HOURS");

            //Totals for class credit and fees
            System.out.printf("%d\t%-24d$%.2f\n", firstClassCrn, firstClassCredit, firstClassTotal);
            System.out.printf("%d\t%-24d$%.2f\n", secondClassCrn, secondClassCredit, secondClassTotal);
            System.out.println("\t\tHealth & id fees\t\t$35.00\n");

            //Total cost for all fees
            System.out.println("****************************************");
            System.out.printf("\t\tTotal Payments\t\t\t$%.2f\n", total);
        }
    }
}