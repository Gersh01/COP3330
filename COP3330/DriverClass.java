//Alexander Gershfeld and Gabriel Perez
//Unit 4 Homework 2
//COP3330C
//Hatim Boustique
//9-24-2023

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

        Company company = new Company();
        company.hire ( new Employee ("Saeed Happy", "sh895" , 2 , 200) );
        company.hire (e);
        company.printCompanyInfo();
        company.hire( new Employee("Enrico Torres" , "et897" , 3 , 150) );
        company.printEmployees();
        System.out.println(company.countEmployees(10000));

        //You may add as many employees to company as you want.
        //The TAs will add their own employees
        //Make sure that each employee of company has a unique employeeNumber

        company.printCheck("ab784");
        company.deleteEmployeesBySalary(378.00);
        company.reverseEmployees();
        company.printEmployees();


        System.out.println( company.SearchByName("WaLiD WiLLiAms") );
        System.out.println(company.countEmployees(10000));
        company.printEmployees();
        System.out.println("Bye!");

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

    //Whenever an employee's address is called, return this string; otherwise if called do the same
    @Override
    public String toString() {
        return "[" + employeeNumber + "/" + fullName + ", " + hoursWorked + " Hours @ " + payRate + " per hour]";
    }

    //Returns the product of payRate and hoursWorked
    public double grossPay() {
        return (payRate * hoursWorked);
    }

    //Returns the result of grossPay and calculates the net pay at a 6% tax
    private double netPay() {
        return grossPay() * .94;
    }

    //Prints the check of specified employee
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

    //Initializes the company class
    public Company() {
        employeeList = new ArrayList<>();
        companyName = "People's Place";
        companyTaxId = "v1rtua7C0mpan1";
    }

    //Setter for the company fields
    public void setCompanyName(String companyName) {this.companyName = companyName;}
    public static void setCompanyTaxId(String companyTaxId) {Company.companyTaxId = companyTaxId;}

    //Getters to return the company fields
    public String getCompanyName() {return companyName;}
    public static String getCompanyTaxId() {return companyTaxId;}

    //Searches to see if the employee number of the new employee conflicts with others,
    //if not adds to the company array
    public boolean hire ( Employee employee ) {
        for (Employee value : employeeList) {
            if (employee.getEmployeeNumber().compareTo(value.getEmployeeNumber()) == 0)
                return false;
        }
        employeeList.add(employee);
        return true;
    }

    //This method prints the company name, the tax id and the current number of employees
    public void printCompanyInfo() {
        System.out.println("Company Name: " + getCompanyName() + " | TaxID: " + getCompanyTaxId() + " | Number of Employees:" + employeeList.size());
    }

    //Prints out the toString of each employee in the list
    public void printEmployees() {
        int index;
        for (index = 0; index < employeeList.size(); index++) {
            System.out.println(employeeList.get(index).toString());
        }
    }

    //Counts how many employees earn less than the maxSalary in the entire array
    public int countEmployees( double maxSalary ) {
        int count = 0;
        for (Employee employee : employeeList) {
            if (maxSalary > employee.grossPay()) {
                count++;
            }

        }
        return count;
    }

    //Returns true if the array contains the target name; false if there is not a matching name
    public boolean SearchByName (String fullName ) {
        for (Employee employee : employeeList)
            if (fullName.compareToIgnoreCase(employee.getFullName()) == 0)
                return true;
        return false;
    }

    //Creates a temporary array that holds the reverse of the company array, replaces the original with reversed
    public void reverseEmployees () {
        ArrayList<Employee> tmpArr = new ArrayList<>();
        for(int j = employeeList.size() - 1; j > -1; j--) {
            tmpArr.add(employeeList.get(j));
        }
        employeeList = tmpArr;
    }

    //Finds any entries in array that match the targetSalary and removes from the array
    public void deleteEmployeesBySalary (double targetSalary ) {
        for (int index = 0; index < employeeList.size(); index++)
            if (targetSalary == employeeList.get(index).grossPay())
                employeeList.remove(index);
    }

    //Matches employeeNumber to the fields in each entry,
    //if there's a match, this method prints the employees check
    public void printCheck ( String employeeNumber) {
        for (Employee employee : employeeList) {
            if (employeeNumber.compareToIgnoreCase(employee.getEmployeeNumber()) == 0) {
                employee.printCheck();
                return;
            }
        }
        System.out.println("NO SUCH EMPLOYEE EXISTS"); //No matching employee
    }
}
