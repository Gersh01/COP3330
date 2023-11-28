//Unit9_HW6
//Alexander Gershfeld
//Hatim Boustique
//COP3330
//December 1, 2023

import java.util.Scanner;

public class Unit9_HW6 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int selection;

        System.out.println("\t\t\tWelcome to the Company Management Software");
        System.out.println("---------------------------------------------------------------------");

        Employee company = null;
        String name;
        double salary;
        int numberOfDependents;
        boolean sentinel = true;

        while(sentinel) {
            printMenu();

            try {
                selection = input.nextInt();
            } catch(Exception e) {
                selection = 7; //impossible value, defaults the switch
            } finally {
                input.nextLine();
            }

            switch(selection) {
                case 1: //print all employees
                    System.out.println("\n---------------------------------------------------------------------");
                    printEmployees(company);
                    System.out.println("---------------------------------------------------------------------\n");
                    break;
                case 2: //add new employee
                    System.out.println("\n---------------------------------------------------------------------");
                    int sum = 0;

                    //collect the input of each employee field
                    name = inputName(input);
                    while(true) {
                        try {
                            System.out.print("Enter salary of employee: ");
                            salary = input.nextDouble();

                            if(salary < 0) throw new Exception(); //takes care of negative doubles
                            break;
                        } catch(Exception e) {
                            System.out.println("Invalid input - try again");
                            continue;
                        } finally {
                            input.nextLine(); //clear the stream
                        }
                    }
                    while(true) {
                        try {
                            System.out.print("Enter number of dependents of employee: ");
                            numberOfDependents = input.nextInt();

                            if(numberOfDependents < 0) throw new Exception(); //checks for negative integers
                            break;
                        } catch(Exception e) {
                            System.out.println("Invalid input - try again");
                            continue;
                        } finally {
                            input.nextLine(); //clears the stream
                        }
                    }

                    //take the name and make the id out of it
                    for(int i = 0; i < name.length(); i++)
                        sum += name.toLowerCase().charAt(i); //add every character converted to lowercase

                    company = addEmployee(company, name, sum, salary, numberOfDependents);

                    System.out.println("---------------------------------------------------------------------\n");
                    break;
                case 3: //search by name
                    System.out.println("\n---------------------------------------------------------------------");

                    if(searchEmployee(company, inputName(input))) System.out.println("Found");
                    else System.out.println("Not Found");

                    System.out.println("---------------------------------------------------------------------\n");
                    break;
                case 4: //find highest net salary
                    System.out.println("\n---------------------------------------------------------------------");
                    Employee tmpCompany = company;
                    Employee highestEmployee = findHighestSalary(company, tmpCompany);

                    //if there are employees in the company
                    if(highestEmployee != null)
                        System.out.println(highestEmployee);
                    else System.out.println("There are no employees in the company");

                    System.out.println("---------------------------------------------------------------------\n");
                    break;
                case 5: //delete an employee
                    System.out.println("\n---------------------------------------------------------------------");
                    name = inputName(input);

                    //if the employee exists delete it
                    if(searchEmployee(company, name))
                        deleteEmployee(company, name);
                    else System.out.println(name + " does not exist");

                    System.out.println("---------------------------------------------------------------------\n");
                    break;
                case 6: //exit program
                    sentinel = false;
                    System.out.println("Goodbye!");

                    break;
                default:
                    System.out.println("Invalid selection - try again");
                    break;
            }
        }
    }

    //Non-Main methods ---------------------------------------------------------

    //print menu
    public static void printMenu() {
        System.out.println("1) Print all the employees");
        System.out.println("2) Add a new employee");
        System.out.println("3) Search an employee by name");
        System.out.println("4) Find the highest net salary");
        System.out.println("5) Delete an employee by name");
        System.out.println("6) Exit program");
        System.out.println("---------------------------------------------------------------------");
        System.out.print("Please enter your selection: ");
    }

    //take in the name and handle any exceptions
    public static String inputName(Scanner input) {
        String name;
        while(true) {
            try {
                System.out.print("Enter name of employee: ");
                name = input.nextLine();
                for(int i = 0; i < name.length(); i++) { //checks for any digits in the name
                    if(Character.isDigit(name.charAt(i)))
                        throw new Exception();
                }

                break;
            } catch(Exception e) {
                System.out.println("Invalid input - try again");
                continue;
            }
        }
        return name;
    }

    //methods for each menu item
    public static void printEmployees(Employee list) {
        if (list != null) {
            System.out.println(list.getName());

            printEmployees(list.below);
            printEmployees(list.next);
        }

    }
    public static Employee addEmployee(Employee list, String name, int id, double salary, int numberOfDependents) {
        if(list == null) { //empty spot for the new employee
            list = new Employee(name, salary, numberOfDependents);
            list.setId(id);
            list.next = null;
            list.below = null;
        }
        else if(list.getId() == id) { //changes the direction when collision is detected
            list.below = addEmployee(list.below, name, id, salary, numberOfDependents);
        }
        else { //iterate until list is null
            list.next = addEmployee(list.next, name, id, salary, numberOfDependents);
        }

        return list;
    }
    public static boolean searchEmployee(Employee list, String name) {
        if(list != null) {
            if(list.getName().compareToIgnoreCase(name) == 0) return true;

            return searchEmployee(list.below, name) || searchEmployee(list.next, name);
        }
        return false;
    }
    public static Employee findHighestSalary(Employee list, Employee tmpList) {
        if(list != null) {
            if(list.getNetSalary() > tmpList.getNetSalary()) tmpList = list; //update the return

            //make sure the return follows each call
            tmpList = findHighestSalary(list.below, tmpList);
            tmpList = findHighestSalary(list.next, tmpList);
        }
        return tmpList;
    }
    public static Employee deleteEmployee(Employee list, String name) {
        if(list != null) {
            if(list.getName().compareToIgnoreCase(name) == 0) {
                System.out.println(name + " has been deleted");
                if(list.next == null && list.below == null) { //has no below or next
                    return null;
                }
                else if(list.next != null && list.below == null) { //has next but no below
                    return list.next;
                }
                else if(list.next == null && list.below != null) { //has below but no next
                    return list.below;
                }
                else { //has both below and next
                    list.below.next = list.next;
                    return list.below;
                }
            }

            //check below and then check next
            list.below = deleteEmployee(list.below, name);
            list.next = deleteEmployee(list.next, name);
        }

        return list;
    }
}

//-----------------------------------
class Employee {
    //data fields
    private int id;
    private String name;
    private double salary;
    private int numberOfDependents;

    //linked list fields
    public Employee next;
    public Employee below;

    //getters
    public int getId() {
        return id;
    }
    public String getName() {
        return name;
    }
    public double getSalary() {
        return salary;
    }
    public double getNetSalary() {
        return (salary * .91) + (numberOfDependents * .01 * salary);
    }
    public int getNumberOfDependents() {
        return numberOfDependents;
    }


    //setters
    public void setId(int id) {
        this.id = id;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setSalary(double salary) {
        this.salary = salary;
    }
    public void setNumberOfDependents(int numberOfDependents) {
        this.numberOfDependents = numberOfDependents;
    }

    //constructors
    public Employee(String name, double salary, int numberOfDependents) {
        setName(name);
        setSalary(salary);
        setNumberOfDependents(numberOfDependents);
    }

    public String toString() {
        return "[" + id + ", " + name + ", " + getNetSalary() + "]";
    }
}