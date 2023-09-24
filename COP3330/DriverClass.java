//

import java.util.ArrayList;

public class DriverClass {
    public static void main(String[] args) {
        String fullName = "Erika T. Jones";
        String employeeNumber = "ej789";
        double payRate = 10.50, hoursWorked = 36.00;

        // TA will change the pay rate and the hours worked to test your code
        Employee e;
        e = new Employee(fullName, employeeNumber, payRate, hoursWorked);
        System.out.println(e); // To Test your toString method


        e.printCheck(); // This prints the check of Erika T. Jones
        /*
        Company company = new Company();
        company.hire ( new Employee ("Saeed Happy", "sh895" , 2 , 200) );
        company.hire (e);
        company.printCompanyInfo();
        company.hire( new Employee("Enrico Torres" , "et897" , 3 , 150) );

        //You may add as many employees to company as you want.
        //The TAs will add their own employees
        //Make sure that each employee of company has a unique employeeNumber
        company.printCheck("ab784");
        company.deleteEmployeesBySalary(256.36);
        company.reverseEmployees();
        System.out.println( company.SearchByName("WaLiD WiLLiAms") );
        company.printEmployees();
        System.out.println("Bye!");
        */
    }
}
//____________________________
class Employee {
    //Add the private attributes and the methods as mentioned above...
    private String fullName;
    private String employeeNumber;
    private double payRate;
    private double hoursWorked;


    //Constructor method
    public Employee(String fullName, String employeeNumber, double payRate, double hoursWorked) {
        setFullName(fullName);
        setEmployeeNumber(employeeNumber);
        setPayRate(payRate);
        setHoursWorked(hoursWorked);
    }

    //Setters
    public void setFullName(String fullName) {this.fullName = fullName;}
    public void setEmployeeNumber(String employeeNumber) {this.employeeNumber = employeeNumber;}
    public void setPayRate(double payRate) {this.payRate = payRate;}
    public void setHoursWorked(double hoursWorked) {this.hoursWorked = hoursWorked;}

    //Getters
    public String getFullName() {return fullName;}
    public String getEmployeeNumber() {return employeeNumber;}
    public double getPayRate() {return payRate;}
    public double getHoursWorked() {return hoursWorked;}

    @Override
    public String toString() {
        return "[" + employeeNumber + "/" + fullName + ", " + hoursWorked + " Hours @ " + payRate + " per hour]";
    }
    private double grossPay() {
        return (payRate * hoursWorked);
    }
    private double netPay() {
        return grossPay() * .94;
    }

    public void printCheck() {
        System.out.println("---------------------------------------------------------------------------");
        System.out.println("\t\tEmployee's name:\t\t" + getFullName());
        System.out.println("\t\tEmployee's number:\t\t" + getEmployeeNumber());
        System.out.println("\t\tHourly rate of pay:\t\t" + getPayRate());
        System.out.println("\t\tHours worked:\t\t\t" + getHoursWorked() + "\n");
        System.out.printf("\t\tTotal Gross Pay:%14.2f\n\n", grossPay());
        System.out.println("\t\tDeductions");
        System.out.printf("\t\tTax (6 %%):%19.2f\n\n", grossPay() - netPay());
        System.out.printf("\t\tNet Pay:%22.2f\n\n", netPay());
        System.out.println("---------------------------------------------------------------------------");
    }
}
//____________________________
class Company {
    private ArrayList<Employee> employeeList;
    private String companyName;
    private static String companyTaxId;

    //Add static Setters and Getters for companyTaxId. We assume that
    //all companies share the same companyTaxId and that may change
    //Add Setter and Getter for the companyName
    //No need to add a Setter and Getter for employeeList
    public Company() {
        employeeList = new ArrayList<>();
        companyName = "People's Place";
        companyTaxId = "v1rtua7C0mpan1";
    }
    public boolean hire ( Employee employee ) {
        //Add employee to employeeList
        //Note well that we can't add an employee whose employeeNumber already
        //assigned to another employee. In that case, this method returns false.
        //This method returns true otherwise
        return true;
    }
    public void printCompanyInfo() {
        //This method prints the company name, the tax id and the current number of employees
        //You may choose to print that any way you like!
    }
    public void printEmployees() {
        //This method prints all employees (One employee per line)
        //Note that you already have toString in Employee
    }
    public int countEmployees( double maxSalary ) {
        //This method returns the number of employees paid less than maxSalary
        return 0;
    }
    public boolean SearchByName (String fullName ) {
        //This method returns true if fullName exists as an employee.
        //It returns false otherwise
        //this is a not a case-sensitive search.
        return false;
    }
    public void reverseEmployees () {
        //This method reverses the order in which the employees were added to
        //the list. The last employee is swapped with the first employee, the
        //second last with the second and so on
    }
    public void deleteEmployeesBySalary (double targetSalary ) {
        //This method deletes all employees who are paid targetSalary as a gross //salary
    }
    public void printCheck ( String employeeNumber) {
        //This method prints the check of the employee whose employee number is
        //employeeNumber. It prints NO SUCH EMPLOYEE EXISTS if employeeNumber is
        //not a registered employee number.
    }
}
